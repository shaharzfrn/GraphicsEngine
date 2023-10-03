//
//  flat_shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 21/01/2023.
//

#ifndef flat_shader_hpp
#define flat_shader_hpp

#include <stdio.h>
#include <memory>

#include "shader.hpp"
#include "uniforms.h"

class FlatShader : public ShaderProgram, public ModelUniforms {
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
	
	SHADER(FlatShader, FLAT_SHADER, input, pass);
	
	SHADER_VERTEX_SIZE();
	SHADER_FRAGMENT_SIZE();
	
	SHADER_VERTEX_INPUT();
	SHADER_VERTEX_OUTPUT();
	SHADER_FRAGMENT_INPUT();
	
	virtual void VertexShader();
	virtual void FragmentShader();
};




#endif /* flat_shader_hpp */
