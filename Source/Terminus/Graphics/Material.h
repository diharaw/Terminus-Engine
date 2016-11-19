#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Types.h"

// Material Key Options

// Normal Mapping
// Parallax Occlusion
// Diffuse Maps or Constant color
// Roughness Maps or value
// Metalness Maps or value

namespace Terminus { namespace Graphics {

	// Forward Declaration
	struct Texture2D;

	enum TexureMap
	{
		DIFFUSE = 0,
		NORMAL = 1,
		ROUGHNESS = 2,
		METALNESS = 3,
		DISPLACEMENT = 4,
	};

	struct Material
	{
		Texture2D* texture_maps[5];
		bool 	   backface_cull;
		uint64 	   material_key;
		Vector4    diffuse_value;
		float 	   roughness_value;
		float 	   metalness_value;
	};

} }

#endif
