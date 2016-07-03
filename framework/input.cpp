#include "input.hpp"

//SDF::SDF(): materials_(){}

void SDF::readInput(std::string const& input){
	std::string line;
	std::string word;
	std::ifstream file (input);

	if(file.is_open()){
		while(getline(file, line)){
			
			line >> word;

			if(word == "define"){

				line >> word;

				if(word == "material"){ createMaterial(line); }

				else if (word == "shape"){} 

				else if (word == "light"){

				}
			} else if (word == "camera"){

			} else if (word == "render"){}
		}
	}
};

void SDF::createMaterial(line){
	std::string name;
	float r,g,b,m;
	Color ka,kd,ks;

	line >> word;
	name = word;

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	ka = {r,g,b};

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	kd = {r,g,b};

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	ks = {r,g,b};

	line >> word;
	m = std::stof(word);

	Material m {name, ka, kd, ks, m};
	materials_.push_back(m);
};

std::vector<Materials> SDF::getMaterials(){
	return materials_;
};

