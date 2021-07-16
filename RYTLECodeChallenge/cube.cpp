#include "cube.h"
#include <iostream>
using namespace std;

Cube::Cube(string id, CubeTypes type, list<Cube> childCubes, string parent)
{
	_id = id;
	_type = type;
	_ownerId = parent;
	_childCubes = childCubes;
}
void Cube::dump() const {

	std::cout << "Cube id: " << _id << " _type: " << _type << " parentId: " << _ownerId << " childCubes: " << _childCubes.size() << endl;
}

string Cube::GetId() const
{
	return _id;
}

string Cube::GetOwnerId() const
{
	return _ownerId;
}

void Cube::RemoveOwnerId()
{
	_ownerId = "";
}
