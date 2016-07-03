#ifndef SDF_HPP
#define SDF_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "material.hpp"

class SDF
{
	
public :
		
	SDF(){}
	void readInput(std::string);
	void createMaterial(std::ifstream&);
	std::vector<Material> getMaterials();

private :
	std::vector<Material> materials_;

};

void SDF::readInput(std::string input){
	
	std::string strline;
	std::string word;
	std::ifstream file (input);

	if(file.is_open()){
		std::cout << "wussup";

		while(getline(file, strline)){

			
			std::ifstream line (strline.c_str());
			line >> word;
			std::cout << strline;

			if(word == "define"){
				std::cout << "wussup";

				line >> word;

				if(word == "material"){ createMaterial(line); }

				else if (word == "shape"){} 

				else if (word == "light"){

				}
			} else if (word == "camera"){

			} else if (word == "render"){}
		}
		file.close();
	}
}

void SDF::createMaterial(std::ifstream& line){
	std::string name;
	std::string word;
	float r,g,b,m;

	line >> word;
	name = word;

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	Color ka {r,g,b};

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	Color kd {r,g,b};

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	Color ks {r,g,b};

	line >> word;
	m = std::stof(word);

	Material mat {name, ka, kd, ks, m};
	materials_.push_back(mat);
}

std::vector<Material> SDF::getMaterials(){
	return materials_;
}

#endif

