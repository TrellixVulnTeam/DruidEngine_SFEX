#pragma once

#include "Scripting/Script.hpp"
#include <string>

#include "Events/Event.hpp"
#include "MapEditorUI/Grid/Grid.hpp"
#include "MapEditorUI/MapEditorUI.hpp"

namespace DE {

class MapEditor: public Script {
private:

	DE_M(Transform, Transform*)
	DE_M(CameraTransform, Transform*)
	DE_M(CameraControl, bool)

	DE_M(IsMapLoaded, bool)

public:

	DE_M(Camera, Camera*)
	DE_M(Layer, u32)
	DE_M(Zoom, f32)
	DE_M(Player, GameObject*)
	DE_M(MapEditorUI, MapEditorUI)

	DE_M(Grid, Grid)
	DE_M(ConfigMap, ConfigMap*)

	DE_CLASS_BODY(MapEditor)

	void createPlayer();
	void destroyPlayer();

	void addColliderToTile(GameObject* tile);

	void cameraZoom();
	void processMovement();
	void switchCameraControl();

	void init() override;
	void firstStep() override;
	void step() override;
	void terminate() override;
};

}

