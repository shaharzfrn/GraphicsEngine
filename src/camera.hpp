//
//  camera.hpp
//  CGApp
//
//  Created by Shahar Zafran on 05/01/2023.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "math.hpp"

class Camera {
public:
	float last_mouse_x;
	float last_mouse_y;
	bool first_mouse = true;
	
	vec3 position = {0, 0, 10};
	vec3 front = {0.0f, 0.0f, -1.0f};
	vec3 up = {0.0f, 1.0f, 0.0f};
	
	float yaw = -90.f;
	float pitch;
	
	void Move(const char key, bool shift, bool ctlr);
	void Rotate(const float& px, const float& py, const bool& shift, const bool& dragging);
};

namespace CGL {

inline Camera camera;

inline mat4 MAIN_CAMERA_VIEW_MATRIX;
};





#endif /* camera_hpp */
