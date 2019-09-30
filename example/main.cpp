#include "fs.hpp"
#include "fwd.hpp"
#include "image.hpp"
#include "object.hpp"
#include "sampler.hpp"
#include "scene.hpp"

int main() {
    using namespace glim;
    Scene scene{{Color3{1.f, 1.f, 0.f}, Color3{1.f, 0.f, 1.f}}};
    Sampler sampler{200, 100, scene};
    scene.objects.push_back(std::make_unique<Sphere>(
          cm::vec3{-1.f, 0.f, -2.f}, 1.f, Color3{0.f, 0.f, 1.f}));
    scene.objects.push_back(std::make_unique<Sphere>(
          cm::vec3{1.f, 0.f, -2.f}, 1.f, Color3{0.f, 1.f, 0.f}));
    sampler.run();
    fs::write(sampler.getImage().asPPM(),
              fs::AbsolutePath{fs::RelativePath{"image.ppm"}});
}
