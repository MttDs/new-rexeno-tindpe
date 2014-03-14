#include "matrix.hh"


using boost::lexical_cast;
using boost::bad_lexical_cast;

// This function constructs
// the null matrix
// 0 line, 0 columns
template<class T>
Matrix<T>::Matrix()
{
  _nlines = 0;
  _ncols = 0;
  _m = new vector<vector<T> *>();
}

// This function constructs
// the matrix described by
// the s string. For example :
// Matrix<T>("1 2 ; 3 4 ; 5 6")
// ==> | 1 2 |
//     | 3 4 |
//     | 5 6 |
// About same syntax as Matlab
// Attention : for now, I do not check
// if the input string is valid so PLEASE
// follow the example's syntax precisely
template<class T>
Matrix<T>::Matrix(string	s)
{
  istringstream	s1(s.c_str());
  string	input;
  T		value = -42;
  _m = new vector<vector<T> *>();
  _nlines = 0;
  _ncols = 0;
  vector<T> *line = new vector<T> ();
  while (!s1.eof())
    {
      s1 >> input;
      if ((input[0]) != ';')
	{
	  ++_ncols;
	  value = lexical_cast<double>(input);
	  line->push_back(value);
	}
      else
	{
	  _m->push_back(line);
	  line = new vector<T> ();
	  _nlines++;
	}
    }
  // Si jamais on a oublié le dernier ';'
  if (input[0] != ';')
    {
      _m->push_back(line);
      _nlines++;
    }
  _ncols /= _nlines;
}

// Get element at i, j
template<class T>
T&
Matrix<T>::At(int	i,
	      int	j)
{
  return (*this)(i, j);
}


// This function constructs
// the Zero matrix with
// the corresponding number
// of lines and columns
template<class T>
Matrix<T>::Matrix(int	nlines,
		  int	ncols)
{
  assert(nlines >= 0);
  assert(ncols >= 0);
  _ncols = ncols;
  _nlines = nlines;
  _m = new vector<vector<T> *>();
  for (int i = 0; i < nlines; ++i)
    {
      vector<T> *line = new vector<T> (ncols);
      _m->push_back(line);
    }
}

// This function constructs
// the Zero square matrix with
// the corresponding number
// of lines and columns
template<class T>
Matrix<T>::Matrix(int	n)
{
  assert(n >= 0);
  _ncols = n;
  _nlines = n;
  _m = new vector<vector<T> *>();
  for (int i = 0; i < n; ++i)
    {
      vector<T> *line = new vector<T> (n);
      _m->push_back(line);
    }
}

template<class T>
Matrix<T>::Matrix(Matrix<T>&	m)
{
  _ncols = m.NbCols();
  _nlines = m.NbLines();
  assert(_nlines >= 0);
  assert(_ncols >= 0);
  _m = new vector<vector<T> *>();
  for (int i = 0; i < _nlines; ++i)
    {
      vector<T> *line = new vector<T> (_ncols);
      _m->push_back(line);
    }
  for (int i = 0; i < _nlines; ++i)
    {
      for (int j = 0; j < _ncols; ++j)
	{
	  At(i, j) = m(i, j);
	}
    }
}

// Access the jth column of the ith line
template<class T>
T&
Matrix<T>::operator()(int	i,
		      int	j)
{
  assert(i >= 0);
  assert(j >= 0);
  assert(i < NbLines());
  assert(j < NbCols());
  return (*_m->at(i))[j];
}

// Access the ith element
// for vectors only !
template<class T>
T&
Matrix<T>::operator()(int	i)
{
  assert(i >= 0);
  assert((NbLines() == 1) || (NbCols() == 1));
  if (NbLines() == 1)
    return (*this)(0, i);
  if (NbCols() == 1)
    return (*this)(i, 0);
  return (*this)(i, 0); // should not get here - is to avoid warning
}

// La matrice appelante (celle qui appelle cette fonction)
// reçoit le résultat de l'addition des matrices a et b
template<class T>
void
Matrix<T>::Add(Matrix<T>&	a,
	       Matrix<T>&	b)
{
  assert(a.NbLines() == b.NbLines());
  assert(a.NbCols() == b.NbCols());
  assert(a.NbLines() == this->NbLines());
  assert(a.NbCols() == this->NbCols());
  for (int i = 0; i < _nlines; ++i)
    {
      for (int j = 0; j < _ncols; ++j)
	{
	  this->operator()(i, j) = a(i, j) + b(i,j);
	}
    }
}

