#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "sphere.hpp"
#include "box.hpp"
#include "shape.hpp"
#include "ray.hpp"

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
//task 5 tests
TEST_CASE("aufgabe5","[ausgabe]")
{
  Box cus1 {"Box1", {1, 0, 0}, {1, 1, 1},{3, 2, 3}};
  Sphere cus2 {"Sphere1", {1, 0, 0}, {2, 2, 4}, 3};

  std::cout << cus1;
  std::cout << cus2; 
}
//task 6 tests
TEST_CASE("intersectRaySphere","[intersect]")
{
  glm::vec3 ray_origin{0, 0, 0};
//ray direction has to be normalized!
//you can use :
// v = glm::normalize(some_vector)
  glm::vec3 ray_direction{0, 0 ,1};
//sphere
  glm::vec3 sphere_center{0, 0, 5};
  float sphere_radius{1};

  float distance{0};
  auto result = glm::intersectRaySphere(ray_origin, ray_direction,
		sphere_center, sphere_radius * sphere_radius,
		distance);
  REQUIRE(distance == Approx(4.0f));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}


