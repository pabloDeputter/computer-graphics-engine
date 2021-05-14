//
// Created by Pabsy on 4/30/2021.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#define UNUSED(x) [&x]{}()

#include <list>
#include "Color.h"
#include "vector3d.h"
#include "ZBuffer.h"

class Figure;

typedef std::list<Figure> Figures3D;

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

    virtual bool isReflective() const;

    virtual void createShadowMask(Figures3D &figures, const int size) {
//        std::ignore = figures;
//        std::ignore = size;
        std::cout << "wrong createShadowMask" << std::endl;
    }

    virtual bool checkShadowMask(const Vector3D &point, const Matrix &eye) const {
//        std::ignore = point;
        std::cout << "wrong checkShadowMaks" << std::endl;
        return true;
    }

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
     /**
      * @brief shadowMask
      */
     ZBuffer shadowMask;
     /**
      * @brief eye
      */
     Matrix eye;
     /**
      * @brief invEye
      */
     Matrix invEye;
     /**
      * @brief d, dx, dy
      */
     double d, dx, dy;
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

    const ZBuffer &getShadowMask() const {
        return shadowMask;
    }

    void setShadowMask(const int x, const int y) {
        this->shadowMask = ZBuffer(x, y);
    }

    void setEye(const Matrix &x) {
        this->eye = x;
    }

    void setInvEye(const Matrix &x) {
        this->invEye = x;
    }

    void createShadowMask(Figures3D &triangulated_figures, const int size) override;

    void fillShadowMask(const Vector3D &A, const Vector3D &B, const Vector3D &C, const int size);

    bool checkShadowMask(const Vector3D &point, const Matrix &eye) const override;

};

typedef std::list<Light*> Lights3D;

#endif //ENGINE_LIGHT_H
