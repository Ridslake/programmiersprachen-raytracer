// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP
#include <glm/glm.hpp>

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "scene.hpp"
#include "camera.hpp"

const unsigned maxdepth = 3;

class Renderer
{
public:
  Renderer();
  Renderer(Scene const& scene);

  void render();
  void write(Pixel const& p);

  Color trace(Ray const& ray);
  Color shade(Ray const& ray, Hit const& hit, float depth);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

  int depth = 0;
private:
  std::vector<Color> colorbuffer_;
  PpmWriter ppm_;
  Scene scene_;
};

#endif // #ifndef BUW_RENDERER_HPP
