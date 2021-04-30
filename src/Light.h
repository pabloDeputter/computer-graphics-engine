//
// Created by Pabsy on 4/30/2021.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include <list>
#include "Color.h"
#include "vector3d.h"

class Light {
private:
    /**
     * \brief Ambient light component
     */
    cc::Color ambientReflection;
    /**
     * \brief Diffuse light component
     */
    cc::Color diffuseReflection;
    /**
     * \brief Diffuse light component
     */
    cc::Color specularReflection;

public:
    const cc::Color &getAmbientReflection() const {
        return ambientReflection;
    }

    void setAmbientReflection(const cc::Color &ambientReflection) {
        Light::ambientReflection = ambientReflection;
    }

    const cc::Color &getDiffuseReflection() const {
        return diffuseReflection;
    }

    void setDiffuseReflection(const cc::Color &diffuseReflection) {
        Light::diffuseReflection = diffuseReflection;
    }

    const cc::Color &getSpecularReflection() const {
        return specularReflection;
    }

    void setSpecularReflection(const cc::Color &specularReflection) {
        Light::specularReflection = specularReflection;
    }
};

class InfLight : public Light {
private:
    /**
     * \brief Direction of light source
     */
     Vector3D ldVector;

};

class PointLight : public Light {
private:
    /**
     * \brief Location of the light source
     */
    Vector3D location;
    /**
     * \brief Angle of light source
     */
     double spotAngle;

};

typedef std::list<Light*> Lights3D;

#endif //ENGINE_LIGHT_H
