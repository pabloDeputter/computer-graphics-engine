//
// Created by Pablo Deputter on 22/02/2021.
//

#ifndef ENGINE_POINT2D_H
#define ENGINE_POINT2D_H

/**
 * \brief This class implements a Point2D object consisting the doubles x and y.
 */
class Point2D {

private:
    /**
     * \brief x-value of a Point2D object
     */
    double x;
    /**
     * \brief y-value of a Point2D object
     */
    double y;
    /**
     * \brief z-value of a Point2D object
     */
    double z;

public:
    /**
     * \brief Default constructor for Point2D object.
     */
    Point2D() : x(0.0), y(0.0), z(0.0) {}

    /**
     * \brief Constructor when given z-axis value
     *
     * \param a x-value as double
     * \param b y-value as double
     * \param c z-value as double
     */
     Point2D(double a, double b, double c) : x(a), y(b), z(c) {}

    /**
     * \brief Constructor for Point2D object.
     * \param a x-value as double
     * \param b y-value as double
     */
    Point2D(double a, double b) : x(a), y(b) {
        z = 0.0;
    }

    /**
     * \brief Copy constructuctor for Point2D object
     * \param a Point2D object to be copied
     */
    Point2D(const Point2D & a) {x = a.x; y = a.y; z = a.z; }

    /**
     * \brief Getter for x-value.
     * \return x-value as double
     */
    double getX() const {

        return x;
    }

    /**
     * \brief Setter for x-value.
     * \param a x-value as double
     */
    void setX(double a) {

        x = a;
    }

    /**
     * \brief Getter for y-value.
     * \return y-value as double
     */
    double getY() const {

        return y;
    }

    /**
     * \brief Setter for y-value.
     * \param b y-value as double
     */
    void setY(double b) {

        y = b;
    }
    /**
    * \brief Getter for y-value.
    * \return y-value as double
    */
    double getZ() const {

        return z;
    }
};


#endif //ENGINE_POINT2D_H
