#include "camera.hpp"
//constructors
Camera::Camera():
  camname ({"Camera_def"}),
  campos ({0, 0, 1}),
  camfov (60)
  {}

Camera::Camera(std::string const& camname, glm::vec3 const& campos,
		glm::vec3 const& camup, float camfov):
  camname (camname),
  campos (campos),
  camup (camup),
  camfov (camfov)
  {}
//getter
std::string const& Camera::getcamname() const
{
  return camname;
}
glm::vec3 const& Camera::getcampos() const
{
  return campos;
}
glm::vec3 const& Camera::getcamup() const
{
  return camup;
}
float const& Camera::getcamfov() const
{
  return camfov;
}

Ray const Camera::castray(glm::vec3 const& dir) const
{
  Ray ray{campos, campos + dir};
  return ray;
}

//Ueberpruefen mit Ausgabe
std::ostream& operator<<(std::ostream& os, Camera const& c)
{
  os << "Camera: \n"
  << "Name: " << c.camname << "\n"
  << "Pos: (" << c.campos.x << "," << c.campos.y << "," << c.campos.z << ")\n"
  << "Up: (" << c.camup.x << "," << c.camup.y << "," << c.camup.z << ")\n"
  << "Fov: "<< c.camfov << "\n\n";
  return os;
}
