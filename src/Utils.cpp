//
// Created by Pablo Deputter on 27/03/2021.
//

#include "Utils.h"

LParser::LSystem2D Utils::LSystem2D(const std::string &file_name) {

    LParser::LSystem2D l_system;

    std::ifstream input_stream(file_name);
    input_stream >> l_system;
    input_stream.close();
    return l_system;
}

LParser::LSystem3D Utils::LSystem3D(const std::string &file_name) {

    LParser::LSystem3D l_system;

    std::ifstream input_stream(file_name);
    input_stream >> l_system;
    input_stream.close();
    return l_system;
}

void Utils::fractal(Figure &figure, Figures3D &fractal, const int iter, const double &scale, bool mengerSponge) {

    fractal.emplace_back(figure);
    int i = iter;

    while (i != 0) {
        Figures3D fractal_new;

        for (Figure& fig : fractal) {

            for (unsigned int j = 0; j < fig.get_points().size(); j++) {

                Figure new_figure = fig;

                Matrix matrix_scale = Figure::scale_figure(1 / scale);
                new_figure.apply_transformation(matrix_scale);

                Vector3D point_i = fig.get_points()[j];
                Vector3D point_i_ = new_figure.get_points()[j];

                Matrix matrix_translate = Figure::translate(point_i - point_i_);
                new_figure.apply_transformation(matrix_translate);

                fractal_new.emplace_back(new_figure);
            }

            if (mengerSponge) {
                for (unsigned int j = 0; j < fig.get_points().size(); j++) {

                    Figure new_figure = fig;

                    Matrix matrix_scale = fig.scale_figure(1 / scale);
                    new_figure.apply_transformation(matrix_scale);

                    Vector3D point_i = fig.get_points()[j];
                    Vector3D point_i_ = new_figure.get_points()[j];
                    Matrix matrix_translate = fig.translate(Vector3D::vector(point_i - point_i_));
                    new_figure.apply_transformation(matrix_translate);

                    int index = j + 1;
                    if (j == 3) index = 0;
                    if (j == 7) index = 4;

                    Vector3D vector_translate = Vector3D::vector(Vector3D::point(fig.get_points()[j].x + (fig.get_points()[index].x - fig.get_points()[j].x) / 3,
                                                                 fig.get_points()[j].y + (fig.get_points()[index].y - fig.get_points()[j].y) / 3,
                                                                 fig.get_points()[j].z + (fig.get_points()[index].z - fig.get_points()[j].z) / 3) - fig.get_points()[j]);

                    Matrix matrix_translate_ = fig.translate(vector_translate);
                    new_figure.apply_transformation(matrix_translate_);

                    fractal_new.emplace_back(new_figure);
                }

                for (unsigned int j = 0; j < (unsigned int) 4; j++) {

                    Figure new_figure = fig;

                    Matrix matrix_scale = fig.scale_figure(1 / scale);
                    new_figure.apply_transformation(matrix_scale);

                    Vector3D point_i = fig.get_points()[j];
                    Vector3D point_i_ = new_figure.get_points()[j];
                    Matrix matrix_translate = fig.translate(Vector3D::vector(point_i - point_i_));
                    new_figure.apply_transformation(matrix_translate);

                    int index = 5;
                    if (j == 1) index -= j;
                    else if (j == 2) index += j;
                    else if (j == 3) index = 6;

                    Vector3D vector_translate = Vector3D::vector(Vector3D::point(fig.get_points()[j].x + (fig.get_points()[index].x - fig.get_points()[j].x) / 3,
                                                                 fig.get_points()[j].y + (fig.get_points()[index].y - fig.get_points()[j].y) / 3,
                                                                 fig.get_points()[j].z + (fig.get_points()[index].z - fig.get_points()[j].z) / 3) - fig.get_points()[j]);

                    Matrix matrix_translate_ = fig.translate(vector_translate);
                    new_figure.apply_transformation(matrix_translate_);

                    fractal_new.emplace_back(new_figure);
                }
            }
        }
        fractal = fractal_new;
        i -= 1;
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

img::Color Utils::saturate_color(const cc::Color &color) {

    int red = static_cast<int>(std::round(color.getRed() * 255));
    int green = static_cast<int>(std::round(color.getGreen() * 255));
    int blue = static_cast<int>(std::round(color.getBlue() * 255));

    if (red > 255) red = 255;
    if (green > 255) green = 255;
    if (blue > 255) blue = 255;

    return img::Color(red, green, blue);
}
