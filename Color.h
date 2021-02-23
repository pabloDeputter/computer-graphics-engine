//
// Created by Pablo Deputter on 22/02/2021.
//

#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H


/**
 * \brief This class implements a Color object consisting of the basic color spectrum: red, green and blue.
 */
class Color {

private:
    /**
     * \brief red-value as double
     */
    double red;
    /**
     * \brief green-value as double
     */
    double green;
    /**
     * \brief blue-value as double
     */
    double blue;

public:
    /**
    * \brief Default constructor for Color object.
    * \
    */
    Color() : red(0.0), green(0.0), blue(0.0) {}

    /**
     * \brief Constructor for Color object.
     * \param x red as double
     * \param y green as double
     * \param z blue as double
     * \
     */
    Color(const double & x, const double & y, const double & z) {

        red = x;
        green = y;
        blue = z;
    }
};


#endif //ENGINE_COLOR_H
