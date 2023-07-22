#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "..\Engine\Audio\AudioSystem.h"
#include "Framework/Scene.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

using namespace std;



class Star
{
public:
	Star(jojo::Vector2& pos, jojo::Vector2& vel) : m_pos{ pos }, m_vel{ vel } {}

	void Update(int width, int height)
	{
		m_pos += m_vel * jojo::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
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
	jojo::seedRandom((unsigned int)time(nullptr));
	jojo::setFilePath("assets");

	jojo::MemoryTracker::Initialize(); //

	jojo::g_renderer.Initalize();
	jojo::g_renderer.CreateWindow("CSC196", 800, 600); 

	jojo::g_inputSystem.Initialize(); 

	jojo::g_audioSystem.Initialize();
	jojo::g_audioSystem.AddAudio("laser", "laser.wav"); 
	jojo::g_audioSystem.AddAudio("hit", "hit.wav");

	std::shared_ptr<jojo::Font> font = std::make_shared<jojo::Font>("Vendetta.ttf", 24);

	std::unique_ptr<jojo::Text> text = std::make_unique<jojo::Text>(font);
	text->Create(jojo::g_renderer, "NEUMONT", jojo::Color{ 1, 1, 1, 1 });

	//std::vector<jojo::vec2> pointsj{ {-3, -2}, { 0,4 }, { 3,-2 }, { 0,-1 }, { -3, -2 } }; //{ {-10, 5}, { 10,5 }, { 0,-5 }, { -10,5 } };
	jojo::Model model;
	model.Load("ship.txt");

	vector<Star> Stars; 
	//vector<jojo::Vector2> points;
	for (int i = 0; i < 1000; i++)
	{
		jojo::Vector2 pos(jojo::random(jojo::g_renderer.GetWidth()), jojo::random(jojo::g_renderer.GetHeight()));
		jojo::Vector2 vel(jojo::randomf(100,400), 0.0f);
		Stars.push_back(Star(pos, vel));
	}

	jojo::Transform transform{ {400, 300}, 0, 3};

	jojo::Scene scene;

	unique_ptr<Player> player;
	player = make_unique<Player>(Player::Player( 200, jojo::Pi, jojo::Transform({400,300},0,6), jojo::g_modelManager.Get("ship.txt")));
	player->m_tag = "Player";
	scene.Add(std::move(player));

		
	for (int i = 0; i < 20; i++) 
	{
		unique_ptr<Enemy> enemy = make_unique<Enemy>(Enemy::Enemy( jojo::randomf(75.0f, 150.0f), jojo::Pi, transform, jojo::g_modelManager.Get("ship.txt")));
		//Enemy* enemy = new Enemy{ 200, jojo::Pi, {{400,300}, jojo::randomf(jojo::Pi), 3}, model };
		enemy->m_tag = "Enemy";
		scene.Add(std::move(enemy));
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

		scene.Update(jojo::g_time.GetDeltaTime());
		

		jojo::g_audioSystem.Update();
		
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			jojo::g_audioSystem.PlayOneShot("laser");
		}			

		
		jojo::g_renderer.SetColor(0, 0, 0, 0);
		jojo::g_renderer.BeginFrame();

		//draw

		scene.Draw(jojo::g_renderer);

		model.Draw(jojo::g_renderer, { 400,300 }, 20, 7);// Why?

		text->Draw(jojo::g_renderer, 400, 300);
		
		jojo::Vector2 vel(1.0f, 0.3f);
		for (auto& star : Stars)
		{
			star.Update(jojo::g_renderer.GetWidth(), jojo::g_renderer.GetHeight());
			jojo::g_renderer.SetColor(jojo::random(256), jojo::random(256), jojo::random(256), 255);
			star.Draw(jojo::g_renderer);
		}

		jojo::g_renderer.EndFrame();

		jojo::MemoryTracker::DisplayInfo();

		
	}
	
	//Stars.clear();
	//scene.RemoveAll();
	//jojo::g_audioSystem.Shutdown();
	//jojo::MemoryTracker::DisplayInfo();

	return 0;
}