#ifndef GLIM_SAMPLER_HPP
#define GLIM_SAMPLER_HPP

#include "fwd.hpp"
#include "image.hpp"
#include "task_queue.hpp"

namespace glim {
class Scene;

class Sampler {
   public:
    struct Consumer {
        virtual ~Consumer() = default;
        virtual void finishedChunk(const Image& image,
                                   usize chunkIndex,
                                   usize chunkSize) = 0;
    };

    struct Config {
        usize width, height;
        usize numberOfBounces;
        usize numberOfSamples;
        usize chunkSize = 32;
        usize numberOfThreads = 1;
    };
    explicit Sampler(const Config& config,
                     const Scene& scene,
                     Consumer* consumer = nullptr)
        : image{config.width, config.height}
        , scene{scene}
        , config{config}
        , consumer{consumer}
        , tasks{config.numberOfThreads} {}

    void run();

    bool finished() const { return tasks.finished(); }
    void cancel() { tasks.cancel(); }

    const Image& getImage() const { return image; }

   private:
    void runChunk(usize startIndex, usize size);

    Image image;
    std::reference_wrapper<const Scene> scene;
    Config config;
    Consumer* consumer;
    TaskQueue tasks;
};
}  // namespace glim

#endif
