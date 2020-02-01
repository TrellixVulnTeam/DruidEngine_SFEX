#include "Engine.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Mesh.h"
#include "Script.h"
#include "Transform.h"
#include "Animation.h"
#include "Renderer.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "CustomScript.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector4.h"

using namespace DE;

int main() {

	Memory::init();

	Engine* engine = Engine::getInstance();

	engine->init();

	Scene* scene = Memory::allocate<Scene>();

  scene->init();

	// camera

	GameObject* cameraGameObject = Memory::allocate<GameObject>();
	cameraGameObject->init();

	cameraGameObject->getTransform()->setLocalPosition(Vector3(0,0,0));

	// script

	//Script* script = Memory::allocate<Script>();
	//cameraGameObject->addComponent<Script>(script);

	Camera* cameraComponent = Memory::allocate<Camera>();
	cameraGameObject->addComponent<Camera>(cameraComponent);
	cameraComponent->setOrtho(-800, 800, -600, 600, 1000, -1000);
	//cameraComponent->setPerspective(100, -100, 800/600, 90);

	// OBJECT 1

	GameObject* gameObject = Memory::allocate<GameObject>();
  gameObject->init();

	// script

	Script* script = Memory::allocate<CustomScript>();
	gameObject->addComponent<Script>(script);

	scene->setCameraGameObject(cameraGameObject);

	scene->addGameObject(gameObject);

	scene->addGameObject(cameraGameObject);

	engine->addScene(scene);
	engine->setScene(0);

	engine->run();

	engine->terminate();

	return 0;
}
