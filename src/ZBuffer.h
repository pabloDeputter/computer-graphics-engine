//
// Created by Pablo Deputter on 25/03/2021.
//

#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include <vector>
#include <limits>
#include <cmath>
#include "Face.h"

/**
 * @brief The ZBuffer class
 */
class ZBuffer : public std::vector<std::vector<double>> {

private:
    /**
     * \brief Will hold all the z-values for each pixel of the image
     */
    std::vector<std::vector<double>> buffer;
public:
    /**
     * \brief Constructor for ZBuffer object with specific height and width
     *
     * @param width Width of image
     * @param height Height of image
     */
    ZBuffer(unsigned int width, unsigned int height);

    /**
     * @brief Contructor for empty ZBuffer object
     */
    ZBuffer() {}

    /**
     * @brief getBuffer
     *
     * @return Const ZBuffer by reference
     */
    const std::vector <std::vector<double>> &getBuffer() const {
        return buffer;
    }

    /**
     * @brief getBuffer
     *
     * @return ZBuffer by reference
     */
    std::vector<std::vector<double>> &getBuffer() {
        return buffer;
    }

    /**
     * \brief Calculate value of z for given pixel
     *
     * @param i
     * @param a
     * @param Za
     * @param Zb
     *
     * @return z-value as double
     */
    static double calculate_z_value(unsigned int i, unsigned int a, const double & Za, const double & Zb);

    /**
     * @brief Check if given z-value is smaller in given position of ZBuffer
     *
     * @param width x-value of ZBuffer
     * @param height y-value of ZByffer
     * @param z Inverse value of z
     *
     * @return True if z-value is smaller
     */
    bool check_z_value(unsigned int width, unsigned int height, const double & z);
};

/**
 * @brief The ZBuffering namespace
 */
namespace ZBuffering {
/**
     * @brief Triangulate face
     *
     * @param face Face object
     *
     * @return Vector containing triangulated face
     */
    std::vector<Face> triangulate(const Face & face);
}

#endif //ENGINE_ZBUFFER_H
