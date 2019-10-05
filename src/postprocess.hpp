#ifndef GLIM_POSTPROCESS_HPP
#define GLIM_POSTPROCESS_HPP

#include "fwd.hpp"
#include "image.hpp"

namespace glim {
namespace postprocess {

struct Gamma2 {
    static constexpr float value = 2.f;
};
template <typename Gamma = Gamma2>
struct GammaCorrect {
    static_assert(std::is_floating_point_v<decltype(Gamma::value)>);
    Image operator()(const Image& img) const {
        Image ret{img.getWidth(), img.getHeight()};
        for (usize i = 0; i < img.getSize(); ++i) {
            ret[i] = correct(img[i]);
        }
        return ret;
    }

   private:
    static Color4 correct(const Color4 inColor) {
        using GType = decltype(Gamma::value);
        constexpr GType g = GType(1) / Gamma::value;
        return Color4{std::pow(inColor.r(), g), std::pow(inColor.g(), g),
                      std::pow(inColor.b(), g), std::pow(inColor.a(), g)};
    }
};

}  // namespace postprocess
}  // namespace glim

#endif
