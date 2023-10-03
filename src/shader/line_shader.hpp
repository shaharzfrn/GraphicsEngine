//
//  line_shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 17/01/2023.
//

#ifndef line_shader_hpp
#define line_shader_hpp

#include <stdio.h>

#include "shader.hpp"
#include "uniforms.h"


class LineShader : public ShaderProgram {
	
	struct { vec3 position; } input;
	struct {} pass;
	
public:
	
	vec3 color;
	mat4 mvp;
	
	SHADER(LineShader, LINE_SHADER, input, pass);
	
	SHADER_VERTEX_SIZE();
	SHADER_FRAGMENT_SIZE();
	
	SHADER_VERTEX_INPUT();
	SHADER_VERTEX_OUTPUT();
	SHADER_FRAGMENT_INPUT();
	
	virtual void VertexShader();
	virtual void FragmentShader();
};


#endif /* line_shader_hpp */
