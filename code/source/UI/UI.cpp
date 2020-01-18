#include "UI.h"
#include "Memory.h"
#include "Texture.h"
#include "Material.h"
#include "GameObject.h"
#include "Renderer.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Input.h"
#include "Camera.h"
#include "RenderEngine.h"
#include "List.h"
#include "HashMap.h"

#include "UIElement.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIText.h"

namespace DE {

// ---------------------------------------------------------------------------

UI::UI() : DE_Class(), Singleton() {
  mButtonTexture = nullptr;
  mButtonMaterial = nullptr;
  mFontTexture = nullptr;
  mFontMaterial = nullptr;
  mUIElements = nullptr;
}

UI::~UI() = default;

// ---------------------------------------------------------------------------

UIButton* UI::createButton(const Vector2& position, const Vector2& size) {

  if( ! mButtonTexture){
    mButtonTexture = Memory::allocate<Texture>();
    mButtonTexture->init("resources/button.bmp");

    mButtonMaterial = Memory::allocate<Material>();
    mButtonMaterial->init();
    mButtonMaterial->setTexture(mButtonTexture);
    mButtonMaterial->setShader(Shader::getDefaultShader());
  }

  UIButton* uiButton = Memory::allocate<UIButton>();
  uiButton->init();

  uiButton->getTransform()->setLocalPosition(position);
  uiButton->getTransform()->setScale(Vector3(size.x,size.y,1));

  Renderer* renderer = Memory::allocate<Renderer>();
  uiButton->addComponent<Renderer>(renderer);

  renderer->setMesh(Mesh::getRectangle());
  renderer->setMaterial(mButtonMaterial);

  RigidBody* rigidBody = Memory::allocate<RigidBody>();
  uiButton->addComponent<RigidBody>(rigidBody);
  rigidBody->setSimulate(false);

  Collider* collider = Memory::allocate<Collider>();
  uiButton->addComponent<Collider>(collider);
  collider->setSize(size.x,size.y);
  collider->getBoundingBox();

  uiButton->setComponentsCache();

  mUIElements->pushBack(uiButton);

  return uiButton;
}

// ---------------------------------------------------------------------------

UIText* UI::createText(const Vector2& position, const Vector2& size, const std::string& text) {

  if( ! mFontTexture){
    mFontTexture = Memory::allocate<Texture>();
    mFontTexture->init("resources/font16x16.png");

    mFontMaterial = Memory::allocate<Material>();
    mFontMaterial->init();
    mFontMaterial->setTexture(mFontTexture);
    mFontMaterial->setShader(Shader::getDefaultShader());
  }

  UIText* uiText = Memory::allocate<UIText>();
  uiText->init();

  uiText->getTransform()->setLocalPosition(position);
  uiText->getTransform()->setScale(Vector3(size.x, size.y,1));

  FOR_RANGE(i, 0, text.length()){
      Renderer* renderer = Memory::allocate<Renderer>();
      uiText->addComponent<Renderer>(renderer);

      renderer->setPositionOffset(Vector3(i * size.x, 0,0));

      renderer->setMesh(Mesh::getRectangle());
      renderer->setMaterial(mFontMaterial);

      renderer->setRegion(mCharMap->get(text.at(i)).x, mCharMap->get(text.at(i)).y, mFontTileTextureSize, mFontTileTextureSize);
  }

  uiText->setComponentsCache();

  mUIElements->pushBack(uiText);

  return uiText;
}

// ---------------------------------------------------------------------------

void UI::init() {
  mUIElements = Memory::allocate<List<UIElement*>>();
  mUIElements->init();

  mFontTilesCount = 16;
  mFontTileTextureSize = 1.0f/mFontTilesCount;

  mCharMap = Memory::allocate<HashMap<c8, Vector2>>();
  mCharMap->init();

  mCharMap->set(' ',Vector2(0/mFontTilesCount, 0/mFontTilesCount));

  mCharMap->set('!',Vector2(1/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('\"',Vector2(2/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('#',Vector2(3/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('$',Vector2(4/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('%',Vector2(5/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('&',Vector2(6/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('(',Vector2(8/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set(')',Vector2(9/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('*',Vector2(10/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('+',Vector2(11/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set(',',Vector2(12/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('-',Vector2(13/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('.',Vector2(14/mFontTilesCount, 2/mFontTilesCount));
  mCharMap->set('/',Vector2(15/mFontTilesCount, 2/mFontTilesCount));

  mCharMap->set('0',Vector2(0/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('1',Vector2(1/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('2',Vector2(2/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('3',Vector2(3/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('4',Vector2(4/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('5',Vector2(5/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('6',Vector2(6/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('7',Vector2(7/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('8',Vector2(8/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('9',Vector2(9/mFontTilesCount, 3/mFontTilesCount));

  mCharMap->set(':',Vector2(10/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set(';',Vector2(11/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('<',Vector2(12/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('=',Vector2(13/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('>',Vector2(14/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('?',Vector2(15/mFontTilesCount, 3/mFontTilesCount));
  mCharMap->set('@',Vector2(0/mFontTilesCount, 4/mFontTilesCount));

  mCharMap->set('A',Vector2(1/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('B',Vector2(2/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('C',Vector2(3/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('D',Vector2(4/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('E',Vector2(5/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('F',Vector2(6/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('G',Vector2(7/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('H',Vector2(8/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('I',Vector2(9/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('J',Vector2(10/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('K',Vector2(11/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('L',Vector2(12/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('M',Vector2(13/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('N',Vector2(14/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('O',Vector2(15/mFontTilesCount, 4/mFontTilesCount));
  mCharMap->set('P',Vector2(0/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('Q',Vector2(1/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('R',Vector2(2/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('S',Vector2(3/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('T',Vector2(4/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('U',Vector2(5/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('V',Vector2(6/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('W',Vector2(7/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('X',Vector2(8/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('Y',Vector2(9/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('Z',Vector2(10/mFontTilesCount, 5/mFontTilesCount));

  mCharMap->set('[',Vector2(11/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('\\',Vector2(12/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set(']',Vector2(13/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('^',Vector2(14/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('_',Vector2(15/mFontTilesCount, 5/mFontTilesCount));
  mCharMap->set('`',Vector2(0/mFontTilesCount, 6/mFontTilesCount));

  mCharMap->set('a',Vector2(1/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('b',Vector2(2/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('c',Vector2(3/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('d',Vector2(4/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('e',Vector2(5/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('f',Vector2(6/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('g',Vector2(7/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('h',Vector2(8/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('i',Vector2(9/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('j',Vector2(10/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('k',Vector2(11/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('l',Vector2(12/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('m',Vector2(13/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('n',Vector2(14/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('o',Vector2(15/mFontTilesCount, 6/mFontTilesCount));
  mCharMap->set('p',Vector2(0/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('q',Vector2(1/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('r',Vector2(2/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('s',Vector2(3/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('t',Vector2(4/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('u',Vector2(5/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('v',Vector2(6/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('w',Vector2(7/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('x',Vector2(8/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('y',Vector2(9/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('z',Vector2(10/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('{',Vector2(11/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('|',Vector2(12/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('}',Vector2(13/mFontTilesCount, 7/mFontTilesCount));
  mCharMap->set('~',Vector2(14/mFontTilesCount, 7/mFontTilesCount));
}

// ---------------------------------------------------------------------------

void UI::step() {

  if(Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){

    Vector2 mouse(Input::getMousePosition());
    Vector3 world = RenderEngine::getInstance()->getCamera()->screenToWorld(mouse);

    FOR_LIST(it, mUIElements){

      UIElement* element = it.get();

      Collider* collider = element->getCollider();

      if(collider->testPoint(world) == ColliderStatus::STATUS_PENETRATION){

        element->onPressed();
        element->getRenderer()->setColor(Vector4(0.25f,0.25f,0.25f,1.0f));
      }
    }
  }
}

// ---------------------------------------------------------------------------

void UI::terminate() {
//  FOR_LIST(it, mUIElements){
//    Memory::free<UIElement>(it.get());
//  }

	Memory::free<HashMap<c8, Vector2>>(mCharMap);

  Memory::free<List<UIElement*>>(mUIElements);
}

// ---------------------------------------------------------------------------

} /* namespace DE */
