//
//  bounding_box_shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 21/01/2023.
//

#ifndef bounding_box_shader_hpp
#define bounding_box_shader_hpp

#include <stdio.h>
#include <memory>

#include "shader.hpp"

class BoundingBoxShader : public ShaderProgram {
	
	struct { vec3 position; } input;
	struct {} pass;
	
public:
	
	vec3 color;
	mat4 mvp;
	
	SHADER(BoundingBoxShader, BOUNDING_BOX_SHADER, input, pass);
	
	SHADER_VERTEX_SIZE();
	SHADER_FRAGMENT_SIZE();
	
	SHADER_VERTEX_INPUT();
	SHADER_VERTEX_OUTPUT();
	SHADER_FRAGMENT_INPUT();
	
	virtual void VertexShader();
	virtual void FragmentShader();
};


#endif /* bounding_box_shader_hpp */
