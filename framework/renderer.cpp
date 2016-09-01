// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include <math.h>
#include "renderer.hpp"
#include "scene.hpp"
#include "camera.hpp"

//Erstellt uns das Bild mit Color und Höhe und Breit (x,y)
//C
Renderer::Renderer():
    scene_{},
    colorbuffer_(scene_.xresolution*scene_.yresolution, Color{}),
    ppm_(scene_.xresolution, scene_.yresolution, "default.ppm")
    {}

Renderer::Renderer(Scene scene):
    scene_{scene},
    colorbuffer_(scene.xresolution*scene.yresolution, Color{}),
    ppm_(scene.xresolution, scene.yresolution, scene.filename)
    {}


void Renderer::render()
{
    //Camera distance mit Field of view
    float pic_ymax = 2/scene_.xresolution*scene_.yresolution;
    float distance = 1/tan((scene_.camera.getcamfovx()*M_PI)/180);
    //Skalierung des Bildes
    int height_= scene_.yresolution;
    int width_= scene_.xresolution;

    float h = -height_/2;

    for (unsigned y = 0; y < height_; ++y) {
            float w = -width_/2;
        for (unsigned x = 0; x < width_; ++x) {

	    //INternetformel
            glm::vec3 eineRichtung {w/(width_/2),h/(height_/2), -distance};
            Ray camray = scene_.camera.castray(eineRichtung);
            Pixel p(x,y);
            Shape* first_hit;
            double shortest = 1;
	}
    }
          
    //Dem Bild einen Namen geben
    ppm_.save(scene_.filename);
    std::cout << "Bild erstellt:" << scene_.filename << "RaytracerX  \n";

}//Unfertig, keine Funktionen, sollte zu Schatten gehören
Color Renderer::shade(Ray const& ray, Hit const& hit){
    Color ka = hit.sptr_->get_material().ka;
    Color kd = hit.sptr_->get_material().kd;
    Color ks = hit.sptr_->get_material().ks;
    Color Ia = scene_.amblight;
    Color Light_amb = Ia * ka;
    Color Id;
    Color Light_diff_spec;
    Color Light_gesamt;

    float winkelA;
    float winkelB;

    std::vector<Color> Id_vec;
    std::vector<float> a1_vec;
    std::vector<float> a2_vec;

    glm::vec3 norm = glm::normalize(hit.normal_);
    glm::vec3 ray_inv_direction = glm::normalize(-ray.direction);
   
  }

//Renderer für Pixel
void Renderer::write(Pixel const& p)
{
    size_t buf_pos = (scene_.xresolution*p.y + p.x);
    if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
        std::cerr << "Render Error: "
            << "Pixel ausserhalb ppm"
            << (int)p.x << "," << (int)p.y
            << std::endl;
    	} 
	else {
        colorbuffer_[buf_pos] = p.color;
    }
    ppm_.write(p);
}





