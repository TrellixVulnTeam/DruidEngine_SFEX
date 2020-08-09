#include "UIBuilder.hpp"
#include "Memory.hpp"
#include "Texture.hpp"
#include "MaterialManager.hpp"
#include "Material.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "RenderEngine.hpp"
#include "RenderContext.hpp"
#include "List.hpp"
#include "HashMap.hpp"
#include "UI.hpp"

namespace DE {

// ---------------------------------------------------------------------------

UIElementData::UIElementData() : DE_Class() {
	mIsAffectedByLayout = true;
}

UIElementData::~UIElementData() = default;

void UIElementData::init(const Vector2 &position, const Vector2 &size, const std::string& text, u32 layer){
	mPosition = position;
	mSize = size;
	mText = text;
	mLayer = layer;
	mIsAffectedByLayout = true;
	mSeparatorSize = 0.01f;
}

// ---------------------------------------------------------------------------

void UIElementData::copy(UIElementData& otherData){
	mPosition = otherData.mPosition;
	mSize = otherData.mSize;
	mText = otherData.mText;
	mLayer = otherData.mLayer;
	mIsAffectedByLayout = otherData.mIsAffectedByLayout;
}

// ---------------------------------------------------------------------------


UIBuilder::UIBuilder() : DE_Class(), Singleton() {
	mScene = nullptr;
	mButtonMaterial = nullptr;
	mCurrentLayout = UILayout::VERTICAL;
	mLastUIElement = nullptr;
	mCurrentUIElement = nullptr;

	mData.init(Vector2(0,0), Vector2(0,0), "", 0);
	mSavedData.init(Vector2(0,0), Vector2(0,0), "", 0);
}

UIBuilder::~UIBuilder() = default;

// ---------------------------------------------------------------------------

UIBuilder* const UIBuilder::setScene(Scene *scene) {
	mScene = scene;
	return this;
}

UIBuilder* const UIBuilder::setLayout(UILayout layout) {
	mCurrentLayout = layout;

	// reset Last Element
	mLastUIElement = nullptr;

	return this;
}

UIBuilder* const UIBuilder::setIsAffectedByLayout(bool affectedByLayout){
	mData.mIsAffectedByLayout = affectedByLayout;
	return this;
}

UIBuilder* const UIBuilder::setData(UIElementData data) {
	mData.copy(data);
	return this;
}

UIBuilder* const UIBuilder::setPosition(const Vector2 &position) {
	mData.mPosition = position;
	return this;
}

UIBuilder* const UIBuilder::setSize(const Vector2 &size) {
	mData.mSize = size;
	return this;
}

UIBuilder* const UIBuilder::setLayer(u32 layer) {
	mData.mLayer = layer;
	return this;
}

UIBuilder* const UIBuilder::setText(const std::string &text) {
	mData.mText = text;
	return this;
}

UIBuilder* const UIBuilder::setSeparatorSize(f32 separatorSize) {
	mData.mSeparatorSize = separatorSize;
	return this;
}

UIBuilder* const UIBuilder::restoreSeparatorSize() {
	mData.mSeparatorSize = 0.01f;
	return this;
}

void UIBuilder::calculateData(){
	if(mData.mIsAffectedByLayout && mLastUIElement) {
		Vector2 offset = Vector2(0,0);

		switch (mCurrentLayout) {
			case UILayout::HORIZONTAL: {
				f32 lastElementHalfSize = mLastData.mSize.x / 2.0f;
				f32 newElementHalfSize = mData.mSize.x / 2.0f;
				offset = Vector2(lastElementHalfSize + newElementHalfSize + mData.mSeparatorSize, 0);
				break;
			}
			case UILayout::VERTICAL:{
				f32 lastElementHalfSize = mLastData.mSize.y / 2.0f;
				f32 newElementHalfSize = mData.mSize.y / 2.0f;
				offset = Vector2(0, -(lastElementHalfSize + newElementHalfSize + mData.mSeparatorSize));
				break;
			}
		}

		mData.mPosition = mLastData.mPosition + offset;
	}
}

UIBuilder* const UIBuilder::saveData() {
	mSavedData.copy(mData);
	return this;
}

UIBuilder* const UIBuilder::restoreData() {
	mData.copy(mSavedData);
	return this;
}

// ---------------------------------------------------------------------------

UIButton* UIBuilder::createButton() {

	calculateData();

	if (!mButtonMaterial) {
		mButtonMaterial = MaterialManager::getInstance()->loadMaterial("resources/button.png");
	}

	UIButton* uiButton = Memory::allocate<UIButton>();
	uiButton->init();

	Vector2 aspectRatioCorrectedPosition = Vector2(mData.mPosition.x / RenderContext::getAspectRatio(), mData.mPosition.y);

	uiButton->getTransform()->setLocalPosition(aspectRatioCorrectedPosition);
	uiButton->getTransform()->setScale(Vector3(mData.mSize.x / RenderContext::getAspectRatio(), mData.mSize.y, 1));

	Renderer* renderer = Memory::allocate<Renderer>();
	uiButton->addComponent<Renderer>(renderer);

	renderer->setMesh(Mesh::getRectangle());
	renderer->setMaterial(mButtonMaterial);
	renderer->setLayer(mData.mLayer);

	renderer->setAffectedByProjection(false);

	RigidBody* rigidBody = Memory::allocate<RigidBody>();
	uiButton->addComponent<RigidBody>(rigidBody);
	rigidBody->setSimulate(false);

	Collider* collider = Memory::allocate<Collider>();
	uiButton->addComponent<Collider>(collider);
	collider->setSize(mData.mSize.x / RenderContext::getAspectRatio(), mData.mSize.y);
	collider->getBoundingBox();

	uiButton->setComponentsCache();

	uiButton->setIsStatic(true);

	mScene->addGameObject(uiButton);

	UI::getInstance()->addUIElement(uiButton);

	uiButton->setText(mData.mText);

	mCurrentUIElement = uiButton;

	if(mData.mIsAffectedByLayout)
		mLastUIElement = mCurrentUIElement;

	return uiButton;
}

// ---------------------------------------------------------------------------

UIText* UIBuilder::createText() {

	calculateData();

	UIText* uiText = Memory::allocate<UIText>();
	uiText->init();

	Vector2 aspectRatioCorrectedPosition = Vector2(mData.mPosition.x / RenderContext::getAspectRatio(), mData.mPosition.y);

	uiText->getTransform()->setLocalPosition(aspectRatioCorrectedPosition);
	uiText->getTransform()->setScale(Vector3(mData.mSize.x / RenderContext::getAspectRatio(), mData.mSize.y, 1));

	uiText->setSize(mData.mSize);
	uiText->setLayer(mData.mLayer);
	uiText->setText(mData.mText);

	uiText->setComponentsCache();

	uiText->setIsStatic(true);

	mScene->addGameObject(uiText);

	UI::getInstance()->addUIElement(uiText);

	mCurrentUIElement = uiText;

	if(mData.mIsAffectedByLayout)
		mLastUIElement = mCurrentUIElement;

	return uiText;
}

// ---------------------------------------------------------------------------

UIText* UIBuilder::createTextBox() {

	calculateData();

	UIText* uiText = Memory::allocate<UIText>();
	uiText->init();

	Vector2 aspectRatioCorrectedPosition = Vector2(mData.mPosition.x / RenderContext::getAspectRatio(), mData.mPosition.y);

	uiText->getTransform()->setLocalPosition(aspectRatioCorrectedPosition);
	uiText->getTransform()->setScale(Vector3(mData.mSize.x / RenderContext::getAspectRatio(), mData.mSize.y, 1));

	RigidBody* rigidBody = Memory::allocate<RigidBody>();
	uiText->addComponent<RigidBody>(rigidBody);
	rigidBody->setSimulate(false);

	f32 width = mData.mSize.x * mData.mText.length() / RenderContext::getAspectRatio();
	Collider* collider = Memory::allocate<Collider>();
	uiText->addComponent<Collider>(collider);
	collider->setSize(width, mData.mSize.y);
	collider->setPositionOffset(Vector3(width/2.0f,0,0));
	collider->getBoundingBox();

	uiText->setSize(mData.mSize);
	uiText->setLayer(mData.mLayer);
	uiText->setText(mData.mText);

	uiText->setComponentsCache();

	uiText->setIsStatic(true);

	uiText->setOnPressedCallback([self = uiText]() {
		Input::setInputCharReceiver(self);
		self->setText("");
	});

	mScene->addGameObject(uiText);

	UI::getInstance()->addUIElement(uiText);

	mCurrentUIElement = uiText;

	if(mData.mIsAffectedByLayout)
		mLastUIElement = mCurrentUIElement;

	return uiText;
}

// ---------------------------------------------------------------------------

UIBuilder* const UIBuilder::create(UIElementType type) {

	switch (type) {
		case UIElementType::BUTTON:
			createButton();
			break;
		case UIElementType::TEXT:
			createText();
			break;
		case UIElementType::TEXTBOX:
			createTextBox();
			break;
		default:
			break;
	}

	if(mData.mIsAffectedByLayout)
		mLastData.copy(mData);

	return this;
}

UIElement* UIBuilder::getUIElement() {
	return mCurrentUIElement;
}

} /* namespace DE */