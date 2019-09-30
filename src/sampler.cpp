#include "sampler.hpp"

#include "ray.hpp"
#include "scene.hpp"

#include <cm/generic_ops.hpp>

namespace glim {

void Sampler::run() {
    constexpr cm::vec3 screenBottomLeft{-2.f, -1.f, -1.f};
    constexpr cm::vec3 screenTopRight{2.f, 1.f, -1.f};
    for (usize r = 0; r < image.getHeight(); ++r) {
        for (usize c = 0; c < image.getWidth(); ++c) {
            const float xf = static_cast<float>(c) / (image.getWidth() - 1);
            const float yf = static_cast<float>(r) / (image.getHeight() - 1);
            constexpr cm::vec3 origin{0.f};
            const Ray ray{
                  origin,
                  cm::vec3{
                        cm::lerp(screenBottomLeft.x(), screenTopRight.x(), xf),
                        cm::lerp(screenBottomLeft.y(), screenTopRight.y(), yf),
                        -1.f}};
            const auto color = cm::vec4{scene.get().sample(ray), 1.f};
            image(c, r) = color;
        }
    }
}

}  // namespace glim