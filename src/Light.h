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
    cc::Color ambientLight;
    /**
     * \brief Diffuse light component
     */
    cc::Color diffuseLight;
    /**
     * \brief Diffuse light component
     */
    cc::Color specularLight;

public:
    /**
     * \brief Default constructor for Light object when no values for components are given
     */
    Light();

    /**
     * \brief Constructor for Light object
     * @param ambientLight Values for ambientLight component
     * @param diffuseLight Values for diffuseLight component
     * @param specularLight Values for specularLight component
     */
    Light(const std::vector<double> & ambientLight, const std::vector<double> & diffuseLight,
          const std::vector<double> & specularLight);

    virtual std::string getName() const {
        return "LIGHT";
    }

    virtual double getAngle() const;

    virtual Vector3D getVector() const;

    const cc::Color &getAmbientLight() const {
        return ambientLight;
    }

    void setAmbientLight(const cc::Color &ambientLight) {
        this->ambientLight = ambientLight;
    }

    const cc::Color &getDiffuseLight() const {
        return diffuseLight;
    }

    void setDiffuseLight(const cc::Color &diffuseLight) {
        Light::diffuseLight = diffuseLight;
    }

    const cc::Color &getSpecularLight() const {
        return specularLight;
    }

    void setSpecularLight(const cc::Color &specularLight) {
        Light::specularLight = specularLight;
    }
};

class InfLight : public Light {
private:
    /**
     * \brief Direction of light source
     */
     Vector3D ldVector;

public:
    /**
     * \brief Constructor for InfLight object
     */
    InfLight(const std::vector<double> &ambientLight, const std::vector<double> &diffuseLight,
             const std::vector<double> &specularLight, const Vector3D &ldVector);

    std::string getName() const override;

    double getAngle() const override;

    Vector3D getVector() const override;

    const Vector3D &getLdVector() const {
        return ldVector;
    }

    void setLdVector(const Vector3D &ldVector) {
        this->ldVector = ldVector;
    }

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

public:
    /**
     * \brief Constructor for PointLight object
     */
    PointLight(const std::vector<double> &ambientLight, const std::vector<double> &diffuseLight,
             const std::vector<double> &specularLight, const Vector3D &location, const double &spotAngle);

    std::string getName() const override;

    Vector3D getVector() const override;

    double getAngle() const override;

    const Vector3D &getLocation() const {
        return location;
    }

    void setLocation(const Vector3D &location) {
        this->location = location;
    }

    double getSpotAngle() const {
        return spotAngle;
    }

    void setSpotAngle(double spotAngle) {
        this->spotAngle = spotAngle;
    }
};

typedef std::list<Light*> Lights3D;

#endif //ENGINE_LIGHT_H
