#include "fs.hpp"
#include "fwd.hpp"
#include "image.hpp"

int main() {
    glim::Image img{100, 100, glim::Color4{1.f, 0.f, 1.f, 1.f}};
    glim::fs::write(img.asPPM(), glim::fs::AbsolutePath{
                                       glim::fs::RelativePath{"image.ppm"}});
}
