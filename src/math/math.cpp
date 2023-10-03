//
//  math.cpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#include "math.hpp"

#include <stdio.h>
#include <iostream>
#include <cmath>

float CGL::Clamp(const float& v, const float& low, const float& high) {
	return fmin(fmax(v, low), high);
}

vec2 CGL::Normolize(const vec2& v1) {
	float length = sqrt(Dot(v1, v1));
	return vec2(v1.x / length, v1.y / length);
};
vec3 CGL::Normolize(const vec3& v1) {
	float length = sqrt(Dot(v1, v1));
	return vec3(v1.x / length, v1.y / length, v1.z / length);
};
vec4 CGL::Normolize(const vec4& v1) {
	float length = sqrt(Dot(v1, v1));
	return vec4(v1.x / length, v1.y / length, v1.z / length, v1.w / length);
};

float CGL::Cross(const vec2& v1, const vec2& v2) {
	return v1[0] * v2[1] - v1[1] * v2[0];
};
vec3 CGL::Cross(const vec3& v1, const vec3& v2) {
	return vec3(v1[1] * v2[2] - v1[2] * v2[1],
				v1[2] * v2[0] - v1[0] * v2[2],
				v1[0] * v2[1] - v1[1] * v2[0]);
}
vec4 CGL::Cross(const vec4& v1, const vec4& v2) {
	return vec4(v1[1] * v2[2] - v1[2] * v2[1],
				v1[2] * v2[0] - v1[0] * v2[2],
				v1[0] * v2[1] - v1[1] * v2[0],
				1);
}

float CGL::Dot(const vec2& v1, const vec2& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1];
}
float CGL::Dot(const vec3& v1, const vec3& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
float CGL::Dot(const vec4& v1, const vec4& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}

vec2 CGL::Reflect(const vec2& v1, const vec2& v2) {
	return v1 - 2.0f * Dot(v2 , v1) * v2;
}
vec3 CGL::Reflect(const vec3& v1, const vec3& v2) {
	return v1 - 2.0f * Dot(v2 , v1) * v2;
}
vec4 CGL::Reflect(const vec4& v1, const vec4& v2) {
	return v1 - 2.0f * Dot(v2 , v1) * v2;
}

vec2 CGL::Clamp(const vec2& v1, const float& low, const float& high) {
	return vec2(Clamp(v1[0], low, high), Clamp(v1[1], low, high));
};
vec3 CGL::Clamp(const vec3& v1, const float& low, const float& high) {
	return vec3(Clamp(v1[0], low, high), Clamp(v1[1], low, high), Clamp(v1[2], low, high));
}
vec4 CGL::Clamp(const vec4& v1, const float& low, const float& high) {
	return vec4(Clamp(v1[0], low, high), Clamp(v1[1], low, high), Clamp(v1[2], low, high), Clamp(v1[3], low, high));
}

float CGL::Distance(const vec2& v1, const vec2& v2) {
	return sqrt(Dot(v1 - v2, v1 - v2));
};
float CGL::Distance(const vec3& v1, const vec3& v2) {
	return sqrt(Dot(v1 - v2, v1 - v2));
}
float CGL::Distance(const vec4& v1, const vec4& v2) {
	return sqrt(Dot(v1 - v2, v1 - v2));
}

float CGL::Area(const vec2& a, const vec2& b, const vec2& c) {
	return Cross(b - a, c - a);
}


mat4 CGL::Zero() {
	return {};
}
mat4 CGL::Identity() {
	mat4 id;
	
	id[0][0] = 1;
	id[1][1] = 1;
	id[2][2] = 1;
	id[3][3] = 1;
	
	return id;
}
mat4 CGL::Rotate(const vec3& angle, const vec3& order) {
	
	// order -> order.x == index of rotate around x axis
	for (int i = 0; i < 3; i++)
		if (order[i] < 0 || order[i] > 2)
			throw std::out_of_range("Order index must be in range [0-2]");
	
	mat4 axis[] = {
		Identity(),
		Identity(),
		Identity()
	};
	
	
	vec3 radians (angle);
	radians = radians * (M_PI / 180);
	
	axis[(int)order.x][1][1] = cos(radians.x);
	axis[(int)order.x][1][2] = -sin(radians.x);
	axis[(int)order.x][2][1] = sin(radians.x);
	axis[(int)order.x][2][2] = cos(radians.x);
	
	
	axis[(int)order.y][0][0] = cos(radians.y);
	axis[(int)order.y][0][2] = sin(radians.y);
	axis[(int)order.y][2][0] = -sin(radians.y);
	axis[(int)order.y][2][2] = cos(radians.y);
	
	
	axis[(int)order.z][0][0] = cos(radians.z);
	axis[(int)order.z][0][1] = -sin(radians.z);
	axis[(int)order.z][1][0] = sin(radians.z);
	axis[(int)order.z][1][1] = cos(radians.z);
	
	return (axis[0] * axis[1]) * axis[2];
	
}
mat4 CGL::Translate(const vec3& pos) {
	mat4 result = Identity();
	
	result[0][3] = pos.x;
	result[1][3] = pos.y;
	result[2][3] = pos.z;
	
	return result * Identity();
}
mat4 CGL::Scale(const vec3& scale) {
	mat4 result = Identity();
	
	result[0][0] = scale.x;
	result[1][1] = scale.y;
	result[2][2] = scale.z;
	
	return result;
}
mat4 CGL::Scale(const float& scale) {
	mat4 result = Identity();
	
	result[0][0] = scale;
	result[1][1] = scale;
	result[2][2] = scale;
	
	return result;
}


mat4 CGL::Transpose(const mat4& mat) {
	mat4 transpose;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			transpose[j][i] = mat[i][j];
		}
	}
	
	return transpose;
}

