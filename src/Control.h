#ifndef CONTROL_H
#define CONTROL_H

#include <list>
#include "easy_image.h"
#include "ini_configuration.h"
#include "Line2D.h"
#include "l_parser.h"
#include "Utils.h"
#include "LSystem2D.h"
#include "LSystem3D.h"
#include "Light.h"

/**
 * @brief List containing of Line2D objects.
 */
typedef std::list<Line2D> Lines2D;

/**
 * @brief Namespace containing members used to call out variety of functions to generate images
 */
namespace Control {

    /**
     * @brief Generate 2DLSystem
     *
     * @param image Image to be generated
     * @param configuration Contains .ini data
     */
    void generate_2DLSystem(img::EasyImage &image, const ini::Configuration &configuration);

    /**
     * @brief Generate a 3D image
     *
     * @param image Image to be generated
     * @param configuration Contains .ini data
     */
    void generate_3D(img::EasyImage &image, const ini::Configuration &configuration);

    /**
     * @brief Generate 3D figures and draw these onto given image
     *
     * @param figures List of 3D figures
     * @param type Type of the figure
     * @param configuration Contains .ini data
     * @param LINES Does image contain lineDrawins
     * @param TEXTURE Is image type "Texture"
     * @param LIGHT Does image contain lights
     * @param lineDrawings List of 3D figures containing line drawings
     */
    void generate_figures(Figures3D &figures, const std::string &type, const ini::Configuration &configuration,
                          bool &LINES, bool &TEXTURE, bool &LIGHT, Figures3D &lineDrawings);

    /**
     * @brief generate_lines Generate lines for given figure
     *
     * @param figure Figure to be generated for
     * @param nr_points Number of points in .ini file
     * @param nr_lines Number of lines in .ini file
     * @param configuration Contains .ini data
     * @param figure_name Name of figure in configuration as string
     */
    void generate_lines(Figure &figure, const int nr_points, const int nr_lines, const ini::Configuration &configuration,
                        const std::string &figure_name);

    /**
     * @brief generate_transMatrix Generate transformation matrix for figure

     * @param trans_matrix Empty matrix
     * @param origin Empty std::vector<double>
     * @param configuration Contains .ini data
     * @param figure_name Name of figure in configuration as string
     */
    void generate_transMatrix(Matrix &trans_matrix, std::vector<double> &origin, const ini::Configuration &configuration,
                            const std::string &figure_name);

    /**
     * @brief setup_figures
     *
     * @param fractal List of 3D figures if figure was a fractal
     * @param figure 3D figure
     * @param figures List containing all figures of image
     * @param figure_name Name of figure in configuration as string
     * @param configuration Contains .ini data
     * @param trans_matrix Transformation matrix for figure
     * @param origin Center of figure
     * @param TEXTURE Is image type "Texture"
     * @param LIGHT Does image contain lights
     * @param is_lineDrawing
     * @param lineDrawings List of 3D figures containing line drawings
     */
    void setup_figures(Figures3D &fractal, Figure &figure, Figures3D &figures, const std::string &figure_name,
                       const ini::Configuration &configuration, const Matrix &trans_matrix, const std::vector<double> &origin,
                       const bool &TEXTURE, const bool &LIGHT, const bool &is_lineDrawing, Figures3D &lineDrawings);

    /**
     * @brief generate_lights
     *
     * @param configuration Contains .ini data
     * @param SHADOW Lights contain shadowMasks
     * @param eyeMatrix Eye matrix
     * @param TEXTURE Is image type "Texture"
     * @param lights List containing 3D lights
     */
    void generate_lights(const ini::Configuration &configuration, const bool &SHADOW, const Matrix &eyeMatrix,
                         const bool &TEXTURE, Lights3D &lights);

    void draw_triangles(Figures3D &figures, Lines2D &lines, Matrix &eyeMatrix,
                        const int size, const bool &SHADOW, const ini::Configuration &configuration,
                        Lights3D &lights, double &image_x, double &image_y, double &d, double &dx,
                        double &dy, ZBuffer &buffer, img::EasyImage &image);
}

#endif // CONTROL_H
