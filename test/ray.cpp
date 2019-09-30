#include <ray.hpp>

#include <catch.hpp>

using glim::Ray;

TEST_CASE("getters", "[ray]") {
    Ray r{cm::vec3{0.f, 0.f, 0.f}, cm::vec3{10.f, 10.f, 10.f}};

    REQUIRE(r.getOrigin() == cm::vec3{0.f});
    REQUIRE(r.getDirection() == cm::normalized(cm::vec3{10.f}));
}

TEST_CASE("pointAtT", "[ray]") {
    Ray r{{0.f}, {1.f, 0.f, 0.f}};

    REQUIRE(r.pointAtT(0.f) == r.getOrigin());
    REQUIRE(r.pointAtT(0.25f) == cm::vec3{0.25f, 0.f, 0.f});
    REQUIRE(r.pointAtT(1.f) == r.getDirection());

    r = Ray{{0.f}, {0.f, 1.f, 0.f}};
    REQUIRE(r.pointAtT(0.f) == r.getOrigin());
    REQUIRE(r.pointAtT(0.75f) == cm::vec3{0.f, 0.75f, 0.f});
    REQUIRE(r.pointAtT(1.f) == r.getDirection());
}