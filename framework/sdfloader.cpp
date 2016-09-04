#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <glm/vec3.hpp>

#include "color.hpp"
#include "material.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "scene.hpp"

Scene load_sdf_file(std::string const& filename)
{
  Scene scene;
  std::string line;
  std::ifstream myfile (filename);

  if (myfile.is_open())
  {
  while (getline(myfile, line))
  {
  std::stringstream ss;
  ss << line;
  std::string keyword;
  ss>>keyword;
	
  if(keyword == "#")
  {
  continue;
  }

  if(keyword == "define")
  {
  ss>>keyword;
    if(keyword == "material")
    {
	Material mat;
	//
	ss>>mat.name;
	ss>>mat.ka.r;
	ss>>mat.ka.g;
	ss>>mat.ka.b;

	ss>>mat.kd.r;
	ss>>mat.kd.g;
	ss>>mat.kd.b;

	ss>>mat.ks.r;
	ss>>mat.ks.g;
	ss>>mat.ks.b;

	ss>>mat.m;
	//
	scene.materials.insert({mat.name, mat});
	std::cout << mat;
    }
    else if(keyword == "shape")
    {
    ss>>keyword;
	if(keyword == "box")
	{
	  std::string name;
	  std::string mat;
	  float minx,miny,minz,maxx,maxy,maxz;
          //
	  ss>>name;
	  ss>>minx;
	  ss>>miny;
	  ss>>minz;
	  ss>>maxx;
	  ss>>maxy;
	  ss>>maxz;
	  ss>>mat;
	  //
	  glm::vec3 min{minx, miny, minz};
	  glm::vec3 max{maxx, maxy, maxz};
	  //
	  std::shared_ptr<Shape> temp_ptr = std::make_shared<Box>
	  (
          Box {name, scene.materials[mat], min, max}
          );
	  //
          std::cout << *temp_ptr;
          scene.shapes_ptr.push_back(temp_ptr);
	}
	//Spehre einlesen
        if(keyword == "sphere")
	{
	  std::string name;
	  std::string mat;
          float x,y,z,r;
	  //
          ss>>name;
	  ss>>x;
	  ss>>y;
	  ss>>z;
	  ss>>r;
          ss>>mat;
	  //
	  glm::vec3 center{x,y,z};
	  //
	  std::shared_ptr<Shape> temp_ptr = std::make_shared<Sphere>
	  (
	  Sphere{name, scene.materials[mat], center, r}
	  );

	  std::cout << *temp_ptr;
	  scene.shapes_ptr.push_back(temp_ptr);
	}
    }
    else if(keyword == "light")
    {
	std::string name;
	float posx, posy, posz, ldr, ldg, ldb;
	//
	ss>>name;
	ss>>posx;
	ss>>posy;
	ss>>posz;
	ss>>ldr;
	ss>>ldg;
	ss>>ldb;
	//
	glm::vec3 pos{posx,posy,posz};
	Color ld{ldr,ldg,ldb};
	//
	scene.lights.push_back( Light(name, pos, ld));
	std::cout << "light: " << ld << "\n\n";
    }
    else if(keyword == "camera")
    {
	//Variablen von camera
	std::string name;
	float fovx, posx, posy, posz, dirx, diry, dirz, upx, upy, upz;
	//
	ss>>name;
	ss>>fovx;
	ss>>posx;
	ss>>posy;
	ss>>posz;
	ss>>dirx;
	ss>>diry;
	ss>>dirz;
	ss>>upx;
	ss>>upy;
	ss>>upz;
	//
	glm::vec3 pos{posx,posy,posz};
	glm::vec3 dir{dirx,diry,dirz};
	glm::vec3 up{upx,upy,upz};
	//
	Camera cam{name,fovx,pos,dir,up};
	std::cout << cam;
	scene.camera=cam;
    }
    else if(keyword == "renderer")
    {
	//
	ss>>keyword;
	ss>>scene.filename;
	ss>>scene.xresolution;
	ss>>scene.yresolution;
	//
	std::cout << scene.filename << "\n"
	<<"Auflösung:"<< scene.xresolution <<" x " <<
	scene.yresolution << "\n";
    }
  }
  myfile.close();
  }
  }
  else
  {
  std::cout << "Datei konnte nicht geöffnet werden!";
  }
    return scene;
}

#endif //define SDFLOADER_HPP
