//
//  shadow.cpp
//  CGApp
//
//  Created by Shahar Zafran on 08/01/2023.
//

#include "shadow.hpp"
#include "cgl.hpp"
#include "cgl_shaders.hpp"

Shadow::Shadow(const Light& light, const vec3& look_at, const ShadowSettings& settings) {
	
	width = settings.width;
	height = settings.height;
	near = settings.near;
	far = settings.far;
	
	view_position = light.position;
	/*
	if (light.type == LIGHT_TYPE_POINT)
		view_position = light.position;

	else {
		
		float z = (far - near) / 4.0f;
		vec3 direction = CGL::Normolize(light.direction);
		float pitch = acos( CGL::Distance(vec2(direction.x, direction.z), {})) * 180.0f / M_PI;
		float yaw = atan2(direction.x, direction.z) * 180.0f / M_PI;
		yaw = direction.y > 0.0f ? yaw - 180.0f : yaw;
		view_position = (CGL::Rotate({pitch, -yaw, 0}) * CGL::Translate({0, 0, z}) * vec4(1, 1, 1, 1)).xyz();
	}
	 */
	
	view_matrix = CGL::GenerateLookAt(view_position, {0.0f, 0.0f, 0.0f}, {0, 1.f, 0});
}
Shadow::~Shadow() {
	if (buffer != nullptr) delete buffer;
	buffer = nullptr;
	
	if (texture != nullptr) delete texture;
	texture = nullptr;
}


ShadowMap::ShadowMap(const Light& light, const vec3& look_at, const ShadowSettings& settings): Shadow(light, look_at, settings) {
	buffer = Buffer::CreateBuffer<float>(width, height);
}

ShadowMap::~ShadowMap() {}

void ShadowMap::SetupShadowBuffer() {
	CGL::BindFrameBuffer(DEPTH_BUFFER, buffer);
	
	CGL::DisableBuffer(COLOR_BUFFER | STENCIL_BUFFER);
	CGL::Clear(DEPTH_BUFFER);
	
	CGL::Viewport(width, height, near, far);
	CGL::SHADOW_SHADER.view_matrix = view_matrix;
	
}
void ShadowMap::SetupShadowTexture() {
	CGL::BindFrameBuffer(DEPTH_BUFFER, nullptr);
	
	if (texture != nullptr) delete texture;
	texture = new Texture(buffer);
}
void ShadowMap::Render(RednerShadow render) {
	render(view_position);
}

bool ShadowMap::InShadow(const vec3& coords) {
	float bias = 0.005f;
	float depth = coords.z;
	
	if (texture->InBounds(coords.xy()))
		depth = texture->Get<float>(coords.xy()) + bias;
	
	// TODO: add option to alias function
	return coords.z > depth;
}


ShadowVolume::ShadowVolume(const Light& light, const vec3& look_at, const ShadowSettings& settings): Shadow(light, look_at, settings) {
	buffer = Buffer::CreateBuffer<u_int8_t>(width, height);
}
ShadowVolume::~ShadowVolume() {}
void ShadowVolume::SetupShadowBuffer() {
	CGL::BindFrameBuffer(STENCIL_BUFFER, buffer);
	
	CGL::DisableBuffer(COLOR_BUFFER);
	CGL::EnableBuffer(DEPTH_BUFFER | STENCIL_BUFFER);
	CGL::Clear(DEPTH_BUFFER | STENCIL_BUFFER);
	
	CGL::Viewport(width, height, near, far);
	CGL::SHADOW_SHADER.view_matrix = view_matrix;
}
void ShadowVolume::SetupShadowTexture() {
	CGL::BindFrameBuffer(STENCIL_BUFFER, nullptr);
	
	if (texture != nullptr) delete texture;
	texture = new Texture(buffer);
}
void ShadowVolume::Render(RednerShadow render) {
		
	CGL::EnableCullFace();
	
	CGL::EnableDepthTest();
	render(view_position);
	CGL::DisableBuffer(DEPTH_BUFFER);
	
	// render the front faces
	CGL::CullFace(FRONT);
	CGL::StencilFunction(ALWAYS, 0x0, 0xFF);
	CGL::StencilOperator(KEEP, INCR, KEEP);
	render(view_position);
	
	// render the back faces
	CGL::CullFace(BACK);
	CGL::StencilFunction(ALWAYS, 0x0, 0xFF);
	CGL::StencilOperator(KEEP, DECR, KEEP);
	render(view_position);
	
	CGL::DisableCullFace();
	CGL::DisableDepthTest();
}

bool ShadowVolume::InShadow(const vec3& coords) {
//	printf("ShadowVolume::InShadow: %f, %f\n", coords.z, depth+bias);
	if (!texture->InBounds(coords.xy()))
		return false;
	
	return texture->Get<u_int8_t>(coords.x, coords.y) != 0;
}

