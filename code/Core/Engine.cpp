#include <TimeUtils.hpp>
#include "Engine.hpp"
#include "Memory.hpp"
#include "List.hpp"
#include "Singleton.hpp"
#include "RenderContext.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "RenderEngine.hpp"
#include "PhysicsEngine.hpp"
#include "ScriptEngine.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Script.hpp"
#include "Camera.hpp"
#include "Log.hpp"
#include "Input.hpp"
#include "RigidBody.hpp"
#include "UI.hpp"
#include "Settings.hpp"
#include "MaterialManager.hpp"
#include "ScenesManager.hpp"
#include "EventsManager.hpp"
#include "TimerManager.hpp"

#include <string>
#include <iostream>

#include <thread>
#include <chrono>

using namespace std::chrono_literals;

namespace DE {

// ---------------------------------------------------------------------------

Engine::Engine() : DE_Class(), Singleton() {
	mFPS = 60;
	mRenderEngine = nullptr;
	mPhysicsEngine = nullptr;
	mScriptEngine = nullptr;
}

Engine::~Engine() = default;

// ---------------------------------------------------------------------------

void Engine::init() {

	DE_TRACE()

	RenderContext::init();

	TimerManager::getInstance()->init();
	EventsManager::getInstance()->init();

	Settings::getInstance()->init();
	MaterialManager::getInstance()->init();

	ScenesManager::getInstance()->init();
}

// ---------------------------------------------------------------------------

void Engine::initSubsystems() {

	f32 sceneSize = ScenesManager::getInstance()->getCurrentScene()->getSize();

	// TODO : set default scene size if scene size is 0

	RenderEngine::getInstance()->init(sceneSize);
	ScriptEngine::getInstance()->init();
	PhysicsEngine::getInstance()->init(sceneSize);
	UI::getInstance()->init();

}

// ---------------------------------------------------------------------------

void Engine::terminateSubSystems() {

	// ScenesManager::getInstance()->getCurrentScene()->unloadScene();

	//if (ScriptEngine::getInstance())
		ScriptEngine::getInstance()->terminate();
	//if (RenderEngine::getInstance())
		RenderEngine::getInstance()->terminate();
	//if (PhysicsEngine::getInstance())
		PhysicsEngine::getInstance()->terminate();
	//if (UI::getInstance())
		UI::getInstance()->terminate();
	//if (EventsManager::getInstance())
		EventsManager::getInstance()->terminate();
	//if(TimerManager::getInstance())
		TimerManager::getInstance()->terminate();
}

// ---------------------------------------------------------------------------

void Engine::run() {
	Time::getInstance()->init();

	f32 FPS = 60.0f; // TODO : Move to settings.
	f32 inverseFPS = 1.0f / FPS;
	f32 inverseFPSMillis = inverseFPS * 1000.0f;

	f32 diff = 0;

	while (!RenderContext::isClosed()) {

		Time::getInstance()->startFrame();

		if (ScenesManager::getInstance()->sceneHasChanged()) {
			terminateSubSystems();
			ScenesManager::getInstance()->loadCurrentScene();
			initSubsystems();
		}

		ScenesManager::getInstance()->step();

		Input::getInstance()->pollEvents();

		TimerManager::getInstance()->step(Time::getInstance()->getDeltaTimeSeconds());

		ScriptEngine::getInstance()->step();

		PhysicsEngine::getInstance()->step(inverseFPS);

		RenderEngine::getInstance()->step();

		//std::cout << " " << Time::getInstance()->getElapsedTime() << std::endl;
		f32 dt = (Time::getInstance()->getElapsedTime());

		diff = inverseFPSMillis - dt;

		if(inverseFPSMillis > dt){
			//std::cout << dt/1000.0f;
			auto diff_duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double, std::milli>(diff/**1000.0f*/));
			std::this_thread::sleep_for(std::chrono::milliseconds(diff_duration.count()));
		}

		Time::getInstance()->endFrame();
		//std::cout << " " << 1.0f/Time::getInstance()->getDeltaTimeSeconds() << std::endl;


	}
}

// ---------------------------------------------------------------------------

void Engine::terminate() {

	terminateSubSystems();

	RenderContext::terminate();

	Memory::free<RenderEngine>(RenderEngine::getInstance());
	Memory::free<MaterialManager>(MaterialManager::getInstance());
	Memory::free<ScriptEngine>(ScriptEngine::getInstance());
	Memory::free<PhysicsEngine>(PhysicsEngine::getInstance());
	Memory::free<UI>(UI::getInstance());
	Memory::free<Settings>(Settings::getInstance());
	Memory::free<ScenesManager>(ScenesManager::getInstance());
	Memory::free<Time>(Time::getInstance());

	if (EventsManager::getInstance()){
		Memory::free<EventsManager>(EventsManager::getInstance());
	}

	if (TimerManager::getInstance()){
		Memory::free<TimerManager>(TimerManager::getInstance());
	}

	Memory::free<Input>(Input::getInstance());

}

// ---------------------------------------------------------------------------

} /* namespace DE */