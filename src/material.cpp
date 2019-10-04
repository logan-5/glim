#include "material.hpp"

#include <cm/random.hpp>
#include <cm/vec_ops.hpp>

namespace glim {

Scatter Diffuse::scatter(cm::vec3 hitPoint,
                         cm::vec3 hitDirection,
                         cm::vec3 normal) const {
    (void)hitDirection;
    const auto nextOrigin = hitPoint;
    const auto nextDirection = normal + cm::random_in_unit_sphere();
    return Scatter{
          Ray{nextOrigin, nextDirection},
          this->color,
    };
}

Scatter Metal::scatter(cm::vec3 hitPoint,
                       cm::vec3 hitDirection,
                       cm::vec3 normal) const {
    const auto nextOrigin = hitPoint;
    const auto nextDirection = cm::bounce(hitDirection, normal) +
                               cm::random_on_unit_sphere() * roughness;
    return Scatter{
          Ray{nextOrigin, nextDirection},
          this->color,
    };
}

}  // namespace glim