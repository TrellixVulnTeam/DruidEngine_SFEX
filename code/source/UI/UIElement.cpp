#include "UIElement.hpp"

#include "Collider.hpp"
#include "Renderer.hpp"
#include "List.hpp"

#include "EventsManager.hpp"
#include "InputEvents.hpp"
#include "Event.hpp"

#include "Input.hpp"
#include "RenderEngine.hpp"
#include "Vector2.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "UI.hpp"

namespace DE {

// ---------------------------------------------------------------------------

UIElement::UIElement() : GameObject() {
	mCollider = nullptr;
	mRenderer = nullptr;
	mPressed = false;
	mConsumeInput = true;
	mGroup = nullptr;
}

// ---------------------------------------------------------------------------

UIElement::~UIElement() = default;

void UIElement::init() {
	GameObject::init();
}

// ---------------------------------------------------------------------------

void UIElement::subscribeToKeyEvents() {
	DE_SUBSCRIBE_TO_EVENT(InputEventKeyPressed, [](const Event* event){

	});

	DE_SUBSCRIBE_TO_EVENT(InputEventKeyReleased, [](const Event* event){

	});
}

void UIElement::subscribeToCharEvents() {
	DE_SUBSCRIBE_TO_EVENT(InputEventChar, [this](const Event* event){

		// TODO : boolean to enable or disable : can receive char input?
		onChar(((const InputEventChar*)event)->mChar);
	});
}

void UIElement::subscribeToMouseButtonEvents() {
	DE_SUBSCRIBE_TO_EVENT(InputEventMouseButtonPressed, [this](const Event* event){
		//ECHO("InputEventMouseButtonPressed")
		const InputEventMouseButtonPressed* e = (const InputEventMouseButtonPressed*)event;

		if(e->mButton == GLFW_MOUSE_BUTTON_LEFT){
			onPressed();
		}
	});

	DE_SUBSCRIBE_TO_EVENT(InputEventMouseButtonReleased, [this](const Event* event){

	});
}

void UIElement::subscribeToEnterEvent() {
	DE_SUBSCRIBE_TO_EVENT(InputEventKeyEnter, [this](const Event* event){
		onFocusLost(); // TODO : call something more generic
	});
}

void UIElement::subscribeToEscEvent() {
	DE_SUBSCRIBE_TO_EVENT(InputEventKeyEsc, [this](const Event* event){
		onFocusLost(); // TODO : call something more generic
	});
}

// ---------------------------------------------------------------------------

bool UIElement::hasFocus() const {
	return this == UI::getInstance()->getFocusedElement();
}

void UIElement::onChar(c8 character) {
	if(hasFocus()){
		mInputString += character;
		setText(mInputString);
	}
}

void UIElement::onFocusLost() {
	if(hasFocus()){
		mOnFocusLostFunctor.execute();
		mInputString.clear();
	}
}

void UIElement::onFocus() {

}


// ---------------------------------------------------------------------------

void UIElement::onPressed() {

	Collider* collider = getCollider();
	// TODO : boolean to enable or disable : can be pressed?

	if (collider){

		Vector2 screenMousePosition(Input::getInstance()->getMousePosition());
		Vector2 worldMousePosition = Vector2(
				RenderEngine::getInstance()->getCamera()->screenToWorld(screenMousePosition));

		collider->getBoundingBox(true); // force regenerate bounding box
		Vector2 mousePosition = getTransform()->isAffectedByProjection() ? worldMousePosition : screenMousePosition;
		bool clickOk = collider->testPoint(mousePosition) == ColliderStatus::STATUS_PENETRATION;

		if(clickOk){
			mPressed = true;
			//mRenderer->setColor(Vector4(1.0f,1.0f,0.0f,1.0f));
			mOnPressedFunctor.execute();

			if(!hasFocus()) {
				UIElement* lastFocusedElement = UI::getInstance()->getFocusedElement();

				if(lastFocusedElement) {
					lastFocusedElement->onFocusLost();
				}

				UI::getInstance()->setFocusedElement(this);
				onFocus();
			}

			if (isConsumeInput()) {
				Input::getInstance()->clearMouseButton();
			}
		}
		/*else {
			UIElement* lastFocusedElement = UI::getInstance()->getFocusedElement();

			if(lastFocusedElement) {
				lastFocusedElement->onFocusLost();
			}

			UI::getInstance()->setFocusedElement(nullptr);
		}*/
	}
}

// ---------------------------------------------------------------------------

void UIElement::onReleased() {

	// TODO : boolean to enable or disable : can be pressed?

	mPressed = false;
	//mRenderer->setColor(Vector4(0.0f,0.0f,0.0f,1.0f));
	mOnReleasedFunctor.execute();
}

// ---------------------------------------------------------------------------

void UIElement::setComponentsCache() {
	mRenderer = getComponents<Renderer>() && getComponents<Renderer>()->getLength() > 0 ? getComponents<Renderer>()->get(0) : nullptr;
	mCollider = getComponents<Collider>() && getComponents<Collider>()->getLength() > 0 ? getComponents<Collider>()->get(0) : nullptr;
}

// ---------------------------------------------------------------------------

void UIElement::setVisibility(bool visibility) {
	getRenderer()->setIsActive(visibility);
	setIsActive(visibility);
}

bool UIElement::isVisible(){
	return getRenderer()->isActive();
}

} /* namespace DE */
