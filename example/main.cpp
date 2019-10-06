#include "WindowSamplerConsumer.hpp"

#include "fs.hpp"
#include "fwd.hpp"
#include "image.hpp"
#include "material.hpp"
#include "object.hpp"
#include "postprocess.hpp"
#include "sampler.hpp"
#include "scene.hpp"

namespace {
glim::Sampler::Config getSamplerConfig() {
    glim::Sampler::Config config;
    config.width = 1000;
    config.height = 500;
    config.numberOfBounces = 5;
    config.numberOfSamples = 500;
    config.chunkSize = 1024;
    config.numberOfThreads = 8;
    return config;
}
}  // namespace

int main() {
    using namespace glim;
    Scene scene{
          BackgroundGradient{Color3{0.5f, 0.5f, 1.f}, Color3{1.f, 0.5f, 1.f}}};
    const auto config = getSamplerConfig();
    WindowSamplerConsumer window{config.width, config.height};
    Sampler sampler{config, scene, &window};

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
    window.loop();
    if (sampler.finished()) {
        fs::write(postprocess::GammaCorrect{}(sampler.getImage()).asPPM(),
                  fs::AbsolutePath{fs::RelativePath{"image.ppm"}});
    } else {
        sampler.cancel();
    }
}
