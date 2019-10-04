#include "object.hpp"

#include "material.hpp"
#include "ray.hpp"

#include <cm/generic_ops.hpp>

#include <atomic>

namespace glim {

namespace {
std::atomic_int nextID = 0;

bool inRange(float x, float min, float max) {
    return (min <= x) && (x <= max);
}

}  // namespace

Object::Object() : objectID{nextID++} {}

MaterialObject::MaterialObject(std::unique_ptr<Material> m)
    : material{std::move(m)} {}

MaterialObject::~MaterialObject() = default;

Scatter MaterialObject::scatter(const HitResult& hitResult) const {
    return material->scatter(hitResult.location, hitResult.fromDirection,
                             hitResult.normal);
}

Sphere::Sphere(cm::vec3 center,
               float radius,
               std::unique_ptr<Material> material)
    : MaterialObject{std::move(material)}, center{center}, radius{radius} {}
Sphere::~Sphere() = default;

std::optional<HitResult> Sphere::hit(const Ray& ray,
                                     const float minT,
                                     const float maxT) const {
    const cm::vec3 origin = ray.getOrigin();
    const cm::vec3 direction = ray.getDirection();
    const cm::vec3 originMinusCenter = origin - center;

    using cm::dot;
    const float a = dot(direction, direction);
    const float b = 2.f * dot(direction, originMinusCenter);
    const float c = dot(originMinusCenter, originMinusCenter) - radius * radius;

    const float discriminant = b * b - 4.f * a * c;
    if (discriminant > 0.f) {
        if (const float hitT = (-b - std::sqrt(discriminant)) / (2.f * a);
            inRange(hitT, minT, maxT)) {
            const cm::vec3 hitPoint = ray.pointAtT(hitT);
            const cm::vec3 normal = cm::normalized(hitPoint - center);
            return HitResult{hitPoint, direction, normal, hitT};
        }
        if (const float hitT = (-b + std::sqrt(discriminant)) / (2.f * a);
            inRange(hitT, minT, maxT)) {
            const cm::vec3 hitPoint = ray.pointAtT(hitT);
            const cm::vec3 normal = cm::normalized(hitPoint - center);
            return HitResult{hitPoint, direction, normal, hitT};
        }
    }
    return std::nullopt;
}

}  // namespace glim
