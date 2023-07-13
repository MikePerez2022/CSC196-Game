#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"

class Actor
{
public:
	Actor() = default;
	Actor(const jojo::Transform& transform, const jojo::Model& model) : m_transform{ transform }, m_model{ model } {}

	virtual void Update(float dt) = 0;
	virtual void Draw(jojo::Renderer& renderer);

protected:
	jojo::Transform m_transform;
	jojo::Model m_model;
};