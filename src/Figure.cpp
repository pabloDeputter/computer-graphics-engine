//
// Created by Pablo Deputter on 05/03/2021.
//

#include "Figure.h"

void Figure::add_point(const std::tuple<int, int, int> &x) {
    points.emplace_back(Vector3D::point(std::get<0>(x), std::get<1>(x), std::get<2>(x)));
}

void Figure::add_point_double(const std::tuple<double, double, double> &x) {
    points.emplace_back(Vector3D::point(std::get<0>(x), std::get<1>(x), std::get<2>(x)));
}


void Figure::correct_indexes() {

    for (Face & i : faces) {
        i.correct_indexes();
    }
}

void Figure::clear_faces() {
    faces.clear();
}

Matrix Figure::scale_figure(const double &scaleFactor) {

    Matrix x;
    // Scale the matrix
    for (int i = 1; i < 4; i++) {
        x(i, i) = scaleFactor;
    }
    return x;
}

Matrix Figure::rotateX(const double &angle) {

    Matrix x;
    // Apply rotation
    x(2,2) = cos(angle);
    x(3, 2) = -sin(angle);
    x(3,3) = cos(angle);
    x(2,3) = sin(angle);
    return x;
}

Matrix Figure::rotateY(const double &angle) {

    Matrix x;
    // Apply rotation
    x(1,1) = cos(angle);
    x(1, 3) = -sin(angle);
    x(3,1) = sin(angle);
    x(3,3) = cos(angle);
    return x;
}

Matrix Figure::rotateZ(const double &angle) {

    Matrix x;
    // Apply rotation
    x(1,1) = cos(angle);
    x(1,2) = sin(angle);
    x(2,1) = (-1) * sin(angle);
    x(2,2) = cos(angle);
    return x;
}

Matrix Figure::translate(const Vector3D &vec) {

    Matrix x;
    // Apply translation
    x(4,1) = vec.x;
    x(4,2) = vec.y;
    x(4,3) = vec.z;
    x(4,4) = 1;
    return x;
}

void Figure::apply_transformation(const Matrix &x) {

    // Apply transformation
    for (Vector3D & i : this->points) {
        i *= x;
    }
}

std::tuple<double, double, double> Figure::to_polar(const Vector3D &point) {

    double r = sqrt((point.x * point.x) + (point.y * point.y) + (point.z * point.z));
    double phi = std::acos(point.z / r);
    double theta = std::atan2(point.y, point.x);
    return std::make_tuple(phi, theta, r);
}

Matrix Figure::eye_point_trans(const Vector3D &eyepoint) {

    // Calculate polar coordinates
    std::tuple<double, double, double> tuple = Figure::to_polar(eyepoint);
    double phi = std::get<0>(tuple);
    double theta = std::get<1>(tuple);
    double r = std::get<2>(tuple);

    // Calculate Eye-point transformation matrix
    Vector3D originOffset = Vector3D::point(0, 0, -r);

    Matrix x = rotateZ((-M_PI / 2) - theta) * rotateX(phi * (-1.0)) * translate(originOffset);

    return x;
}

Point2D Figure::do_projection(const Vector3D &point, const double &d) {

    double x_ = (d * point.x) / (-1.0 * point.z);
    double y_ = (d * point.y) / (-1.0 * point.z);

    return Point2D(x_, y_, point.z);
}

Lines2D Figure::do_projection() {

    std::vector<Point2D> array_points;
    for (const Vector3D & i : this->points) {
        // d is constant 1
        array_points.emplace_back(this->do_projection(i, 1));
    }

    Lines2D array_lines;
    // Traverse "faces" of figure
    for (const Face & i : this->faces) {

        for (unsigned int j = 0; j != i.get_point_indexes().size(); j++) {

            Point2D a = array_points[i.get_point_indexes()[j % i.get_point_indexes().size()]];
            Point2D b = array_points[i.get_point_indexes()[(j + 1) % i.get_point_indexes().size()]];

            array_lines.emplace_back(a, b, this->ambientReflection.getColor());
        }
    }
    return array_lines;
}
