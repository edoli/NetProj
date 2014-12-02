/*
 * Vec2d.hpp
 *
 *  Created on: Dec 2, 2014
 *      Author: daniel
 */
#ifndef _VEC2D_H_
#define _VEC2D_H_

#include <ostream>
#include <cmath>

class Vec2d {
 public:
  //////////////////
  // Data Members //
  //////////////////
  union {
    struct { double x, y; };
    struct { double u, v; };
    double data[2];
  };

 public:
  /////////////////
  // Constructor //
  /////////////////
  explicit Vec2d(double value=0.0f);
  Vec2d(double x, double y);
  Vec2d(const Vec2d& v);

  /////////////////
  // Desctructor //
  /////////////////
  ~Vec2d(void) {}

  ////////////////
  // Inspectors //
  ////////////////
  size_t size(void) const { return 2; }

  double  operator[](size_t index) const;
  double& operator[](size_t index);

  ///////////////
  // Operators //
  ///////////////
  Vec2d& operator=(const Vec2d& v);

  bool operator==(const Vec2d& v) const;
  bool operator!=(const Vec2d& v) const;

  Vec2d operator+(const Vec2d& v) const;
  Vec2d operator-(const Vec2d& v) const;
  Vec2d operator*(const Vec2d& v) const;
  Vec2d operator*(double scale) const;
  Vec2d operator/(const Vec2d& v) const;
  Vec2d operator/(double scale) const;

  Vec2d& operator+=(const Vec2d& v);
  Vec2d& operator-=(const Vec2d& v);
  Vec2d& operator*=(const Vec2d& v);
  Vec2d& operator*=(double scale);
  Vec2d& operator/=(const Vec2d& v);
  Vec2d& operator/=(double scale);

  ///////////////
  // Modifiers //
  ///////////////
  double dot(const Vec2d& v) const;
  double squared_length(void) const;
  double length(void) const;
  double squared_distance(const Vec2d& v) const;
  double distance(const Vec2d& v) const;

  Vec2d normalize(void) const;

  /////////////
  // Friends //
  /////////////
  friend void  swap(Vec2d& a, Vec2d& b)                { return a._swap(b); }
  friend void  normalize(Vec2d& v)                     { v /= v.length(); }
  friend Vec2d operator*(double scale, const Vec2d& v)  { return (v*scale); }

  friend std::ostream& operator<<(std::ostream& s, const Vec2d& v)
  {
    s << "[" << v.x << "," << v.y << "]";
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _assign(const Vec2d& v);
  void _swap(Vec2d& v);
};

#endif /* _VEC2D_H_ */
