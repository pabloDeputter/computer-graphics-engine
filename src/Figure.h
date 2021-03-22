//
// Created by Pablo Deputter on 05/03/2021.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H


#include <list>
#include <tuple>
#include <cmath>
#include <tgmath.h>
#include "Face.h"
#include "vector3d.h"
#include "Color.h"
#include "Line2D.h"

class Figure {

private:
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    cc::Color color;

public:
    std::vector<Vector3D> &get_points() {
        return points;
    }

    std::vector<Face> &get_faces() {
        return faces;
    }

    const cc::Color &get_color() const {
        return color;
    }

    void set_color(const cc::Color & x) {

        Figure::color = x;
    }

    void add_point(const std::tuple<int, int, int> & x);

    void add_point_double(const std::tuple<double, double, double> & x);

    void correct_indexes();

    void clear_faces();

    static Matrix scale_figure(const double & scaleFactor);

    static Matrix rotateX(const double & angle);

    static Matrix rotateY(const double & angle);

    static Matrix rotateZ(const double & angle);

    static Matrix translate(const Vector3D & vector);

    void apply_transformation(const Matrix & x);

    static std::tuple<double, double, double> to_polar(const Vector3D & x);

    static Matrix eye_point_trans(const Vector3D & eyepoint);

    Point2D do_projection(const Vector3D & point, const double & d);

    Lines2D do_projection();
};

typedef std::list<Figure> Figures3D;

#endif //ENGINE_FIGURE_H
