#include "Control.h"

void Control::generate_2DLSystem(img::EasyImage &image, const ini::Configuration &configuration) {

        std::string file_name = configuration["2DLSystem"]["inputfile"].as_string_or_die();
        std::vector<double> color = configuration["2DLSystem"]["color"].as_double_tuple_or_default({0, 0, 0});
        LParser::LSystem2D lSystem = Utils::LSystem2D(file_name);

        if (lSystem.get_stochastic()) {
            // Insert time seed
            srand(time(NULL));
        }
        Lines2D LSystem_lines = LSystem_2D::drawLSystem(lSystem, cc::Color(color));
        Line2D::draw2DLines(LSystem_lines, image.get_height(), image, false);
}

void Control::generate_3D(img::EasyImage &image, const ini::Configuration &configuration) {

     // General data for all figures
     std::string type = configuration["General"]["type"].as_string_or_die();
     std::vector<double> eye = configuration["General"]["eye"].as_double_tuple_or_die();

     bool SHADOW = configuration["General"]["shadowEnabled"].as_bool_or_default(false);

     // Light DATA
     bool LIGHT = false;
     if (type == "LightedZBuffering" || type == "Texture") LIGHT = true;

     bool TEXTURE = false;
     if (type == "Texture") TEXTURE = true;

     bool LINES = false;

     // Hold all figures
     Figures3D figures;

     // Hold all lines figures
     Figures3D figures_lineDrawings;

     Control::generate_figures(figures, type, configuration, LINES, TEXTURE, LIGHT, figures_lineDrawings);

     Matrix eyeMatrix = Figure::eye_point_trans(Vector3D::point(eye[0], eye[1], eye[2]));

     Lights3D lights;
     Lines2D lines;
     Lines2D lineDrawing_lines;

    if (LIGHT) Control::generate_lights(configuration, SHADOW, eyeMatrix, TEXTURE, lights);

    if (type == "Wireframe" || type == "ZBufferedWireframe") {

        bool ZBuffered = false;
        if (type == "ZBufferedWireframe") ZBuffered = true;

        Utils::generate_lines(figures, lines, eyeMatrix);
        Line2D::draw2DLines(lines, configuration["General"]["size"].as_int_or_die(), image, ZBuffered);

        if (LINES) {
            Utils::generate_lines(figures_lineDrawings, lineDrawing_lines, eyeMatrix);
            if (figures.empty()) Line2D::draw2DLines(lineDrawing_lines, configuration["General"]["size"].as_int_or_die(),
                                                     image, true);
            }
        }

    if (type == "ZBuffering" || type == "LightedZBuffering" || type == "Texture") {

        double image_x;
        double image_y;
        double d;
        double dx;
        double dy;
        ZBuffer buffer = ZBuffer(0, 0);

        if (!figures.empty()) {
            Control::draw_triangles(figures, lines, eyeMatrix, configuration["General"]["size"].as_int_or_die(),
                                    SHADOW, configuration, lights, image_x, image_y, d, dx, dy, buffer, image);
        }
        if (LINES) {
            Utils::generate_lines(figures_lineDrawings, lineDrawing_lines, eyeMatrix);
            if (figures.empty()) Line2D::draw2DLines(lineDrawing_lines, configuration["General"]["size"].as_int_or_die(),
                                                     image, true);
            else {
                for (Line2D &i : lineDrawing_lines) {
                    i.line2D_scale(d);
                    i.line2D_move(dx, dy);
                    i.round();

                    image.draw_line(static_cast<int>(std::round(i.getP1().getX())),
                                    static_cast<int>(std::round(i.getP1().getY())),
                                    static_cast<int>(std::round(i.getP2().getX())),
                                    static_cast<int>(std::round(i.getP2().getY())),
                                    Utils::saturate_color(i.getColor()));
                }
            }
        }
    }
}

