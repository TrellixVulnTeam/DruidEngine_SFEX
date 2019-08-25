#ifndef DE_CUSTOMSCRIPT_H
#define DE_CUSTOMSCRIPT_H

#include "Script.h"

#include "Renderer.h"
#include "Transform.h"

namespace DE {

class CustomScript : public Script{
private:

  Renderer* mRenderer;
  Transform* mTransform;

public:

DE_CLASS(CustomScript, Script);

void init() override;
void step() override;
void terminate() override;
};

} /* namespace DE */

#endif /* DE_CUSTOMSCRIPT_H */
