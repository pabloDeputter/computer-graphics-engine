//
// Created by Pablo Deputter on 12/03/2021.
//

#ifndef ENGINE_PLATONIC_H
#define ENGINE_PLATONIC_H

#include "Figure.h"

/**
 * \brief Namespace implemented to generate a variety of platonic bodies
 */
namespace Platonic {

    /**
     * \brief Generate cube
     *
     * @return Cube as Figure object
     */
    Figure cube();

    /**
     * \brief Generate tetrahedron
     *
     * @return Tetrahedron as Figure object
     */
    Figure tetrahedron();

    /**
     * \brief Generate octahedron
     *
     * @return Octahedron as Figure object
     */
    Figure octahedron();

    /**
     * \brief Generate icosahedron
     *
     * @return Icosahedron as Figure object
     */
    Figure icosahedron();

    /**
     * \brief Generate dodecahedron
     *
     * @return Dodecahedron as Figure object
     */
    Figure dodecahedron();

    /**
     * \brief Split up a Icosahedron up in triangles to generate a sphere-like figure
     *
     * @param ico Takes a Icosahedron as Figure
     */
    void create_triangles(Figure & ico);

    /**
     * \brief Generate a Sphere by triangulating a Icosahedron
     *
     * @param n Amount of times create_triangles() will be repeated
     *
     * @return Sphere as Figure object
     */
    Figure sphere(const int & n);

    /**
     * \brief Generate a Cone
     *
     * @param n Width of the cone
     * @param h Height of the Cone
     *
     * @return Cone as Figure object
     */
    Figure cone(const int & n, const double & h);

    /**
     * \brief Generate a Cylinder
     *
     * @param n Width of the Cylinder
     * @param h Height of the Cylinder
     *
     * @return Cylinder as Figure object
     */
    Figure cylinder(const int & n, const double & h);

    /**
     * \brief Creates a Torus
     *
     * @param r Distance from tube to Torus
     * @param R Distance from middlepoint from Figure to middlepoint from Torus
     * @param n Amount of points used inside the tube to approach from the horizontal way
     * @param m Amount of points used inside the tube to approach from the vertical way
     *
     * @return Torus as Figure object
     */
    Figure torus(const double & r, const double & R, const int & n, const int & m);

    /**
     * \brief Creates a BuckyBall
     *
     * @return BuckyBall as Figure object
     */
    Figure buckyBall();
}


#endif //ENGINE_PLATONIC_H
