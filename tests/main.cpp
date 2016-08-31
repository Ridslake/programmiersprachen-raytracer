#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <sstream>
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>

#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "material.hpp"
#include "ray.hpp"

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}


