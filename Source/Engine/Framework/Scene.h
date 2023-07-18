#pragma once
#include "Actor.h"
#include <list>

namespace jojo
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		void Update(float gt);
		void Draw(Renderer& renderer);

		void Add(Actor* actor);
		void Remove(Actor* actor);
		void RemoveAll();

		friend class Actor;

	private:
		std::list<Actor*> m_actors;
	};

}