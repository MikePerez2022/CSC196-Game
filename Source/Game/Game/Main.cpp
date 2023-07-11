#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include <iostream>
#include <vector>
#include <thread>

using namespace std;



class Star
{
public:
	Star(jojo::Vector2& pos, jojo::Vector2& vel) : m_pos{ pos }, m_vel{ vel } {}

	void Update(int width, int height)
	{
		m_pos += m_vel + kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.x >= height) m_pos.x = 0;
	}

	void Draw(jojo::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	jojo::vec2 m_pos;
	jojo::vec2 m_vel;
};

int main(int argc, char* argv[])
{

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	jojo::Renderer renderer;
	renderer.Initalize();
	renderer.CreateWindow("CSC196", 800, 600);

	jojo::InputSystem inputSystem;
	inputSystem.Initialize();


	std::vector<jojo::vec2> pointsj{ {-3, 0}, { 0,-3 }, { 4,0 }, { 4,2 }, { -3,2 }, { -3, 0 } }; //{ {-10, 5}, { 10,5 }, { 0,-5 }, { -10,5 } };
 	jojo::Model model(pointsj);
	//model.Load("ship.TXT");


	vector<Star> Stars; 
	vector<jojo::Vector2> points;
	for (int i = 0; i < 1000; i++)
	{
		jojo::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		jojo::Vector2 vel(kiko::randomf(1, 4), 0.0f);
		Stars.push_back(Star(pos, vel));
	}


	jojo::vec2 position(400, 300);
	float speed = 20;

	//Main game loop
	bool quit = false;	
	while (!quit) 
	{
		kiko::g_time.Tick();

		inputSystem.Update();
				
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		jojo::vec2 direction;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		else if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		else if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		else if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		position += direction * speed + kiko::g_time.GetDeltaTime();

		if (inputSystem.GetMouseButtonDown(0) || inputSystem.GetMouseButtonDown(2) || inputSystem.GetMouseButtonDown(3))
		{
			cout << "mouse button pressed" << endl;

			std::cout << "( " << inputSystem.GetMousePosition().x << ", " << inputSystem.GetMousePosition().y << " )" << endl;
		}
		
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//Draw
		jojo::Vector2 vel(1.0f, 0.3f);


		for (auto& star : Stars)
		{

			star.Update(renderer.GetWidth(), renderer.GetHeight());

			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			
		}

		

		model.Draw(renderer, position, 4.0f);
		
		renderer.EndFrame();

		//std::this_thread::sleep_for(chrono::milliseconds(100)); // best to show click and position
	}
	return 0;
}