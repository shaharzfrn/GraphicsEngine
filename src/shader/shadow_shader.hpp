//
//  shadow_shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 08/01/2023.
//

#ifndef shadow_shader_hpp
#define shadow_shader_hpp

#include <stdio.h>
#include <memory>


#include "shader.hpp"

class ShadowShader : public ShaderProgram {
	
	struct {
		vec3 position;
	} input;
	
	struct { u_int8_t fake; } pass;
	
public:
	
	
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 mvp; // view + projection
	
	SHADER(ShadowShader, SHADOW_SHADER, input, pass);
	
	SHADER_VERTEX_SIZE();
	SHADER_FRAGMENT_SIZE();
	
	SHADER_VERTEX_INPUT();
	SHADER_VERTEX_OUTPUT();
	SHADER_FRAGMENT_INPUT();
	
	virtual void VertexShader();
	virtual void FragmentShader();
};


#endif /* shadow_shader_hpp */
