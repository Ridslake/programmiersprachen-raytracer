#include "camera.hpp"
//constructors
Camera::Camera():
  camname ({"Camera_def"}),
  camfovx (60),
  campos ({0, 0, 0}),
  camdir ({0, 0, -1}),
  camup ({0, 1, 0})
  {}

  Camera(std::string const& name,float fovx glm::vec3 const& eye, glm::vec3 const& dir, glm::vec3 const& up):
  camname (name),
  camfovx (fovx)
  campos (eye),
  camdir (dir),
  camup (up)
  {}

//getter
std::string const& Camera::getcamname() const
{
  return camname;
}
float const& Camera::getcamfov() const
{
  return camfov;
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

/*Ray const Camera::castray(glm::vec3 const& dir) const
{
  Ray ray{campos, campos + dir};
  return ray;
}*/

glm::mat4 Camera::camtransform() const
{
  glm::vec3 eye = campos;
  glm::vec3 n = glm::normalize(camdir);
  glm::vec3 up = camup;

  glm::vec3 u = glm::normalize(glm::cross(n, up));
  glm::vec3 v = glm::normalize(glm::cross(u, n));

  glm::mat4 transformCam;
  transformCam[0] = glm::vec4 {u, 0.0f};
  transformCam[1] = glm::vec4 {v, 0.0f};
  transformCam[2] = glm::vec4 {n * -1.0f, 0.0f};
  transformCam[3] = glm::vec4 {e, 1.0f};

  return camtransform;
} 

Ray Camera::eye_calc(int x, int y, int height, int width) const
{
  glm::vec3 direction {float(x) * 1.0 / float(width) - 0.5,
  float(y) * 1.0 / float(height) - 0.5, 
  -1.0 * (0.5 / tan(aovX_/2))}; // distance to canvas = 0.5 / tan(angle / 2)

  Ray camRay{origin_, direction};
  auto transformedCam = transformCam();

  return camRay.transformRay(transformedCam);
}

//Ueberpruefen mit Ausgabe
std::ostream& operator<<(std::ostream& os, Camera const& c)
{
  os << "Camera: \n"
  << "Name: " << c.camname << "\n"
  << "Fovx: " << c.camfovx << "\n"
  << "Pos: (" << c.campos.x << "," << c.campos.y << "," << c.campos.z << ")\n"
  << "Pos: (" << c.camdir.x << "," << c.camdir.y << "," << c.camdir.z << ")\n"
  << "Up: (" << c.camup.x << "," << c.camup.y << "," << c.camup.z << ")\n"
  return os;
}
