#pragma once
#include "ui_Element.h"
#include "SFML/Graphics.hpp"

enum BUTTON_SIZE {
    TINY,
    SMALL,
    MEDIUM,
    LARGE,
    MASSIVE
};

class Button : public uiElement {
public:
    Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string text);
    Button(sf::Vector2f position, BUTTON_SIZE size, sf::Color color, std::string text);
    ~Button();
    void update(sf::Vector2f mousePos);
    void render(sf::RenderWindow& window);
    bool isClicked();

private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Font m_font;
    bool m_clicked;
};

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string text)
    : m_clicked(false)
{
    if (!m_font.loadFromFile("arial.ttf")) {
        //blegh
    }

    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(color);

    m_text.setString(text);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = m_text.getLocalBounds();
    while (textRect.width > size.x || textRect.height > size.y) {
        m_text.setCharacterSize(m_text.getCharacterSize() - 1);
        textRect = m_text.getLocalBounds();
    }
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_text.setPosition(position + size / 10.0f);
    m_text.setFont(m_font);

    //drawableList[0] = &m_shape;
    //drawableList[1] = &m_text;
}

Button::Button(sf::Vector2f position, BUTTON_SIZE size, sf::Color color, std::string text)
    : m_clicked(false)
{
    if (!m_font.loadFromFile("arial.ttf")) {
        //blegh
    }

    m_shape.setPosition(position);
    m_shape.setFillColor(color);

    m_text.setString(text);
    m_text.setFillColor(sf::Color::Black);

    sf::Vector2f m_size;
    int m_csize = 14;
    switch (size) {
    case TINY:
        m_size = { 50, 20 };
        m_csize = 9;
        break;
    case SMALL:
        m_size = { 75, 30 };
        m_csize = 12;
        break;
    case MEDIUM:
        m_size = { 100, 40 };
        m_csize = 14;
        break;
    case LARGE:
        m_size = { 150, 60 };
        m_csize = 18;
        break;
    case MASSIVE:
        m_size = { 200, 80 };
        m_csize = 24;
        break;

    default:
        m_size = { 100, 40 };
        m_csize = 14;
        break;
    }

    m_shape.setSize(m_size);
    m_text.setCharacterSize(m_csize);
    sf::FloatRect textRect = m_text.getLocalBounds();
    //m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    int xPad = (m_size.x - textRect.width) / 5.0f;
    int yPad = (m_size.y - textRect.height) / 5.0f;

    m_text.setPosition(position.x + xPad, position.y + yPad);
    m_text.setFont(m_font);

    //drawableList[0] = &m_shape;
    //drawableList[1] = &m_text;
}

Button::~Button() {
}

void Button::update(sf::Vector2f mousePos) {
    if (m_shape.getGlobalBounds().contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            m_clicked = true;
        }
    }
}

void Button::render(sf::RenderWindow& window) {
    window.draw(m_shape);
    window.draw(m_text);
}

bool Button::isClicked() {
    if (m_clicked) {
        m_clicked = false;
        return true;
    }
    return false;
}


namespace UIButtonHelper {
    std::map<int, Button*> list;

    int createButton(sf::Vector2f position, BUTTON_SIZE size, sf::Color color, std::string text) {
        auto tempEnt = new Button(position, size, color, text);

        list[tempEnt->id] = tempEnt;
        UIButtonHelper::list[tempEnt->id] = tempEnt;

        return tempEnt->id;
    }

    int createExactButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string text) {
        auto tempEnt = new Button(position, size, color, text);

        list[tempEnt->id] = tempEnt;
        UIButtonHelper::list[tempEnt->id] = tempEnt;

        return tempEnt->id;
    }
}