#pragma once

#include <cmath>
#include <cstdint>

template <typename T> struct Vec {
  T x = {};
  T y = {};

  //

  template <typename U> explicit operator Vec<U>() {
    return Vec<U>{.x = static_cast<U>(x), .y = static_cast<U>(y)};
  }

  //

  Vec &operator-() {
    x = -x;
    y = -y;
    return *this;
  }

  Vec &operator*=(const T &value) {
    x *= value;
    y *= value;
    return *this;
  }

  Vec &operator/=(const T &value) {
    x /= value;
    y /= value;
    return *this;
  }

  Vec operator*(const T &value) const {
    auto copy = Vec{*this};
    copy *= value;
    return copy;
  }

  Vec operator/(const T &value) const {
    auto copy = Vec{*this};
    copy /= value;
    return copy;
  }

  //

  Vec &operator+=(const Vec &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec &operator-=(const Vec &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec operator+(const Vec &other) const {
    auto copy = Vec{*this};
    copy += other;
    return copy;
  }

  Vec operator-(const Vec &other) const {
    auto copy = Vec{*this};
    copy -= other;
    return copy;
  }

  //

  bool operator==(const Vec &other) const = default;

  bool operator!=(const Vec &other) const = default;

  //

  T len_sq() const { return dot(*this, *this); }

  double len() const { return std::sqrt(len_sq()); }

  Vec<double> norm() { return Vec<double>(*this) / len(); }

  //

  T static dot(Vec left, Vec right) {
    return left.x * right.x + left.y * right.y;
  }

  T static cross(Vec left, Vec right) {
    return left.x * right.y - left.y * right.x;
  }
};

using Veci = Vec<int64_t>;
using Vecf = Vec<double>;
