#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() 
{
	kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000000; i++) {}
	auto end = std::chrono::high_resolution_clock::now();

	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;






	/*cout << kiko::getFilePath() << endl;
	kiko::setFilePath("Assets");
	cout << kiko::getFilePath() << endl;
	size_t size;
	kiko::getFileSize("game.txt", size);
	cout << size << endl;

	std::string s;
	kiko::readFile("game.txt", s);
	cout << s << endl;

	Kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {

		cout << Kiko::random(5, 20) << endl;

	}*/
}