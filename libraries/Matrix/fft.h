//   fft.h - declaration of class
//   of fast Fourier transform - FFT
//
//   The code is property of LIBROW
//   You can use it on your own
//   When utilizing credit LIBROW site

#ifndef _FFT_H_
# define _FFT_H_

//   Include complex numbers header
// #include "complex.h"
#  include "matrix.hh"

template<class T>
class CFFT
{
public:
  //   FORWARD FOURIER TRANSFORM
  //     Input  - input data
  //     Output - transform result
  //     N      - length of both input data and result
  static bool Forward(Matrix<T>&	 Input, 
		      Matrix<T>&	 Output, 
		      const unsigned int N);

  //   FORWARD FOURIER TRANSFORM, INPLACE VERSION
  //     Data - both input data and output
  //     N    - length of input data
  static bool Forward(Matrix<T>&		Data, 
		      const unsigned int  N);

  //   INVERSE FOURIER TRANSFORM
  //     Input  - input data
  //     Output - transform result
  //     N      - length of both input data and result
  //     Scale  - if to scale result
  static bool Inverse(Matrix<T>&		Input, 
		      Matrix<T>&		Output, 
		      const unsigned int	N, 
		      const bool		Scale = true);

  //   INVERSE FOURIER TRANSFORM, INPLACE VERSION
  //     Data  - both input data and output
  //     N     - length of both input data and result
  //     Scale - if to scale result
  static bool Inverse(Matrix<T>&		Data, 
		      const unsigned int  N, 
		      const bool		Scale = true);

protected:
  //   Rearrange function and its inplace version
  static void Rearrange(Matrix<T>&	 Input, 
			Matrix<T>&	 Output, 
			const unsigned int N);
  static void Rearrange(Matrix<T>&	 Data,
			const unsigned int N);

  //   FFT implementation
  static void Perform(Matrix<T>&		Data, 
		      const unsigned int  N, 
		      const bool		Inverse = false);

  //   Scaling of inverse FFT result
  static void Scale(Matrix<T>&		Data, 
		    const unsigned int    N);
};

# include "fft.cxx"

#endif
