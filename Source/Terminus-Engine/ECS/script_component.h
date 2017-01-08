#pragma once

#ifndef  SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include <ECS/component.h>
#include <types.h>

namespace terminus
{
	using Entity = uint32;

	struct ScriptComponent : IComponent
	{
        static const ComponentID _id;
		virtual void Initialize() = 0;
		virtual void Update(double delta, Entity entity) = 0;
		virtual void Shutdown() = 0;
	};
}

#endif