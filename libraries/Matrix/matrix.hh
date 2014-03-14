#ifndef MATRIX_HH_
# define MATRIX_HH_

# include <vector>
# include <assert.h>
# include <string>
# include <iostream>
# include <sstream>
# include <boost/cast.hpp>
# include <boost/lexical_cast.hpp>

using namespace std;

template<class T>
class Matrix
{
public:
  Matrix();
  Matrix(string	s);
  Matrix(int	nlines,
	 int	ncols);
  Matrix(int	n);
  Matrix(Matrix&);

  ~Matrix();

  T&		operator()(int	i,
			   int	j);
  T&		operator()(int	i);
  Matrix*	operator+(Matrix&	m);
  Matrix*	operator*(T		x);
  Matrix*	operator+=(T		x);
  Matrix*	operator*(Matrix&	x);

  T&		At(int	i,
		   int	j);
  void		Add(Matrix&	a,
		    Matrix&	b);
  void		Mult(Matrix&	a,
		     Matrix&	b);
  int		NbLines() {return _nlines;}
  int		NbCols() {return _ncols;}  
  int		NbElem() {return _ncols * _nlines;}
  void		Disp();
  Matrix*	Trans();
  T		Mean();
  void		Id();
  Matrix*	Inverse();
  void		SwapLines(int	a,
			  int	b);
  T		Max();
  T		Max(int	a,
		    int	b);
  int		ArgMax(int	a,
		       int	b);
  Matrix*	FFT();
  void		PrepareFFT();

  bool		IsVector();

private:
  int			_nlines;
  int			_ncols;
  bool			_isempty;

  vector<vector<T> *>	*_m;

};

#include "matrix.cxx"

#endif /* MATRIX_HH_ */
