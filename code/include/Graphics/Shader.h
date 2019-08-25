#ifndef DE_SHADER_H
#define DE_SHADER_H

#include "DE_Class.h"
#include "BasicTypes.h"

namespace DE {

class Matrix4;

// ---------------------------------------------------------------------------

class Shader : public DE_Class{
private:
	u32 mVertexShader;
	u32 mFragmentShader;
	u32 mProgram;

public:

	DE_CLASS(Shader, DE_Class);

	void init();
	void use();

	void addMatrix(const Matrix4& matrix, std::string name);
	void addInt(i32 value, std::string name);
	void addUInt(u32 value, std::string name);
	void addFloat(f32 value, std::string name);
};

// ---------------------------------------------------------------------------

} /* namespace DE */

#endif /* DE_SHADER_H */