// La matrice appelante (celle qui appelle cette fonction)
// reçoit le résultat de l'addition des matrices a et b
template<class T>
void
Matrix<T>::Mult(Matrix<T>&	a,
		Matrix<T>&	b)
{
  assert(a.NbCols() == b.NbLines());
  assert(a.NbLines() == this->NbLines());
  assert(this->NbCols() == b.NbCols());
  for(unsigned int i = 0; i < a.NbLines(); ++i)
    {
      for(unsigned int j = 0; j < b.NbCols(); ++j)
	{
	  T	product=0;
	  for(unsigned int z = 0; z < a.NbCols(); z++)
	    {
	      product += a(i,z) * b(z,j);
	    }
	  (*this)(i,j)=product;
	}
    }
}

// Display a human readable representation of the matrix
template<class T>
void
Matrix<T>::Disp()
{
  assert(this);
  for (int i = 0; i < _nlines; ++i)
    {
      cout << "| ";
      for (int j = 0; j < _ncols; ++j)
	{
	  cout << Matrix<T>::operator()(i, j) << " ";
	}
      cout << "|" << endl;
    }
}

template<class T>
Matrix<T>::~Matrix<T>()
{
  delete _m;
}

template<class T>
Matrix<T>*
Matrix<T>::operator+(Matrix<T>&	m)
{
  Matrix<T>	*res = new Matrix<T>(_nlines, _ncols);
  res->Add(*this, m);
  return res;
}



template<class T>
Matrix<T>*
Matrix<T>::operator*(Matrix<T>& b)
{
  Matrix<T>     *a=this;
  assert(a->NbCols() == b.NbLines());
  Matrix<T>     *res = new Matrix<T>(a->NbLines(), b.NbCols());
  for(unsigned int i = 0; i < a->NbLines(); ++i)
    {
      for(unsigned int j = 0; j < b.NbCols(); ++j)
        {
          T     product=0;
          for(unsigned int z = 0; z < a->NbCols(); z++)
            {
              product += (*a)(i,z) * b(z,j);
            }
          (*res)(i,j)=product;
        }
    }
  return res;
}


template<class T>
Matrix<T>*
Matrix<T>::operator*(T	x)
{
  Matrix<T>	*res = new Matrix<T>(_nlines, _ncols);
  for (int i = 0; i < _nlines; ++i)
    {
      for (int j = 0; j < _ncols; ++j)
	{
	  (*this)(i, j) *= x;
	}
    }
  return res;
}


template<class T>
Matrix<T>*
Matrix<T>::operator+=(T	b)
{
  Matrix<T>	*a=this;
  //Matrix<T>	*res = new Matrix<T>(a->NbLines(), b.NbCols());

  for (int i = 0; i < _nlines; ++i)
    {
      for (int j = 0; j < _ncols; ++j)
	{
	  (*this)(i, j) += b;
	}
    }
  //return res;
}

template<class T>
Matrix<T>*
Matrix<T>::Trans()
{
  // La matrice résultat
  // nombre de colonnes = nombre de ligne
  // et inversement (on transpose quoi)
  // donc les arguments sont inversés
  Matrix<T>	*res = new Matrix<T>(_ncols, _nlines);
  for (int i = 0; i < _nlines; ++i)
    {
      for (int j = 0; j < _ncols; ++j)
	{
	  (*res)(j, i) = (*this)(i, j);
	}
    }
  return (res);
}

// Calcul la moyenne de tous les elements d'une matrice
template<class T>
T
Matrix<T>::Mean()
{
  assert(this && _m);
  T	res = 0;
  T	N = NbElem();
  for (int i = 0; i < _nlines; ++i)
    {
      for (int j = 0; j < _ncols; ++j)
	{
	  res += (*this)(i, j);
	}
    }
  return (res / N);
}

