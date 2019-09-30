#include "scene.hpp"

#include "ray.hpp"

#include <cm/generic_ops.hpp>

namespace glim {

Color3 Scene::sample(const Ray& ray) const {
    return cm::lerp(background.bottom, background.top,
                    cm::linearstep(-1.f, 1.f, ray.getDirection().y()));
}

}  // namespace glim