mat4 CGL::Inverse(const mat4& matrix) {
	mat4 inverse;
	
	float sub_factor_00 = matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3];
	float sub_factor_01 = matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3];
	float sub_factor_02 = matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2];
	float sub_factor_03 = matrix[2][0] * matrix[3][3] - matrix[3][0] * matrix[2][3];
	float sub_factor_04 = matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2];
	float sub_factor_05 = matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1];
	float sub_factor_06 = matrix[1][2] * matrix[3][3] - matrix[3][2] * matrix[1][3];
	float sub_factor_07 = matrix[1][1] * matrix[3][3] - matrix[3][1] * matrix[1][3];
	float sub_factor_08 = matrix[1][1] * matrix[3][2] - matrix[3][1] * matrix[1][2];
	float sub_factor_09 = matrix[1][0] * matrix[3][3] - matrix[3][0] * matrix[1][3];
	float sub_factor_10 = matrix[1][0] * matrix[3][2] - matrix[3][0] * matrix[1][2];
	float sub_factor_11 = matrix[1][0] * matrix[3][1] - matrix[3][0] * matrix[1][1];
	float sub_factor_12 = matrix[1][2] * matrix[2][3] - matrix[2][2] * matrix[1][3];
	float sub_factor_13 = matrix[1][1] * matrix[2][3] - matrix[2][1] * matrix[1][3];
	float sub_factor_14 = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];
	float sub_factor_15 = matrix[1][0] * matrix[2][3] - matrix[2][0] * matrix[1][3];
	float sub_factor_16 = matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2];
	float sub_factor_17 = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];
	
	inverse[0][0] = + (matrix[1][1] * sub_factor_00 - matrix[1][2] * sub_factor_01 + matrix[1][3] * sub_factor_02);
	inverse[0][1] = - (matrix[1][0] * sub_factor_00 - matrix[1][2] * sub_factor_03 + matrix[1][3] * sub_factor_04);
	inverse[0][2] = + (matrix[1][0] * sub_factor_01 - matrix[1][1] * sub_factor_03 + matrix[1][3] * sub_factor_05);
	inverse[0][3] = - (matrix[1][0] * sub_factor_02 - matrix[1][1] * sub_factor_04 + matrix[1][2] * sub_factor_05);
	
	inverse[1][0] = - (matrix[0][1] * sub_factor_00 - matrix[0][2] * sub_factor_01 + matrix[0][3] * sub_factor_02);
	inverse[1][1] = + (matrix[0][0] * sub_factor_00 - matrix[0][2] * sub_factor_03 + matrix[0][3] * sub_factor_04);
	inverse[1][2] = - (matrix[0][0] * sub_factor_01 - matrix[0][1] * sub_factor_03 + matrix[0][3] * sub_factor_05);
	inverse[1][3] = + (matrix[0][0] * sub_factor_02 - matrix[0][1] * sub_factor_04 + matrix[0][2] * sub_factor_05);
	
	inverse[2][0] = + (matrix[0][1] * sub_factor_06 - matrix[0][2] * sub_factor_07 + matrix[0][3] * sub_factor_08);
	inverse[2][1] = - (matrix[0][0] * sub_factor_06 - matrix[0][2] * sub_factor_09 + matrix[0][3] * sub_factor_10);
	inverse[2][2] = + (matrix[0][0] * sub_factor_07 - matrix[0][1] * sub_factor_09 + matrix[0][3] * sub_factor_11);
	inverse[2][3] = - (matrix[0][0] * sub_factor_08 - matrix[0][1] * sub_factor_10 + matrix[0][2] * sub_factor_11);
	
	inverse[3][0] = - (matrix[0][1] * sub_factor_12 - matrix[0][2] * sub_factor_13 + matrix[0][3] * sub_factor_14);
	inverse[3][1] = + (matrix[0][0] * sub_factor_12 - matrix[0][2] * sub_factor_15 + matrix[0][3] * sub_factor_16);
	inverse[3][2] = - (matrix[0][0] * sub_factor_13 - matrix[0][1] * sub_factor_15 + matrix[0][3] * sub_factor_17);
	inverse[3][3] = + (matrix[0][0] * sub_factor_14 - matrix[0][1] * sub_factor_16 + matrix[0][2] * sub_factor_17);
	
	float determinant =
	+ matrix[0][0] * inverse[0][0]
	+ matrix[0][1] * inverse[0][1]
	+ matrix[0][2] * inverse[0][2]
	+ matrix[0][3] * inverse[0][3];
	
	
	return inverse * (1 / determinant);
}




