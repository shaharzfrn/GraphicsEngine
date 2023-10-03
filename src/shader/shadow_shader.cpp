//
//  shadow_shader.cpp
//  CGApp
//
//  Created by Shahar Zafran on 08/01/2023.
//

#include "shadow_shader.hpp"

void ShadowShader::VertexShader() {
	out_position = mvp * model_matrix * vec4(input.position, 1.0f);
}
void ShadowShader::FragmentShader() {
	frag_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
