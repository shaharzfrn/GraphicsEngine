//
//  mat.hpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#ifndef mat_hpp
#define mat_hpp

#include <stdio.h>
#include <stdexcept>

#include "vec.hpp"

typedef struct mat4 {
	
	
	float mat[4][4];
	
	mat4();
	mat4(const mat4& other);
	
	mat4& operator=(const mat4& other);
	
	mat4 operator + (const mat4& other) const;
	mat4 operator + (const float& other) const;
	mat4& operator += (const mat4& other);
	mat4& operator += (const float& other);
	
	mat4 operator - (const mat4& other) const;
	mat4 operator - (const float& other) const;
	mat4& operator -= (const mat4& other);
	mat4& operator -= (const float& other);
	
	mat4 operator * (const mat4& other) const;
	mat4 operator * (const float& other) const;
	vec4 operator * (const vec4& other) const;
	mat4& operator *= (const mat4& other);
	mat4& operator *= (const float& other);
	
	float* operator[](size_t i);
	const float* operator[](size_t i) const;
	
} mat4;



#endif /* mat_hpp */
