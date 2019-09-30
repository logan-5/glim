#include "object.hpp"

#include "ray.hpp"

namespace glim {

std::optional<Color3> Sphere::hit(const Ray& ray) const {
    const auto origin = ray.getOrigin();
    const auto direction = ray.getDirection();
    const auto originMinusCenter = origin - center;

    using cm::dot;
    const auto a = dot(direction, direction);
    const auto b = 2.f * dot(direction, originMinusCenter);
    const auto c = dot(originMinusCenter, originMinusCenter) - radius * radius;

    const auto discriminant = b * b - 4.f * a * c;
    if (discriminant < 0.f) {
        return std::nullopt;
    }
    return color;
}

}  // namespace glim
