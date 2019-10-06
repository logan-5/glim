#include "sampler.hpp"

#include "ray.hpp"
#include "scene.hpp"
#include "task_queue.hpp"

#include <cm/generic_ops.hpp>
#include <cm/random.hpp>

namespace glim {

void Sampler::run() {
    const usize numberOfChunks = (image.getSize() / config.chunkSize) + 1;
    for (usize i = 0; i < numberOfChunks; ++i) {
        const usize idx = i * config.chunkSize;
        const usize size = config.chunkSize;
        tasks.enqueue([=] {
            runChunk(i * config.chunkSize, config.chunkSize);
            if (consumer) {
                consumer->finishedChunk(image, idx, size);
            }
        });
    }
}

void Sampler::runChunk(usize startIndex, usize size) {
    constexpr cm::vec3 screenTopLeft{-2.f, 1.f, -1.f};
    constexpr cm::vec3 screenBottomRight{2.f, -1.f, -1.f};

    const usize end = std::min(startIndex + size, image.getSize());
    for (usize i = startIndex; i < end; ++i) {
        const usize r = i / config.width;
        const usize c = i % config.width;
        cm::vec3 color{0.f};
        for (usize s = 0; s < config.numberOfSamples; ++s) {
            const float xf =
                  (static_cast<float>(c) + cm::random_real(-1.f, 1.f)) /
                  (image.getWidth() - 1);
            const float yf =
                  (static_cast<float>(r) + cm::random_real(-1.f, 1.f)) /
                  (image.getHeight() - 1);
            constexpr cm::vec3 origin{0.f};
            const Ray ray{
                  origin,
                  cm::vec3{
                        cm::lerp(screenTopLeft.x(), screenBottomRight.x(), xf),
                        cm::lerp(screenTopLeft.y(), screenBottomRight.y(), yf),
                        -1.f}};

            color += scene.get().sample(ray, config.numberOfBounces);
        }
        image(c, r) = cm::vec4{color * (1.f / config.numberOfSamples), 1.f};
    }
}

}  // namespace glim
