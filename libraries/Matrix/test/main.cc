#include "../matrix.hh"
#include "../fft.h"
#include <complex>

typedef complex<double>	cd;

int	main()
{
  //Matrix<cd>	m("1 2 3 4 5 5 4 2 33 4 5 6 2 1 33 11");
  Matrix<double>    m("1 2 3 ; 4 5 5 ; 4 2 33");
  Matrix<double>    m2("1 2 3 ; 4 5 5 ; 4 2 33");
  Matrix<double>    *mI;
  
  // Matrix<cd>	m2(m.NbCols(), 1);
  // Matrix<cd>	m3(m.NbCols(), 1);

  // m.Trans();
  // m2.Trans();

  //CFFT<cd>	F;
  //F.Forward(m, m2, m.NbCols());
  //m2.Disp();
  //F.Inverse(m2, m3, m.NbCols());
  //m3.Disp();
  //cout << m.Mean() << endl;
  //m.SwapLines(0, 2);
  
  mI = m.Inverse();
  m.Disp();
  cout << endl;
  m2.Disp();
  cout << endl;
  
  Matrix<double>	*m3;// = m * m2;

  m3 = *mI * m;
  
  mI->Disp();
}
