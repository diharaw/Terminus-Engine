#pragma once

#ifndef MESHFACTORY_H
#define MESHFACTORY_H

#include "Mesh.h"
#include "../Graphics/render_device.h"
#include "../Global.h"
#include <string>

namespace terminus
{
    struct MeshGPUResourcesTaskData
    {
        Mesh* mesh;
        VertexBuffer* vertexBuffer;
        IndexBuffer* indexBuffer;
        InputLayoutType layoutType;
        InputLayout* layout;
        void* index_buffer_data;
        void* vertex_buffer_data;
        uint index_buffer_size;
        uint vertex_buffer_size;
        BufferUsageType usageType;
    };
    
	class MeshFactory
	{
	private:
        ThreadPool* m_rendering_thread_pool;
        MeshGPUResourcesTaskData m_task_data;

	public:
		MeshFactory();
		~MeshFactory();
		void Initialize();
		Mesh* Create(AssetCommon::MeshLoadData* _Data);
        
    private:
        TASK_METHOD_DECLARATION(CreateGPUResourcesTask);
	};
}

#endif
