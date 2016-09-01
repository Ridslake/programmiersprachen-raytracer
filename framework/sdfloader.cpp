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
  while (getline(myfile,line))
  {
  std::stringstream ss;
  ss << line;
  std::string keyword;
  ss>>keyword;
	
  if(keyword == "#")
  {
  continue;
  }

//material, name, ka, kd, ks input
  if(keyword == "define")
  {
  ss>>keyword;
    if(keyword == "material")
    {
	Material mat;
	ss>>mat.name;
	//ka
	ss>>mat.ka.r;
	ss>>mat.ka.g;
	ss>>mat.ka.b;
	//kd
	ss>>mat.kd.r;
	ss>>mat.kd.g;
	ss>>mat.kd.b;
	//ks
	ss>>mat.ks.r;
	ss>>mat.ks.g;
	ss>>mat.ks.b;
	//Exponent
	ss>>mat.m;

	scene.materials.insert({mat.name, mat});
	//materials[mat.name]= mat;
	std::cout << mat;
    }
    else if(keyword == "shape")
    {
    ss>>keyword;
	//Box einlesen
	if(keyword == "box")
	{
	  //Variablen von Box
	  std::string name;
	  std::string mat_namebox;
	  float minx,miny,minz,maxx,maxy,maxz;
          //Das wird eingelesen //Name
	  ss>>name;
	  //minimum
	  ss>>minx;
	  ss>>miny;
	  ss>>minz;
          //maximum
	  ss>>maxx;
	  ss>>maxy;
	  ss>>maxz;
	  //floats in vec3
	  glm::vec3 min{minx, miny, minz};
	  glm::vec3 max{maxx, maxy, maxz};
	  //Name des Materials
	  ss>>mat_namebox;
	  //shared pointer fuer die Box
	  std::shared_ptr<Shape> temp_ptr = std::make_shared<Box>
	  (
          Box {name, scene.materials[mat_namebox], min, max}
          );

          std::cout << *temp_ptr;
          scene.shapes_ptr.push_back(temp_ptr);
	}
	//Spehre einlesen
        if(keyword == "sphere")
	{
	  //Variablen von sphere
	  std::string name;
	  std::string mat_namesphere;
          float x,y,z,r;
	  //name, center
          ss>>name;
	  ss>>x;
	  ss>>y;
	  ss>>z;
	  //floats in vec3
	  glm::vec3 center{x,y,z};
	  //radius
	  ss>>r;
	  //Name des Materials
	  ss>>mat_namesphere;
	  //shared pointer fuer die Sphere
	  std::shared_ptr<Shape> temp_ptr = std::make_shared<Sphere>
	  (
	  Sphere{name,scene.materials[mat_namesphere],center,r}
	  );

	  std::cout << *temp_ptr;
	  scene.shapes_ptr.push_back(temp_ptr);
	}

	//else if Shape scope zuende
    }
	else if(keyword == "light")
	{
	//Variablen von light
	  std::string name;
	  std::string mat_namelight;
	  float posx, posy, posz, ldr, ldg, ldb;
	  //Light Variablen einlesen und zuordnen
	  //lightname
	  ss>>name;
	  //lightpos
	  ss>>posx;
	  ss>>posy;
	  ss>>posz;
	  glm::vec3 pos{posx,posy,posz};
	  //Color
	  ss>>ldr;
	  ss>>ldg;
	  ss>>ldb;
	  Color ld{ldr,ldg,ldb};

	  scene.lights.push_back( Light(name, pos, ld));
	  std::cout << "light: " << ld << "\n";
	}
	
	else if(keyword == "camera")
	{
	//Variablen von camera
          std::string name;
	  float fovx, posx, posy, posz, dirx, diry, dirz, upx, upy, upz;
	  //Einlesen und Zuweisen der Werte
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
	  glm::vec3 pos{posx,posy,posz};
	  glm::vec3 dir{dirx,diry,dirz};
	  glm::vec3 up{upx,upy,upz};

	  Camera cam{name,fovx,pos,dir,up};
	  std::cout << cam;
	  scene.camera=cam;
	}

	else if(keyword == "renderer")
	{
	  ss>>keyword;

	  ss>>scene.filename;

	  ss>>scene.xres_;
	  ss>>scene.yres_;

	  std::cout << scene.filename << "\n"
	  <<"Resolution: "<< scene.xres_ <<" x " <<
	  scene.yres_ << "\n";
	}
  }
  }
  myfile.close();
  }
  else
  {
  std::cout << "Unable to open file";
  }
    return scene;
}

#endif //define SDFLOADER_HPP
