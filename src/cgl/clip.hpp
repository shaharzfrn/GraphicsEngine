//
//  clip.hpp
//  CGApp
//
//  Created by Shahar Zafran on 02/01/2023.
//

#ifndef clip_hpp
#define clip_hpp

#include <stdio.h>
#include "math.hpp"



#define clip_func(name, sign, dir, dir1, dir2) \
static float name(const vec4& a, const vec4& b, vec4& c) \
{\
	float t, dx, dy, dz, dw, den;\
	dx = (b.x - a.x);\
	dy = (b.y - a.y);\
	dz = (b.z - a.z);\
	dw = (b.w - a.w);\
	den = -(sign d ## dir) + dw;\
	if (den == 0) t=0;\
	else t = ( sign a.dir - a.w) / den;\
	c.dir1 = a.dir1 + t * d ## dir1;\
	c.dir2 = a.dir2 + t * d ## dir2;\
	c.w = a.w + t * dw;\
	c.dir = sign c.w;\
	return t;\
}


clip_func(ClipMin_X, -, x, y, z);
clip_func(ClipMax_X, +, x, y, z);
//
clip_func(ClipMin_Y, -, y, x, z);
clip_func(ClipMax_Y, +, y, x, z);
//
clip_func(ClipMin_Z, -, z, x, y);
clip_func(ClipMax_Z, +, z, x, y);




//static float ClipMin_X(const vec4& v1, const vec4& v2, vec4& out) {
//
//	vec4 dir = v2 - v1;
//	float den = dir.x + dir.w;
//	float t = 0;
//	if (den != 0)
//		t = -(v1.x + v1.w) / den;
//
//	out = v1 + dir * t;
//	out.x = -out.w;
//
//	return t;
//};
//
//static float ClipMax_X(const vec4& v1, const vec4& v2, vec4& out) {
//
//	vec4 dir = v2 - v1;
//	float den = -dir.x + dir.w;
//	float t = 0;
//	if (den != 0)
//		t = (v1.x - v1.w) / den;
//
//	out = v1 + dir * t;
//	out.x = out.w;
//
//	return t;
//};
//
//
//static float ClipMin_Y(const vec4& v1, const vec4& v2, vec4& out) {
//
//	vec4 dir = v2 - v1;
//	float den = dir.y + dir.w;
//	float t = 0;
//	if (den != 0)
//		t = -(v1.y + v1.w) / den;
//
//	out = v1 + dir * t;
//	out.y = -out.w;
//
//	return t;
//};
//
//static float ClipMax_Y(const vec4& v1, const vec4& v2, vec4& out) {
//
//	vec4 dir = v2 - v1;
//	float den = -dir.y + dir.w;
//	float t = 0;
//	if (den != 0)
//		t = (v1.y - v1.w) / den;
//
//	out = v1 + dir * t;
//	out.y = out.w;
//
//	return t;
//};
//
//
//static float ClipMin_Z(const vec4& v1, const vec4& v2, vec4& out) {
//
//	vec4 dir = v2 - v1;
//	float den = dir.z + dir.w;
//	float t = 0;
//	if (den != 0)
//		t = -(v1.z + v1.w) / den;
//
//	out = v1 + dir * t;
//	out.z = -out.w;
//
//	return t;
//};
//
//static float ClipMax_Z(const vec4& v1, const vec4& v2, vec4& out) {
//
//	vec4 dir = v2 - v1;
//	float den = -dir.z + dir.w;
//	float t = 0;
//	if (den != 0)
//		t = (v1.z - v1.w) / den;
//
//	out = v1 + dir * t;
//	out.z = out.w;
//
//	return t;
//};



static float (*clip_proc[6])(const vec4&, const vec4&, vec4&) = {
	ClipMin_Z, ClipMax_Z,
	ClipMin_X, ClipMax_X,
	ClipMin_Y, ClipMax_Y
};


/*
static float (*clip_proc[6])(vec4&, vec4&, vec4&) {
	[](vec4& c, vec4& a, vec4& b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		float dw = b.w - a.w;
		float den = -(-dz) + dw;
		float t = 0;
		
		if (den != 0)
			t = ( -a.z - a.w) / den;
		
		c.x = a.x + t * dx;
		c.y = a.y + t * dy;
		c.w = a.w + t * dw;
		c.z = -c.w;
		
		return t;
	}, // clip_z_min
	[](vec4& c, vec4& a, vec4& b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		float dw = b.w - a.w;
		float den = -( + dz) + dw;
		float t = 0;
		
		if (den != 0)
			t = (+ a.z - a.w) / den;
		
		c.x = a.x + t * dx;
		c.y = a.y + t * dy;
		c.w = a.w + t * dw;
		c.z = + c.w;
		
		return t;
	}, // clip_z_max
	[](vec4& c, vec4& a, vec4& b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		float dw = b.w - a.w;
		float den = -(-dx) + dw;
		float t = 0;
		
		if (den != 0)
			t = ( -a.x - a.w) / den;
		
		c.y = a.y + t * dy;
		c.z = a.z + t * dz;
		c.w = a.w + t * dw;
		c.x = -c.w;
		
		return t;
	}, // clip_x_min
	[](vec4& c, vec4& a, vec4& b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		float dw = b.w - a.w;
		float den = -( + dx) + dw;
		float t = 0;
		
		if (den != 0)
			t = (+ a.x - a.w) / den;
		
		c.y = a.y + t * dy;
		c.z = a.z + t * dz;
		c.w = a.w + t * dw;
		c.x = + c.w;
		
		return t;
	}, // clip_x_max
	[](vec4& c, vec4& a, vec4& b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		float dw = b.w - a.w;
		float den = -( + dy) + dw;
		float t = 0;
		
		if (den != 0)
			t = (+ a.y - a.w) / den;
		
		c.x = a.x + t * dx;
		c.z = a.z + t * dz;
		c.w = a.w + t * dw;
		c.y = + c.w;
		
		return t;
	}, // clip_y_min
	[](vec4& c, vec4& a, vec4& b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		float dw = b.w - a.w;
		float den = -( + dy) + dw;
		float t = 0;
		
		if (den != 0)
			t = (+ a.y - a.w) / den;
		
		c.x = a.x + t * dx;
		c.z = a.z + t * dz;
		c.w = a.w + t * dw;
		c.y = + c.w;
		
		return t;
	}, // clip_y_max
}; // WTF ??????? HOW DID I FIGURE IT OUT :O :0
*/

#endif /* clip_hpp */
