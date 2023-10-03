//
//  light.cpp
//  CGApp
//
//  Created by Shahar Zafran on 04/01/2023.
//

#include "light.hpp"

#include <cmath>


using namespace CGL;



void Light::CalculateLight(const vec3& to_eye, const vec3& normal, const vec3& world_position, const float& diffuse_factor, const float& specular_factor, const float& specular_exp, vec3& total_diffuse, vec3& total_specular) {
	
	vec3 light_color;
	vec3 to_light;
	if (type == LIGHT_TYPE_POINT || type == LIGHT_TYPE_SPOT) {
		to_light = CGL::Normolize(position - world_position);
	} else if (type == LIGHT_TYPE_DIRECTIONAL) {
		to_light = CGL::Normolize(direction);
	}
	
	vec3 reflect_light = CGL::Normolize(CGL::Reflect(-to_light, normal));
	
	float diffuse = fmax(CGL::Dot(to_light, normal), 0.f);
	light_color += color * diffuse * diffuse_factor;
	
	float specular = pow(fmax(CGL::Dot(to_eye, reflect_light), 0.0f), specular_exp);
	light_color += color * specular * specular_factor;
	
	if (type == LIGHT_TYPE_SPOT) {
		
		float spot_light_intensity;
		float spot_factor = Dot(to_light, CGL::Normolize(direction));
		
		if (type == LIGHT_TYPE_SPOT && spot_factor > cutoff_angle) {
			spot_light_intensity = (1.0f - (1.0f - spot_factor) / (1.0f - cutoff_angle));
		} else {
			spot_light_intensity = 0.f;
		}

		light_color = light_color * spot_light_intensity;
	}
	
	total_diffuse += light_color;
//	total_specular = total_specular + specular_light;
}
