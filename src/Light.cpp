//
// Created by Pabsy on 4/30/2021.
//

#include "Light.h"

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
                       const double &spotAngle) : Light(ambientLight,
                                                        diffuseLight, 
                                                        specularLight),
                                                        location(location), 
                                                        spotAngle(spotAngle) {}

std::string PointLight::getName() const {
    return "POINT";
}

Vector3D PointLight::getVector() const {
    return this->location;
}

double PointLight::getAngle() const {
  return this->spotAngle;
}
