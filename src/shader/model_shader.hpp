//
//  model_shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 31/12/2022.
//

#ifndef model_shader_hpp
#define model_shader_hpp

#include <stdio.h>
#include "shader.hpp"

#include "math.hpp"

#include "texture.hpp"

class ModelShader : public ShaderProgram {
	
protected:
	// struct to get the data for vertex shader
	struct {
		vec3 position;
		vec3 color;
		vec3 normal;
	} input;
	
public:
	
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 projection_matrix;
	
	bool silhouette_enabled;
	bool silhouette_depth_top;
	vec3 silhouette_color;
	
	Texture *silhouette_texture;
	
	vec3 camera_position;
	
	float diffuse_factor;
	float specular_factor;
	float specular_exp;
	
	bool object_selected;
	
	ModelShader(const ShaderType type);
	
	
	
//	virtual size_t GetVertexShaderInputSize() const;
//	virtual void SetVertexInput(const u_int8_t* data);
	
};


#endif /* model_shader_hpp */