void Control::generate_figures(Figures3D &figures, const std::string &type, const ini::Configuration &configuration,
                               bool &LINES, bool &TEXTURE, bool &LIGHT, Figures3D &lineDrawings) {

    std::ignore = type;

    int nr_figures = configuration["General"]["nrFigures"].as_int_or_die();
    // Traverse all figures inside .ini file
    for (int i = 0; i < nr_figures; i++) {

        Figure figure;

        bool is_lineDrawing = false;
        bool is_fractal = false;
        bool is_mengerSponge = false;
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

        else if (figure_type == "MengerSponge") {
            figure = Platonic::cube();
            is_fractal = true;
            is_mengerSponge = true;
        }

        else if (figure_type == "3DLSystem") {
            LINES = true;
            is_lineDrawing = true;

            std::string file_name = configuration[figure_name]["inputfile"].as_string_or_die();
            LParser::LSystem3D lSystem = Utils::LSystem3D(file_name);
            figure = LSystem_3D::drawLSystem(lSystem);
        }

        else if (figure_type == "LineDrawing") {
            LINES = true;
            is_lineDrawing = true;

            int nr_points = configuration[figure_name]["nrPoints"].as_int_or_die();
            int nr_lines = configuration[figure_name]["nrLines"].as_int_or_die();
            Control::generate_lines(figure, nr_points, nr_lines, configuration, figure_name);
        }

        Figures3D fractal;
        if (is_fractal) {
            double fractal_scale = 3;
            if (!is_mengerSponge) {
                fractal_scale = configuration[figure_name]["fractalScale"].as_double_or_die();
            }
            Utils::fractal(figure, fractal,
                           configuration[figure_name]["nrIterations"].as_int_or_die(),
                           fractal_scale, is_mengerSponge);
        }

        Matrix trans_matrix;
        std::vector<double> origin;
        Control::generate_transMatrix(trans_matrix, origin, configuration, figure_name);

        Control::setup_figures(fractal, figure, figures, figure_name, configuration, trans_matrix, origin,
                               TEXTURE, LIGHT, is_lineDrawing, lineDrawings);
    }
}

