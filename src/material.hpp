#ifndef GLIM_MATERIAL_HPP
#define GLIM_MATERIAL_HPP

#include "fwd.hpp"
#include "ray.hpp"

namespace glim {

struct Scatter {
    Ray next;
    Color3 attenuation;
};

class Material {
   public:
    virtual ~Material() = default;

    virtual Scatter scatter(cm::vec3 hitPoint,
                            cm::vec3 hitDirection,
                            cm::vec3 normal) const = 0;
};

class Diffuse : public Material {
   public:
    explicit Diffuse(Color3 color) : color{color} {}

    Scatter scatter(cm::vec3 hitPoint,
                    cm::vec3 hitDirection,
                    cm::vec3 normal) const override;

   private:
    Color3 color;
};

class Metal : public Material {
   public:
    explicit Metal(Color3 color) : color{color} {}

    Scatter scatter(cm::vec3 hitPoint,
                    cm::vec3 hitDirection,
                    cm::vec3 normal) const override;

   private:
    Color3 color;
};

}  // namespace glim

#endif
