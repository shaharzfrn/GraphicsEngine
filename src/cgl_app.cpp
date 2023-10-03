//
//  cgl_app.cpp
//  CGApp
//
//  Created by Shahar Zafran on 02/01/2023.
//

#include "cgl.hpp"
#include "cgl_app.hpp"
#include "cgl_shaders.hpp"

#include "model.hpp"
#include "loader.hpp"
#include "light.hpp"
#include "shadow.hpp"

#include "projection.hpp"
#include "camera.hpp"

float r = 0;
vec3 camera_pos;
int proj_type = 0;

vec3 center {};


bool is_shift_down = false;


void CGLApp::OnInit() {
	CGL::EnableBuffer(DEPTH_BUFFER | COLOR_BUFFER);
	CGL::ClearDepth(1);
	CGL::polygon_fineness = 20;
	
	CGL::camera.position = {0, 0, 20};
	CGL::MAIN_CAMERA_VIEW_MATRIX = CGL::GenerateLookAt(CGL::camera.position, CGL::camera.position + CGL::camera.front, CGL::camera.up);
	
	CGL::lights[0].enabled = true;
	CGL::lights[0].color = {1, 1, 1};
	CGL::lights[0].type = LIGHT_TYPE_SPOT;
	CGL::lights[0].position = {0, 0.f, 30};
	CGL::lights[0].direction = {0, 0.f, 1.0f};
	CGL::lights[0].cutoff_angle = cosf((20.0f * ( M_PI / 180.0f)));
	
	CGL::lights[1].enabled = false;
	CGL::lights[1].color = {1, 1, 1};
	CGL::lights[1].type = LIGHT_TYPE_DIRECTIONAL;
	CGL::lights[1].direction = {-1, 0, 0};
	
	CGL::ambiant_light.enabled = true;
	CGL::ambiant_light.color = {1, 1, 1};
	CGL::ambiant_light.strength = 0.4;
	
	for (int i = 0; i < MAX_LIGHTS; i++) {
		CGL::shadows_settings[i] = {
			VOLUME_SHADOW,
			CGL::SHADOW_MAP_SIZE,
			CGL::SHADOW_MAP_SIZE,
			CGL::SHADOW_MAP_NEAR,
			CGL::SHADOW_MAP_FAR
		};
		
		CGL::shadows[i] = new ShadowMap(CGL::lights[i], {}, CGL::shadows_settings[i]);
	}
};

// Screen events
void CGLApp::OnRender() {
	
	for (int i = 0; i < MAX_LIGHTS; i++) {
		Light light = CGL::lights[i];
		if (!light.enabled || light.type == LIGHT_TYPE_SPOT)
			continue;
		
		CGL::shadows[i]->RenderShadow([&](const vec3& light_position) {
			for (auto& [name, object] : CGL::objects) {
				object.DrawShadow(light_position);
			}
		});
	}
	
	// return to the display viewport
	CGL::Viewport(CGL::display_width, CGL::display_height, CGL::NEAR, CGL::FAR);
	CGL::EnableBuffer(COLOR_BUFFER | DEPTH_BUFFER);
	CGL::DisableBuffer(STENCIL_BUFFER);
	
	CGL::ClearColor(CGL::background_color.x, CGL::background_color.y, CGL::background_color.z, CGL::background_color.w);
	CGL::Clear(COLOR_BUFFER | DEPTH_BUFFER);
	
	if (CGL::background_image != nullptr) {
		Buffer* buffer;
		CGL::GetFrameBuffer(COLOR_BUFFER, &buffer);
		
		ColorBuffer *color_buffer = static_cast<ColorBuffer*>(buffer);
		color_buffer->SetBackgroundImage(CGL::background_image);
	}
	
//	CGL::model_uniforms = &CGL::PHONG_SHADER;
//	CGL::model_uniforms->camera_position = CGL::camera.position;
	
//	CGL::shader = &CGL::PHONG_SHADER;

	for (auto& [name, object] : CGL::objects) {
		object.Draw(CGL::camera.position);
	}
}


void CGLApp::OnResize(const int& width, const int& height, const int& dpi) {
}

// Keyboard events
void CGLApp::OnKeyPress(const char& key, const bool& shift, const bool& ctlr) {
	if (CGL::selected_object != nullptr) {
		if (key == 'I') {
			CGL::selected_object->position.z -= 0.5f;
		} else if (key == 'K') {
			CGL::selected_object->position.z += 0.5f;
		} else if (key == 'J') {
			CGL::selected_object->position.x -= 0.5f;
		} else if (key == 'L') {
			CGL::selected_object->position.x += 0.5f;
		} else if (key == '=') {
			CGL::selected_object->position.y += 0.4f;
		} else if (key == '-') {
			CGL::selected_object->position.y -= 0.4f;
		}
	}
	
	CGL::camera.Move(key, shift, ctlr);
	
	if (key == 27 && CGL::selected_object != nullptr) {
		CGL::selected_object->Diselect();
		CGL::selected_object = nullptr;
	}
	
	CGL::MAIN_CAMERA_VIEW_MATRIX = CGL::GenerateLookAt(CGL::camera.position, CGL::camera.position + CGL::camera.front, CGL::camera.up);
	
	is_shift_down = shift;
	
	Refresh();
}
void CGLApp::OnKeyRelese(const char& key, const bool& shift, const bool& ctlr) {}

// Mouse events
void CGLApp::OnMouseMove(const float& px, const float& py, const bool& left, const bool& dragging) {
	if (is_shift_down) {
		if (CGL::selected_object != nullptr) {
			float dx = CGL::camera.last_mouse_x - px;
			float dy = CGL::camera.last_mouse_y - py;
			
			CGL::selected_object->rotation.x += dx * 4e-1;
			CGL::selected_object->rotation.y += dy * 4e-1 * !left;
			CGL::selected_object->rotation.z += dy * 4e-1 *  left;
		}
	}
	CGL::camera.Rotate(px, py, is_shift_down, dragging);
	
	CGL::MAIN_CAMERA_VIEW_MATRIX = CGL::GenerateLookAt(CGL::camera.position, CGL::camera.position + CGL::camera.front, CGL::camera.up);
	Refresh();
}
void CGLApp::OnMouseScroll(const int& scroll) {
	
}

void CGLApp::OnClose() {
	for (int i = 0; i < MAX_SHADOWS; i++) {
		delete CGL::shadows[i];
	}
}
