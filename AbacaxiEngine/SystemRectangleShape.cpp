#include "pch.h"
#include "SystemRectangleShape.h"
#include "Entity.h"
#include "Window.h"

abx::SystemRectangleShape::SystemRectangleShape(){}

abx::SystemRectangleShape::~SystemRectangleShape(){}

void abx::SystemRectangleShape::Render(){
	auto window = m_entity->GetSharedData()->m_window;

	window->Draw(&m_shape);
}

void abx::SystemRectangleShape::OnCreate(){
	m_shape.setSize(sf::Vector2f(500, 500));
	m_shape.setFillColor(sf::Color::Red);
}

sf::RectangleShape* abx::SystemRectangleShape::GetShape(){
	return &m_shape;
}
