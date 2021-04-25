#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "easy_image.h"
#include "ini_configuration.h"
#include "l_parser.h"
#include "vector3d.h"
#include "Color.h"
#include "Figure.h"
#include "LSystem2D.h"
#include "LSystem3D.h"
#include "Platonic.h"
#include "Utils.h"

using namespace std;

// #### - SCRIPTS - ####
// find ./ -name '*.bmp' | xargs rm
// #### - SCRIPTS - ####

/**
 * \brief Scales colors of vector
 * \param colors Vector with color values in 0-1 range
 * \return Vector of colors in 0-256 range in img::Color object
 */
img::Color scale_colors(std::vector<double> & colors) {

    for (double & i : colors) {
        i = i*255;
    }
    return img::Color(colors[0], colors[1], colors[2]);
}

/**
 * \brief Scales colors of vector
 * \param colors Vector with color values in 0-1 range
 * \return Vector of colors in 0-256 range in Color object
 */
cc::Color scale_colors_(std::vector<double> & colors) {

    for (double & i : colors) {
        i = i*255;
    }
    return cc::Color(colors);
}

/**
 * \brief Read a LSystem2D file in
 * \param file_name Name of input-file
 * \return LSystem2D object-type
 */
LParser::LSystem2D LSystem2D(const std::string & file_name) {

    LParser::LSystem2D l_system;

    std::ifstream input_stream(file_name);
    input_stream >> l_system;
    input_stream.close();
    return l_system;

}

/**
 * \brief Read a LSystem3D file in
 * \param file_name Name of input-file
 * \return LSystem3D object-type
 */
LParser::LSystem3D LSystem3D(const std::string & file_name) {

    LParser::LSystem3D l_system;

    std::ifstream input_stream(file_name);
    input_stream >> l_system;
    input_stream.close();
    return l_system;

}

/**
 * \brief Generates a image off a .ini file
 * \return EasyImage object-type
 */
