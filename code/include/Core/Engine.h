#ifndef DE_ENGINE_H
#define DE_ENGINE_H

#include "DE_Class.h"
#include "Singleton.h"


namespace DE {

template <class T> class List;
class Scene;
class RenderEngine;
class ScriptEngine;

class Engine : public DE_Class, public Singleton<Engine> {
private:
  f32 mFPS;

  u32 mCurrentSceneIndex;
  List<Scene*>* mScenes;
  RenderEngine* mRenderEngine;
  ScriptEngine* mScriptEngine;

  void loadScene(Scene* scene);

public:
  Engine();
  ~Engine() override;

  void init();

  void addScene(Scene* newScene);
  void setScene(u32 i);

  void run();
  void terminate();
};

} /* namespace DE */

#endif /* DE_ENGINE_H */
