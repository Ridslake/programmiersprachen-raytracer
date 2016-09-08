#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"




class Composite : public Shape{
public:
	Composite();

	Composite(std::string name);

	~Composite();

	void addChild(std::shared_ptr<Shape>& shape) override; 
	void removeChild(std::shared_ptr<Shape>& shape) override; 
	void print(std::ostream os) const;


	std::vector<std::shared_ptr<Shape>> getChild() override; 
	inline Hit intersect(Ray const& ray) override
	{
		return Hit{};
	}



private:
	std::string namex;
	std::vector<std::shared_ptr<Shape>> shapex;
};

#endif
