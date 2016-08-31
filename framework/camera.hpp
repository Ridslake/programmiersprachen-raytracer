#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include "ray.hpp"

class Camera
{
public:
//d
  Camera();

//c //Camera name, position, direction, field of view
  Camera(std::string const&, glm::vec3 const&, glm::vec3 const&, float);
  

//getter, koennte man auch alles in der HPP machen
  std::string const& getcamname() const;
  glm::vec3 const& getcampos() const;
  glm::vec3 const& getcamup() const;
  float const& getcamfov() const;

  Ray const castray(glm::vec3 const& dir) const;

//Ausgabe zur Überprüfung
friend std::ostream& operator<<(std::ostream& os, Camera const& c);

//Varibalen Camera
private:
  std::string camname;
  glm::vec3 campos;
  glm::vec3 camup;
  float camfov;
};

#endif //#define CAMERA_HPP
