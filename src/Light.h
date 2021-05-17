//
// Created by Pabsy on 4/30/2021.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include <list>
#include "Color.h"
#include "vector3d.h"
#include "ZBuffer.h"
#include "easy_image.h"

class Figure;
typedef std::list<Figure> Figures3D;

namespace img {
    class EasyImage;
}
/**
 * @brief The Light class
 */
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
    /**
     * @brief isTexture bool
     */
    bool textureFlag;
    /**
     * @brief Texture
     */
    img::EasyImage texture;
public:
    /**
     * \brief Default constructor for Light object when no values for components are given
     */
    Light();

    /**
     * \brief Constructor for Light object
     *
     * @param ambientLight Values for ambientLight component
     * @param diffuseLight Values for diffuseLight component
     * @param specularLight Values for specularLight component
     */
    Light(const std::vector<double> &ambientLight, const std::vector<double> &diffuseLight,
          const std::vector<double> &specularLight);

    /**
     * @brief Get name of type of Light
     *
     * @return "LIGHT" because of Light class
     */
    virtual std::string getName() const {
        return "LIGHT";
    }

    /**
     * @brief Get angle of Light
     *
     * @return 0.0
     */
    virtual double getAngle() const;

    /**
     * @brief Get vector of Light
     *
     * @return Vector3D()
     */
    virtual Vector3D getVector() const;

    /**
     * @brief Check if Light is reflective
     *
     * @return true if RGB-value of specularLight component is not zero
     */
    virtual bool isReflective() const;

    /**
     * @brief Create shadowMask for Light
     *
     * @param figures List containing figures which z-values will be added in ZBuffer
     * @param size Height and Width of ZBuffer
     */
    virtual void createShadowMask(Figures3D &figures, const int size) {
        std::ignore = figures;
        std::ignore = size;
    }

    /**
     * @brief Check if given point z-value is smaller than in shadowMask for Light object
     *
     * @param point Pixel point in eye-coordinate-system
     *
     * @return true if smaller
     */
    virtual bool checkShadowMask(const Vector3D &point) const {
        std::ignore = point;
        return false;
    }

    /**
     * @brief Get ambientLight component
     *
     * @return cc::Color object by reference as const
     */
    const cc::Color &getAmbientLight() const {
        return ambientLight;
    }

    /**
     * @brief Set ambientLight component
     *
     * @param ambientLight cc::Color object with RGB-value between 0 & 1
     */
    void setAmbientLight(const cc::Color &ambientLight) {
        this->ambientLight = ambientLight;
    }

    /**
     * @brief Get diffuseLight component
     *
     * @return cc::Color object by reference as const
     */
    const cc::Color &getDiffuseLight() const {
        return diffuseLight;
    }

    /**
     * @brief Set diffuseLight component
     *
     * @param diffuseLight cc::Color object with RGB-value between 0 & 1
     */
    void setDiffuseLight(const cc::Color &diffuseLight) {
        Light::diffuseLight = diffuseLight;
    }

    /**
     * @brief Get specularLight component
     *
     * @return cc::Color object by reference as const
     */
    const cc::Color &getSpecularLight() const {
        return specularLight;
    }

    /**
     * @brief Set specularLight component
     *
     * @param diffuseLight cc::Color object with RGB-value between 0 & 1
     */
    void setSpecularLight(const cc::Color &specularLight) {
        Light::specularLight = specularLight;
    }

    /**
     * @brief Set textureFlag bool
     *
     * @param x bool
     */
    void setTextureFlag(const bool &x) {
        Light::textureFlag = x;
    }

    /**
     * @brief Check if Light object has texture
     *
     * @return true if object has texture
     */
    const bool &isTexture() const {
        return textureFlag;
    }

    /**
     * @brief Set texture of Light object
     *
     * @param x img::EasyImage object holding texture
     */
    void setTexture(const img::EasyImage &x) {
        Light::texture = x;
    }

    /**
     * @brief Get texture
     *
     * @return img::EasyImage object by reference as const
     */
    const img::EasyImage &getTexture() const {
        return texture;
    }

    /**
     * @brief Get texture
     *
     * @return img::EasyImage object by reference
     */
    img::EasyImage &getTexture() {
        return texture;
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
     * @brief Constructor for InfLight object
     *
     * @param ambientLight Values for ambientLight component
     * @param diffuseLight Values for diffuseLight component
     * @param specularLight Values for specularLight component
     * @param ldVector Vector of InfLight
     */
    InfLight(const std::vector<double> &ambientLight, const std::vector<double> &diffuseLight,
             const std::vector<double> &specularLight, const Vector3D &ldVector);

    /**
     * @brief Get name of type of Light
     *
     * @return "INFINITY" because of InfLight class
     */
    std::string getName() const override;

    /**
     * @brief Get angle of Light
     *
     * @return 0.0
     */
    double getAngle() const override;

    /**
     * @brief Get vector of Light
     *
     * @return ldVector as Vector3D
     */
    Vector3D getVector() const override;

    /**
     * @brief Get ldVector of Light
     *
     * @return ldVector as Vector3D
     */
    const Vector3D &getLdVector() const {
        return ldVector;
    }

    /**
     * @brief Set ldVector
     *
     * @return ldVector Vector3D
     */
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
     * @brief Constructor for PointLight object
     *
     * @param ambientLight Values for ambientLight component
     * @param diffuseLight Values for diffuseLight component
     * @param specularLight Values for specularLight component
     * @param location Location of spot
     * @param spotAngle Angle of spot
     */
    PointLight(const std::vector<double> &ambientLight, const std::vector<double> &diffuseLight,
             const std::vector<double> &specularLight, const Vector3D &location, const double &spotAngle);

    /**
     * @brief Get name of type of Light
     *
     * @return "POINT" because of PointLight class
     */
    std::string getName() const override;

    /**
     * @brief Get vector
     *
     * @return location as Vector3D
     */
    Vector3D getVector() const override;

    /**
     * @brief Get angle of Light
     *
     * @return spotAngle as double
     */
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

    /**
     * @brief Create shadowMask for Light
     *
     * @param figures List containing figures which z-values will be added in ZBuffer
     * @param size Height and Width of ZBuffer
     */
    void createShadowMask(Figures3D &triangulated_figures, const int size) override;

    /**
     * @brief Fill shadowMask with given triangle
     *
     * @param size Size of shadowMask
     */
    void fillShadowMask(const Vector3D &A, const Vector3D &B, const Vector3D &C, const int size);

    /**
     * @brief Check if given point z-value is smaller than in shadowMask for Light object
     *
     * @param point Pixel point in eye-coordinate-system
     *
     * @return true if smaller
     */
    bool checkShadowMask(const Vector3D &point) const override;

};

typedef std::list<Light*> Lights3D;

#endif //ENGINE_LIGHT_H