mat4 CGL::GenerateViewPortMatrix(const int& x, const int& y, const int& width, const int& height, const float& z_min, const float& z_max) {
	
	mat4 viewport = Identity();
	
	float l = x;			// left
	float b = y; 			// bottom
	
	float r = l + width; 	// right
	float t = b + height; 	// top
	
	float n = z_min;		// near
	float f = z_max;		// far
	
	viewport[0][0] = (r - l) / 2;
	viewport[0][3] = (r + l) / 2;
	
	viewport[1][1] = (t - b) / 2;
	viewport[1][3] = (t + b) / 2;
	
	//	viewport[2][2] = -(f - n);
	//	viewport[2][3] = n;
	
	viewport[3][3] = 1.f;
	
	return viewport;
};

mat4 CGL::GenerateModelMatrix(const vec3 &position, const vec3 &rotation, const vec3 &scale, const bool &object) {
	return (object ? Translate(position) * Rotate(rotation) : Rotate(rotation) * Translate(position)) * Scale(scale);
};

mat4 CGL::GenerateLookAt(const vec3 &position, const vec3 &direction, const vec3 &up) {
	mat4 result;
	
	vec3 n = Normolize(position - direction);
	vec3 u = Normolize(Cross(up, n));
	vec3 v = Normolize(Cross(n, u));
	
	vec3 t = {Dot(u, -position), Dot(v, -position), Dot(n, -position)};
	
	float matrix[4][4] = {
		{u.x, u.y, u.z, t.x},
		{v.x, v.y, v.z, t.y},
		{n.x, n.y, n.z, t.z},
		{0.f, 0.f, 0.f, 1.0f}
	};
	
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = matrix[i][j];
		}
	}
	
	return result;
}

mat4 CGL::GeneratePerspectiveProjectionMatrix(const float& width, const float& height, const float& near, const float& far, const float& fov) {
	
	mat4 projection = Zero();
	
	float aspect_ratio = (float)width / (float)height;
	float f = 1.0f / ((float)tan(fov * M_PI / 360.f));
	
	projection[0][0] = f / aspect_ratio;
	projection[1][1] = -f;
	projection[2][2] = -(far + near) / (far - near);
	
	projection[2][3] = -2.0f * far * near / (far - near);
	projection[3][2] = -1.0f;
	
	return projection;
}

mat4 CGL::GenerateOrthoProjectionMatrix(const float& width, const float& height, const float& distance, const float& near, const float& far) {
	mat4 projection;
	
	float aspect_ratio = width / height;
	float f = 1.0f / ((float)(distance * tan(M_PI / 8.0f)));
	
	projection[0][0] = f / aspect_ratio;
	projection[1][1] = -f;
	projection[2][2] = -2.0f / (far - near);
	projection[3][3] = 1.0f;
	
	projection[2][3] = -(far + near) / (far - near);
	
	return projection;
}
