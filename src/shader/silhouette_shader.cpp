//
//  silhouette_shader.cpp
//  CGApp
//
//  Created by Shahar Zafran on 06/01/2023.
//

#include "silhouette_shader.hpp"


SilhouetteShader::SilhouetteShader(): ShaderProgram(SILHOUETTE_SHADER) {};


size_t SilhouetteShader::GetVertexShaderInputSize() const {
	return sizeof(input);
};
size_t SilhouetteShader::GetFragmentShaderInputSize() const {
	return 1;
};

void SilhouetteShader::SetVertexInput(const u_int8_t* data) {};
void SilhouetteShader::SetFragmentInput(const float* data) {};

void SilhouetteShader::GetVertexOutput(float* data) const {};

void SilhouetteShader::VertexShader() {
	out_position = projection_matrix * view_matrix * model_matrix * vec4(input.position, 1.0);
};
void SilhouetteShader::FragmentShader() {
	frag_color = {1, 1, 1, 1};
};
