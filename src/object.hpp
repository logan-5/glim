#ifndef GLIM_OBJECT_HPP
#define GLIM_OBJECT_HPP

#include "fwd.hpp"

#include <optional>

namespace glim {
class Ray;

class Object {
   public:
    virtual ~Object() = default;
    virtual std::optional<Color3> hit(const Ray& r) const = 0;
};

class Sphere : public Object {
   public:
    explicit Sphere(cm::vec3 center, float radius, Color3 color)
        : center{center}, radius{radius}, color{color} {}

    std::optional<Color3> hit(const Ray&) const override;

   private:
    cm::vec3 center;
    float radius;
    Color3 color;
};

}  // namespace glim

#endif
