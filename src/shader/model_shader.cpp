//
//  model_shader.cpp
//  CGApp
//
//  Created by Shahar Zafran on 31/12/2022.
//

#include "model_shader.hpp"
#include <memory>


ModelShader::ModelShader(const ShaderType type): ShaderProgram(type) {
	
};

//size_t ModelShader::GetVertexShaderInputSize() const {
//	return sizeof(input);
//}

//void ModelShader::SetVertexInput(const u_int8_t* data) {
//	memcpy(&input, data, sizeof(input));
//}