void Control::generate_lines(Figure &figure, const int nr_points, const int nr_lines, const ini::Configuration &configuration,
                             const std::string &figure_name) {

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

void Control::generate_transMatrix(Matrix &trans_matrix, std::vector<double> &origin, const ini::Configuration &configuration,
                                 const std::string &figure_name) {

    double rotateX = configuration[figure_name]["rotateX"].as_double_or_default(0);
    double rotateY = configuration[figure_name]["rotateY"].as_double_or_default(0);
    double rotateZ = configuration[figure_name]["rotateZ"].as_double_or_default(0);

    double scale_d = configuration[figure_name]["scale"].as_double_or_default(1.0);
    origin = configuration[figure_name]["center"].as_double_tuple_or_default({0,0,0});

    trans_matrix = Figure::rotateX(rotateX * M_PI / 180)
                  * Figure::rotateY(rotateY * M_PI / 180)
                  * Figure::rotateZ(rotateZ * M_PI / 180)
                  * Figure::scale_figure(scale_d)
                  * Figure::translate(Vector3D::point(origin[0], origin[1], origin[2]));
}

void Control::setup_figures(Figures3D &fractal, Figure &figure, Figures3D &figures, const std::string &figure_name,
                            const ini::Configuration &configuration, const Matrix &trans_matrix, const std::vector<double> &origin,
                            const bool &TEXTURE, const bool &LIGHT, const bool &is_lineDrawing, Figures3D &lineDrawings) {

    if (!fractal.empty()) {
        for (Figure & fig : fractal) {
            if (!LIGHT) {
                fig.setAmbientReflection(configuration[figure_name]["color"].as_double_tuple_or_default({0, 0, 0}));
            }
            else {
                fig.setAmbientReflection(configuration[figure_name]["ambientReflection"].as_double_tuple_or_default({0, 0, 0}));
                fig.setDiffuseReflection(configuration[figure_name]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0}));
                fig.setSpecularReflection(configuration[figure_name]["specularReflection"].as_double_tuple_or_default({0, 0, 0}));
                fig.setReflectionCoefficient(configuration[figure_name]["reflectionCoefficient"].as_double_or_default(0));
            }
            fig.apply_transformation(trans_matrix);

            fig.setTextureFlag(false);
            bool texture_exists = false;
            if (configuration[figure_name]["textureName"].exists()) texture_exists = true;

            if (TEXTURE && texture_exists) {
                std::ifstream fin(configuration[figure_name]["textureName"].as_string_or_die());
                img::EasyImage new_texture;
                fin >> new_texture;
                fin.close();
                fig.setTexture(new_texture);
                fig.setTextureFlag(true);
            }
            figures.emplace_back(fig);
        }
    }
    else{
        if (!LIGHT) {
            figure.setAmbientReflection(configuration[figure_name]["color"].as_double_tuple_or_default({0, 0, 0}));
        }
        else {
            figure.setAmbientReflection(configuration[figure_name]["ambientReflection"].as_double_tuple_or_default({0, 0, 0}));
            figure.setDiffuseReflection(configuration[figure_name]["diffuseReflection"].as_double_tuple_or_default({0, 0, 0}));
            figure.setSpecularReflection(configuration[figure_name]["specularReflection"].as_double_tuple_or_default({0, 0, 0}));
            figure.setReflectionCoefficient(configuration[figure_name]["reflectionCoefficient"].as_double_or_default(0));
        }
        figure.apply_transformation(trans_matrix);

        figure.setTextureFlag(false);
        bool texture_exists = false;
        if (configuration[figure_name]["textureName"].exists()) texture_exists = true;

        if (TEXTURE && texture_exists) {
            std::ifstream fin(configuration[figure_name]["textureName"].as_string_or_die());
            img::EasyImage new_texture;
            fin >> new_texture;
            fin.close();
            figure.setTexture(new_texture);
            figure.setTextureFlag(true);
            figure.setCenter(Vector3D::point(origin[0], origin[1], origin[2]));
        }

        if (is_lineDrawing) {
            lineDrawings.emplace_back(figure);
        }
        else {
            figures.emplace_back(figure);
        }
    }
}

