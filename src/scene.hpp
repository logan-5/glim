#ifndef GLIM_SCENE_HPP
#define GLIM_SCENE_HPP

#include "fwd.hpp"
#include "object.hpp"

#include <memory>
#include <vector>

namespace glim {

class Ray;

struct BackgroundGradient {  // for now
    Color3 top, bottom;
};

class Scene {
   public:
    explicit Scene(BackgroundGradient background) : background{background} {}
    ~Scene();

    Color3 sample(const Ray& ray, int numberOfBounces) const;

    std::vector<std::unique_ptr<Object>> objects;

   private:
    Color3 sampleBackground(const Ray& ray) const;

    BackgroundGradient background;
};

}  // namespace glim

#endif
