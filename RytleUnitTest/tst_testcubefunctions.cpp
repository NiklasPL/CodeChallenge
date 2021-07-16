#include <QtTest>
#include <iostream>
#include "../RYTLECodeChallenge/cube.h"
#include "../RYTLECodeChallenge/cube.cpp"
#include "../RYTLECodeChallenge/testcubefunction.h"
#include "../RYTLECodeChallenge/testcubefunction.cpp"
#include <future>
#include <mutex>
// add necessary includes here
using namespace std;
class TestCubeFunctions : public QObject
{
	Q_OBJECT

public:
	TestCubeFunctions();
	~TestCubeFunctions();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void CreateFiveCubes();
	void CreateFiveCubesAndDeleteOneWithOutChildren();
	void CreateFiveCubesAndDeleteOneWithChildren();
	void CreateFiveCubesAndDeleteUnavailableCubeId();

};

TestCubeFunctions::TestCubeFunctions()
{

}

TestCubeFunctions::~TestCubeFunctions()
{

}

void TestCubeFunctions::initTestCase()
{

}

void TestCubeFunctions::cleanupTestCase()
{

}

void TestCubeFunctions::CreateFiveCubes()
{
	list<Cube> cubes;
	int cubeIdCounter	= 0;
	string id		= TestCubeFunction::GetNextId(cubeIdCounter);
	list<string> childIds	= TestCubeFunction::GetNextIds(cubeIdCounter, 4);
	async(launch::async, TestCubeFunction::createCube, ref(cubes), id, CubeTypes::Small, "", childIds);

	QVERIFY(cubes.size() == 5);
}

void TestCubeFunctions::CreateFiveCubesAndDeleteOneWithOutChildren()
{

	list<Cube> cubes;
	int cubeIdCounter	= 0;
	string id		= TestCubeFunction::GetNextId(cubeIdCounter);
	list<string> childIds	= TestCubeFunction::GetNextIds(cubeIdCounter, 4);
	async(launch::async, TestCubeFunction::createCube, ref(cubes), id, CubeTypes::Small, "", childIds);

	bool throwException = false;
	try {
		async(launch::async, TestCubeFunction::deleteCube, ref(cubes), id, false);
	} catch (const std::exception &ex) {
		cerr << ex.what() << '\n';
		throwException = true;
	}

	QVERIFY(cubes.size() == 4);
	QVERIFY(throwException == false);
}

void TestCubeFunctions::CreateFiveCubesAndDeleteOneWithChildren()
{

	list<Cube> cubes;
	int cubeIdCounter	= 0;
	string id		= TestCubeFunction::GetNextId(cubeIdCounter);
	list<string> childIds	= TestCubeFunction::GetNextIds(cubeIdCounter, 4);
	async(launch::async, TestCubeFunction::createCube, ref(cubes), id, CubeTypes::Small, "", childIds);

	bool throwException = false;
	try {
		async(launch::async, TestCubeFunction::deleteCube, ref(cubes), id, true);
	} catch (const std::exception &ex) {
		cerr << ex.what() << '\n';
		throwException = true;
	}

	QVERIFY(cubes.size() == 0);
	QVERIFY(throwException == false);
}

void TestCubeFunctions::CreateFiveCubesAndDeleteUnavailableCubeId()
{
	list<Cube> cubes;
	int cubeIdCounter	= 0;
	string id		= TestCubeFunction::GetNextId(cubeIdCounter);
	list<string> childIds	= TestCubeFunction::GetNextIds(cubeIdCounter, 4);
	async(launch::async, TestCubeFunction::createCube, ref(cubes), id, CubeTypes::Small, "", childIds);
	std::future<list<Cube>> fut;
	bool throwException = false;

	id = TestCubeFunction::GetNextId(cubeIdCounter);
	fut = async(launch::async, TestCubeFunction::deleteCube, ref(cubes), id, true);
	std::future_status status = fut.wait_for(std::chrono::milliseconds(500u));
	if (status == std::future_status::deferred) {
		cout << "AsyncMethodThrowsException has not started" << endl;
	} else if (status == std::future_status::timeout) {
		cout << "AsyncMethodThrowsException timed out" << endl;
	} else if (status == std::future_status::ready) {
		cout << "AsyncMethodThrowsException successfully completed" << endl;
		try {
			if(fut.valid()) {
				fut.get();
			}
		} catch(const std::exception& ex) {
			cout << "AsyncMethodThrowsExceptionTest catch block: " << ex.what() << endl;
			throwException = true;
		}
	}
	QVERIFY(throwException == true);
}

QTEST_APPLESS_MAIN(TestCubeFunctions)

#include "tst_testcubefunctions.moc"
