#include <QCoreApplication>
#include <QTimer>
#include "cube.h"
#include <future>
using namespace std;




int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	//int cubeIndex			= 0;
	//list<Cube> cubes		= list<Cube>();
	//const string& parentId		= GetNextId(cubeIndex);
	//list<string> uniqueChildIds	= {GetNextId(cubeIndex),GetNextId(cubeIndex)};

	QTimer::singleShot( 0, &a, &QCoreApplication::quit);
	//for (const Cube& cube : cubes) {
	//	cube.dump();
	//}
	return a.exec();
}



