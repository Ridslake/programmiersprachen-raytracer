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
    scene_(),
    colorbuffer_(scene_.xresolution*scene_.yresolution, Color{}),
    ppm_(scene_.xresolution, scene_.yresolution, "default.ppm")
    {}

Renderer::Renderer(Scene const& scene, float depth):
    scene_(scene),
    colorbuffer_(scene.xresolution*scene.yresolution, Color{}),
    ppm_(scene.xresolution, scene.yresolution, scene.filename),
    depth (depth)
    {}


void Renderer::render()
{
    //Camera distance mit Field of view
    float pic_ymax = 2/scene_.xresolution*scene_.yresolution;
    float distance = 1/tan((scene_.camera.angle()*M_PI)/180);
    //Skalierung des Bildes
    int height_= scene_.yresolution;
    int width_= scene_.xresolution;

    float h = -height_/2;

    for (unsigned y = 0; y < height_; ++y)
    {
	float w = -width_/2;
        
	for (unsigned x = 0; x < width_; ++x)
	{
	  //INternetformel
          glm::vec3 eineRichtung {w/(width_/2),h/(height_/2), -distance};
          Ray camray = scene_.camera.castray(eineRichtung);
          Pixel p(x,y);

	  p.color = trace(camray);

	  write(p);

	}
    }          
    ppm_.save(scene_.filename);
    std::cout << "Bild erstellt:" << scene_.filename << "RaytracerX  \n";
}

Color Renderer::trace(Ray const& ray)
{
  Shape* first_hit;
  Color pc;
  double shortest = 999999.9;

  for (std::vector<std::shared_ptr<Shape>>::iterator i = scene_.shapes_ptr.begin();
  i != scene_.shapes_ptr.end();++i)
  {
    Hit hit = (*i)->intersect(ray);
	if(hit.hit_ == true)
	{
	  if(hit.distance_ < shortest)
	  {
	  shortest = hit.distance_;
	  first_hit = hit.sptr_;
	  pc = shade(ray, hit, depth);
	  }
	}
	  if(shortest == 999999.9)
	  {
	  pc = scene_.background;
	  }
  }
  depth=0;
  return pc;
}

Color Renderer::shade(Ray const& ray, Hit const& hit, float depth_)
{
  Color ka = hit.sptr_->get_material().ka;
  Color kd = hit.sptr_->get_material().kd;
  Color ks = hit.sptr_->get_material().ks;

  Color Ia = scene_.amblight;
    Color L_amb = Ia * ka;
    Color Id;
    Color L_diff_spec;
    Color L_gesamt;

    float angle1;
    float angle2;
    float shadowbias = 0.0009f;

    std::vector<Color> Id_vec;
    std::vector<float> a1_vec;
    std::vector<float> a2_vec;

    glm::vec3 norm = glm::normalize(hit.normal_);
    glm::vec3 rref;
    glm::vec3 ray_inv_dir = glm::normalize(-ray.direction);

    for (std::vector<Light>::iterator i = scene_.lights.begin();i != scene_.lights.end();++i){
        glm::vec3 lightvec = glm::normalize(glm::vec3{ i->lightpos - hit.target_ });


        Ray lightray{hit.target_ + (shadowbias*norm), lightvec};


            for (std::vector<std::shared_ptr<Shape>>::iterator j = scene_.shapes_ptr.begin();j != scene_.shapes_ptr.end();++j){
                Hit shadowhit = (*j)->intersect(lightray);

                if(shadowhit.hit_ && shadowhit.distance_ < sqrt(pow(lightvec.x, 2) + pow(lightvec.y, 2) + pow(lightvec.z,2))){
                    Id = {0.0,0.0,0.0};
                    angle1 = 0.0;
                    angle2 = 0.0;

                    break;
                }

                else
		{

                    Id = i->ld;
                    angle1 = std::max(0.0f, glm::dot(norm, lightvec));

                    rref = 2.0f * angle1 * norm - lightvec;
                    angle2 = std::max(0.0f, glm::dot(rref, ray_inv_dir));

                }
            }

            Id_vec.push_back(Id);

            a1_vec.push_back(angle1);
            a2_vec.push_back(pow(angle2, hit.sptr_->get_material().m));

            Id = {0.0,0.0,0.0};
            angle1 = 0.0;
            angle2 = 0.0;
            lightvec = {0.0,0.0,0.0};
    }

    for(int t = 0; t < Id_vec.size(); ++t)
    {
        L_diff_spec = L_diff_spec + (Id_vec[t]*((kd*a1_vec[t]) + (ks*a2_vec[t])));

    }

    if (hit.sptr_->get_material().reflc > 0.0f && depth > 0)
    {
        --depth;
        float  angle3=glm::dot(norm,ray_inv_dir);
        glm::vec3 reflectionvec = 2.0f * angle3 * norm - ray_inv_dir;
        Ray reflectionray{hit.target_ + (glm::normalize(hit.normal_) * shadowbias),reflectionvec};
        Color reflectioncolor;
        reflectioncolor=trace(reflectionray);
        reflectioncolor=reflectioncolor * hit.sptr_->get_material().reflc;
        L_diff_spec=L_diff_spec*(1-hit.sptr_->get_material().reflc)+reflectioncolor;

    L_gesamt = L_diff_spec + L_amb;
    return L_gesamt;
    }

    L_gesamt = L_diff_spec + L_amb;
    return L_gesamt;

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
