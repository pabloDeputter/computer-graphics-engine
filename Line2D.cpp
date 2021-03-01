//
// Created by Pablo Deputter on 22/02/2021.
//

#include "Line2D.h"
#include <cmath>

void Line2D::line2D_scale(const double & x) {

    // Scale all points
    p1.setX(p1.getX()*x);
    p1.setY(p1.getY()*x);
    p2.setX(p2.getX()*x);
    p2.setY(p2.getY()*x);
}

void Line2D::line2D_move(const double & dx, const double & dy) {

    // Move all points
    p1.setX(p1.getX()+dx);
    p1.setY(p1.getY()+dy);
    p2.setX(p2.getX()+dx);
    p2.setY(p2.getY()+dy);
}

void Line2D::round() {

    // Round all points to int's
    p1.setX(static_cast<int>(std::round(p1.getX())));
    p1.setY(static_cast<int>(std::round(p1.getY())));
    p2.setX(static_cast<int>(std::round(p2.getX())));
    p2.setY(static_cast<int>(std::round(p2.getY())));
}
