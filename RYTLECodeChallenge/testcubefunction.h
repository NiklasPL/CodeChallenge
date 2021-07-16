#ifndef TESTCUBEFUNCTION_H
#define TESTCUBEFUNCTION_H

#include "cube.h"
#include <list>

using namespace std;

class TestCubeFunction
{
public:
	explicit TestCubeFunction();
	static string		GetNextId(int& currentIndex);
	static list<string>	GetNextIds(int& currentIndex, int count);
	static Cube		createCube(list<Cube>& cubeReference, const string& id, CubeTypes type, const string& ownerId, list<string> childCubeIds);
	static list<Cube>	deleteCube(list<Cube>& cubeReference, const string& id, bool deleteChildCubes);
};

//#include "testcubefunction.moc"

#endif // TESTCUBEFUNCTION_H
