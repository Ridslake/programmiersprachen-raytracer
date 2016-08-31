#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

#include "ray.hpp"

class Camera
{
public:
//d
  Camera();

//c //Kameraposition und -orientierung wird durch 3 Angaben festgelegt
//Beobachtungspunkt e(ye), Blickrichtung n (dir),  Up-Vektor (up)
  Camera(std::string const&, float, glm::vec3 const&, glm::vec3 const&, glm::vec3 const&);
  

//getter, koennte man auch alles in der HPP machen
  std::string const& getcamname() const;
  float const& getcamfovx() const;
  glm::vec3 const& getcampos() const;
  glm::vec3 const& getcamdir() const;
  glm::vec3 const& getcamup() const;

//Ray const castray(glm::vec3 const& dir) const;
  glm::mat4 transformCam() const;
  Ray eye_calc(int x, int y, int height, int width) const;

//Ausgabe zur Überprüfung
friend std::ostream& operator<<(std::ostream& os, Camera const& c);

//Varibalen Camera
private:
  std::string camname;
  float camfovx;
  glm::vec3 campos;
  glm::vec3 camdir;
  glm::vec3 camup;
};

#endif //#define CAMERA_HPP
