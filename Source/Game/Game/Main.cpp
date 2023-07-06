#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <vector>

using namespace std;

//using vec2 = kiko::Vector2;

class Star
{
public:
	Star(jojo::Vector2& pos, jojo::Vector2& vel) : m_pos{ pos }, m_vel{ vel } {}

	void Update(int width, int height)
	{
		m_pos += m_vel;
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.x >= height) m_pos.x = 0;
	}

	void Draw(jojo::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	jojo::Vector2 m_pos;
	jojo::Vector2 m_vel;
};

int main(int argc, char* argv[])
{

	kiko::seedRandom((unsigned int)time(nullptr));

	jojo::Renderer renderer;
	renderer.Initalize();
	renderer.CreateWindow("CSC196", 800, 600);


	vector<Star> Stars; 
	vector<jojo::Vector2> points;
	for (int i = 0; i < 1000; i++)
	{
		jojo::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		jojo::Vector2 vel(kiko::randomf(1, 4), 0.0f);
		Stars.push_back(Star(pos, vel));
	}

	while (true) 
	{

		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//Draw
		jojo::Vector2 vel(1.0f, 0.3f);


		for (auto& star : Stars)
		{

			star.Update(renderer.GetWidth(), renderer.GetHeight());

			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			
		}

		renderer.DrawLine(kiko::random(800), kiko::random(600), kiko::random(800), kiko::random(600)); 

		//for (int i = 0; i < 1000; i++)
		//{
		//	jojo::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));

		//	renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
		//	renderer.DrawPoint(pos.x, pos.y);
		//}
		renderer.EndFrame();
	}
	return 0;
}