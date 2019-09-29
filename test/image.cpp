#include <image.hpp>

#include <catch.hpp>

TEST_CASE("asPPM", "[image]") {
    constexpr const char* result = R"(P3
3 2
255
255 0 0
0 255 0
0 0 255
255 255 0
255 255 255
0 0 0
)";

    using namespace glim;
    Image img(3, 2);
    img(0, 0) = Color4{1.f, 0.f, 0.f, 1.f};
    img(1, 0) = Color4{0.f, 1.f, 0.f, 1.f};
    img(2, 0) = Color4{0.f, 0.f, 1.f, 1.f};
    img(0, 1) = Color4{1.f, 1.f, 0.f, 1.f};
    img(1, 1) = Color4{1.f, 1.f, 1.f, 1.f};
    img(2, 1) = Color4{0.f, 0.f, 0.f, 1.f};

    REQUIRE(img.asPPM() == result);
}