img::EasyImage generate_image(const ini::Configuration &configuration) {

    // General data for every image
    std::string type = configuration["General"]["type"].as_string_or_die();
    int size = configuration["General"]["size"].as_int_or_die();
    std::vector<double> bg = configuration["General"]["backgroundcolor"].as_double_tuple_or_default({0, 0, 0});

    // Create new image
    img::EasyImage image = img::EasyImage(size, size, scale_colors(bg));

    // 2DLSystem as type
    if (type == "2DLSystem") {
        std::string file_name = configuration[type]["inputfile"].as_string_or_die();
        std::vector<double> color = configuration[type]["color"].as_double_tuple_or_default({0, 0, 0});
        LParser::LSystem2D l_system = LSystem2D(file_name);

        if (l_system.get_stochastic()) {
            // Insert time seed
            srand(time(NULL));
        }

        Lines2D l_system_lines = LSystem_2D::drawLSystem(l_system, scale_colors_(color));
        Line2D::draw2DLines(l_system_lines, size, image, false);
    }

    else if (type == "Wireframe" || type == "ZBufferedWireframe" || type == "ZBuffering") {

        // General data for all figures
        int nr_figures = configuration["General"]["nrFigures"].as_int_or_die();
        std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();

        // Clipping DATA
        bool CLIPPING = configuration["General"]["clipping"].as_bool_or_default(false);
        std::vector<int> viewDirection;
        int fov;
        double aspect_ratio;
        int d_near;
        int d_far;
        if (CLIPPING){
            viewDirection = configuration["General"]["viewDirection"].as_int_tuple_or_die();
            fov = configuration["General"]["hfov"].as_int_or_die();
            aspect_ratio = configuration["General"]["aspectRatio"].as_double_or_die();
            d_near = configuration["General"]["dNear"].as_int_or_die();
            d_far = configuration["General"]["dFar"].as_int_or_die();
        }

        // Hold all figures
        Figures3D figures;

        // Hold all lines figures
        Figures3D figures_line_drawing;

        bool LINES = false;

        // Traverse all figures inside .ini file
        for (int i = 0; i < nr_figures; i++) {

            Figure figure;

            bool line_drawing = false;
            bool is_fractal = false;
            std::string figure_name = "Figure" + std::to_string(i);
            std::string figure_type = configuration[figure_name]["type"].as_string_or_die();

            if (figure_type == "Cube") {

                figure = Platonic::cube();
            }

            else if (figure_type == "FractalCube") {

                figure = Platonic::cube();
                is_fractal = true;
            }

            else if (figure_type == "Tetrahedron") {

                figure = Platonic::tetrahedron();
            }

            else if (figure_type == "FractalTetrahedron") {

                figure = Platonic::tetrahedron();
                is_fractal = true;
            }

            else if (figure_type == "Octahedron") {

                figure = Platonic::octahedron();
            }

            else if (figure_type == "FractalOctahedron") {

                figure = Platonic::octahedron();
                is_fractal = true;
            }

            else if (figure_type == "Icosahedron") {

                figure = Platonic::icosahedron();
            }

            else if (figure_type == "FractalIcosahedron") {

                figure = Platonic::icosahedron();
                is_fractal = true;
            }

            else if (figure_type == "Dodecahedron") {

                figure = Platonic::dodecahedron();
            }

            else if (figure_type == "FractalDodecahedron") {

                figure = Platonic::dodecahedron();
                is_fractal = true;
            }

            else if (figure_type == "BuckyBall") {

                figure = Platonic::buckyBall();
            }

            else if (figure_type == "FractalBuckyBall") {

                figure = Platonic::buckyBall();
                is_fractal = true;
            }

            else if (figure_type == "Sphere") {

                figure = Platonic::sphere(configuration[figure_name]["n"].as_int_or_die());
            }

            else if (figure_type == "Cone") {

                figure = Platonic::cone(configuration[figure_name]["n"].as_int_or_die(),
                                        configuration[figure_name]["height"].as_double_or_die());
            }

            else if (figure_type == "Cylinder") {

                figure = Platonic::cylinder(configuration[figure_name]["n"].as_int_or_die(),
                                            configuration[figure_name]["height"].as_double_or_die());
            }

            else if (figure_type == "Torus") {

                figure = Platonic::torus(configuration[figure_name]["r"].as_double_or_die(),
                                         configuration[figure_name]["R"].as_double_or_die(),
                                         configuration[figure_name]["n"].as_double_or_die(),
                                         configuration[figure_name]["m"].as_double_or_die());
            }

            else if (figure_type == "3DLSystem") {

                LINES = true;
                line_drawing = true;

                std::string file_name = configuration[figure_name]["inputfile"].as_string_or_die();
                LParser::LSystem3D l_system = LSystem3D(file_name);
                figure = LSystem_3D::drawLSystem(l_system);
            }

            else if (figure_type == "LineDrawing") {

                LINES = true;
                line_drawing = true;

                int nr_points = configuration[figure_name]["nrPoints"].as_int_or_die();
                int nr_lines = configuration[figure_name]["nrLines"].as_int_or_die();

                for (int j = 0; j < nr_points; j++) {
                    std::string point_name = "point" + std::to_string(j);
                    std::vector<double> point = configuration[figure_name][point_name].as_double_tuple_or_die();
                    figure.get_points().emplace_back(Vector3D::point(point[0], point[1], point[2]));
                }

                for (int j = 0; j < nr_lines; j++) {
                    std::string line_name = "line" + std::to_string(j);
                    std::vector<int> line = configuration[figure_name][line_name].as_int_tuple_or_die();
                    figure.get_faces().emplace_back(Face(line));
                }
            }

            // Will hold extra figures that later will be added
            Figures3D temp_fig_holder;
            if (is_fractal) {
                Utils::fractal(figure, temp_fig_holder,
                                  configuration[figure_name]["nrIterations"].as_int_or_die(),
                                  configuration[figure_name]["fractalScale"].as_double_or_die());
            }

            // Calculate transformation-matrix
            double rotateX = configuration[figure_name]["rotateX"].as_double_or_default(0);
            double rotateY = configuration[figure_name]["rotateY"].as_double_or_default(0);
            double rotateZ = configuration[figure_name]["rotateZ"].as_double_or_default(0);

            double scale_d = configuration[figure_name]["scale"].as_double_or_default(1.0);
            std::vector<double> origin = configuration[figure_name]["center"].as_double_tuple_or_default({0,0,0});

            std::vector<double> color_ = configuration[figure_name]["color"].as_double_tuple_or_default({0,0,0});
            cc::Color figure_color = scale_colors_(color_);

            Matrix trans_matrix = Figure::rotateX(rotateX * M_PI / 180)
                                  * Figure::rotateY(rotateY * M_PI / 180)
                                  * Figure::rotateZ(rotateZ * M_PI / 180)
                                  * Figure::scale_figure(scale_d)
                                  * Figure::translate(Vector3D::point(origin[0], origin[1], origin[2]));

            // If there are extra figures stored, traverse these and add to figures sepperately
            if (!temp_fig_holder.empty()) {

                for (Figure & fig : temp_fig_holder) {
                    fig.apply_transformation(trans_matrix);
                    fig.set_color(figure_color);
                    figures.emplace_back(fig);
                }
            }
            else{
                figure.apply_transformation(trans_matrix);
                figure.set_color(figure_color);

                if (line_drawing) {
                    figures_line_drawing.emplace_back(figure);
                }
                else {
                    figures.emplace_back(figure);
                }
            }
        }

        Matrix trans_eye_matrix = Figure::eye_point_trans(Vector3D::point(eye[0], eye[1], eye[2]));
        std::cout << trans_eye_matrix << std::endl;
        if (CLIPPING) {
            trans_eye_matrix = Figure::eye_point_trans_clipping(Vector3D::point(eye[0], eye[1], eye[2]));
        }

        Lines2D figures_lines;
        Lines2D line_drawing_lines;

        if (type == "Wireframe") {

            std::cout << "Wireframe" << std::endl;

            Utils::generate_lines(figures, figures_lines, trans_eye_matrix);
            Line2D::draw2DLines(figures_lines, size, image, false);

            if (LINES) {
                Utils::generate_lines(figures_line_drawing, line_drawing_lines, trans_eye_matrix);
                Line2D::draw2DLines(line_drawing_lines, size, image, false);
            }
        }

        if (type == "ZBufferedWireframe") {

            std::cout << "ZBufferedWireframe" << std::endl;

            Utils::generate_lines(figures, figures_lines, trans_eye_matrix);
            Line2D::draw2DLines(figures_lines, size, image, true);

            if (LINES) {
                Utils::generate_lines(figures_line_drawing, line_drawing_lines, trans_eye_matrix);
                Line2D::draw2DLines(line_drawing_lines, size, image, true);
            }
        }

        if (type == "ZBuffering") {

            std::cout << "ZBuffering" << std::endl;

            double image_x;
            double image_y;
            double d;
            double dx;
            double dy;
            ZBuffer buffer = ZBuffer(0, 0);

            if (!figures.empty()) {

                std::cout << "figures" << std::endl;


                // TODO
                Utils::clipping_data clippingData = Utils::clipping_data();
                if (CLIPPING) {

                    clippingData = Utils::clipping_data(viewDirection, fov, aspect_ratio, d_near, d_far);
                }

                std::tuple<double, double, double, double, double> a = Utils::prep_zbuffering(figures, figures_lines,
                                                                                              trans_eye_matrix, size, CLIPPING, clippingData);

                image_x = std::get<0>(a);
                image_y = std::get<1>(a);
                d = std::get<2>(a);
                dx = std::get<3>(a);
                dy = std::get<4>(a);

                // Create buffer
                buffer = ZBuffer( (unsigned int) std::round(image_x), (unsigned int) std::round(image_y));

                // Resize image
                image.image_resize( (int) std::round(image_x), (int) std::round(image_y));

                // Traverse created triangle-faces in figures
                for (Figure & i : figures) {

                    // Get color of figure
                    std::tuple<double, double, double> color_values = i.get_color().getColor();

                    for (Face & j : i.get_faces()) {

                        image.draw_zbuf_triag(buffer, i.get_points()[j.get_point_indexes()[0]],
                                              i.get_points()[j.get_point_indexes()[1]],
                                              i.get_points()[j.get_point_indexes()[2]],
                                              d,
                                              dx,
                                              dy,
                                              img::Color(std::get<0>(color_values),
                                                         std::get<1>(color_values),
                                                         std::get<2>(color_values)));
                    }
                }
            }

            if (LINES) {

                Utils::generate_lines(figures_line_drawing, line_drawing_lines, trans_eye_matrix);

                if (figures.empty()) {

                    std::cout << "lines" << std::endl;

                    Line2D::draw2DLines(line_drawing_lines, size, image, false);
                }
                else {

                    std::cout << "lines + figures" << std::endl;

                    // Calculate x-min, y-min, x-max and y-max
//                    std::tuple<std::pair<double, double>, std::pair<double, double>> max_line2D = Line2D::Line2D_findMax(line2D);
//
//                    double x = std::get<0>(max_line2D).first;
//                    double y = std::get<0>(max_line2D).second;
//
//                    double X = std::get<1>(max_line2D).first;
//                    double Y = std::get<1>(max_line2D).second;

                    // Calculate x-range, y-range
//                    double xrange = X - x;
//                    double yrange = Y - y;

                    // Calculate max(xrange, yrange)
//                    double range = xrange > yrange ? xrange : yrange;

                    // Calculate dimensions of image
//                    double image_x = size*(xrange/range);
//                    double image_y = size*(yrange/range);

                    // Calculate scale-factor
//                    double d = 0.95*(image_x/xrange);

                    // Multiply coordinates of all points with scale-factor
                    for (Line2D & i : line_drawing_lines) {
                        i.line2D_scale(d);
                    }
//
//                    double DC_x = d*((x + X)/2);
//                    double DC_y = d*((y + Y)/2);
//
//                    double dx = (image_x/2) - DC_x;
//                    double dy = (image_y/2) - DC_y;

                    // Move all coordinates
                    for (Line2D & i : line_drawing_lines) {
                        i.line2D_move(dx, dy);
                    }

                    // Round all points
                    for (Line2D & i : line_drawing_lines) {
                        i.round();
                    }

                    for (Line2D & i : line_drawing_lines) {

                        std::cout << static_cast<int>(std::round(i.getP1().getX())) << " " << static_cast<int>(std::round(i.getP1().getY())) << " " << static_cast<int>(std::round(i.getP2().getX())) << " " << static_cast<int>(std::round(i.getP2().getY())) << std::endl;

                        std::tuple<double, double, double> color_values = i.getColor().getColor();
                        image.draw_line(static_cast<int>(std::round(i.getP1().getX())),
                                        static_cast<int>(std::round(i.getP1().getY())),
                                        static_cast<int>(std::round(i.getP2().getX())),
                                        static_cast<int>(std::round(i.getP2().getY())),
                                        img::Color(std::get<0>(color_values),
                                                   std::get<1>(color_values),
                                                   std::get<2>(color_values)));
                    }

                }
            }

        }
    }
    return image;
}

