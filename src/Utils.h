//
// Created by Pablo Deputter on 27/03/2021.
//

#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include "Figure.h"
#include "easy_image.h"

/**
 * \brief Namespace implemented to hold a variety of "helper" functions
 */
namespace Utils {
    /**
     * \brief Generates a fractal (vector of figures) for every Platonic body implemented
     *
     * @param figure Figure to be made a fractal of
     * @param fractal Vector of figures that holds the fractal
     * @param iter Amount of times the fractal-algorithm will be repeated
     * @param scale Factor that will be used to rescale the original Figure and turn it into smaller figures
     */
    void fractal(Figure & figure, Figures3D & fractal, const int iter, const double & scale);

    /**
     * \brief Generate 2D lines for a list of figures
     *
     * @param figures List of 3D figures
     * @param figures_lines Empty or not list with 2D lines passed by reference
     * @param trans_matrix Transformation-matrix to apply the transformation for each Figure of figures
     */
    void generate_lines(Figures3D & figures, Lines2D & figures_lines, const Matrix & trans_matrix);

    void triangulate_figures(Figures3D &figures);

    std::tuple<double, double, double, double, double> calculate_data(const double &x, const double &X, const double &y,
                                                                      const double &Y, const int size);

    /**
     * \brief Calculate every variable used in the z-buffering algorithm
     *
     * @param figures List of 3D figures
     * @param figures_lines Empty or not list with 2D lines
     * @param trans_eye_matrix Transformation-matrix to apply the transformation for each Figure of figures
     * @param size Size of image
     *
     * @return Return std::tuple<image_x, image_y, d, dx, dy>
     */
    std::tuple<double, double, double, double, double, Figures3D> prep_zbuffering(Figures3D & figures, Lines2D & figures_lines,
                                                                                  const Matrix & trans_eye_matrix, const int size);

    double overwriteMax(double i, const int & max);

    img::Color scaleColor(const std::tuple<double, double, double> & color);

    void createShadowMaskBuffer(const Figures3D &figures);
};


#endif //ENGINE_UTILS_H