void Control::generate_lights(const ini::Configuration &configuration, const bool &SHADOW, const Matrix &eyeMatrix,
                              const bool &TEXTURE, Lights3D &lights) {

    const int amountLights = configuration["General"]["nrLights"].as_int_or_default(0);

    for (int i = 0; i != amountLights; i++) {
        std::string light_name = "Light" + std::to_string(i);
        bool infinity = configuration[light_name]["infinity"].as_bool_or_default(false);
        bool location = false;
        if (configuration[light_name]["location"].exists()) location = true;

        std::vector<double> ambient_light =
                configuration[light_name]["ambientLight"].as_double_tuple_or_default({0, 0, 0});
        std::vector<double> diffuse_light =
                configuration[light_name]["diffuseLight"].as_double_tuple_or_default({0, 0, 0});
        std::vector<double> specular_light =
                configuration[light_name]["specularLight"].as_double_tuple_or_default({0, 0, 0});

        bool texture_exists = false;
        if (configuration[light_name]["textureName"].exists()) texture_exists = true;

        if (infinity) {
            std::vector<double> direc =
                    configuration[light_name]["direction"].as_double_tuple_or_default({0, 0, 0});

            Vector3D ld = Vector3D::vector(direc[0], direc[1], direc[2]);
            ld *= eyeMatrix;
            InfLight *new_light = new InfLight(ambient_light, diffuse_light, specular_light, ld);

            if (texture_exists && TEXTURE) {
                std::ifstream fin(configuration[light_name]["textureName"].as_string_or_die());
                img::EasyImage new_texture;
                fin >> new_texture;
                fin.close();
                new_light->setTextureFlag(true);
                new_light->setTexture(new_texture);
            }
            lights.emplace_back(new_light);
            continue;
        }
        else if (location) {
            std::vector<double> loc =
                        configuration[light_name]["location"].as_double_tuple_or_default({0, 0, 0});
            Vector3D position = Vector3D::point(loc[0], loc[1], loc[2]);
            position = position * eyeMatrix;
            double spotAngle = configuration[light_name]["spotAngle"].as_double_or_default(0.0);
            PointLight *new_light = new PointLight(ambient_light, diffuse_light, specular_light, position, spotAngle);
            int shadowMask = 0;

            if (SHADOW) {
                shadowMask = configuration["General"]["shadowMask"].as_int_or_die();
                new_light->setShadowMask(shadowMask, shadowMask);
                Matrix eye_light = Figure::eye_point_trans(Vector3D::point(loc[0], loc[1], loc[2]));
                new_light->setEye(eye_light);
                new_light->setInvEye(Matrix::inv(eyeMatrix));
            }

            if (texture_exists && TEXTURE) {
                std::ifstream fin(configuration[light_name]["textureName"].as_string_or_die());
                img::EasyImage new_texture;
                fin >> new_texture;
                fin.close();
                new_light->setTextureFlag(true);
                new_light->setTexture(new_texture);
            }

            lights.emplace_back(new_light);
            continue;
        }
        Light *new_light = new Light(ambient_light, diffuse_light, specular_light);

        if (texture_exists && TEXTURE) {
            std::ifstream fin(configuration[light_name]["textureName"].as_string_or_die());
            img::EasyImage new_texture;
            fin >> new_texture;
            fin.close();
            new_light->setTextureFlag(true);
            new_light->setTexture(new_texture);
        }
        lights.emplace_back(new_light);
    }
}

void Control::draw_triangles(Figures3D &figures, Lines2D &lines, Matrix &eyeMatrix,
                             const int size, const bool &SHADOW, const ini::Configuration &configuration,
                             Lights3D &lights, double &image_x, double &image_y, double &d, double &dx,
                             double &dy, ZBuffer &buffer, img::EasyImage &image) {

    std::tuple<double, double,
               double, double,
               double, Figures3D> return_data = Utils::prep_zbuffering(figures, lines,
                                                                       eyeMatrix, size);

    image_x = std::get<0>(return_data);
    image_y = std::get<1>(return_data);
    d = std::get<2>(return_data);
    dx = std::get<3>(return_data);
    dy = std::get<4>(return_data);
    Figures3D triangulated_figures = std::get<5>(return_data);

    std::cout << "SIZE: " <<triangulated_figures.rbegin()->get_faces().size() << std::endl;

    // Create buffer
    buffer = ZBuffer( (unsigned int) std::round(image_x), (unsigned int) std::round(image_y));
    // Resize image
    image.image_resize( (int) std::round(image_x), (int) std::round(image_y));

    // Create shadowMask for every light if SHADOW == true
    if (SHADOW) {
        for (Light *i : lights) {
            if (i->getName() == "POINT") {
                i->createShadowMask(triangulated_figures,
                                    configuration["General"]["shadowMask"].as_int_or_die());
            }
        }
    }

    // Traverse created triangles and draw
    for (Figure & i : figures) {
        for (Face & j : i.get_faces()) {

            image.draw_zbuf_triag(buffer, i.get_points()[j.get_point_indexes()[0]],
                                  i.get_points()[j.get_point_indexes()[1]],
                                  i.get_points()[j.get_point_indexes()[2]],
                                  d, dx, dy, i.getAmbientReflection(), i.getDiffuseReflection(),
                                  i.getSpecularReflection(), i.getReflectionCoefficient(), lights,
                                  eyeMatrix, SHADOW, i.getTexture(), i.isTexture(), i.getCenter());
        }
    }
}
