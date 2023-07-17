#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "..\Engine\Audio\AudioSystem.h"
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
		m_pos += m_vel + jojo::g_time.GetDeltaTime();
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

	jojo::AudioSystem audioSystem;

	audioSystem.Initialize();
	audioSystem.AddAudio("hit", "Hit.wav");

	//auto m1 = jojo::Max(4.0f, 3.0f);
	//int m2 = jojo::Max(4, 3);

	constexpr float a = jojo::DegreesToRadians(180);

	jojo::seedRandom((unsigned int)time(nullptr));
	jojo::setFilePath("assets");

	
	jojo::g_renderer.Initalize();
	jojo::g_renderer.CreateWindow("CSC196", 800, 600);


	jojo::g_inputSystem.Initialize();


	std::vector<jojo::vec2> pointsj{ {-3, -2}, { 0,4 }, { 3,-2 }, { 0,-1 }, { -3, -2 } }; //{ {-10, 5}, { 10,5 }, { 0,-5 }, { -10,5 } };
 	jojo::Model model(pointsj);
	//model.Load("ship.TXT");


	vector<Star> Stars; 
	vector<jojo::Vector2> points;
	for (int i = 0; i < 1000; i++)
	{
		jojo::Vector2 pos(jojo::random(jojo::g_renderer.GetWidth()), jojo::random(jojo::g_renderer.GetHeight()));
		jojo::Vector2 vel(jojo::randomf(100,400), 0.0f);
		Stars.push_back(Star(pos, vel));
	}

	jojo::Transform transform{ {400, 300}, 0, 3};


	jojo::vec2 position(400, 300);
	float speed = 200;
	constexpr float turnRate = jojo::DegreesToRadians(180);

	Player player{200, jojo::Pi, {{400,300},0,6}, model };

	std::vector<Enemy> enemies;
	Enemy enemy{200, jojo::Pi, {{400,300}, jojo::randomf(jojo::Pi), 3}, model};

	for (int i = 0; i < 20; i++) 
	{
		Enemy enemy{ 200, jojo::Pi, {{400,300}, jojo::randomf(jojo::Pi), 3}, model };
		enemies.push_back(enemy);
	}

	//Main game loop
	bool quit = false;	
	while (!quit) 
	{
		jojo::g_time.Tick();

		jojo::g_inputSystem.Update();
				
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		player.Update(jojo::g_time.GetDeltaTime());
		for(auto& enemy : enemies) enemy.Update(jojo::g_time.GetDeltaTime());

		audioSystem.Update();
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			audioSystem.PlayOneShot("hit");
			audioSystem.PlayOneShot("hit");
		}		


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
		
		jojo::g_renderer.SetColor(0, 0, 0, 0);
		jojo::g_renderer.BeginFrame();

		//draw
		
		jojo::Vector2 vel(1.0f, 0.3f);
		for (auto& star : Stars)
		{
			star.Update(jojo::g_renderer.GetWidth(), jojo::g_renderer.GetHeight());
			jojo::g_renderer.SetColor(jojo::random(256), jojo::random(256), jojo::random(256), 255);
			star.Draw(jojo::g_renderer);
		}

		player.Draw(jojo::g_renderer);
		for (auto& enemy : enemies) enemy.Draw(jojo::g_renderer);
		

		//model.Draw(jojo::g_renderer, transform.position, transform.rotation, transform.scale);
		
		jojo::g_renderer.EndFrame();


	}
	return 0;
}