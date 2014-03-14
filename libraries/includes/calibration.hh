#ifndef CALIBRATION_HH_
# define CALIBRATION_HH_

# include "matrix.hh"
# include "types.hh"

class Calibration
{
public:
  Calibration() {}
  virtual ~Calibration() {}

  virtual void adjustPoint(datas&) = 0;
  virtual void React2input() = 0;
  virtual void Reset(){};
};

class KeyboardCalibration : public Calibration
{
public:
  KeyboardCalibration();
  ~KeyboardCalibration() {}

  void adjustPoint(datas&);
  void React2input();

private:
  Matrix<double>* _m;
};

#endif
