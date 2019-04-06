#ifndef DE_ENGINE_H
#define DE_ENGINE_H

#include "DE_Class.h"
#include "List.h"

namespace DE {

class Scene;
class RenderEngine;
class ScriptEngine;

class Engine : public DE_Class{
private:
  f32 mFPS;

  List<Scene*>* mScenes;
  RenderEngine* mRenderEngine;
  ScriptEngine* mScriptEngine;

public:
  Engine();
  ~Engine() override;

  void init();
  void run();
  void terminate();
};

} /* namespace DE */

#endif /* DE_ENGINE_H */