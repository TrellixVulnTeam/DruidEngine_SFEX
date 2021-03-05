#pragma once

#include "Core/DE_Class.hpp"
#include "Core/Singleton.hpp"
#include "Scene/GameObject.hpp"
#include "Maths/Vector3.hpp"

namespace DE {

class Material;

class GameObjectBuilder: public DE_Class, public Singleton<GameObjectBuilder> {

private:

	DE_M_GET(GameObject, GameObject*)

public:

	DE_CLASS_BODY(GameObjectBuilder)

	GameObjectBuilder* createSprite(Material* material, u32 layer, bool isStatic);
};

}

