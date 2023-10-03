//
//  box.hpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#ifndef box_hpp
#define box_hpp

#include <stdio.h>
#include "vec.hpp"

typedef struct Box2f {
	float min_x;
	float min_y;
	
	float max_x;
	float max_y;
	
	void Join(const vec2& other);
} box2;

typedef struct Box3f {
	float min_x;
	float min_y;
	float min_z;
	
	float max_x;
	float max_y;
	float max_z;
	
	void Join(const vec3& other);
	void Join(const Box3f& other);
} box3;


#endif /* box_hpp */
