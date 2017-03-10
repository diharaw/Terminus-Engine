#include <core/global.h>
#include <core/types.h>
#include <core/context.h>
#include <resource/config_file_factory.h>
#include <graphics/imgui_console.h>
#include <iostream>

namespace terminus
{
    namespace global
    {
        void* g_memory = nullptr;
        void* g_per_frame_memory = nullptr;
        LinearAllocator* g_allocator = nullptr;
        LinearAllocator* g_per_frame_allocator = nullptr;
        DefaultThreadPool*   g_thread_pool = nullptr;
		Context* g_context = nullptr;
        
        void initialize()
        {
            logger::initialize();
            
            logger::open_file_stream();
            
            g_memory = malloc(MAX_MEMORY);
            g_allocator = new LinearAllocator(MAX_MEMORY, g_memory);
            
            g_per_frame_memory = malloc(MAX_PER_FRAME_MEMORY);
            g_per_frame_allocator = new LinearAllocator(MAX_PER_FRAME_MEMORY, g_per_frame_memory);
            
            g_thread_pool = T_NEW DefaultThreadPool();
            
            g_context = T_NEW Context();
            g_context->_shutdown = false;
            
            filesystem::add_directory("config");
            g_context->_engine_config = config_file_factory::create("engine_config.json");
            
            imgui_console::initialize();
            logger::open_custom_stream(&imgui_console::logger_callback);
        }
        
        void set_platform(Platform* platform)
        {
            g_context->_platform = platform;
        }
        
        void set_imgui_backend(ImGuiBackend* backend)
        {
            g_context->_imgui_backend = backend;
        }
        
        Context& get_context()
        {
            return *g_context;
        }
        
        LinearAllocator* get_default_allocator()
        {
            return g_allocator;
        }
        
        LinearAllocator* get_per_frame_allocator()
        {
            return g_per_frame_allocator;
        }
        
        DefaultThreadPool* get_default_threadpool()
        {
            return g_thread_pool;
        }
        
        void shutdown()
        {
            if(g_per_frame_memory)
            {
                g_per_frame_allocator->Clear();
                std::cout << "Per-Frame Allocator : "<< g_per_frame_allocator->GetUsedMemory() << " / " << g_per_frame_allocator->GetTotalMemory() << std::endl;
                T_SAFE_DELETE(g_per_frame_allocator);
            }
            
            free(g_per_frame_memory);
            
            if(g_allocator)
            {
                g_allocator->Clear();
                std::cout << "Default Allocator : "<< g_allocator->GetUsedMemory() << " / " << g_allocator->GetTotalMemory() << std::endl;
                T_SAFE_DELETE(g_allocator);
            }
            
            free(g_memory);
            
        #if defined(TERMINUS_WITH_EDITOR)
            logger::close_custom_stream();
            imgui_console::shutdown();
        #endif
            
            logger::close_file_stream();
        }
    }
}

void* operator new (size_t size, unsigned line, const char* file)
{
    std::cout << "Performing Allocation of size " << size << " in File " << file << " at line number " << line << std::endl;
    return terminus::global::g_allocator->Allocate(size, MEMORY_ALIGNMENT);
}