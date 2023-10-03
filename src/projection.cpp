//
//  projection.cpp
//  CGApp
//
//  Created by Shahar Zafran on 04/01/2023.
//

#include "projection.hpp"
#include "cgl.hpp"
#include "camera.hpp"
#include "shadow.hpp"


mat4 CGL::GenerateProjectionMatrix(const vec3& position) {
	mat4 projection;
	
	switch (projection_type) {
		case PRESPECTIVE_PROJECTION:
			projection = CGL::GeneratePerspectiveProjectionMatrix((float)CGL::display_width, (float)CGL::display_height, CGL::near, CGL::far, CGL::fov);
			break;
			
		case OTHOGRAPHIC_PROJECTION:
			projection = CGL::GenerateOrthoProjectionMatrix((float)CGL::display_width, (float)CGL::display_height, CGL::Distance(position, {0, 0, 0}), CGL::near, CGL::far);
		default:
			break;
	}
	
	return projection;
}

mat4 CGL::GenerateShadowProjection(const vec3& position) {
	return CGL::GenerateOrthoProjectionMatrix((float)CGL::SHADOW_MAP_SIZE, (float)CGL::SHADOW_MAP_SIZE, CGL::Distance(position, {0, 0, 0}), CGL::SHADOW_MAP_NEAR, CGL::SHADOW_MAP_FAR);
}
