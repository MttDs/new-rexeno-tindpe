/**
 * @file   xenoDriver.cc
 * @author hadrien <hadrien@barbow>
 * @date   Wed Jul  3 23:59:48 2013
 * 
 * @brief  Implementation of the rexeno driver through Xenomai API
 * This implementation requires the xenomai native library and analogy drivers
 * 
 */
#ifdef XENO

#include "driver.hh"

#include <native/task.h>
#include <native/alarm.h>
#include <native/timer.h>
#include <native/mutex.h>
#include <native/buffer.h>
#include <nucleus/sched.h>
#include <analogy/analogy.h>
#include <analogy/descriptor.h>
#include <analogy/subdevice.h>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/mman.h>
#include <native/pipe.h>

#include <iostream>
#include <fstream>

// NAME OF THE RTDM NODE TO LINK
#define FILENAME "analogy0"
#define NB_CHANNELS 16

// Descriptive structures
a4l_chinfo_t *chinfo;
a4l_rnginfo_t *rnginfo;

// Instructions to send to the card
a4l_insn_t inst[NB_CHANNELS];
a4l_insnlst_t *instructions;
#define NB_DATA 1
#define DATA_SIZE 2

// Temporary and final buffers for translating from raw to double and then link to the timestamp
double rawBuffer[NB_CHANNELS*NB_DATA*2];
double doubleBuffer[NB_CHANNELS*NB_DATA*2];
double finalBuffer[NB_CHANNELS*NB_DATA * 2 *2];
RT_TASK	analogy_task;
RT_ALARM alarm_acquire;
RT_TASK recorder_task;
RT_PIPE pipe_desc;
double recorderArray[NB_CHANNELS*NB_DATA * 2 *2];

a4l_desc_t	*descriptor = 0;

int
XenoDriver::_initNidaqCard()
{
  a4l_sbinfo_t	*sbinfo;
    
  descriptor = (a4l_desc_t*) malloc(sizeof(a4l_desc_t));

  descriptor->sbdata = NULL;
  a4l_open(descriptor, FILENAME);
  
  descriptor->sbdata = (void*) malloc(descriptor->sbsize);
  a4l_fill_desc(descriptor);
  int i = 0;
  for (i = 0; i < descriptor->nb_subd; i++)
    {
      /* rerieve the subdevice informations, search for Analog output sub-device */
      a4l_get_subdinfo(descriptor, i , &sbinfo);
      if ((sbinfo->flags & A4L_SUBD_TYPES) == A4L_SUBD_AI) 
	{
	  descriptor->idx_write_subd = i;
	  break;
	}
      if (i == descriptor->nb_subd -1)
	{
	  printf("No Analog Output found\n");
	  return 1;
	}
    }
  // Find range and fill range descriptor with the voltage unit and the values 
  a4l_find_range(descriptor, descriptor->idx_read_subd,
		 0, A4L_RNG_VOLT_UNIT, -10, 10 ,&rnginfo);

  /* Retrieve the subdevice channel informations, based on the channel 0 */
  a4l_get_chinfo(descriptor, descriptor->idx_read_subd, 0, &chinfo);
  // Creation of the instructions to pass to the Ni-DAQ card
  instructions = (a4l_insnlst_t*)malloc(sizeof( a4l_insnlst_t));
  instructions->count = NB_CHANNELS;
  instructions->insns = inst;
  for (unsigned int i = 0 ; i < instructions->count ; i++)
    {
      inst[i].type = A4L_INSN_MASK_READ;
      inst[i].idx_subd = descriptor->idx_read_subd;
      inst[i].chan_desc = i;
      inst[i].data_size = DATA_SIZE * NB_DATA;
      inst[i].data = rawBuffer+DATA_SIZE * NB_DATA * i;
    }

  // Initialization of buffers to 0
  for (i=0;i<NB_CHANNELS*NB_DATA;i++) doubleBuffer[i] = 0;
  for (i=0;i<NB_CHANNELS*NB_DATA;i++) finalBuffer[i] = 0;

  return (0);
}

