//
// Created by Pablo Deputter on 22/02/2021.
//

#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H

#include <list>
#include "Point2D.h"
#include "Color.h"

class Line2D;

/**
 * \brief List containing of Line2D objects.
 */
typedef std::list<Line2D> Lines2D;

/**
 * \brief This class implements a Line2D object consisting of 2 Point2D objects and a Color object.
 */
class Line2D {

private:
    /**
     * \brief First Point2D object of line
     */
    Point2D p1;
    /**
     * \brief Second Point2D object of line
     */
    Point2D p2;
    /**
     * \brief Color all points existing between p1 and p2
     */
    Color color;

public:
    /**
     * \brief Default constructor of Line2D object
     */
    Line2D() : p1(), p2(), color() {}

    /**
     * \brief Constructor of Line2D object
     * \param a First Point2D object
     * \param b Second Point2D object
     */
    Line2D(const Point2D & a, const Point2D & b) : p1(a), p2(b) {}

    /**
     * \brief Setter for P1 that will return by reference
     */
    Point2D & getP1() {

        return p1;
    }

    /**
     * \brief Setter for P2 that will return by reference
     */
    Point2D & getP2() {

        return p2;
    }

    /**
     * \brief Setter for color-value
     * \param x Color object
     */
    void setColor(const Color & x) {

        Line2D::color = x;
    }

    /**
    * \brief Scale all points of object with scale-factor
    * \param x 	Scale-factor which the Point2D objects will be scaled with
    */
    void line2D_scale(const double & x);

    /**
    * \brief Move all points with (dx, dy)
    * \param dx Will be added to every x-coordinate of Point2D object
    * \param dy Will be added to every y-coordinate of Point2D object
    */
    void line2D_move(const double & dx, const double & dy);

    /**
    * \brief Round all Point2D members from doubles to int
    */
    void round();
};


#endif //ENGINE_LINE2D_H