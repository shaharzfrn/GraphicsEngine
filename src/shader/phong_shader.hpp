//
//  phong_shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 31/12/2022.
//

#ifndef phong_shader_hpp
#define phong_shader_hpp

#include <stdio.h>
#include <memory>
//#include "model_shader.hpp"

#include "shader.hpp"
#include "uniforms.h"

#include "light.hpp"


class PhongShader : public ShaderProgram, public ModelUniforms {
	
	struct {
		vec3 position;
		vec3 normal;
		vec2 texture_coords;
	} input;
	
	struct {
		vec2 texture_coords;
		vec3 normal;
		vec3 world_position;
		vec4 shadow_map_coords[MAX_LIGHTS];
	} pass;
	
public:
	
	SHADER(PhongShader, PHONG_SHADER, input, pass);
	
	SHADER_VERTEX_SIZE();
	SHADER_FRAGMENT_SIZE();
	
	SHADER_VERTEX_INPUT();
	SHADER_VERTEX_OUTPUT();
	SHADER_FRAGMENT_INPUT();
	
	virtual void VertexShader();
	virtual void FragmentShader();
};

#endif /* phong_shader_hpp */
