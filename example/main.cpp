#include "fs.hpp"
#include "fwd.hpp"
#include "image.hpp"
#include "material.hpp"
#include "object.hpp"
#include "sampler.hpp"
#include "scene.hpp"

int main() {
    using namespace glim;
    Scene scene{
          BackgroundGradient{Color3{0.8f, 0.4f, 0.8f}, Color3{1.f, 1.f, 0.f}}};
    Sampler sampler{1000, 500, scene, 5, 500};

    auto blueSteel = std::make_unique<Metal>(Color3{0.3f, 0.5f, 1.f}, 0.025f);
    auto red = std::make_unique<Diffuse>(Color3{1.f, 0.5f, 0.5f});
    auto green = std::make_unique<Diffuse>(Color3{0.5f, 1.f, 0.5f});
    scene.objects.push_back(std::make_unique<Sphere>(
          cm::vec3{-1.f, 0.f, -2.f}, 1.f, std::move(blueSteel)));
    scene.objects.push_back(std::make_unique<Sphere>(cm::vec3{1.f, 0.f, -2.f},
                                                     1.f, std::move(red)));
    scene.objects.push_back(std::make_unique<Plane>(cm::vec3{0.f, -1.f, -2.f},
                                                    cm::vec3{0.f, 1.f, 0.f},
                                                    std::move(green)));
    sampler.run();
    fs::write(sampler.getImage().asPPM(),
              fs::AbsolutePath{fs::RelativePath{"image.ppm"}});
}
