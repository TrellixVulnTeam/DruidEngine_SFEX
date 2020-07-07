#ifndef DE_PLAYERSCRIPT_H
#define DE_PLAYERSCRIPT_H

#include "Script.hpp"
#include "Vector2.hpp"
#include "Vector4.hpp"
#include "Element.hpp"

namespace DE {

class UIText;
class Renderer;
class RigidBody;

class PlayerScript: public Script {

private:
	Renderer* mRenderer;
	RigidBody* mRigidBody;
	f32 mAttackAnimTime;
	f32 mAttackAnimTimeCount;
	bool mIsAttackPlaying;

	GameObject* mBook;
	Vector4 mBookColor;
	Element mElement;
	u32 mMana;
	bool mManaChanged;

public:

	DE_CLASS(PlayerScript, Script)
	;

	void init() override;
	void firstStep() override;
	void step() override;
	void terminate() override;

	void onEnterCollision(GameObject *otherGameObject) override;
	void onCollision(GameObject *otherGameObject) override;
	void onExitCollision(GameObject *otherGameObject) override;

	void createProjectile(f32 x, f32 y, f32 clickX, f32 clickY);
	void createWall(f32 x, f32 y);
	void createBook(f32 x, f32 y, const Vector4 &color);

	void setBookColor(const Vector4 &color) {
		mBookColor = color;
	}
	void setElement(Element element) {
		mElement = element;
	}

	u32 getMana() const {
		return mMana;
	}
	bool isManaChanged() const {
		return mManaChanged;
	}
	void setMana(u32 mana) {
		mMana = mana;
	}

};

} /* namespace DE */

#endif /* DE_PLAYERSCRIPT_H */