int main(int argc, char const* argv[])
{
    int retVal = 0;
    try
    {
        for(int i = 1; i < argc; ++i)
        {
            ini::Configuration conf;
            try
            {
                std::ifstream fin(argv[i]);
                std::cout << argv[i] << std::endl;

                fin >> conf;
                fin.close();
            }
            catch(ini::ParseException& ex)
            {
                std::cerr << "Error parsing file: " << argv[i] << ": " << ex.what() << std::endl;
                retVal = 1;
                continue;
            }

            img::EasyImage image = generate_image(conf);
            if(image.get_height() > 0 && image.get_width() > 0)
            {
                std::string fileName(argv[i]);
                std::string::size_type pos = fileName.rfind('.');
                if(pos == std::string::npos)
                {
                    //filename does not contain a '.' --> append a '.bmp' suffix
                    fileName += ".bmp";
                }
                else
                {
                    fileName = fileName.substr(0,pos) + ".bmp";
                }
                try
                {
                    std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                    f_out << image;

                }
                catch(std::exception& ex)
                {
                    std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                    retVal = 1;
                }
            }
            else
            {
                std::cout << "Could not generate image for " << argv[i] << std::endl;
            }
        }
    }
    catch(const std::bad_alloc &exception)
    {
        //When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
        //Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
        //(Unless of course you are already consuming the maximum allowed amount of memory)
        //If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
        //mark the test as failed while in reality it just needed a bit more memory
        std::cerr << "Error: insufficient memory" << std::endl;
        retVal = 100;
    }
    return retVal;
}