#include "scene.hpp"

#include "material.hpp"
#include "ray.hpp"

#include <cm/generic_ops.hpp>

#include <vector>

namespace glim {

Scene::~Scene() = default;

Color3 Scene::sampleBackground(const Ray& ray) const {
    return cm::lerp(background.bottom, background.top,
                    cm::linearstep(-1.f, 1.f, ray.getDirection().y()));
}

Color3 Scene::sample(const Ray& ray, int numberOfBounces) const {
    if (numberOfBounces == 0) {
        return sampleBackground(ray);
    }
    struct HitPair {
        HitResult hit;
        Object* object;
    };
    std::vector<HitPair> hits;
    for (auto& object : objects) {
        if (auto hit = object->hit(ray, 0.0001f,
                                   std::numeric_limits<float>::max())) {
            hits.push_back({*std::move(hit), object.get()});
        }
    }
    if (hits.empty()) {
        return sampleBackground(ray);
    }
    const auto& hitP = *std::min_element(
          hits.begin(), hits.end(),
          [](const HitPair& a, const HitPair& b) { return a.hit.t < b.hit.t; });
    const Scatter s = hitP.object->scatter(hitP.hit);
    hits = {};
    return s.attenuation * sample(s.next, numberOfBounces - 1);
}

}  // namespace glim
