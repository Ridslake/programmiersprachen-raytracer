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

//Rendern, ray durch jedes Pixel um die Farbe jedes Pixels zu bekommen
void Renderer::render()
{
  //360 anstatt von 180
  float distance = 1/tan((scene_.camera.getcamfovx()*M_PI)/360);
  int height_= scene_.yresolution;
  int width_= scene_.xresolution;
  float h = height_/2;

  for (unsigned y = 0; y < height_; ++y)
  {
    float w = width_/2;    
    for (unsigned x = 0; x < width_; ++x)
    {
    Pixel p(x,y);
	//Antialiasing
	for(float i = 0.0f; i < 1.0f; i += 0.5f)
	{
	  for(float j = 0.0f; j < 1.0f; j += 0.5f)
	  {
	    //(float)x, x wird zum float umgewandelt
	    float xa = (float)x + i;
	    float ya = (float)y + j;
	    
	    glm::vec3 Direction{(xa - w)/width_, (ya - h)/width_, -distance};
	    Ray camray = scene_.camera.castray(Direction);
	    Color coloraa = raytrace(camray);
	    p.color += coloraa * 0.25f;
	  }
	} 	
	write(p);
    }
  }          
  ppm_.save(scene_.filename);
  std::cout << "Bild erstellt:" << scene_.filename << "\n";
}

Color Renderer::raytrace(Ray const& ray)
{
  Hit first_hit;
  Color pc;
  double shortest = 999999.9; //std Wert

  //über die shapes iterieren und auf hit prüfen
  for (std::vector<std::shared_ptr<Shape>>::iterator i = scene_.shapes_ptr.begin();
  i != scene_.shapes_ptr.end();++i)
  {
    Hit hit = (*i)->intersect(ray);
	if(hit.hit_ == true)
	{
	  if(hit.distance_ < shortest)
	  {
	  shortest = hit.distance_;
	  first_hit = hit;
	  }
	}
  }
  //Falls nichts getroffen wird
  if(shortest == 999999.9)
  {
  pc = scene_.background;
  }
  //Falls etwas getroffen wird ermittle Color über shades
  else
  {
  pc = shades(ray, first_hit, depth);
  }
  return pc;
}

Color Renderer::shades(Ray const& ray, Hit const& hit, float depth_)
{
  //Material
  Color ka = hit.sptr_->get_material().ka;
  Color kd = hit.sptr_->get_material().kd;
  Color ks = hit.sptr_->get_material().ks;
  //Lichtfarbe
  Color Ia = scene_.amblight;
  Color L_amb = Ia * ka;
  Color Id;
  Color L_diff_spec;
  Color L_gesamt;
  //Winkel für Lichtreflexion
  float angle1;
  float angle2;
  //shadowbias, wird benutzt um vom Schnittpunkt "wegzukommen"
  //0.01 scheint ein guter Wert zu sein, da bei anderen Werten es zu Fehlern kommt
  //aber nur bei den Spheres, die Box scheint unbeinträchtigt
  float shadowbias = 0.01f;

  std::vector<Color> Id_vec;
  std::vector<float> a1_vec;
  std::vector<float> a2_vec;

  glm::vec3 norm = glm::normalize(hit.normal_);
  glm::vec3 rref;
  glm::vec3 ray_inv_dir = glm::normalize(-ray.direction);

  //Über die Lichter iterieren
  for (std::vector<Light>::iterator i = scene_.lights.begin();
  i != scene_.lights.end();++i)
  {
    //Richtungsvektor zum Licht
    glm::vec3 lightvec = glm::normalize(glm::vec3{ i->lightpos - hit.target_ });

    //Vektor vom Schnittpunkt zur Lichtquelle für Schattenüberprüfung Schnittpunkt entlang des NormVektors verschoben
    Ray lightray{hit.target_ + (shadowbias*norm), lightvec};

    //Überprüfung Schatten,über shapes iterieren
    for (std::vector<std::shared_ptr<Shape>>::iterator j
    = scene_.shapes_ptr.begin();j != scene_.shapes_ptr.end();++j)
    {
	Hit shadowhit = (*j)->intersect(lightray);
	//Abbruchbedingung um zu langes tracing zu verhindern
	if(shadowhit.hit_ && shadowhit.distance_ <
	sqrt(pow(lightvec.x, 2) + pow(lightvec.y, 2) + pow(lightvec.z,2)))
	{
	  Id = {0.0,0.0,0.0};
	  angle1 = 0.0;
	  angle2 = 0.0;
	  break;
	}

	else
	{
	  Id = i->ld;
	  angle1 = std::max(0.0f, glm::dot(norm, lightvec));
	  //Spiegelnde/Spekulare Reflexion l+r = 2(n*l)*n
	  rref = 2.0f * angle1 * norm - lightvec;
	  angle2 = std::max(0.0f, glm::dot(rref, ray_inv_dir));
	}
    }

    Id_vec.push_back(Id);

    a1_vec.push_back(angle1);
    a2_vec.push_back(pow(angle2, hit.sptr_->get_material().m));
    //Alles zurück auf Null setzen damit for von 0 anfängt.
    Id = {0.0,0.0,0.0};
    angle1 = 0.0;
    angle2 = 0.0;
    lightvec = {0.0,0.0,0.0};
  }

  for(int t = 0; t < Id_vec.size(); ++t)
  {
    L_diff_spec = L_diff_spec + (Id_vec[t]*((kd*a1_vec[t]) + (ks*a2_vec[t])));
  }

  //Reflektion des Lichts, maximal 3 mal gespiegelt, nur wenn Material einen solchen 
  //Wert hat
  if (hit.sptr_->get_material().reflc > 0.0f && depth > 0)
  {
    --depth; //maximale Spiegelung (in raytracer cpp festgelegt, = 3)
    float angle3 = glm::dot(norm, ray_inv_dir);
    //Richtung des reflektierten Lichts
    glm::vec3 reflectionvec = 2.0f * angle3 * norm - ray_inv_dir;
    //Reflectierter Ray
    Ray reflectionray{hit.target_ + (glm::normalize(hit.normal_) *
    shadowbias), reflectionvec};
    Color reflectioncolor;
    //Um Farbe zu ermitteln
    reflectioncolor = raytrace(reflectionray);
    reflectioncolor = reflectioncolor * hit.sptr_->get_material().reflc;
    L_diff_spec = L_diff_spec*(1-hit.sptr_->get_material().reflc)+reflectioncolor;
    //Sollte Material reflektieren wird dies zum Gesamtlicht hinzugefügt
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
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0)
  {
    std::cerr
    << "Render Error: "
    << "Pixel ausserhalb ppm"
    << (int)p.x << "," << (int)p.y
    << std::endl;
  } 
  else
  {
    colorbuffer_[buf_pos] = p.color;
  }
  ppm_.write(p);
}
