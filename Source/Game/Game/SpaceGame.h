#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class SpaceGame : public jojo::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver,
	};

public:

	virtual bool Initalize() override;
	virtual bool Shutdown() override;
	virtual void Update(float dt) override;
	virtual void Draw(jojo::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	friend class Game;

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;

	std::shared_ptr<jojo::Font> m_font;
	std::unique_ptr<jojo::Text> m_scoreText;
	std::unique_ptr<jojo::Text> m_titleText;
};