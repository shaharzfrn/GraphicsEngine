//
//  cgl_shaders.cpp
//  CGApp
//
//  Created by Shahar Zafran on 16/01/2023.
//

#include "cgl_shaders.hpp"


ShaderProgram* CGL::GetShaderProgram(const ShaderType type) {
	
	switch (type) {
		case ShaderType::PHONG_SHADER:
			return &PHONG_SHADER;
		
		case ShaderType::GOURAUD_SHADER:
			return &GOURAUD_SHADER;
			
		case ShaderType::FLAT_SHADER:
			return &FLAT_SHADER;
			
		case ShaderType::LINE_SHADER:
			return &LINE_SHADER;
		
		case ShaderType::BOUNDING_BOX_SHADER:
			return &BOUNDING_BOX_SHADER;
			
		default:
			break;
	}
	
	return nullptr;
}
ModelUniforms* CGL::GetModelUniforms(const ShaderType type) {
	
	switch (type) {
		case ShaderType::PHONG_SHADER:
			return &PHONG_SHADER;
		
		case ShaderType::GOURAUD_SHADER:
			return &GOURAUD_SHADER;
			
		case ShaderType::FLAT_SHADER:
			return &FLAT_SHADER;
			
		default:
			break;
	}
	
	return nullptr;
}
