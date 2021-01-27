#pragma once

#include "Scene/Component.hpp"
#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"
#include "Maths/Matrix4.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Animation.hpp"
#include "Containers/HashMap.hpp"
#include "Containers/Array.hpp"
#include "Graphics/Chunk.hpp"

#include <string>

namespace DE {

class Renderer: public Component {
private:

	using AnimationsMap = HashMap<std::string, Animation*>;
	DE_M(Animations, AnimationsMap*)
	DE_M(RenderereModelMatrix, Matrix4)
	DE_M(PositionOffsetDirty, bool)
	DE_M(ForceRecalculateVertices, bool)
	DE_M(Vertices, Array<Vector2>*)
	DE_M(IsAffectedByProjection, bool)

	DE_M_GET(CurrentAnimation, Animation*)
	DE_M_GET(Color, Array<f32>*)
	DE_M_GET(PositionOffset, Vector3)
	DE_M_GET(RegionPosition, Vector2)
	DE_M_GET(RegionSize, Vector2)
	DE_M_GET_SET(Mesh, Mesh*)
	DE_M_GET_SET(Material, Material*)
	DE_M_GET_SET(IsInvertAxis, bool)
	DE_M_GET_SET(IsLineMode, bool)
	DE_M_GET_SET(Layer, u32)
	DE_M_GET_SET(RenderDistance, f32)
	DE_M_GET_SET(IsOutOfCamera, bool)
	DE_M_GET_SET(IsAlreadyInBatch, bool)
	DE_M_GET_SET(Chunk, Chunk*)

public:

	DE_CLASS(Renderer)

	void init() override;
	void setAnimation(const std::string& name);
	void addAnimation(const std::string& name, Animation* animation);
	bool hasAnimations() const;
	void updateAnimation();
	void setColor(const Vector4& color);
	void setRegion(f32 u, f32 v, f32 width, f32 height);
	void setPositionOffset(Vector3 newPositionOffset);
	bool getIsAffectedByProjection();
	const Array<Vector2>* getVertices(bool force = false);
	void forceRecalculateVertices();

	virtual void save(ConfigMap* configMap, const std::string& objectName) override;
	virtual void load(ConfigMap* configMap, const std::string& objectName) override;
};

}

