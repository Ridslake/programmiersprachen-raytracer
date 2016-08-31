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

//Scene Sdfloader::load_scene(std::string file) const {
Scene load_sdf_file(std::string const& filename) {
    Scene scene;
    std::string line;
    std::ifstream myfile (filename);
    //  std::cout << filename << "\n";
    /*std::map<std::string, std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<Light*> lights;
    int xres,yres;
    Color amblight, background;
    std::string filename;
    Camera cam;*/
    //  Scene scene1;

    if (myfile.is_open())
    {
        while ( getline(myfile,line) )
        {
            //std::cout << line << '\n';
            std::stringstream ss;
            ss << line;
            std::string keyword;

            ss>>keyword;
            if(keyword == "#"){
                continue;
            }

            if(keyword == "define"){
                ss>>keyword;
                if(keyword == "material"){
                    Material mat;
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


                    scene.materials.insert({mat.name, mat});
                    //materials[mat.name]= mat;
                    std::cout << mat;
                }
                else if(keyword == "shape"){
                    ss>>keyword;

                    if(keyword == "box"){
                        std::string name;
                        std::string mat_namebox;
                        float minx,miny,minz,maxx,maxy,maxz;
                        ss>>name;

                        ss>>minx;
                        ss>>miny;
                        ss>>minz;
                        ss>>maxx;
                        ss>>maxy;
                        ss>>maxz;

                        glm::vec3 min{minx,miny,minz};
                        glm::vec3 max{maxx,maxy,maxz};

                        ss>>mat_namebox;
                        //std::string mat_namebox;

                        std::shared_ptr<Shape> temp_ptr = std::make_shared<Box>
                        (
                            Box{name,scene.materials[mat_namebox],min,max}
                        );
                            std::cout << *temp_ptr;
                            scene.shapes_ptr.push_back(temp_ptr);

                    }
                    if(keyword == "sphere"){
                        std::string name;
                        float x,y,z,r;
                        ss>>name;
                        ss>>x;
                        ss>>y;
                        ss>>z;
                        glm::vec3 center{x,y,z};
                        ss>>r;
                        std::string mat_name;
                        ss>>mat_name;
                        //alternative

                    /*std::cout <<mat_name;
                        ss>>sph.name_;
                        ss>>sph.middle_.x;
                        ss>>sph.middle_.y;
                        ss>>sph.middle_.z;
                        ss>>sph.r_;
                        ss>>sph.mat_;
                        std::cout << sph;sph.mat_=*materials(mat_name);*/
                        std::shared_ptr<Shape> temp_ptr = std::make_shared<Sphere>
                        (
                            Sphere{name,scene.materials[mat_name],center,r}
                        );
                            std::cout << *temp_ptr;
                            scene.shapes_ptr.push_back(temp_ptr);
                        // std::cout << sph;
                    }

                    if(keyword == "composite"){
                        std::cout << "\n" << "-------------------------" << "\n";
                        std::string name;
                        ss>>name;
                        std::cout << name << " erstellen:" << "\n";
                        std::vector<std::shared_ptr<Shape>> comp;
                        ss>>keyword;
                        std::cout << "Folgende Objekte sind enthalten:"<< "\n";
                        while(keyword != "endcomp"){
                            for (std::vector<std::shared_ptr<Shape>>::iterator i = scene.shapes_ptr.begin();i != scene.shapes_ptr.end();++i){


                                    if(keyword == (*i)->getname()){
                                        comp.push_back(*i);
                                        std::cout << *(*i) << "\n";
                                }


                            }
                            ss>>keyword;
                        }
                            //insertmap
                        scene.composites.insert({name,comp});
                        std::cout<< "-------------------------"<< "\n";

                    }
                }
                else if(keyword == "light"){
                    std::string name;
                    std::string mat_namelight;
                    float posx, posy, posz, ldr, ldg, ldb;
                    ss>>name;
                    ss>>posx;
                    ss>>posy;
                    ss>>posz;
                    glm::vec3 pos{posx,posy,posz};
                    ss>>ldr;
                    ss>>ldg;
                    ss>>ldb;
                    Color ld{ldr,ldg,ldb};



                    scene.lights.push_back( Light(name, pos, ld));
                    std::cout << "light: " << ld << "\n";
                }
                else if(keyword == "camera"){
                    std::string name;
                    float angle, posx, posy, posz, upx,upy,upz;
                    ss>>name;
                    ss>>posx;
                    ss>>posy;
                    ss>>posz;
                    ss>>upx;
                    ss>>upy;
                    ss>>upz;
                    glm::vec3 pos{posx,posy,posz};
                    glm::vec3 up{upx,upy,upz};
                    ss>>angle;


                    /*std::shared_ptr<Camera> cam_ptr = std::make_shared<Camera>
                    (
                        Camera{name,pos,angle}
                    );*/
                    //Camera cam;
                    //cam.name_=name;
                    //cam.pos_=pos;
                    //cam.angle_=angle;
                    Camera cam{name,pos,up, angle};
                    std::cout << cam;
                    scene.camera=cam;
                }
                else if(keyword == "amblight"){
                    float ambr,ambg,ambb;
                    ss>>ambr;
                    ss>>ambg;
                    ss>>ambb;
                    Color amb{ambr,ambg,ambb};
                    scene.amblight=amb;
                    std::cout <<amb;
                }
                else if(keyword == "background"){
                    float backr, backg, backb;
                    ss>>backr;
                    ss>>backg;
                    ss>>backb;
                    Color back{backr,backg,backb};
                    scene.background=back;
                    std::cout <<back;
                }
                else if(keyword == "renderer"){
                    ss>>keyword;

                    ss>>scene.filename;

                    ss>>scene.xres_;
                    ss>>scene.yres_;
                    /*std::shared_ptr<Scene> scene_ptr = std::make_shared<Scene>
                        (
                            Scene{filename, xres, yres, cam, amblight, background, materials, shapes, lights}
                        );*/
                    std::cout << scene.filename << "\n" <<"Resolution: "<< scene.xres_ << " x " << scene.yres_ << "\n";
                }
            }

        }
        myfile.close();
    }
    else {
        std::cout << "Unable to open file";
    }

    return scene;
}

#endif
