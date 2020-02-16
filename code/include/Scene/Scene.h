#ifndef DE_SCENE_H
#define DE_SCENE_H

#include "DE_Class.h"

namespace DE {

template <class T> class List;
class GameObject;

class Scene : public DE_Class {

private:

	List<GameObject*>* mGameObjects;
	List<GameObject*>* mNewGameObjects;
	GameObject* mCameraGameObject;

	u32 mMaxNewGameObjectsToSpawn;

public:

	DE_CLASS(Scene, DE_Class);

	void init();

	void addGameObject(GameObject* gameObject);
	void removeGameObject(GameObject* gameObject);

	List<GameObject*>* getGameObjects() const { return mGameObjects; };
	List<GameObject*>* getNewGameObjects() const { return mNewGameObjects; };
	GameObject* getCameraGameObject() const { return mCameraGameObject; };
	void setCameraGameObject(GameObject* newCameraGameObject ) { mCameraGameObject = newCameraGameObject; };

	u32 getMaxNewGameObjectsToSpawn() const { return mMaxNewGameObjectsToSpawn; };

	bool thereAreNewGameObjects() const;
	void flushNewGameObjects();
};

} /* namespace DE */

#endif /* DE_SCENE_H */
