//
//  shader.cpp
//  CGApp
//
//  Created by Shahar Zafran on 29/12/2022.
//

#include "shader.hpp"
ShaderProgram::ShaderProgram(const ShaderType type): type(type) {};


void ShaderProgram::InterpolateFragment(const float* v1, const float* v2, const float& t, float* out) {
	
	for(size_t i = 0; i < GetFragmentShaderInputSize(); i++) {
		out[i] = v1[i] + (v2[i] - v1[i]) * t;
	}
}

void ShaderProgram::InterpolateFragment(const float* v1, const float* v2, const vec2& perspective, float* out) {
	for (int i = 0; i < GetFragmentShaderInputSize(); i++) {
		out[i] = v1[i] * perspective[0] + v2[i] * perspective[1];
	}
}

void ShaderProgram::InterpolateFragment(const float* v1, const float* v2, const float* v3, const vec3& perspective, float* out) {
	for (int i = 0; i < GetFragmentShaderInputSize(); i++) {
		out[i] = v1[i] * perspective[0] + v2[i] * perspective[1] + v3[i] * perspective[2];
	}
	
}
