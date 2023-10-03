//
//  box.cpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#include "box.hpp"
#include <cmath>

void Box2f::Join(const vec2& other) {
	min_y = fmin(min_y, other.y);
	max_y = fmax(max_y, other.y);
	
	min_x = fmin(min_x, other.x);
	max_x = fmax(max_x, other.x);
}

void Box3f::Join(const vec3& other) {
	min_x = fmin(min_x, other.x);
	max_x = fmax(max_x, other.x);
	
	min_y = fmin(min_y, other.y);
	max_y = fmax(max_y, other.y);
	
	min_z = fmin(min_z, other.z);
	max_z = fmax(max_z, other.z);
}

void Box3f::Join(const Box3f& other) {
	min_x = fmin(min_x, other.min_x);
	min_y = fmin(min_y, other.min_y);
	min_z = fmin(min_z, other.min_z);
	
	max_x = fmax(max_x, other.max_x);
	max_y = fmax(max_y, other.max_y);
	max_z = fmax(max_z, other.max_z);
}
