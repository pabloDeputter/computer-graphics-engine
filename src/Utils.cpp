//
// Created by Pablo Deputter on 27/03/2021.
//

#include "Utils.h"

void Utils::fractal(Figure & figure, Figures3D & fractal, const int iter, const double & scale) {

    fractal.emplace_back(figure);
    int i = iter;

    while (i != 0) {
        Figures3D fractal_new;

        for (Figure& fig : fractal) {

            for (unsigned int j = 0; j < fig.get_points().size(); j++) {

                Figure figure_new = fig;

                Matrix matrix_scale = Figure::scale_figure(1 / scale);
                figure_new.apply_transformation(matrix_scale);

                Vector3D point_i = fig.get_points()[j];
                Vector3D point_i_ = figure_new.get_points()[j];

                Matrix matrix_translate = Figure::translate(point_i - point_i_);
                figure_new.apply_transformation(matrix_translate);

                fractal_new.emplace_back(figure_new);
            }

        }
        fractal = fractal_new;
        i = i - 1;
    }
}

void Utils::triangulate_figures(Figures3D &figures) {

    for (Figure &i : figures) {
        std::vector<Face> new_faces;

        for (Face &j : i.get_faces()) {
            std::vector<Face> triangles = ZBuffering::triangulate(j);
            new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
        }
        i.get_faces().clear();
        i.get_faces() = new_faces;
    }
}

void Utils::generate_lines(Figures3D &figures, Lines2D &figures_lines, const Matrix &trans_matrix) {

    for (Figure & fig : figures) {

        fig.apply_transformation(trans_matrix);
        Lines2D figure_lines = fig.do_projection();
        figures_lines.splice(figures_lines.end(), figure_lines);
    }
}

std::tuple<double, double, double, double, double> Utils::calculate_data(const double &x, const double &X, const double &y,
                                                                         const double &Y, const int size) {

    // Calculate x-range, y-range
    double xrange = X - x;
    double yrange = Y - y;

    double _size = static_cast<double>(std::round(size));

    // Calculate dimensions of image
    double image_x = _size * (xrange / std::max(xrange, yrange) );
    double image_y = _size * (yrange / std::max(xrange, yrange) );

    // Calculate scale-factor
    double d = 0.95 * (image_x / xrange);

    double a = x + X;
    double b = y + Y;

    double DC_x = d * (a / static_cast<double>(2) );
    double DC_y = d * (b / static_cast<double>(2) );

    double dx = (image_x / static_cast<double>(2) ) - DC_x;
    double dy = (image_y / static_cast<double>(2) ) - DC_y;

    return std::make_tuple(image_x, image_y, d, dx, dy);
}

std::tuple<double, double, double, double, double, Figures3D> Utils::prep_zbuffering(Figures3D &figures, Lines2D &figures_lines,
                                                                                     const Matrix &trans_eye_matrix, const int size) {

    figures_lines.clear();

    // Traverse figures and triangulate every face
    Utils::triangulate_figures(figures);

    Figures3D triangulated_figures = figures;

    // Do projection and generate lines
    Utils::generate_lines(figures, figures_lines, trans_eye_matrix);

    // Calculate x-min, y-min, x-max and y-max
    std::tuple<std::pair<double, double>, std::pair<double, double>> max_line2D = Line2D::Line2D_findMax(figures_lines);

    double x = std::get<0>(max_line2D).first;
    double y = std::get<0>(max_line2D).second;

    double X = std::get<1>(max_line2D).first;
    double Y = std::get<1>(max_line2D).second;

    // Calculate image_x, image_y, d, dx, dy
    std::tuple<double, double, double, double, double> data = Utils::calculate_data(x, X, y, Y, size);

    return std::make_tuple(std::get<0>(data), std::get<1>(data),
                           std::get<2>(data), std::get<3>(data),
                           std::get<4>(data), triangulated_figures);
}

double Utils::overwriteMax(double i, const int &max) {

    if (i > max) return i = static_cast<double>(max);
    else return i;
}

img::Color Utils::scaleColor(const std::tuple<double, double, double> & color) {

    double red = std::get<0>(color) * 255;
    double green = std::get<1>(color) * 255;
    double blue = std::get<2>(color) * 255;

    if (red > 255) red = 255;
    if (green > 255) green = 255;
    if (blue > 255) blue = 255;

    return img::Color(red, green, blue);
}


