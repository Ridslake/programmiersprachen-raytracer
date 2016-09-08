#include "camera.hpp"
//constructors
Camera::Camera():
  camname ({"Camera_def"}),
  camfovx (60),
  campos ({0, 0, 0}),
  camdir ({0, 0, -1}),
  camup ({0, 1, 0})
  {}

Camera::Camera(std::string const& name, float fovx, glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up):
  camname (name),
  camfovx (fovx),
  campos (eye),
  camdir (dir),
  camup (up)
  {}

//getter
std::string const& Camera::getcamname() const
{
  return camname;
}
float const& Camera::getcamfovx() const
{
  return camfovx;
}
glm::vec3 const& Camera::getcampos() const
{
  return campos;
}
glm::vec3 const& Camera::getcamdir() const
{
  return camdir;
}
glm::vec3 const& Camera::getcamup() const
{
  return camup;
}

//Intersect braucht Raycast (aus Kamera kommend)
Ray const Camera::castray(glm::vec3 const& dir) const
{
  Ray ray{campos, dir};
  ray.transformRay(CamTrans());
  return ray;
}

//Camera Transformation nach Vorlesung
glm::mat4 Camera::CamTrans() const
{
  glm::vec3 eye = campos;
  glm::vec3 n = glm::normalize(camdir); //zu normieren
  glm::vec3 up = camup;

//u steht senkrecht auf n(dir) und up, zu normieren
  glm::vec3 u = glm::normalize(glm::cross(n, up));
//v um sicher zu gehen das up senkrecht zu u und n ist, zu normieren
  glm::vec3 v = glm::normalize(glm::cross(u, n));

  glm::mat4 CamTrans;
  CamTrans[0] = glm::vec4 {u, 0.0f}; //erste Spalte der Matrix
  CamTrans[1] = glm::vec4 {v, 0.0f};
  CamTrans[2] = glm::vec4 {n * -1.0f, 0.0f};
  CamTrans[3] = glm::vec4 {eye, 1.0f};

  return CamTrans; //transformierte Camera
} 


//Ueberpruefen mit Ausgabe
std::ostream& operator<<(std::ostream& os, Camera const& c)
{
  os << "Camera: \n"
  << "Name: " << c.camname << "\n"
  << "Fovx: " << c.camfovx << "\n"
  << "Pos: (" << c.campos.x << "," << c.campos.y << "," << c.campos.z << ")\n"
  << "Dir: (" << c.camdir.x << "," << c.camdir.y << "," << c.camdir.z << ")\n"
  << "Up: (" << c.camup.x << "," << c.camup.y << "," << c.camup.z << ")\n\n";
  return os;
}
