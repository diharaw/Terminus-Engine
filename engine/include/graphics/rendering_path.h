#ifndef RENDERINGPATH_H
#define RENDERINGPATH_H

#include <graphics/render_pass.h>

#define MAX_RENDER_PASSES 10

namespace terminus
{
    using RenderPassArray = std::array<RenderPass*, MAX_RENDER_PASSES>;
    
    struct RenderingPath
    {
        StringBuffer32  _name;
        int             _num_render_passes;
        RenderPassArray _render_passes;;
    };
}

#endif