// Trouve le max de tous les elements d'une matrice
template<class T>
T
Matrix<T>::Max()
{
  assert(this && _m);
  T	res = (*this)(0,0);
  for (int i = 0; i < _nlines; ++i)
    {
      for (int j = 0; j < _ncols; ++j)
	{
	  if (res < (*this)(i, j))
	    res = (*this)(i, j);
	}
    }
  return (res);
}

// Trouve le max
// On peut indiquer la colonne ou la ligne
// -1 = n'importe quelle colonne ou ligne
template<class T>
T
Matrix<T>::Max(int	i,
	       int	j)
{
  T	res;
  assert(i >= -1);
  assert(j >= -1);
  assert(i < _ncols);
  assert(i < _nlines);
  if ((i == -1) && (j != -1))
    {
      res = (*this)(0, j);
      for (i = 0; i < _nlines; ++i)
	if (res < (*this)(i, j))
	  res = (*this)(i, j);
      return res;
    }
  if ((j == -1) && (i != -1))
    {
      res = (*this)(i, 0);
      for (i = 0; i < _nlines; ++i)
	if (res < (*this)(i, j))
	  res = (*this)(i, j);
      return res;
    }
  if ((i >= 0) and (j >= 0))
    return (*this)(i,j);
  else
    return (Max());
}

// Trouve l'indice du max
// On peut indiquer la colonne ou la ligne
// -1 = n'importe quelle colonne ou ligne
template<class T>
int
Matrix<T>::ArgMax(int	i,
		  int	j)
{
  T	res;
  assert(i >= -1);
  assert(j >= -1);
  assert(i < _ncols);
  assert(i < _nlines);
  if ((i == -1) && (j != -1))
    {
      res = (*this)(0, j);
      for (i = 0; i < _nlines; ++i)
	if (res < (*this)(i, j))
	  res = (*this)(i, j);
      return i;
    }
  if ((j == -1) && (i != -1))
    {
      res = (*this)(i, 0);
      for (j = 0; j < _ncols; ++j)
	if (res < (*this)(i, j))
	  res = (*this)(i, j);
      return i;
    }
  if ((i >= 0) and (j >= 0))
    return -1;
}

template<class T>
void
Matrix<T>::Id()
{
  assert(_nlines == _ncols);
  for (int i = 0; i < _nlines; ++i)
    {
      for (int j = 0; j < _ncols; ++j)
	{
	  if (i == j)
	    At(i, j) = 1;
	  else
	    At(i, j) = 0;
	}
    }  
}

template<class T>
void
Matrix<T>::SwapLines(int	a,
		     int	b)
{
  assert(a < NbLines());
  assert(b < NbLines());
  vector<T>	*temp_line;
  temp_line = (*_m)[a];
  (*_m)[a] = (*_m)[b];
  (*_m)[b] = temp_line;
}

// Inversion par le pivot de Gauss
// l'algo de Gauss-Jordan.
// Cf Gauss-Jordan pseudo-code in matrix.txt
template <class T>
Matrix<T>*
Matrix<T>::Inverse()
{
  assert(_nlines == _ncols);
  Matrix<T>	cpy = *this;
  Matrix<T>	*res = new Matrix<T> (_nlines, _ncols);
  int	t = _nlines;
  int	k, i, colonne, colonnebis;
  T	var, var1;
  k=0;
  res->Id();
  while(k < t)
    {
      if (cpy.At(k, k) != 0)
	{
	  var = cpy.At(k, k);
	  for (colonne = 0; colonne < 1 * t; colonne++)
	    {
	      cpy.At(k, colonne) = cpy.At(k, colonne) / var;  //Normalisation de la ligne contenant l'élément diagonal
	      res->At(k, colonne) = res->At(k, colonne) / var;
	    }
	  for (i = 0; i < t; i++)
	    {
	      if (i != k)
		{
		  var1 = cpy.At(i, k);
		  for (colonnebis = 0; colonnebis < 1 * t; colonnebis++)
		    {
		      cpy.At(i, colonnebis) = cpy.At(i, colonnebis) - cpy.At(k, colonnebis) * var1;
		      res->At(i, colonnebis) = res->At(i, colonnebis) - res->At(k, colonnebis) * var1;
		    }
		}
	    }
	  k++;
	}
      else
	{
	  // Non inversible
	  return (NULL);
	}
    }
  return (res);
}
