#include "Scene/Scene.hpp"
#include "Scene/GameObject.hpp"
#include "Scene/Transform.hpp"
#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
#include "Config/ConfigMap.hpp"
#include "Maths/MathUtils.hpp"
#include <future>         // std::async, std::future

Scene::Scene() {
	mGameObjects = nullptr;
}

Scene::~Scene() {

	destroyGameObjects();

	delete mGameObjects;
	delete mNewGameObjects;
	delete mLoadSceneConfigMap;
}

void Scene::destroyGameObjects() {
	FOR_LIST(it, *mGameObjects) {
		if (!(*it)->getIsDestroyed()) {
			(*it)->destroy();
			delete (*it);
		}
	}

	if(mCameraGameObject){
		//delete mCameraGameObject->getFirstComponent<Camera>();
		mCameraGameObject->destroy();
		delete mCameraGameObject;
	}
}

void Scene::init() {
	TRACE()

	mGameObjects = new std::list<GameObject*>;

	mNewGameObjects = new std::list<GameObject*>;

	mSize = 0;

	mPath = "config/sceneTmp.conf";

	// CAMERA
	GameObject* cameraGameObject = new GameObject;
	cameraGameObject->init();

	cameraGameObject->getTransform()->setLocalPosition(Vector3(0, 0, 0));

	//Camera* cameraComponent = new Camera;
	//cameraGameObject->addComponent<Camera>(cameraComponent);

	//f32 size = RenderContext::getWindowSize().y;
	// TODO : use RenderContext::getWindowSize().x also? To keep the scaleproportions?
	//cameraComponent->setOrtho(-size, size, -size, size, 1, -1);

	setCameraGameObject(cameraGameObject);

	// SET DEFAULT SIZE
	mSize = 4000; //EngineConfig::getInstance()->getF32("scene.defaultSize");

	mMaxGameObjectsToLoadPerFrame = 10; // TODO : move to settings
}

void Scene::loadScene(const std::string &path) {

	if(!mLoadSceneConfigMap){
		mLoadSceneConfigMap = new ConfigMap;
		mLoadSceneConfigMap->init();
	}
	else {
		mLoadSceneConfigMap->clear();
	}

	mPath = path;

	//std::future<void> fut = std::async (&ConfigMap::readConfigFile,&mLoadSceneConfigMap,mPath); 
	mLoadSceneConfigMap->readConfigFile(mPath); // TODO: do async / in other thread.
	//fut.wait();

	mSize = mLoadSceneConfigMap->getF32("scene.size");

	if (mSize == 0) {
		mSize = 4000; //EngineConfig::getInstance()->getF32("scene.defaultSize");
	}

	u32 length = mLoadSceneConfigMap->getU32("objects.length");

	mGameObjectsToLoadTotal = length;
	mGameObjectsToLoadIndex = 0;
}

void Scene::saveScene(const std::string &path) {

	ConfigMap* configMap = new ConfigMap;
	configMap->init();

	f32 maxSize = 0;
	u32 counter = 0;

	FOR_LIST(it, *mGameObjects) {
		if ((*it)->getShouldPersist()) {
			// ECHO("SAVE")
			std::string indexStr = std::to_string(counter);
			std::string objectName = "objects[" + indexStr + "]";

			Transform *t = (*it)->getTransform();
			Vector3 worldPosition = t->getWorldPosition();
			Vector3 scale = t->getScale();

			f32 maxObjectScale = std::max(std::abs(scale.x), std::abs(scale.y));
			maxSize = std::max(std::max(maxSize, std::abs(worldPosition.x) + maxObjectScale),
							   std::abs(worldPosition.y) + maxObjectScale);

			(*it)->save(configMap, objectName);

			counter++;
		}
	}

	configMap->setU32("objects.length", counter);
	configMap->setF32("scene.size", maxSize * 2.0f);

	configMap->writeConfigFile(path);

	delete configMap;
}

void Scene::unloadScene() {
	destroyGameObjects();
}

bool Scene::isLoadFinished() const {
	return mGameObjectsToLoadIndex == mGameObjectsToLoadTotal;
}

void Scene::addGameObject(GameObject *gameObject) {
	gameObject->setScene(this);
	mNewGameObjects->push_back(gameObject);
}

void Scene::updateComponents(GameObject *gameObject) {
	/*std::list<Renderer*>* rendererList = gameObject->getComponents<Renderer>();

	Script* script = gameObject->getFirstComponent<Script>();
	RigidBody* rigidBody = gameObject->getFirstComponent<RigidBody>();

	if (script && !script->getAlreadyAddedToEngine()) {
		ScriptEngine::getInstance()->addScript(script);
		script->setAlreadyAddedToEngine(true);
	}

	if (rendererList) {
		FOR_LIST (it, rendererList) {
			if (!(*it)->getAlreadyAddedToEngine()) {
				RenderEngine::getInstance()->addRenderer((*it));
				(*it)->setAlreadyAddedToEngine(true);
			}
		}
	}

	if (rigidBody) {
		if (!rigidBody->getAlreadyAddedToEngine()) {
			PhysicsEngine::getInstance()->addRigidBody(rigidBody);
			rigidBody->setAlreadyAddedToEngine(true);
		}

		Collider* collider = gameObject->getFirstComponent<Collider>();

		if (collider && !collider->getAlreadyAddedToEngine()) {
			PhysicsEngine::getInstance()->addCollider(rigidBody, collider);
			collider->setAlreadyAddedToEngine(true);
		}
	}*/
}

void Scene::removeGameObject(GameObject *gameObject) {

	if (!(gameObject->getIsDestroyed() || gameObject->getIsPendingToBeDestroyed())) {
		mGameObjects->remove(gameObject);

		gameObject->destroy();
		gameObject->finallyDestroy();
		delete gameObject;
	}
}

void Scene::step() {

	// TODO : refactor into a private method
	/*if(mGameObjectsToLoadIndex < mGameObjectsToLoadTotal){
		FOR_RANGE_COND(i, 0, mMaxGameObjectsToLoadPerFrame, mGameObjectsToLoadIndex < mGameObjectsToLoadTotal){
			std::string indexStr = std::to_string(mGameObjectsToLoadIndex);
			std::string objectName = "objects[" + indexStr + "]";

			std::string className = mLoadSceneConfigMap->getString(objectName + ".class");
			
			GameObject* gameObject = Memory::fromClassName<GameObject>(className);
			gameObject->init();
			gameObject->load(mLoadSceneConfigMap, objectName);
			addGameObject(gameObject);
			mGameObjectsToLoadIndex += 1;
		}
	}*/

	if (thereAreNewGameObjects()) {

		const std::list<GameObject*>* newGameObjects = getNewGameObjects();
		//u32 maxToSpawn = EngineConfig::getInstance()->getF32("scene.maxNewObjectsToSpawn");

		// VAR(f32, newGameObjects->getLength());

		FOR_LIST (itGameObjects, *newGameObjects)
		{
			GameObject* gameObject = (*itGameObjects);

			updateComponents(gameObject);
		}

		flushNewGameObjects();
	}
}

void Scene::flushNewGameObjects() {
	FOR_LIST (itGameObjects, *mNewGameObjects) {
		mGameObjects->push_back(*itGameObjects);
	}

	mNewGameObjects->clear();
}

bool Scene::thereAreNewGameObjects() const {
	return mNewGameObjects->size() > 0;
}