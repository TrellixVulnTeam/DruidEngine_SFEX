#ifndef DE_RENDERER_H
#define DE_RENDERER_H

#include "Component.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

#include <string>

namespace DE {

class Material;
class Mesh;
class Animation;
template <class K, class V> class HashMap;
template <class T> class Array;

class Renderer : public Component{

private:

	HashMap<std::string, Animation*>* mAnimations;
	Animation* mCurrentAnimation;
	Material* mMaterial;
	Mesh* mMesh;

	Array<f32>* mColor;

	Vector3 mPositionOffset;
	Matrix4* mPositionOffsetMatrix;

	Vector2 mRegionPosition;
  f32 mRegionWidth;
  f32 mRegionHeight;

	bool mInvertXAxis;

	bool mLineMode;
	bool mAlphaEnabled;

	u32 mLayer;

	f32 mRenderDistance;
	bool mOutOfCamera;

	bool mIsInChunk;
	bool mIsChunkLoaded;

public:

	DE_CLASS(Renderer, Component);

	void init() override;

	void setRegion(f32 u, f32 v, f32 width, f32 height);

	/**
	* Set the animation, by name.
	* \param string name The name.
	*/
	void setAnimation(const std::string& name);

	/**
	* Add an animation, by name.
	* \param string name The name.
	* \param Animation animation The animation.
	*/
	void addAnimation(const std::string& name, Animation* animation);

	/**
	* Update de material with information about the region, the alphacolor and the animation.
	* \param Material material The material.
	*/
	void updateMaterial(Material* material);

	void setColor(const Vector4& color);
	bool isLineMode();

	Vector3 getPositionOffset() const { return mPositionOffset;};
	void setPositionOffset(Vector3 newPositionOffset ) { mPositionOffset = newPositionOffset; };

	const Matrix4& getPositionOffsetMatrix();

	Mesh* getMesh() const { return mMesh;};
	void setMesh(Mesh* newMesh ) { mMesh = newMesh; };

	Material* getMaterial() const { return mMaterial;};
	void setMaterial(Material* newMaterial ) { mMaterial = newMaterial; };

	void setInvertXAxis(bool newInvertXAxis ) { mInvertXAxis = newInvertXAxis; };
	void setAlphaEnabled(bool newAlphaEnabled ) { mAlphaEnabled = newAlphaEnabled; };
	void setLineMode(bool newLineMode ) { mLineMode = newLineMode; };

	u32 getLayer() const { return mLayer;};
	void setLayer(u32 newLayer ) { mLayer = newLayer; };
	f32 getRenderDistance() const { return mRenderDistance;};
	void setRenderDistance(f32 newRenderDistance ) { mRenderDistance = newRenderDistance; };
	bool getOutOfCamera() const { return mOutOfCamera;};
	void setOutOfCamera(bool newOutOfCamera ) { mOutOfCamera = newOutOfCamera; };
	bool isInChunk() const { return mIsInChunk;};
	void setIsInChunk(bool newIsInChunk ) { mIsInChunk = newIsInChunk; };
	bool isChunkLoaded() const { return mIsChunkLoaded;};
	void setIsChunkLoaded(bool newIsChunkLoaded ) { mIsChunkLoaded = newIsChunkLoaded; };
};

} /* namespace DE */

#endif /* DE_RENDERER_H */
