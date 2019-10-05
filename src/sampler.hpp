#ifndef GLIM_SAMPLER_HPP
#define GLIM_SAMPLER_HPP

#include "fwd.hpp"
#include "image.hpp"

namespace glim {
class Scene;

class Sampler {
   public:
    struct Consumer {
        virtual ~Consumer() = default;
        virtual void finishedChunk(usize chunkIndex, usize chunkSize) = 0;
    };

    struct Config {
        usize width, height;
        usize numberOfBounces;
        usize numberOfSamples;
        usize chunkSize = 32;
    };
    explicit Sampler(const Config& config,
                     const Scene& scene,
                     Consumer* consumer = nullptr)
        : image{config.width, config.height}
        , scene{scene}
        , config{config}
        , consumer{consumer} {}

    void run();

    const Image& getImage() const { return image; }

   private:
    void runChunk(usize startIndex, usize size);

    Image image;
    std::reference_wrapper<const Scene> scene;
    Config config;
    Consumer* consumer;
};
}  // namespace glim

#endif
