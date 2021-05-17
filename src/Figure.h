//
// Created by Pablo Deputter on 05/03/2021.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H


#include <list>
#include <tuple>
#include <cmath>
#include <tgmath.h>
#include "Face.h"
#include "vector3d.h"
#include "Color.h"
#include "Line2D.h"

class Figure {

private:
    /**
     * @brief points Vector of Vector3D objects
     */
    std::vector<Vector3D> points;
    /**
     * @brief faces Vector of Face objects
     */
    std::vector<Face> faces;
    /**
     * @brief color cc::Color object with RGB-value between 0 & 1
     */
    cc::Color color;
    /**
     * @brief ambientReflection AmbientLight component
     */
    cc::Color ambientReflection;
    /**
     * @brief diffuseReflection DiffuseLight component
     */
    cc::Color diffuseReflection;
    /**
     * @brief specularReflection SpecularLight component
     */
    cc::Color specularReflection;
    /**
     * @brief reflectionCoefficient Reflection grade of figure, thus smaller is the greater the effect
     */
    double reflectionCoefficient;
    /**
     * @brief textureFlag Bool if Figure contains a texture
     */
    bool textureFlag;
    /**
     * @brief texture Texture as img::EasyImage object
     */
    img::EasyImage texture;
    /**
     * @brief center Centre of the figure, used for textures
     */
    Vector3D center;
public:
    std::vector<Vector3D> &get_points() {
        return points;
    }

    std::vector<Face> &get_faces() {
        return faces;
    }

    const cc::Color &get_color() const {
        return color;
    }

    void set_color(const cc::Color &x) {

        Figure::color = x;
    }

    const cc::Color &getAmbientReflection() const {
        return ambientReflection;
    }

    void setAmbientReflection(const std::vector<double> &i) {
        Figure::ambientReflection = cc::Color(i);
    }

    const cc::Color &getDiffuseReflection() const {
        return diffuseReflection;
    }

    void setDiffuseReflection(const std::vector<double> &i) {
        Figure::diffuseReflection = cc::Color(i);
    }

    const cc::Color &getSpecularReflection() const {
        return specularReflection;
    }

    void setSpecularReflection(const std::vector<double> &i) {
        Figure::specularReflection = cc::Color(i);
    }

    double getReflectionCoefficient() const {
        return reflectionCoefficient;
    }

    void setReflectionCoefficient(double reflectionCoefficient) {
        Figure::reflectionCoefficient = reflectionCoefficient;
    }

    const bool &isTexture() const {
        return Figure::textureFlag;
    }

    void setTextureFlag(const bool &x) {
        Figure::textureFlag = x;
    }

    const img::EasyImage &getTexture() const {
        return Figure::texture;
    }

    img::EasyImage &getTexture() {
        return Figure::texture;
    }

    void setTexture(const img::EasyImage &x) {
        Figure::texture = x;
    }

    const Vector3D &getCenter() const {
        return Figure::center;
    }

    void setCenter(const Vector3D &x) {
        Figure::center = x;
    }

    void add_point(const std::tuple<int, int, int> &x);

    void add_point_double(const std::tuple<double, double, double> &x);

    void correct_indexes();

    void clear_faces();

    static Matrix scale_figure(const double &scaleFactor);

    static Matrix rotateX(const double &angle);

    static Matrix rotateY(const double &angle);

    static Matrix rotateZ(const double &angle);

    static Matrix translate(const Vector3D &vector);

    void apply_transformation(const Matrix &x);

    static std::tuple<double, double, double> to_polar(const Vector3D &x);

    static Matrix eye_point_trans(const Vector3D &eyepoint);

    static Point2D do_projection(const Vector3D &point, const double &d);

    Lines2D do_projection();
};

typedef std::list<Figure> Figures3D;

#endif //ENGINE_FIGURE_H
