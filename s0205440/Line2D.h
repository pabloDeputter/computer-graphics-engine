//
// Created by Pablo Deputter on 22/02/2021.
//

#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H

#include <list>
#include <cmath>
#include "Point2D.h"
#include "Color.h"
#include "easy_image.h"
#include "ZBuffer.h"

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
    cc::Color color;

    double z1;
    double z2;

public:
    // TODO
    /**
     * \brief Default constructor of Line2D object
     */
    Line2D() : p1(), p2(), color(), z1(0.0), z2(0.0) {}

    /**
     * \brief Constructor of Line2D object
     * \param a First Point2D object
     * \param b Second Point2D object
     */
    Line2D(const Point2D & a, const Point2D & b, const cc::Color & c) : p1(a), p2(b), color(c), z1(a.getZ()), z2(b.getZ()) {}

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
     * \brief Getter for color that will return by reference
     */
    const cc::Color & getColor() const {

        return color;
    }

    /**
    * \brief Getter for Z1-value as double
    */
    const double & getZ1() const {

        return z1;
    }

    /**
    * \brief Getter for Z2-value as double
    */
    const double & getZ2() const {

        return z2;
    }

    /**
     * \brief Setter for color-value
     * \param x Vector with color-values
     */
    void setColor(const std::vector<double> & x) {

        Line2D::color = cc::Color(x);
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

    /**
    * \brief Find x-min, y-min, x-max and y-max of list
    *
    * \param line2D 	List with all the Line2D objects to be represented on image
     * \return          A tuple of pairs of doubles containing x-min, y-min, x-max and y-max respectively
    */
    static std::tuple<std::pair<double, double>, std::pair<double, double>> Line2D_findMax(Lines2D & line2D);

    /**
    * \brief            Draws list of Line2D objects representing straight lines on image
    *
    * \param line2D 	List with all the straight lines needed to be represented
    * \param size       Maximum amount of pixels of image, cannot be overwritten
    */
    static void draw2DLines(Lines2D & line2D, const int & size, img::EasyImage & image, bool ZBuffering);
};


#endif //ENGINE_LINE2D_H
