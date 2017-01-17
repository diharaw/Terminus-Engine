#pragma once

#include <Utility/serializable.h>
#include <ECS/scene.h>

namespace terminus
{
	class CppScript : public Serializable
	{
    public:
        Entity _entity;
        Scene* _scene;
        
	public:
		CppScript() {}
		virtual ~CppScript() {}
		virtual void initialize() = 0;
		virtual void update(double dt) = 0;
		virtual void shutdown() = 0;
	};
}