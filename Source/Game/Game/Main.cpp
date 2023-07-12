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

	constexpr float a = jojo::DegreesToRadians(180.0f);

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	jojo::Renderer renderer;
	renderer.Initalize();
	renderer.CreateWindow("CSC196", 800, 600);

	jojo::InputSystem inputSystem;
	inputSystem.Initialize();


	std::vector<jojo::vec2> pointsj{ {-3, -2}, { 0,4 }, { 3,-2 }, { 0,-1 }, { -3, -2 } }; //{ {-10, 5}, { 10,5 }, { 0,-5 }, { -10,5 } };
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

	jojo::Transform transform{ {400, 300}, 0, 3};


	jojo::vec2 position(400, 300);
	float speed = 200;
	constexpr float turnRate = jojo::DegreesToRadians(180);

	//Main game loop
	bool quit = false;	
	while (!quit) 
	{
		kiko::g_time.Tick();

		inputSystem.Update();
				
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		float rotate = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		transform.rotation += rotate * turnRate * kiko::g_time.GetDeltaTime();
		

		float thrust = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		jojo::vec2 forward = jojo::vec2{ 0,1 }.Rotate(transform.rotation);
		transform.position += forward * speed * thrust * kiko::g_time.GetDeltaTime();
		transform.position.x = jojo::Wrap(transform.position.x, renderer.GetWidth());
		transform.position.y = jojo::Wrap(transform.position.y, renderer.GetHeight());


		//jojo::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//else if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//else if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//else if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		//position += direction * speed + kiko::g_time.GetDeltaTime();

		//if (inputSystem.GetMouseButtonDown(0) || inputSystem.GetMouseButtonDown(2) || inputSystem.GetMouseButtonDown(3))
		//{
		//	cout << "mouse button pressed" << endl;
		//
		//	std::cout << "( " << inputSystem.GetMousePosition().x << ", " << inputSystem.GetMousePosition().y << " )" << endl;
		//}
		
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		//draw
		
		jojo::Vector2 vel(1.0f, 0.3f);
		for (auto& star : Stars)
		{
			star.Update(renderer.GetWidth(), renderer.GetHeight());
			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);	
		}

		

		model.Draw(renderer, transform.position, transform.rotation, transform.scale);
		
		renderer.EndFrame();


	}
	return 0;
}