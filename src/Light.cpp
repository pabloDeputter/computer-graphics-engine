//
// Created by Pabsy on 4/30/2021.
//

#include "Light.h"
#include "Figure.h"
#include "Utils.h"
#include "DesignByContract.h"
#include <fstream>
#include <unistd.h>

Light::Light() {

    Light::ambientLight = cc::Color(1, 1, 1);
    Light::diffuseLight = cc::Color(0, 0, 0);
    Light::specularLight = cc::Color(0, 0, 0);
}

Light::Light(const std::vector<double> &ambientLight, const std::vector<double> &diffuseLight,
             const std::vector<double> &specularLight) {

    Light::ambientLight = cc::Color(ambientLight);
    Light::diffuseLight = cc::Color(diffuseLight);
    Light::specularLight = cc::Color(specularLight);
}

Vector3D Light::getVector() const {
    return Vector3D();
}

double Light::getAngle() const {
    return 0;
}

bool Light::isReflective() const {
    return this->specularLight.getRed() == this->specularLight.getGreen() == this->specularLight.getBlue() != 0;
}

InfLight::InfLight(const std::vector<double> &ambientLight, const std::vector<double> &diffuseLight,
                   const std::vector<double> &specularLight, const Vector3D &ldVector) : Light(ambientLight,
                                                                                               diffuseLight,
                                                                                               specularLight),
                                                                                         ldVector(ldVector) {}

std::string InfLight::getName() const {
    return "INFINITY";
}

Vector3D InfLight::getVector() const {

    return this->ldVector;
}

double InfLight::getAngle() const {
  return 0;
}

PointLight::PointLight(const std::vector<double> &ambientLight, const std::vector<double> &diffuseLight,
                       const std::vector<double> &specularLight, const Vector3D &location,
                       const double &x) : Light(ambientLight,
                                                        diffuseLight, 
                                                        specularLight),
                                                        location(location) {
    this->spotAngle = 0;
    if (x != 0) {
        this->spotAngle = cos(cos(x)) + 0.022; // TODO - bug diffuse_light801.bmp
    }
}

std::string PointLight::getName() const {
    return "POINT";
}

Vector3D PointLight::getVector() const {
    return this->location;
}

double PointLight::getAngle() const {
    return this->spotAngle;
}


void PointLight::createShadowMask(Figures3D &triangulated_figures, const int size) {

    Lines2D shadow_lines;

    // Do projection and generate lines
    Utils::generate_lines(triangulated_figures, shadow_lines, this->eye);

    // Calculate x-min, y-min, x-max, and y-max
    std::tuple<std::pair<double, double>, std::pair<double, double>> max_line2D = Line2D::Line2D_findMax(shadow_lines);
    double x = std::get<0>(max_line2D).first;
    double y = std::get<0>(max_line2D).second;

    double X = std::get<1>(max_line2D).first;
    double Y = std::get<1>(max_line2D).second;

    // Calculate image_x, image_y, d, dx, dy
    std::tuple<double, double, double, double, double> data = Utils::calculate_data(x, X, y, Y, size);
    double image_x = std::get<0>(data);
    double image_y = std::get<1>(data);
    this->d = std::get<2>(data);
    this->dx = std::get<3>(data);
    this->dy = std::get<4>(data);

    std::cout << "d: " << d << std::endl;
    std::cout << "dx: " << dx << std::endl;
    std::cout << "dy: " << dy << std::endl;

    this->shadowMask = ZBuffer( (unsigned int) std::round(image_x), (unsigned int) std::round(image_y));

    // Create shadowMask
    for (Figure &i : triangulated_figures) {
        for (Face &j : i.get_faces()) {

            PointLight::fillShadowMask(i.get_points()[j.get_point_indexes()[0]],
                                       i.get_points()[j.get_point_indexes()[1]],
                                       i.get_points()[j.get_point_indexes()[2]], size);
        }
    }
}

