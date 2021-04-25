//
// Created by Pablo Deputter on 27/03/2021.
//

#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include "Figure.h"
#include "Platonic.h"

/**
 * \brief Namespace implemented to hold a variety of "helper" functions
 */
namespace Utils {

    /**
     * \brief Struct implemented to store clipping data for image
     */
    struct clipping_data {
        clipping_data() {}

        clipping_data(const std::vector<int> &viewDirection, int fov, double aspectRatio, int dNear, int dFar)
                : viewDirection(viewDirection), fov(fov), aspect_ratio(aspectRatio), d_near(dNear), d_far(dFar) {}

        std::vector<int> viewDirection;
        int fov;
        double aspect_ratio;
        int d_near;
        int d_far;
    };

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

    void clipping_near_far(std::vector<Face> & new_faces, const Face & j, Figure & i, const double & d_val);

    void clipping_left_right(std::vector<Face> & new_faces, const Face & j, Figure & i, const double & d_val, const clipping_data & clippingData);

    void clipping_top_bottom(std::vector<Face> & new_faces, const Face & j, Figure & i, const double & d_val, const clipping_data & clippingData);
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
    std::tuple<double, double, double, double, double> prep_zbuffering(Figures3D & figures, Lines2D & figures_lines,
                                                                            const Matrix & trans_eye_matrix, const int size,
                                                                            bool clipping, const clipping_data & clippingData);
};


#endif //ENGINE_UTILS_H
