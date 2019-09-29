#include "image.hpp"

namespace glim {
namespace {
std::string ppmHeader(usize width, usize height) {
    std::string header = "P3\n";
    header += std::to_string(width);
    header += ' ';
    header += std::to_string(height);
    header += '\n';
    header += "255\n";
    return header;
}
}  // namespace
std::string Image::asPPM() const {
    std::string ppm = ppmHeader(width, height);
    constexpr usize channels = 3;

    for (usize r = 0; r < height; ++r) {
        for (usize c = 0; c < width; ++c) {
            const ColorType& pixel = (*this)(c, r);
            for (usize i = 0; i < channels; ++i) {
                ppm += std::to_string(static_cast<int>(pixel[i]) * 255);
                ppm += (i + 1 == channels) ? '\n' : ' ';
            }
        }
    }

    return ppm;
}
}  // namespace glim