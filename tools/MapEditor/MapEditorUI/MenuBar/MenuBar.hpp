#pragma once

#include "Maths/Vector2.hpp"
#include <string>
#include "UI/UIElement.hpp"
#include "../StringsUI.hpp"

namespace DE {

class Transform;
class Renderer;
class RigidBody;
class Collider;
class GameObject;
class Camera;
class UIButton;
class UIText;
class UITextEditable;
class Texture;
class Material;
template<class K, class V> class HashMap;
template<class T> class Array;
template<class T> class List;

class MapEditor;

class MenuBar : public DE_Class{

private:

	const StringsUI mStringsUI;

	MapEditor* mMapEditor;

public:

	DE_CLASS(MenuBar)

	void init(MapEditor *mapEditor);

	void createMenuBar();
};

}