void PointLight::fillShadowMask(const Vector3D &A, const Vector3D &B, const Vector3D &C, const int size) {

    // Project triangle ABC -> A'B'C' on real points
    Point2D A_ = Point2D((d * A.x) / -A.z + dx, (d * A.y) / -A.z + dy);
    Point2D B_ = Point2D((d * B.x) / -B.z + dx, (d * B.y) / -B.z + dy);
    Point2D C_ = Point2D((d * C.x) / -C.z + dx, (d * C.y) / -C.z + dy);

    std::ofstream outfile;
    outfile.open("test.txt", std::ios_base::app); // append instead of overwrite

    outfile << "A :" << A << std::endl;
    outfile << "B :" << B << std::endl;
    outfile << "C :" << C << std::endl;

    // Calculate ymin and ymax
    const int ymin = static_cast<int>(std::round(std::min(A_.getY(), std::min(B_.getY(), C_.getY())) + 0.5));
    const int ymax = static_cast<int>(std::round(std::max(A_.getY(), std::max(B_.getY(), C_.getY())) - 0.5));

    // Calculate middle point triangle
    double x_g = A_.getX() + B_.getX() + C_.getX();
    double y_g = A_.getY() + B_.getY() + C_.getY();
    double xg = x_g / 3;
    double yg = y_g / 3;

    double zg = 1 / (3 * A.z) + 1 / (3 * B.z) + 1 / (3 * C.z);

    Vector3D u = B - A;
    Vector3D v = C - A;
    Vector3D w = Vector3D::point( u.y * v.z - u.z * v.y,
                                  u.z * v.x - u.x * v.z,
                                  u.x * v.y - u.y * v.x );

    double k = w.x * A.x + w.y * A.y + w.z * A.z;

    const double dzdx = w.x / (-d * k);
    const double dzdy = w.y / (-d * k);

    outfile << "zg: " << zg << std::endl;

    // Iterate over all y-values
    for (unsigned int y = static_cast<unsigned int>(ymin); y <= static_cast<unsigned int>(ymax); y++) {

        // Calculate value of xl and xr for AB, AC, BC
        double xl_AB = +std::numeric_limits<double>::infinity();
        double xl_AC = +std::numeric_limits<double>::infinity();
        double xl_BC = +std::numeric_limits<double>::infinity();

        double xr_AB = -std::numeric_limits<double>::infinity();
        double xr_AC = -std::numeric_limits<double>::infinity();
        double xr_BC = -std::numeric_limits<double>::infinity();

        // PQ = AB
        if ( (y - A_.getY()) * (y - B_.getY()) <= 0 && A_.getY() != B_.getY() ) {

            xl_AB = B_.getX() + (A_.getX() - B_.getX()) * ( (double) y - B_.getY() ) / (A_.getY() - B_.getY());
            xr_AB = xl_AB;
        }

        // PQ = AC
        if ( (y - A_.getY()) * (y - C_.getY()) <= 0 && A_.getY() != C_.getY() ) {

            xl_AC = C_.getX() + (A_.getX() - C_.getX()) * ( (double) y - C_.getY() ) / (A_.getY() - C_.getY());
            xr_AC = xl_AC;
        }

        // PQ = BC
        if ( (y - B_.getY()) * (y - C_.getY()) <= 0 && B_.getY() != C_.getY() ) {

            xl_BC = C_.getX() + (B_.getX() - C_.getX()) * ( (double) y - C_.getY() ) / (B_.getY() - C_.getY());
            xr_BC = xl_BC;
        }

        int xl = std::round(std::min(xl_AB, std::min(xl_AC, xl_BC)) + 0.5);
        int xr = std::round(std::max(xr_AB, std::max(xr_AC, xr_BC)) + 0.5);

        for (unsigned int x = static_cast<unsigned int>(xl); x != static_cast<unsigned int>(xr); x++) {

            double a_ = static_cast<double>(std::round(x)) - xg;
            double b_ = static_cast<double>(std::round(y)) - yg;

            double a = a_ * dzdx;
            double b = b_ * dzdy;

            double z = zg + a + b;

//            outfile << "z: " << z << std::endl;

            // TODO
            shadowMask.check_z_value(x, y, z);
        }
    }
}

bool PointLight::checkShadowMask(const Vector3D &point, const Matrix &eye) const {

    // TODO - point meegegeven is normale point denk ik

    Vector3D light_point = point * this->invEye;
    light_point = light_point * this->eye;

    double xl = (this->d * light_point.x / -light_point.z) + this->dx;
    double yl = (this->d * light_point.y / -light_point.z) + this->dy;

    double ax = xl - std::floor(xl);
    double ay = yl - std::floor(yl);

    double aZ = shadowMask.getBuffer()[std::floor(xl)][std::ceil(yl)];
    double bZ = shadowMask.getBuffer()[std::ceil(xl)][std::ceil(yl)];
    double cZ = shadowMask.getBuffer()[std::floor(xl)][std::floor(yl)];
    double dZ = shadowMask.getBuffer()[std::ceil(xl)][std::floor(yl)];


    double eZ = (1 - ax) * aZ + ax * bZ;
    double fZ = (1 - ax) * cZ + ax * dZ;

    double z_inverse = (1 - ay) * fZ + ay * eZ;

    if (std::abs(z_inverse - (1 / light_point.z)) > std::pow(10, -4)) {
        return true;
    }
    return false;
}


