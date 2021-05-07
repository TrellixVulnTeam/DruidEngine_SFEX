#pragma once

#include "Scene/GameObject.hpp"
#include "Graphics/Material.hpp"
#include "Maths/Vector3.hpp"
#include "Scene/Scene.hpp"

namespace DE
{
    class MapElementData;
    
    class MapElement  : public GameObject {
    public:
        GENERATE_METADATA(MapElement);

        MapElement();
        virtual ~MapElement() override;
        virtual void initFromData(const MapElementData* data);
        static MapElement *create(const MapElementData* data);
    };

    class MapElementData  : public ObjectBase {
    public:
        GENERATE_METADATA(MapElementData)

        PUBLIC(MapElementClassName, NONE, String)
        PUBLIC(Position, NONE, Vector3)
        PUBLIC(Size, NONE, Vector2)
        PUBLIC(Material, NONE, Material*)
        PUBLIC(Layer, NONE, u32)
        PUBLIC(MaterialRegionPosition, NONE, Vector2)
        PUBLIC(MaterialRegionSize, NONE, Vector2)

        MapElementData() { mMapElementClassName = MapElement::getClassNameStatic(); }
    };

    class MapElement_Tile  : public MapElement {
    public:
        GENERATE_METADATA(MapElement_Tile);
        MapElement_Tile();
        virtual ~MapElement_Tile() override;
    };

    class MapElementData_Tile  : public MapElementData {
    public:
        GENERATE_METADATA(MapElementData_Tile)
        MapElementData_Tile() { mMapElementClassName = MapElement_Tile::getClassNameStatic(); }
    };

    class MapElement_ActionPoint  : public MapElement {
    public:
        GENERATE_METADATA(MapElement_ActionPoint);
        MapElement_ActionPoint();
        virtual ~MapElement_ActionPoint() override;
    };

    class MapElementData_ActionPoint  : public MapElementData {
    public:
        GENERATE_METADATA(MapElementData_ActionPoint)
        MapElementData_ActionPoint() { mMapElementClassName = MapElement_ActionPoint::getClassNameStatic(); }
    };
}

