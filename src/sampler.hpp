#ifndef GLIM_SAMPLER_HPP
#define GLIM_SAMPLER_HPP

#include "fwd.hpp"
#include "image.hpp"

namespace glim {
class Scene;

class Sampler {
   public:
    explicit Sampler(usize width,
                     usize height,
                     const Scene& scene,
                     usize numberOfBounces,
                     usize numberOfSamples)
        : image{width, height}
        , scene{scene}
        , numberOfBounces{numberOfBounces}
        , numberOfSamples{numberOfSamples} {}

    void run();

    const Image& getImage() const { return image; }

   private:
    Image image;
    std::reference_wrapper<const Scene> scene;
    usize numberOfBounces;
    usize numberOfSamples;
};
}  // namespace glim

#endif
