//
//  uniforms.h
//  CGApp
//
//  Created by Shahar Zafran on 08/01/2023.
//

#ifndef uniforms_h
#define uniforms_h

#include "math.hpp"
#include "texture.hpp"


struct ModelUniforms {
	
	mat4 model_matrix;
	mat4 inverse_model_matrix;
	mat4 view_matrix;
	mat4 projection_matrix;
	
	bool silhouette_enabled;
	bool silhouette_depth_top;
	vec3 silhouette_color;
	
	vec3 object_front_color;
	vec3 object_back_color;
	
	Texture *silhouette_texture;
	Texture *color_texture;
	
	vec3 camera_position;
	
	float diffuse_factor;
	float specular_factor;
	float specular_exp;
	
	bool object_selected;
	bool reverse_normals;
};




#endif /* uniforms_h */
