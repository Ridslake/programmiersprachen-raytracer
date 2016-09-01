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

//tranformieren der Camera nach Vorlesung
  glm::mat4 CamTrans() const;

  Ray const castray(glm::vec3 const& dir) const;

//Ausgabe zur Überprüfung
//methoden zugriff auf die elemente einer anderen Klasse = friend
friend std::ostream& operator<<(std::ostream& os, Camera const& c);

//Variablen Camera
private:
  std::string camname;
  float camfovx;
  glm::vec3 campos; //Urpsprung ({0, 0, 0})
  glm::vec3 camdir; //blickt entlang der negativen Z-Achse
  glm::vec3 camup;  //Orientierung
};

#endif //#define CAMERA_HPP
