#ifndef GLIM_IMAGE_HPP
#define GLIM_IMAGE_HPP

#include "fwd.hpp"

#include <string>
#include <vector>

namespace glim {
class Image {
   public:
    using ColorType = Color4;

    explicit Image(usize width, usize height, const Color4 fill)
        : width{width}, height{height}, buffer(width * height, fill) {}
    explicit Image(usize width, usize height)
        : Image{width, height, Color4{}} {}

    ColorType& operator[](usize idx) noexcept { return buffer[idx]; }
    const ColorType& operator[](usize idx) const noexcept {
        return buffer[idx];
    }

    ColorType& operator()(usize column, usize row) noexcept {
        return this->operator[](column + row * width);
    }
    const ColorType& operator()(usize column, usize row) const noexcept {
        return this->operator[](column + row * width);
    }

    std::string asPPM() const;

    usize getWidth() const { return width; }
    usize getHeight() const { return height; }

    usize getSize() const { return getWidth() * getHeight(); }

   private:
    usize width, height;
    std::vector<ColorType> buffer;
};
}  // namespace glim

#endif
