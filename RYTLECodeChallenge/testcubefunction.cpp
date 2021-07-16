#include "testcubefunction.h"
#include <iostream>
#include "cube.h"
#include <future>
#include <mutex>

using namespace std;

mutex m;

TestCubeFunction::TestCubeFunction()
{
}

Cube TestCubeFunction::createCube(list<Cube>& cubeReference, const string& id, CubeTypes type, const string& ownerId, list<string> childCubeIds) {
	list<Cube> childCubes;
	for (const string& childId : childCubeIds) {
		future<Cube> fut = async(launch::async, &TestCubeFunction::createCube, ref(cubeReference), childId, CubeTypes::Small, id, list<string>());
		childCubes.push_back(fut.get());
	}
	Cube cube = Cube(id, type, childCubes, ownerId);
	lock_guard<mutex> lk(m);
	cubeReference.push_back(cube);
	return cube;
}

list<Cube> TestCubeFunction::deleteCube(list<Cube>& cubeReference, const string& id, bool deleteChildCubes) {
	list<Cube> deletedCubes;

	list<Cube>::iterator i = cubeReference.begin();

	cout << "TestCubeFunction::deleteCube ::: id: " << id << endl;

	lock_guard<mutex> lk(m);
	while (i != cubeReference.end())
	{
		if (i->GetId() != id && i->GetOwnerId() != id) {
			i++;
			continue;
		}

		if (!deleteChildCubes && i->GetOwnerId() == id) {
			i->RemoveOwnerId();
			i++;
			continue;
		}
		deletedCubes.push_back(*i);
		cubeReference.erase(i++);

	}
	cout << "TestCubeFunction::deleteCube: Size: " << deletedCubes.size() << endl;
	if (deletedCubes.size() == 0) {
		cout << "We didnt deleted anything" << endl;
		throw invalid_argument( "CubeId not found" );
	}

	/*
	cout << "RemainingCubes" << endl;
	for (const Cube& cube : cubeReference ) {
		cube.dump();
	}

	cout << "DeletedCubes" << endl;
	for (const Cube& cube : deletedCubes ) {
		cube.dump();
	}
	*/

	return deletedCubes;
}

string TestCubeFunction::GetNextId(int& currentIndex)
{
	return "id_"+ std::to_string(currentIndex++);;
}

list<string> TestCubeFunction::GetNextIds(int& currentIndex, int count)
{
	list<string> ids;
	for (int i = 0; i < count; i++) {
		ids.push_back(GetNextId(currentIndex));
	}
	return ids;
}


