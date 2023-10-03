//
//  line_shader.cpp
//  CGApp
//
//  Created by Shahar Zafran on 17/01/2023.
//

#include "line_shader.hpp"



void LineShader::VertexShader() {
	out_position = mvp * vec4(input.position, 1.0);
}
void LineShader::FragmentShader() {
	frag_color = vec4(color, 1.0f);
}
