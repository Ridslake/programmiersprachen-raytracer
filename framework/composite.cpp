#include "composite.hpp"

/*ERKLRÄUNG (mit composite Bild):
Der Composite ist dann ein Composite, wenn er ein Child enthält (Parent-Classe -> Child-Class)
Leaf ist die Klasse, die aus dem Composite entspringt.
*/
Composite::Composite() 
{}

Composite::Composite(std::string name): namex{name} 
{}

Composite::~Composite() 
{}

//Child Unterzweig von Parent-Klasse 
//Add um weiteren Zweig hinzuzufügen
void Composite::addChild(std::shared_ptr<Shape>& shape)
{

//Fügt neues Element am Ende der Liste hinzu (nach dem jetzigen letzten Element. 
//Value wird dorthin verschoben. Container Size +1

	shapex.push_back(shape);
}

void Composite::removeChild(std::shared_ptr<Shape>& shape)
{
//shared_ptr=Übernimmt Besitz über den Pointer und teilt diesen Besitz mit anderen Pointern. (Diese Verantwortlich für Löschung des Pointers/Besitzes)
	std::vector<std::shared_ptr<Shape>>::iterator it;//abstrakter Zeiger it

	for (it = shapex.begin(); it!=shapex.end(); )
	{
		if ((*it)==shape) //*it = erhalte aktuelles Element an Position it 
		{
			it = shapex.erase(it); //remove iterator
		}
		else
		{
			++it;//iterator wird auf das nächste Element im Container gesetzt
		}
	}

}
//Für Leaf einfach nur print
void Composite::print(std::ostream os) const
{
	for(auto comp: shapex) 
	{
		comp->print(os);
	}
}

std::vector<std::shared_ptr<Shape>> Composite::getChild()
{
	return shapex;
}


