#ifndef UTILS_H
#define UTILS_H
//------------------------------------------------------------------------
//
//  Name: utils.h
//
//  Desc: misc utility functions and constants
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cassert>
#include <iomanip>



//a few useful constants
const int     MaxInt    = (std::numeric_limits<int>::max)();
const double  MaxDouble = (std::numeric_limits<double>::max)();
const double  MinDouble = (std::numeric_limits<double>::min)();
const float   MaxFloat  = (std::numeric_limits<float>::max)();
const float   MinFloat  = (std::numeric_limits<float>::min)();

const double   Pi        = 3.14159;
const double   TwoPi     = Pi * 2;
const double   HalfPi    = Pi / 2;
const double   QuarterPi = Pi / 4;

//returns true if the value is a NaN
template <typename T>
inline bool isNaN(T val)
{
  return val != val;
}

inline double DegsToRads(double degs)
{
  return TwoPi * (degs/360.0);
}



//returns true if the parameter is equal to zero
inline bool IsZero(double val)
{
  return ( (-MinDouble < val) && (val < MinDouble) );
}

//returns true is the third parameter is in the range described by the
//first two
inline bool InRange(double start, double end, double val)
{
  if (start < end)
  {
    if ( (val > start) && (val < end) ) return true;
    else return false;
  }

  else
  {
    if ( (val < start) && (val > end) ) return true;
    else return false;
  }
}

template <class T>
T Maximum(const T& v1, const T& v2)
{
  return v1 > v2 ? v1 : v2;
}





//-----------------------------------------------------------------------
//
//  some handy little functions
//-----------------------------------------------------------------------


inline double Sigmoid(double input, double response = 1.0)
{
	return ( 1.0 / ( 1.0 + exp(-input / response)));
}


//returns the maximum of two values
template <class T>
inline T MaxOf(const T& a, const T& b)
{
  if (a>b) return a; return b;
}

//returns the minimum of two values
template <class T>
inline T MinOf(const T& a, const T& b)
{
  if (a<b) return a; return b;
}


//clamps the first argument between the second two
template <class T, class U, class V>
inline void Clamp(T& arg, const U& minVal, const V& maxVal)
{
  assert ( (minVal < maxVal) && "<Clamp>MaxVal < MinVal!");

  if (arg < (T)minVal)
  {
    arg = (T)minVal;
  }

  if (arg > (T)maxVal)
  {
    arg = (T)maxVal;
  }
}


//rounds a double up or down depending on its value
inline int Rounded(double val)
{
  int    integral = (int)val;
  double mantissa = val - integral;

  if (mantissa < 0.5)
  {
    return integral;
  }

  else
  {
    return integral + 1;
  }
}

//rounds a double up or down depending on whether its
//mantissa is higher or lower than offset
inline int RoundUnderOffset(double val, double offset)
{
  int    integral = (int)val;
  double mantissa = val - integral;

  if (mantissa < offset)
  {
    return integral;
  }

  else
  {
    return integral + 1;
  }
}

//compares two real numbers. Returns true if they are equal
inline bool isEqual(float a, float b)
{
  if (fabs(a-b) < 1E-12)
  {
    return true;
  }

  return false;
}

inline bool isEqual(double a, double b)
{
  if (fabs(a-b) < 1E-12)
  {
    return true;
  }

  return false;
}


template <class T>
inline double Average(const std::vector<T>& v)
{
  double average = 0.0;

  for (unsigned int i=0; i < v.size(); ++i)
  {
    average += (double)v[i];
  }

  return average / (double)v.size();
}


inline double StandardDeviation(const std::vector<double>& v)
{
  double sd      = 0.0;
  double average = Average(v);

  for (unsigned int i=0; i<v.size(); ++i)
  {
    sd += (v[i] - average) * (v[i] - average);
  }

  sd = sd / v.size();

  return sqrt(sd);
}








#endif