void input(void* p)
{
  RT_MUTEX* mutex = (RT_MUTEX*) p;
  int i;
  RT_BUFFER bufferRecorder;
  RT_BUFFER bufferDisplay;

  rt_buffer_bind(&bufferRecorder, "recorder_buffer", TM_INFINITE);
  rt_buffer_bind(&bufferDisplay, "display_buffer", TM_INFINITE);

  while (1)
  {
    a4l_snd_insnlist (descriptor, instructions);
    rt_alarm_wait(&alarm_acquire);
    rt_mutex_acquire(mutex, TM_INFINITE);
    a4l_rawtod(chinfo, rnginfo, 
	       doubleBuffer, rawBuffer, NB_DATA*NB_CHANNELS*DATA_SIZE);
    RTIME timestamp = rt_timer_read();
    for (i=0;i<NB_CHANNELS*NB_DATA*2;i++)
    {
      finalBuffer[i] = doubleBuffer[i];
      //printf("%f\n", doubleBuffer[i]);
      finalBuffer[++i] = timestamp;
    }
    rt_mutex_release(mutex);
    //rt_pipe_write(&pipe_desc, finalBuffer, NB_CHANNELS*NB_DATA*2 * sizeof(double), P_NORMAL);
    rt_buffer_write(&bufferRecorder, finalBuffer, NB_CHANNELS*NB_DATA*2 * sizeof(double), TM_INFINITE);
    rt_buffer_write(&bufferDisplay, finalBuffer, NB_CHANNELS*NB_DATA*2 * sizeof(double), TM_INFINITE);
  }
}

void recorder(void* p)
{
  ofstream ofs ("/tmp/Eye", std::ofstream::out);

  RT_BUFFER bufferRecorder;
  Recorder* rec = (Recorder*) p;

  rt_buffer_bind(&bufferRecorder, "recorder_buffer", TM_INFINITE);
  while (1)
  {
    rt_buffer_read(&bufferRecorder, recorderArray, NB_CHANNELS*NB_DATA*2 * sizeof(double), TM_INFINITE);
    if (rec)
      {
	for (int i = 0; i < NB_CHANNELS*NB_DATA*2; ++i)
	  {
	    ofs << recorderArray[i] << " " << recorderArray[i + 1] << "\n";
	  }
      }
  }
}

int
XenoDriver::_launch()
{
  /* Avoids memory swapping for this program */
  mlockall(MCL_CURRENT|MCL_FUTURE);

  _mutex = new RT_MUTEX;
  _recorderBuffer = new RT_BUFFER;
  _displayBuffer = new RT_BUFFER;
  rt_mutex_create(_mutex, "driver_mutex");

  // rt_alarm_t  	handler_acquire;
  rt_alarm_create(&alarm_acquire, "acquisition_time");
  rt_alarm_start(&alarm_acquire,
		 0,
		 1000000); // 1000 Hz
    

  //rt_pipe_create(&pipe_desc, NULL, 0, 12000);
  rt_buffer_create(_recorderBuffer, "recorder_buffer", 12000, 0);
  rt_buffer_create(_displayBuffer, "display_buffer", 12000, 0);

  if (_initNidaqCard())
    printf("nidaq initialization : OK\n");

  rt_task_create (&analogy_task, "AnalogyReader", 0, 99, T_JOINABLE);
  rt_task_start(&analogy_task, (input), (void*) _mutex);

  rt_task_create (&recorder_task, "AnalogyRecorder", 0, 50, T_JOINABLE);
  rt_task_start(&recorder_task, (recorder), (void*)_recorder);

  sleep(1);

  //rt_task_join(&analogy_task);

  return(0);
}


XenoDriver::XenoDriver()
{
  _calibration = new KeyboardCalibration();
  _name = "xenomai";
  _launch();
  _analogData = finalBuffer;
  _start = rt_timer_read();
}

/**
   return nanosecond
**/
ms
XenoDriver::GetTime()
{
  RTIME current = rt_timer_read();
  return (current - _start); 
}

/**
   return milliseconds
**/
ms
XenoDriver::GetTimeMilliseconds()
{
  RTIME current = rt_timer_read();
  int pow = std::pow(10,6);
 
  return floor(static_cast<float>(current - _start)/pow+0.5); //milliseconds plz
}

void
XenoDriver::React2input()
{
  if (_calibration)
    _calibration->React2input();
}

void
XenoDriver::AnalogIn(datas& data)
{
  RT_BUFFER bufferRecorder;
  rt_buffer_bind(&bufferRecorder, "recorder_buffer", TM_INFINITE);
  unsigned int i;
  size_t size;

  // rt_mutex_acquire(_mutex, TM_INFINITE);
  size = rt_buffer_read(&bufferRecorder, recorderArray, NB_CHANNELS*NB_DATA*2 * sizeof(double), TM_INFINITE);
  for (i = 0; size && (i < data.size()); ++i)
  {
    data[0][i].volt = _analogData[2 * i];
    data[0][i].timing = _analogData[2 * i + 1];
  }
  // rt_mutex_release(_mutex);
  _calibration->adjustPoint(data);
}

#endif /* XENO */
