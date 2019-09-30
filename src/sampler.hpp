#ifndef GLIM_SAMPLER_HPP
#define GLIM_SAMPLER_HPP

#include "fwd.hpp"
#include "image.hpp"

namespace glim {
class Scene;

class Sampler {
   public:
    explicit Sampler(usize width, usize height, const Scene& scene)
        : image{width, height}, scene{scene} {}

    void run();

    const Image& getImage() const { return image; }

   private:
    Image image;
    std::reference_wrapper<const Scene> scene;
};
}  // namespace glim

#endif
