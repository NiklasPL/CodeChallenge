#ifndef CUBE_H
#define CUBE_H
#include <QString>
#include <list>


enum CubeTypes
{
   Small,
   Big
};

class Cube
{
public:
	Cube(std::string id, CubeTypes type, std::list<Cube> childCubes = std::list<Cube>(), std::string parent = "");
	void dump() const;

	std::string GetId() const;
	std::string GetOwnerId() const;
	void RemoveOwnerId();

private:
	std::string _id;
	std::string _ownerId;
	std::list<Cube> _childCubes;
	CubeTypes _type;
};

#endif // CUBE_H
