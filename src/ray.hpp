#ifndef GLIM_RAY_HPP
#define GLIM_RAY_HPP

#include "fwd.hpp"

namespace glim {
class Ray {
   public:
    explicit Ray(cm::vec3 origin, cm::vec3 direction)
        : origin{origin}, direction{cm::normalized(direction)} {}

    cm::vec3 getOrigin() const noexcept { return origin; }
    cm::vec3 getDirection() const noexcept { return direction; }
    cm::vec3 pointAtT(float t) const noexcept { return origin + direction * t; }

   private:
    cm::vec3 origin, direction;
};
}  // namespace glim

#endif
