#include "logger.hh"

Logger::Logger(string filename,
               string mode,
               Recorder* recorder)
  : _filename(filename),
    _mode(mode),
    _r(recorder)
{

}

Logger::~Logger()
{

}

void
Logger::log(string message)
{
  _r->Save("message", _filename);
}
