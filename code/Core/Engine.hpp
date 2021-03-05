#pragma once

#include "Core/DE_Class.hpp"
#include "Core/Singleton.hpp"

namespace DE {

class RenderEngine;
class PhysicsEngine;
class ScriptEngine;

class Engine: public DE_Class, public Singleton<Engine> {

private:

	DE_M(FPS, f32)
	DE_M(RenderEngine, RenderEngine*)
	DE_M(PhysicsEngine, PhysicsEngine*)
	DE_M(ScriptEngine, ScriptEngine*)

public:

	DE_CLASS_BODY(Engine)

	void init();
	void initSubsystems();
	void terminateSubSystems();
	void run();
	void terminate();
};

}

