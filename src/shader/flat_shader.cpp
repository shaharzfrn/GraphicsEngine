//
//  flat_shader.cpp
//  CGApp
//
//  Created by Shahar Zafran on 21/01/2023.
//

#include "flat_shader.hpp"

#include "math.hpp"
#include "light.hpp"
#include "shadow.hpp"


void FlatShader::VertexShader() {
	vec4 world_position = model_matrix * vec4(input.position, 1.0);
	out_position = projection_matrix * view_matrix * world_position;
//	printf("%f, %f, %f\n", out_position.x, out_position.y, out_position.z);
	vec3 total_diffuse = {0, 0, 0};
	vec3 total_specular = {0, 0, 0};
	
	// we always want to add the ambiant light (if it's enabled)
	if (CGL::ambiant_light.enabled)
		pass.illumination = CGL::ambiant_light.color * CGL::ambiant_light.strength;
	
	vec3 to_eye = CGL::Normolize(camera_position - world_position.xyz());
	vec3 normal = CGL::Normolize((inverse_model_matrix * vec4(input.normal, 1.0f)).xyz() * (reverse_normals ? -1.0f : 1.0f));
	
	for (int i = 0; i < MAX_LIGHTS; i++) {
		
		Light light = CGL::lights[i];
		
		if (light.enabled) {
			vec4 shadow_map_coords = CGL::shadows[i]->mvp * world_position;
			// if the pixel is in the shadow, we don't want to add the light
			// diffuse and specular effects
			if (light.type != LIGHT_TYPE_SPOT  && CGL::shadows[i]->InShadow(shadow_map_coords.xyz())) {
				continue;
			}
			
			light.CalculateLight(to_eye, normal, world_position.xyz(), diffuse_factor, specular_factor, specular_exp, total_diffuse, total_specular);
		}
	}
	
	// add the total diffuse and specular effect on the pixel
	pass.illumination += total_diffuse + total_specular;
	pass.texture_coords = input.texture_coords;
}
void FlatShader::FragmentShader() {
	bool draw_silhouette = false;
	if (silhouette_enabled) {
		
		int count = 0;
		int x = frag_coords.x;
		int y = frag_coords.y;

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				
				if (!silhouette_texture->InBounds(x + i, y + j))
					continue;
				
				if (((int)silhouette_texture->Get<u_int8_t>(x + i, y + j)) == 0xFF)
					count++;
			}
		}
		
		draw_silhouette = 0 < count && count < 9;
	}
	
	if (draw_silhouette) {
		frag_color = vec4(silhouette_color, 1.0f);
		frag_depth = silhouette_depth_top ? INFINITY : frag_depth;
		return;
	}
	
	vec3 color;
	if (color_texture != nullptr && color_texture->InBounds(pass.texture_coords)) {
		color = color_texture->Get<vec4>(pass.texture_coords).xyz();
	} else {
		color = front_facing ? object_front_color : object_back_color;
	}
	
	frag_color = vec4(pass.illumination * color, 1.0);
	
	if (object_selected) {
		frag_color = frag_color * 0.6 + vec4(0.4, 0.4, 0.4 ,1);
	}
	
	// calmp the output result color
	frag_color = CGL::Clamp(frag_color);
}
