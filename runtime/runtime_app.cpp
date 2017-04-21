#include "runtime_app.h"

#include <core/terminus.h>
#include <core/sync.h>
#include <platform/platform_sdl2.h>
#include <graphics/imgui_backend_sdl2.h>

#if defined(TERMINUS_PLATFORM_WIN32)
#include <Windows.h>
#endif

namespace terminus
{
    RuntimeApp::RuntimeApp()
    {
        
    }
    
    RuntimeApp::~RuntimeApp()
    {
        
    }
    
    void RuntimeApp::run()
    {
        Context& context = global::get_context();
        Platform* platform = context::get_platform();
        Renderer& renderer = context::get_renderer();
        
        ImGuiBackend* gui_backend = context::get_imgui_backend();
        load_initial_scene();
        
        while (!context._shutdown)
        {
            TERMINUS_BEGIN_CPU_PROFILE(simulation);
            
            platform->begin_frame();
            platform->update();
            EventHandler::update();
            physics::update(platform->get_delta_time());
            
            context._scene_manager.update(platform->get_delta_time());
            
            TERMINUS_END_CPU_PROFILE;
            // Synchronize Rendering Thread
            sync::wait_for_renderer_done();
            
            // Only swap Graphics Queues when Front-Buffer Command generation and Back-Buffer Command Submission has completed.
            renderer.swap();
            
            TERMINUS_BEGIN_CPU_PROFILE(gui_update);
            //temp_render();
            gui_backend->new_frame();
            imgui_console::draw();
            static bool tw = true;
            ImGui::ShowTestWindow(&tw);
            
            global::get_per_frame_allocator()->Clear();
            
            sync::notify_swap_done();
            platform->end_frame();
            
            TERMINUS_END_CPU_PROFILE;
        }

    }
    
    bool RuntimeApp::initialize_app()
    {
        return true;
    }
    
    void RuntimeApp::shutdown_app()
    {
        
    }
    
    void RuntimeApp::load_initial_scene()
    {
        SceneManager& scene_manager = context::get_scene_manager();
        
        if (context::get_engine_config()->has_value(CONFIG_INITIAL_SCENE))
        {
            StringBuffer64 scene_name = context::get_engine_config()->get_string(CONFIG_INITIAL_SCENE);
            scene_manager.load(String(scene_name.c_str()));
        }
    }
}