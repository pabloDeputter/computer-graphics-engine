//
// Created by Pablo Deputter on 12/03/2021.
//

#ifndef ENGINE_PLATONIC_H
#define ENGINE_PLATONIC_H

#include "Figure.h"

namespace Platonic {

    Figure cube();

    Figure tetrahedron();

    Figure octahedron();

    Figure icosahedron();

    Figure dodecahedron();

    void create_triangles(Figure & ico);

    Figure sphere(const int & n);

    Figure cone(const int & n, const double & h);

    Figure cylinder(const int & n, const double & h);

    Figure torus(const double & r, const double & R, const int & n, const int & m);
}


#endif //ENGINE_PLATONIC_H
