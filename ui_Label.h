//#pragma once
//#include "ui_Element.h"
//#include "SFML/Graphics.hpp"
//
//enum ALIGNMENT {
//    ALIGN_CENTER,
//    ALIGN_LEFT,
//    ALIGN_RIGHT
//};
//
//class Label : public uiElement {
//public:
//    Label(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color text_color, std::string text, ALIGNMENT alignment);
//    ~Label();
//    void update(sf::Vector2f mousePos);
//    void render(sf::RenderWindow& window);
//    bool isClicked();
//
//private:
//    sf::RectangleShape m_shape;
//    sf::Text m_text;
//    sf::Font m_font;
//    ALIGNMENT alignment;
//    bool m_clicked;
//};
//
//Label::Label(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color text_color, std::string text, ALIGNMENT align)
//    : m_clicked(false)
//{
//    if (!m_font.loadFromFile("arial.ttf")) {
//        //blegh
//    }
//
//    alignment = align;
//
//    m_shape.setPosition(position);
//    m_shape.setSize(size);
//    m_shape.setFillColor(color);
//
//    m_text.setString(text);
//    m_text.setCharacterSize(24);
//    m_text.setFillColor(text_color);
//    sf::FloatRect textRect = m_text.getLocalBounds();
//    while (textRect.width > size.x || textRect.height > size.y) {
//        m_text.setCharacterSize(m_text.getCharacterSize() - 1);
//        textRect = m_text.getLocalBounds();
//    }
//    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
//    m_text.setPosition(position + size / 10.0f);
//    m_text.setFont(m_font);
//
//    //drawableList[0] = &m_shape;
//    //drawableList[1] = &m_text;
//}
//
//Label::~Label() {
//}
//
//void Label::update(sf::Vector2f mousePos) {
//    if (m_shape.getGlobalBounds().contains(mousePos)) {
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            m_clicked = true;
//        }
//    }
//}
//
//void Label::render(sf::RenderWindow& window) {
//    window.draw(m_shape);
//    window.draw(m_text);
//}
//
//bool Label::isClicked() {
//    if (m_clicked) {
//        m_clicked = false;
//        return true;
//    }
//    return false;
//}
//
//
//namespace UILabelHelper {
//    std::map<int, Label*> list;
//
//    int createLabel(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color text_color, std::string text, ALIGNMENT alignment) {
//        auto tempEnt = new Label(position, size, color, text_color, text, alignment);
//
//        list[tempEnt->id] = tempEnt;
//        UILabelHelper::list[tempEnt->id] = tempEnt;
//
//        return tempEnt->id;
//    }
//
//}