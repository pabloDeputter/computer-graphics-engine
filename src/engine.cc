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

using namespace std;

// #### - SCRIPTS - ####
// find ./ -name '*.bmp' | xargs rm

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

        int nr_figures = configuration["General"]["nrFigures"].as_int_or_die();
        std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();

        Figures3D figures;

        for (int i = 0; i < nr_figures; i++) {
            Figure figure;

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

                std::string file_name = configuration[figure_name]["inputfile"].as_string_or_die();
                LParser::LSystem3D l_system = LSystem3D(file_name);
                figure = LSystem_3D::drawLSystem(l_system);

            }

            else if (figure_type == "LineDrawing") {

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

            Figures3D temp_fig_holder;
            if (is_fractal) {
                Platonic::fractal(figure, temp_fig_holder,
                                  configuration[figure_name]["nrIterations"].as_int_or_die(),
                                  configuration[figure_name]["fractalScale"].as_double_or_die());
                std::cout << temp_fig_holder.size() << std::endl;
            }

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

            if (!temp_fig_holder.empty()) {

                for (Figure & i : temp_fig_holder) {
                    i.apply_transformation(trans_matrix);
                    i.set_color(figure_color);
                    figures.emplace_back(i);
                }
            }
            else{
                figure.apply_transformation(trans_matrix);
                figure.set_color(figure_color);
                figures.emplace_back(figure);
            }

        }

        // TODO
        Matrix trans_eye_matrix = Figure::eye_point_trans(Vector3D::point(eye[0], eye[1], eye[2]));
        Lines2D figures_lines;


        if (type == "ZBuffering") {

            std::cout << "ZBuffering" << std::endl;

            figures_lines.clear();

            for (Figure & i : figures) {

                std::vector<Face> new_faces;

                for (Face & j : i.get_faces()) {

                    std::vector<Face> triangles = ZBuffering::triangulate(j);

                    new_faces.insert(new_faces.end(), triangles.begin(), triangles.end());
                }
                i.get_faces().clear();
                i.get_faces() = new_faces;
            }

            for (Figure & i : figures) {
                i.apply_transformation(trans_eye_matrix);
                Lines2D figure_lines = i.do_projection();
                figures_lines.splice(figures_lines.end(), figure_lines);
            }

            // Calculate x-min, y-min, x-max and y-max
            std::tuple<std::pair<double, double>, std::pair<double, double>> max_line2D = Line2D::Line2D_findMax(figures_lines);

            double x = std::get<0>(max_line2D).first;
            double y = std::get<0>(max_line2D).second;


            double X = std::get<1>(max_line2D).first;
            double Y = std::get<1>(max_line2D).second;

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


//            std::cout << image_x << " " << image_y << std::endl;
//            std::cout << (unsigned int) std::round(image_x) << " " << (unsigned int) std::round(image_y) << std::endl;
//            std::cout << (int) std::round(image_x) << " " << (int) std::round(image_y) << std::endl;


            // Create buffer
            ZBuffer buffer = ZBuffer( (unsigned int) std::round(image_x), (unsigned int) std::round(image_y));

            // Resize image
            image.image_resize( (int) std::round(image_x), (int) std::round(image_y));

            // Traverse created triangle-faces in figures
            for (Figure & i : figures) {

                // Get color of figure
                std::tuple<double, double, double> color_values = i.get_color().getColor();

                for (Face & j : i.get_faces()) {

                    image.draw_zbuf_triag(buffer, i.get_points()[j.get_point_indexes()[0]],
                                          i.get_points()[j.get_point_indexes()[1]],
                                          i.get_points()[j.get_point_indexes()[2]], d, dx, dy,
                                          img::Color(std::get<0>(color_values),
                                                     std::get<1>(color_values),
                                                     std::get<2>(color_values)));
                }
            }
        }

        for (Figure & i : figures) {
            i.apply_transformation(trans_eye_matrix);
            Lines2D figure_lines = i.do_projection();
            figures_lines.splice(figures_lines.end(), figure_lines);
        }

        if (type == "Wireframe") {
            std::cout << "Wireframe" << std::endl;
            Line2D::draw2DLines(figures_lines, size, image, false);
        }

        if (type == "ZBufferedWireframe") {
            std::cout << "ZBufferedWireframe" << std::endl;
            Line2D::draw2DLines(figures_lines, size, image, true);
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