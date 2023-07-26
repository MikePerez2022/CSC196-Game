#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initalize()
{

	//create font
	std::shared_ptr<jojo::Font> font = std::make_shared<jojo::Font>("ArcadeClassic.ttf", 24);
	std::unique_ptr<jojo::Text> text = std::make_unique<jojo::Text>(font);
	text->Create(jojo::g_renderer, "NEUMONT", jojo::Color{ 81, 90, 1, 255 });
	m_font = font;//

	m_scoreText = std::make_unique<jojo::Text>(font);//
	m_scoreText->Create(jojo::g_renderer, "ooooo", jojo::Color{ 1, 90, 71, 255 });

	m_titleText = std::make_unique<jojo::Text>(font);//
	m_titleText->Create(jojo::g_renderer, "SPACE GAME", jojo::Color{ 91, 1, 1, 255 });//

	//Load Audio
	jojo::g_audioSystem.AddAudio("laser", "laser.wav");
	jojo::g_audioSystem.AddAudio("hit", "hit.wav");

	//scene
	m_scene = std::make_unique<jojo::Scene>();


    return true;
}

bool SpaceGame::Shutdown()
{
    return false;
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_X) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_X))
		{
			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		std::unique_ptr<Player> player = std::make_unique<Player>(Player::Player(200, jojo::Pi, jojo::Transform({ 400,300 }, 0, 6), jojo::g_modelManager.Get("ship.txt")));
		player->m_tag = "Player";
		player->m_game = this;
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Enemy::Enemy(jojo::randomf(75.0f, 150.0f), jojo::Pi, jojo::Transform({ 400,300 }, 0, 3), jojo::g_modelManager.Get("enemyShip.txt")));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		break;
	case SpaceGame::eState::PlayerDead:
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::GameOver:
		break;
	default:
		break;
	}

	//m_scoreText->Create(jojo::g_renderer, std::to_string(m_score), { 1,91,1,255 });
	m_scene->Update(dt); 
}

void SpaceGame::Draw(jojo::Renderer& renderer)
{
	if (m_state == eState::Title) {
		
		m_titleText->Draw(renderer, 350, 200);
	}

	m_scoreText->Draw(renderer, 350, 350);
	m_scene->Draw(renderer);
}
