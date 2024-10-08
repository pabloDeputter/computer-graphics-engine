//
// Created by Pablo Deputter on 22/02/2021.
//

#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H

#include <vector>
#include <tuple>

/**
 * @brief Namespace holding the Color class for no confusion with img::Color class
 */
namespace cc {
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
    */
    Color() : red(0.0), green(0.0), blue(0.0) {}

    /**
     * \brief Constructor for Color object.
     *
     * \param x red as double
     * \param y green as double
     * \param z blue as double
     */
    Color(const double &x, const double &y, const double &z) {

        Color::red = x;
        Color::green = y;
        Color::blue = z;
    }
    /**
     * \brief Constructor for Color object.
     *
     * \param x Color-values in a vector
     */
    explicit Color(const std::vector<double> &x) {

        Color::red = x[0];
        Color::green = x[1];
        Color::blue = x[2];
    }

    /**
     * @brief Get color in tuple format
     *
     * @return Tuple containing RGB-values
     */
    const std::tuple<double, double, double> getColor() const {
        return std::make_tuple(Color::red, Color::green, Color::blue);
    }

    /**
     * @brief Get color as cc::Color object
     *
     * @return cc::Color object
     */
    cc::Color getColor() {
        return cc::Color(Color::red, Color::green, Color::blue);
    }

    double getRed() const {
        return red;
    }

    double getGreen() const {
        return green;
    }

    double getBlue() const {
        return blue;
    }

    double &getRed() {
        return red;
    }

    double &getGreen() {
        return green;
    }

    double &getBlue() {
        return blue;
    }
};
}

#endif //ENGINE_COLOR_H
