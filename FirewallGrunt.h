//#pragma once
//#include "AIEntity.h"
//
//class FirewallGrunt : public AIEntity {
//public:
//	sf::Texture IdleTexture;
//	sf::IntRect IdleRectSourceSprite;
//
//	sf::Texture RunningTexture;
//	sf::IntRect RunningRectSourceSprite;
//
//	sf::Sprite sprite;
//	sf::Clock spriteClock;
//
//	FirewallGrunt(sf::Vector2f pos, sf::RectangleShape& shape) {
//		
//	}
//
//	void animate() {
//
//		if (isRunning) {
//			sprite.setTexture(RunningTexture);
//			sprite.setTextureRect(RunningRectSourceSprite);
//
//			if (spriteClock.getElapsedTime().asSeconds() > 0.1f) {
//				if (RunningRectSourceSprite.left == (384 - 48))
//				{
//					RunningRectSourceSprite.left = 0;
//				}
//				else
//				{
//					RunningRectSourceSprite.left += 48;
//				}
//				sprite.setTextureRect(RunningRectSourceSprite);
//				spriteClock.restart();
//			}
//		}
//		else {
//			sprite.setTexture(IdleTexture);
//			sprite.setTextureRect(IdleRectSourceSprite);
//
//			if (spriteClock.getElapsedTime().asSeconds() > 0.1f) {
//
//				if (IdleRectSourceSprite.left == (480 - 48))
//				{
//					IdleRectSourceSprite.left = 0;
//				}
//				else
//				{
//					IdleRectSourceSprite.left += 48;
//				}
//				sprite.setTextureRect(IdleRectSourceSprite);
//				spriteClock.restart();
//			}
//		}
//	}
//	
//
//};