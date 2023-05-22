#pragma once

#include <Geode/Geode.hpp>

class GameObjectController {
 protected:
	GameObject* m_object;
	bool m_glowEnabled;
 public:
 	GameObjectController(GameObject* g) : m_object(g) {}

 	// These are for saving custom data for objects
 	inline virtual std::map<uint32_t, std::string> onExport() {
		return std::map<uint32_t, std::string>();
 	}
 	inline virtual void onImport(std::map<uint32_t, std::string> data) {}

 	// This happens when the object is reset, typically when the game resets
 	inline virtual void onReset() {}

 	// This happens when the object is "triggered", like a move trigger
 	inline virtual void onTrigger(GJBaseGameLayer* gl) {}

 	// This happens when the player collides with the object
 	inline virtual void onCollide(float dt, PlayerObject* pl) { pl->collidedWithObject(dt, m_object); }

 	// All setup goes here
 	inline virtual void setup() {}

 	inline bool isGlowEnabled() { return m_glowEnabled; }

 	// Simple getters and setters for the underlying GameObject
 	inline GameObject* getObject() { return m_object; }
 	inline void setObject(GameObject* g) { m_object = g; }

 	// Setup custom sprite frame name
 	inline void overrideSpriteFrame(std::string const& fname) {
 		m_object->m_parentMode = -2;

 		auto cache = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache();
 		auto frame = cache->spriteFrameByName(fname.c_str());

 		m_object->setDisplayFrame(frame);
 		m_object->m_objectSize = cocos2d::CCSizeMake(frame->getRect().size.width, frame->getRect().size.height);

 		m_object->m_textureName = fname;
 	}

 	// Set custom texture
 	inline void overrideTexture(cocos2d::CCTexture2D* texture) {
 		m_object->m_parentMode = -2;
 		m_object->setTexture(texture);
 		m_object->setTextureRect(cocos2d::CCRectMake(0, 0, texture->getContentSize().width, texture->getContentSize().height));
 		m_object->m_objectSize = cocos2d::CCSizeMake(texture->getContentSize().width, texture->getContentSize().height);
 	}
};