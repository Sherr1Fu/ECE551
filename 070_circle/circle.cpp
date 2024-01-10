#include "circle.hpp"

#include <cmath>

Circle::Circle(const Point & center, double radius) : center(center), radius(radius) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  if (d >= radius + otherCircle.radius) {
    return 0;  // Circles do not intersect
  }
  else if (d <= std::abs(radius - otherCircle.radius)) {
    // One circle is completely inside the other
    double smallerRadius = (radius < otherCircle.radius) ? radius : otherCircle.radius;
    return M_PI * smallerRadius * smallerRadius;
  }
  else {
    // Circles intersect, compute intersection area
    double r1_sq = radius * radius;
    double r2_sq = otherCircle.radius * otherCircle.radius;
    double d_sq = d * d;
    double alpha = acos((r1_sq + d_sq - r2_sq) / (2 * radius * d));
    double beta = acos((r2_sq + d_sq - r1_sq) / (2 * otherCircle.radius * d));
    double intersectionArea =
        r1_sq * alpha + r2_sq * beta -
        0.5 * (radius * radius * sin(2 * alpha) +
               otherCircle.radius * otherCircle.radius * sin(2 * beta));
    return intersectionArea;
  }
}
