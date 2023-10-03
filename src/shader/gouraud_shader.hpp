//
//  gouraud_shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 08/01/2023.
//

#ifndef gouraud_shader_hpp
#define gouraud_shader_hpp

#include <stdio.h>
#include <memory>

#include "shader.hpp"
#include "uniforms.h"

class GouraudShader : public ShaderProgram, public ModelUniforms {
	struct {
		vec3 position;
		vec3 normal;
		vec2 texture_coords;
	} input;
	
	struct {
		vec2 texture_coords;
		vec3 illumination;
	} pass;
	
public:
	
	SHADER(GouraudShader, GOURAUD_SHADER, input, pass);
	
	SHADER_VERTEX_SIZE();
	SHADER_FRAGMENT_SIZE();
	
	SHADER_VERTEX_INPUT();
	SHADER_VERTEX_OUTPUT();
	SHADER_FRAGMENT_INPUT();
	
	virtual void VertexShader();
	virtual void FragmentShader();
};



#endif /* gouraud_shader_hpp */
