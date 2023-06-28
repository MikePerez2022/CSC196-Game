#include "../../Engine/Core/Random.h"
#include "../../Engine/Core/FileIO.cpp"
#include <iostream>

using namespace std;

int main() 
{
	cout << Kiko::getFilePath() << endl;


	kiko::seedRandom((unsigned int)time(nullptr));

	for (int i = 0; i < 10; i++) {

		cout << kiko::random(5, 20) << endl;

	}
}