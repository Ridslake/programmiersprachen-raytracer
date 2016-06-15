#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "sphere.hpp"
#include "box.hpp"
#include "shape.hpp"

//sphere tests
TEST_CASE("Spheredefault","[spheredefault]")
{
  Sphere def;
  glm::vec3 center_default{0, 0, 0};

  REQUIRE(glm::all (glm::equal(def.get_spherecenter(), center_default)));
  REQUIRE(def.get_sphereradius() == Approx(0));
  REQUIRE(def.volume() == Approx(0));
  REQUIRE(def.area() == Approx(0));
}

TEST_CASE("Spherecustom","[spherecustom]")
{
  Sphere cus {"Sphere1", {1, 0, 0}, {2, 2, 4}, 3};
  glm::vec3 center_custom{2, 2, 4};
  Color color_red{1, 0, 0};

  REQUIRE(glm::all (glm::equal(cus.get_spherecenter(), center_custom)));
  REQUIRE(cus.get_sphereradius() == Approx(3));
  REQUIRE(cus.volume() == Approx(4/3*M_PI*3*3*3));
  REQUIRE(cus.area() == Approx(4*M_PI*3*3));

}

//box tests
TEST_CASE("Boxdefault","[Boxdefault]")
{
  Box def;
  glm::vec3 min_default{0, 0, 0};
  glm::vec3 max_default{0, 0, 0};

  REQUIRE(glm::all (glm::equal(def.get_boxmin(), min_default)));
  REQUIRE(glm::all (glm::equal(def.get_boxmax(), max_default)));
  REQUIRE(def.volume() == Approx(0));
  REQUIRE(def.area() == Approx(0));
}

TEST_CASE("Boxcustom","[Boxcustom]")
{
  Box cus {"Box1", {1, 0, 0}, {1, 1, 1},{3, 2, 3}};
  glm::vec3 min_custom{1, 1, 1};
  glm::vec3 max_custom{3, 2, 3};
  Color color_red{1, 0, 0};

  REQUIRE(glm::all (glm::equal(cus.get_boxmin(), min_custom)));
  REQUIRE(glm::all (glm::equal(cus.get_boxmax(), max_custom)));
  REQUIRE(cus.volume() == Approx(4));
  REQUIRE(cus.area() == Approx(16));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
