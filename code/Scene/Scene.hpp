#pragma once

#include "Core/DE_Class.hpp"
#include "File/File.hpp"

namespace DE {

template<class T> class List;
class GameObject;

class Scene: public DE_Class {

private:

	DE_M_GET(GameObjects, List<GameObject*>*)
	DE_M_GET(NewGameObjects, List<GameObject*>*)
	DE_M_GET_SET(CameraGameObject, GameObject*)

	DE_M_GET(Size, f32)
	DE_M_GET(Path, std::string)

	void destroyGameObjects();

public:

	DE_CLASS(Scene)

	void init();

	void loadScene(const std::string &path);
	void saveScene(const std::string &path);
	void unloadScene();

	void addGameObject(GameObject *gameObject);
	void updateComponents(GameObject *gameObject);
	void removeGameObject(GameObject *gameObject);

	void step();

	bool thereAreNewGameObjects() const;
	void flushNewGameObjects();
};

}

