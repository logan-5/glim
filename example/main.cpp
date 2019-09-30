#include "fs.hpp"
#include "fwd.hpp"
#include "image.hpp"
#include "sampler.hpp"
#include "scene.hpp"

int main() {
    glim::Scene scene{
          {glim::Color3{1.f, 1.f, 0.f}, glim::Color3{1.f, 0.f, 1.f}}};
    glim::Sampler sampler{200, 100, scene};
    sampler.run();
    glim::fs::write(
          sampler.getImage().asPPM(),
          glim::fs::AbsolutePath{glim::fs::RelativePath{"image.ppm"}});
}
