#pragma once
#include"ObjectComponent.h"
class RenderComponentInterface : public ObjectComponent
{
public:
	//    virtual ComponentId VGetComponentId(void) const override { return COMPONENT_ID; }

	// RenderComponentInterface
	virtual std::shared_ptr<SceneNode> VGetSceneNode(void) = 0;
};
