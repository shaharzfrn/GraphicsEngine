//
//  light.hpp
//  CGApp
//
//  Created by Shahar Zafran on 04/01/2023.
//

#ifndef light_hpp
#define light_hpp

#include <stdio.h>
#include "math.hpp"

#define MAX_LIGHTS 	7
#define MAX_SHADOWS MAX_LIGHTS

typedef enum {
	LIGHT_TYPE_DIRECTIONAL,
	LIGHT_TYPE_POINT,
	LIGHT_TYPE_SPOT
} LightType;

typedef enum {
	LIGHT_SPACE_VIEW,
	LIGHT_SPACE_LOCAL
} LightSpace;



class Light {
public:
	
	LightType type;
	
	vec3 position;
	vec3 direction;
	
	vec3 color;
	
	bool enabled;
	
	float strength;
	float cutoff_angle; // in radians
	
	mat4 to_light_shadow_map_space;
	
	
	void CalculateLight(const vec3& to_eye, const vec3& normal, const vec3& world_position, const float& diffuse_factor, const float& specular_factor, const float& specular_exp, vec3& total_diffuse, vec3& total_specular);
	
	
};


namespace CGL {
inline Light lights[MAX_LIGHTS];
inline Light ambiant_light;

};
#endif /* light_hpp */
