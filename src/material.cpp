#include "material.hpp"

#include <cm/random.hpp>

namespace glim {

Scatter Diffuse::scatter(cm::vec3 hitPoint, cm::vec3 normal) const {
    const auto nextOrigin = hitPoint;
    const auto nextDirection = normal + cm::random_in_unit_sphere();
    return Scatter{
          Ray{nextOrigin, nextDirection},
          this->color,
    };
}

}  // namespace glim