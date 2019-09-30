#ifndef GLIM_SCENE_HPP
#define GLIM_SCENE_HPP

#include "fwd.hpp"

namespace glim {

class Ray;

struct BackgroundGradient {  // for now
    Color3 top, bottom;
};

class Scene {
   public:
    explicit Scene(BackgroundGradient background) : background{background} {}

    Color3 sample(const Ray& ray) const;

   private:
    BackgroundGradient background;
};

}  // namespace glim

#endif
