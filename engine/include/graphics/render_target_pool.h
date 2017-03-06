#pragma once

#include <graphics/render_device.h>
#include <core/types.h>

#include <unordered_map>

namespace terminus
{
    class RenderTargetPool
    {
    private:
        std::unordered_map<String, Texture*> _rt_map;
        
    public:
        RenderTargetPool();
        ~RenderTargetPool();
        
        Texture* create(String name ,uint16 width, uint16 height, TextureFormat format);
        Texture* lookup(String name);
    };
}
