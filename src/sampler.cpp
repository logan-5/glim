#include "sampler.hpp"

#include "ray.hpp"
#include "scene.hpp"

#include <cm/generic_ops.hpp>
#include <cm/random.hpp>

namespace glim {

void Sampler::run() {
    constexpr cm::vec3 screenTopLeft{-2.f, 1.f, -1.f};
    constexpr cm::vec3 screenBottomRight{2.f, -1.f, -1.f};
    for (usize r = 0; r < image.getHeight(); ++r) {
        for (usize c = 0; c < image.getWidth(); ++c) {
            cm::vec3 color{0.f};
            for (usize s = 0; s < numberOfSamples; ++s) {
                const float xf =
                      (static_cast<float>(c) + cm::random_real(-1.f, 1.f)) /
                      (image.getWidth() - 1);
                const float yf =
                      (static_cast<float>(r) + cm::random_real(-1.f, 1.f)) /
                      (image.getHeight() - 1);
                constexpr cm::vec3 origin{0.f};
                const Ray ray{origin,
                              cm::vec3{cm::lerp(screenTopLeft.x(),
                                                screenBottomRight.x(), xf),
                                       cm::lerp(screenTopLeft.y(),
                                                screenBottomRight.y(), yf),
                                       -1.f}};

                color += scene.get().sample(ray, numberOfBounces);
            }
            image(c, r) = cm::vec4{color * (1.f / numberOfSamples), 1.f};
        }
    }
}

}  // namespace glim