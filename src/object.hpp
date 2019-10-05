#ifndef GLIM_OBJECT_HPP
#define GLIM_OBJECT_HPP

#include "fwd.hpp"

#include <optional>

namespace glim {

class Material;
class Ray;
struct Scatter;

struct HitResult {
    HitResult(cm::vec3 location, cm::vec3 direction, cm::vec3 normal, float t)
        : location{location}
        , fromDirection{cm::normalized(direction)}
        , normal{normal}
        , t{t} {}
    cm::vec3 location;
    cm::vec3 fromDirection;
    cm::vec3 normal;
    float t;
};

class Object {
   public:
    Object();
    virtual ~Object() = default;
    virtual std::optional<HitResult> hit(const Ray& r,
                                         float minT,
                                         float maxT) const = 0;
    virtual Scatter scatter(const HitResult& hit) const = 0;

    int getID() const { return objectID; }

   protected:
    int objectID;
};

class MaterialObject : public Object {
   public:
    explicit MaterialObject(std::unique_ptr<Material> m);
    ~MaterialObject() override;

    Scatter scatter(const HitResult& hit) const override;

   protected:
    std::unique_ptr<Material> material;
};

class Sphere final : public MaterialObject {
   public:
    explicit Sphere(cm::vec3 center,
                    float radius,
                    std::unique_ptr<Material> material);

    std::optional<HitResult> hit(const Ray&,
                                 float minT,
                                 float maxT) const override;

   private:
    cm::vec3 center;
    float radius;
};

class Plane : public MaterialObject {
   public:
    explicit Plane(cm::vec3 point,
                   cm::vec3 normal,
                   std::unique_ptr<Material> material);

    explicit Plane(cm::vec3 a,
                   cm::vec3 b,
                   cm::vec3 c,
                   std::unique_ptr<Material> m);

    std::optional<HitResult> hit(const Ray&,
                                 const float minT,
                                 const float maxT) const override;

   private:
    cm::vec3 point;
    cm::vec3 normal;
};

}  // namespace glim

#endif
