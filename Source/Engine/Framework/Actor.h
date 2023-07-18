#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
//#include "Scene.h"

namespace jojo
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const jojo::Transform& transform, const jojo::Model& model) : m_transform{ transform }, m_model{ model } {}

		virtual void Update(float dt) = 0;
		virtual void Draw(jojo::Renderer& renderer);

		//friend class scene;
		//class Scene* m_scene = nullptr;

	protected:
		Transform m_transform;
		Model m_model;
	};
}

