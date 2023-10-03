//
//  bounding_box_shader.cpp
//  CGApp
//
//  Created by Shahar Zafran on 21/01/2023.
//

#include "bounding_box_shader.hpp"

void BoundingBoxShader::VertexShader() {
	out_position = mvp * vec4(input.position, 1.0);
}
void BoundingBoxShader::FragmentShader() {
	frag_color = vec4(color, 1.0f);
}
