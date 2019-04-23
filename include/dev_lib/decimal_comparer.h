#ifndef __DEV_LIB_DECIMAL_COMPARER_H__
#define __DEV_LIB_DECIMAL_COMPARER_H__

#include <cmath>

class DecimalComparer
{
public:
  template <typename T>
  static bool isEqual(T rhs, T lhs, float eps = EPS);
  template <typename T>
  static bool isGreat(T rhs, T lhs, float eps = EPS);
  template <typename T>
  static bool isLess(T rhs, T lhs, float eps = EPS);
  template <typename T>
  static bool isGreatEqual(T rhs, T lhs, float eps = EPS);
  template <typename T>
  static bool isLessEqual(T rhs, T lhs, float eps = EPS);
private:
  static const float EPS;
};

template <typename T>
inline bool DecimalComparer::isEqual(T rhs, T lhs, float eps /*= EPS */)
{
  return (std::fabs(rhs - lhs) <= eps);
}

template <typename T>
inline bool DecimalComparer::isGreat(T rhs, T lhs, float eps /*= EPS */)
{
  return (rhs - lhs > eps);
}

template <typename T>
inline bool DecimalComparer::isLess(T rhs, T lhs, float eps /*= EPS */)
{
  return (rhs - lhs < -eps);
}

template <typename T>
inline bool DecimalComparer::isGreatEqual(T rhs, T lhs, float eps /*= EPS */)
{
  return (rhs - lhs > -eps);
}

template <typename T>
inline bool DecimalComparer::isLessEqual(T rhs, T lhs, float eps /*= EPS */)
{
  return (rhs - lhs < eps);
}

#endif
