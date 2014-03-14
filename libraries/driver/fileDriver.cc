/**
 * @file   fileDriver.cc
 * @author hadrien <hadrien@barbow>
 * @date   Sat Nov 30 18:39:55 2013
 * 
 * @brief  Implementation of the driver for a project
 * where the input comes from a datafile
 * This uses non-real time functions so it works on a
 * regular non-xenomai computer. But we should not expect
 * exact replication of the results of a xenomai system.
 * Exact behaviour replication will be done later by another driver.
 * 
 */

#include <iostream>
#include <fstream>
#include <string>


FileDriver::FileDriver(std::string filename)
   : _infile.open("infile.txt");
{
  _calibration = new KeyboardCalibration();
  
}

void
FileDriver::AnalogIn(datas& data)
{
  unsigned int i = 0;
  while (!infile.eof())
  {
    infile >> data[i].timing;
    infile >> data[i].volt;
    ++i;
    // getline(infile, sLine);
    // cout << sLine << endl;
  }

  // for (i = 0; size && (i < data.size()); ++i)
  // {
  //   data[i].volt = _analogData[2 * i];
  //   data[i].timing = _analogData[2 * i + 1];
  // }

}
