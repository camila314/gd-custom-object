#include <Geode.hpp>
#include <GameObjectFactory.hpp>

USE_GEODE_NAMESPACE();

using namespace cocos2d;

class TestObject : public GameObjectController {
 public:
	TestObject(GameObject* g) : GameObjectController(g) {}

	void onTrigger(GJBaseGameLayer* gl) override {
		auto r = CCScaleTo::create(1.0, 1.25f, 0.75f);
		gl->m_objectLayer->runAction(r);
	}

	void setup() override {
		m_glowEnabled = false;
		overrideSpriteFrame("GJ_arrow_01_001.png");

		m_object->m_touchTriggered = true;
		m_object->m_objectType = GameObjectType::Modifier;
	}
};

GEODE_API void GEODE_DLL geode_load(Mod*) {
	GameObjectFactory::get()->add(1, [](GameObject* g) {
		return new TestObject(g);
	});
}
