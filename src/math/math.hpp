//
//  math.h
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#ifndef math_h
#define math_h


#include "vec.hpp"
#include "mat.hpp"
#include "box.hpp"




namespace CGL {


auto Map = [](auto x, auto in_min, auto in_max, auto out_min, auto out_max) {
	return (x - in_min)/(in_max - in_min) * (out_max - out_min) + out_min;
};

float Clamp(const float& v, const float& low=0, const float& high=1);

vec2 Normolize(const vec2& v1);
vec3 Normolize(const vec3& v1);
vec4 Normolize(const vec4& v1);

float Cross(const vec2& v1, const vec2& v2);
vec3 Cross(const vec3& v1, const vec3& v2);
vec4 Cross(const vec4& v1, const vec4& v2);

float Dot(const vec2& v1, const vec2& v2);
float Dot(const vec3& v1, const vec3& v2);
float Dot(const vec4& v1, const vec4& v2);

vec2 Reflect(const vec2& v1, const vec2& v2);
vec3 Reflect(const vec3& v1, const vec3& v2);
vec4 Reflect(const vec4& v1, const vec4& v2);

vec2 Clamp(const vec2& v1, const float& low=0, const float& high=1);
vec3 Clamp(const vec3& v1, const float& low=0, const float& high=1);
vec4 Clamp(const vec4& v1, const float& low=0, const float& high=1);

float Distance(const vec2& v1, const vec2& v2);
float Distance(const vec3& v1, const vec3& v2);
float Distance(const vec4& v1, const vec4& v2);

float Area(const vec2& a, const vec2& b, const vec2& c);

mat4 Zero();
mat4 Identity();

mat4 Rotate(const vec3& angle, const vec3& order={0, 1, 2});
mat4 Translate(const vec3& pos);
mat4 Scale(const vec3& scale);
mat4 Scale(const float& scale);

mat4 Transpose(const mat4& mat);
mat4 Inverse(const mat4& mat);




mat4 GenerateViewPortMatrix(const int& x, const int& y, const int& width, const int& height, const float& z_min, const float& z_max);
mat4 GenerateModelMatrix(const vec3 &position, const vec3 &rotation, const vec3 &scale, const bool &object=true);
mat4 GenerateLookAt(const vec3 &position, const vec3 &direction, const vec3 &up);
mat4 GeneratePerspectiveProjectionMatrix(const float& width, const float& height, const float& near, const float& far, const float& fov);
mat4 GenerateOrthoProjectionMatrix(const float& width, const float& height, const float& distance, const float& near, const float& far);
}

#endif /* math_h */
