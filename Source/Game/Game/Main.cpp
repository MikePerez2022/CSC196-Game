#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include <iostream>

using namespace std;

int main() 
{
	kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time Timer;
	for (int i = 0; i < 10000000; i++) {}
	cout << Timer.GetElapsedSeconds() << endl;


	//jojo::CreateWindow("CSC196", 800, 600);
	//cin.get(); // pause




	//________________________________________________//


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