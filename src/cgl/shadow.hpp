//
//  shadow.hpp
//  CGApp
//
//  Created by Shahar Zafran on 08/01/2023.
//

#ifndef shadow_hpp
#define shadow_hpp

#include <stdio.h>
#include <cmath>

#include "math.hpp"
#include "texture.hpp"
#include "buffer.hpp"

#include "light.hpp"

#include <vector>


#define MAX_SHADOWS MAX_LIGHTS

typedef enum {
	MAP_SHADOW,
	VOLUME_SHADOW
} ShadowType;


typedef struct  {
	mat4 mvp;
	mat4 view_matrix;
	Texture *texture;
} ShadowMap2;

struct ShadowSettings {
	
	ShadowType type;
	
	int width;
	int height;
	
	float near;
	float far;
};

typedef std::function<void(const vec3&)> RednerShadow;
 
class Shadow {
protected:
	
	virtual void SetupShadowBuffer() = 0;
	virtual void SetupShadowTexture() = 0;
	virtual void Render(RednerShadow render) = 0;
	
	int width;
	int height;
	float near;
	float far;
	
public:
	
	vec3 view_position;
	
	mat4 mvp;
	mat4 view_matrix;
	
	Texture *texture;
	Buffer *buffer;
	
	Shadow(const Light& light, const vec3& look_at, const ShadowSettings& settings);
	virtual ~Shadow();
	
//	virtual void SetObjectPosition(const vec3& object_position) {
//
//		/*
//		if (light->type == LIGHT_TYPE_POINT)
//			mvp = CGL::GenerateShadowProjection(object_position - light->position) * view_matrix;
//		else {
//
//			float pitch = (float) acos(CGL::Distance(vec2(light->direction.x, light->direction.z), {0, 0}));
//			float yaw = (float) atan(light->direction.x / light->direction.z) * (180.0f / M_PI);
//			yaw = light->direction.z > 0 ? yaw - 180.0f : yaw;
//
//
//
////			Matrix4f.rotate(pitch, new Vector3f(1, 0, 0), lightViewMatrix, lightViewMatrix);
////			float yaw = (float) Math.toDegrees(((float) Math.atan(direction.x / direction.z)));
////			yaw = direction.z > 0 ? yaw - 180 : yaw;
////			Matrix4f.rotate((float) -Math.toRadians(yaw), new Vector3f(0, 1, 0), lightViewMatrix,
////					lightViewMatrix);
////			Matrix4f.translate(center, lightViewMatrix, lightViewMatrix);
//
//
//		}
//		 */
//	};
	virtual void RenderShadow(RednerShadow render) final {
		SetupShadowBuffer();
		Render(render);
		SetupShadowTexture();
	};
	virtual bool InShadow(const vec3& coords) = 0;
};


class ShadowMap : public Shadow {
protected:
	virtual void SetupShadowBuffer();
	virtual void SetupShadowTexture();
	virtual void Render(RednerShadow render);
	
public:
	
	ShadowMap(const Light& light, const vec3& look_at, const ShadowSettings& settings);
	virtual ~ShadowMap();
	
	virtual bool InShadow(const vec3& coords);
};

class ShadowVolume : public Shadow {
	
protected:
	virtual void SetupShadowBuffer();
	virtual void SetupShadowTexture();
	virtual void Render(RednerShadow render);
	
public:
	ShadowVolume(const Light& light, const vec3& look_at, const ShadowSettings& settings);
	virtual ~ShadowVolume();
	
//	virtual void SetupShadowBuffer() {
//		// create buffer
//		// disable color and depth buffer;
//		// clear all
//
//		Buffer *shadow_buffer = Buffer::CreateBuffer<u_int8_t>(width, height);
//
//		CGL::BindFrameBuffer(DEPTH_BUFFER, light_buffer);
//		CGL::Viewport(CGL::SHADOW_MAP_SIZE, CGL::SHADOW_MAP_SIZE, CGL::SHADOW_MAP_NEAR, CGL::SHADOW_MAP_FAR);
//
//		CGL::SHADOW_SHADER.view_matrix = CGL::GenerateLookAt(light.position, {0.0f, 0.0f, 0.0f}, {0, 1.f, 0});
//		// set all the shader settings
//	};
//
//	virtual void Render(const RednerShadow& render) {
//
//		// set stencil operator for front faceing
//		// set cullface to front
//		render(light_position);
//
//		// set stencil operator for back faceing
//		// set cullface to back
//		render(light_position);
//	};
//
	virtual bool InShadow(const vec3& coords);
};


namespace CGL {

inline int SHADOW_MAP_SIZE = 1024.0f;
inline float SHADOW_MAP_NEAR = 0.1f;
inline float SHADOW_MAP_FAR = 400.0f;

inline ShadowMap2 lights_shadow[MAX_LIGHTS];


// if light at index i is disabled, shadows[i] will be nullptr
inline Shadow *shadows[MAX_SHADOWS];


// array of settings for each shadow, will be change in the settings dialog
inline ShadowSettings shadows_settings[MAX_SHADOWS];

};







#endif /* shadow_hpp */
