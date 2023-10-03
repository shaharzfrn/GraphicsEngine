//
//  camera.cpp
//  CGApp
//
//  Created by Shahar Zafran on 05/01/2023.
//

#include "camera.hpp"

#include <cmath>

void Camera::Move(const char key, bool shift, bool ctlr) {
	float camera_speed = 1.0f;

	if (key == 'W') {
		position = position + camera_speed * front;
	} else if (key == 'S') {
		position = position - camera_speed * front;
	} else if (key == 'A' ) {
		position = position - camera_speed * CGL::Normolize(CGL::Cross(front, up));
	} else if (key == 'D') {
		position = position + camera_speed * CGL::Normolize(CGL::Cross(front, up));
	}
}
void Camera::Rotate(const float& px, const float& py, const bool& shift, const bool& dragging) {
	
	if (first_mouse) {
		last_mouse_x = px;
		last_mouse_y = py;
		first_mouse = false;
	}
	
	
	
	float dx = px - last_mouse_x;
	float dy = py - last_mouse_y;
	
	last_mouse_x = px;
	last_mouse_y = py;
	
	if (!dragging || shift)
		return;
	
	yaw += dx;
	pitch = fmax(fmin(pitch + dy, 89.0f), -89.0f);

	front.x = cos(yaw * (M_PI / 180.f)) * cos(pitch * (M_PI / 180.f));
	front.y = sin(pitch * (M_PI / 180.f));
	front.z = sin(yaw * (M_PI / 180.f)) * cos(pitch * (M_PI / 180.f));

	front = CGL::Normolize(front);
}
