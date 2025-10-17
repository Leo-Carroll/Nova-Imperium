#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <functional>
#include <thread>
#include <chrono>

class Button {
public:
	bool m_WasPressed;
	sf::Text m_Label;
	sf::RectangleShape m_Rect;
	std::function<void()> m_OnClick;

	Button(const sf::Font& font, const std::string& label, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f size = sf::Vector2f(50.0f, 50.0f), std::function<void()> onClick = nullptr)
		: m_Label(font, label, 20U), m_OnClick(onClick) {
		m_WasPressed = false;

		m_Rect.setPosition(position);
		m_Rect.setSize(size);

		m_Rect.setFillColor(sf::Color::Black);
		m_Rect.setOutlineColor(sf::Color::White);
		m_Rect.setOutlineThickness(2);

		sf::FloatRect textBounds = m_Label.getGlobalBounds();
		m_Label.setOrigin(sf::Vector2f(textBounds.size.x / 2.0f, textBounds.size.y / 2.0f));
		m_Label.setPosition(sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2 - 5));
	}

	void UpdateTextPosition() {
		sf::FloatRect textBounds = m_Label.getGlobalBounds();
		m_Label.setOrigin(sf::Vector2f(textBounds.size.x / 2.0f, textBounds.size.y / 2.0f));
		m_Label.setPosition(sf::Vector2f(m_Rect.getPosition().x + m_Rect.getSize().x / 2, m_Rect.getPosition().y + m_Rect.getSize().y / 2 - 5));
	}

	bool IsPressed(unsigned int mx, unsigned int my, bool mouseButtonPressed) {
		if (m_Rect.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mx), static_cast<float>(my))) && mouseButtonPressed && !m_WasPressed) {
			m_WasPressed = mouseButtonPressed;
			return true;
		}
		m_WasPressed = mouseButtonPressed;
		return false;
	}
};