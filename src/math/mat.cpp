//
//  mat.cpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#include "mat.hpp"
#include <memory>

mat4::mat4() {
	memset(mat, 0, sizeof(float) * 16);
};
mat4::mat4(const mat4& other) {
	memcpy(mat, other.mat, sizeof(float) * 16);
};

mat4& mat4::operator=(const mat4& other) {
	memcpy(mat, other.mat, sizeof(float) * 16);
	return *this;
};

mat4 mat4::operator + (const mat4& other) const {
	mat4 result;
	
	result[0][0] = mat[0][0] + other[0][0];
	result[0][1] = mat[0][1] + other[0][1];
	result[0][2] = mat[0][2] + other[0][2];
	result[0][3] = mat[0][3] + other[0][3];
	
	result[1][0] = mat[1][0] + other[1][0];
	result[1][1] = mat[1][1] + other[1][1];
	result[1][2] = mat[1][2] + other[1][2];
	result[1][3] = mat[1][3] + other[1][3];
	
	result[2][0] = mat[2][0] + other[2][0];
	result[2][1] = mat[2][1] + other[2][1];
	result[2][2] = mat[2][2] + other[2][2];
	result[2][3] = mat[2][3] + other[2][3];
	
	result[3][0] = mat[3][0] + other[3][0];
	result[3][1] = mat[3][1] + other[3][1];
	result[3][2] = mat[3][2] + other[3][2];
	result[3][3] = mat[3][3] + other[3][3];
	
	return result;
};
mat4 mat4::operator + (const float& other) const {
	mat4 result;
	
	result[0][0] = mat[0][0] + other;
	result[0][1] = mat[0][1] + other;
	result[0][2] = mat[0][2] + other;
	result[0][3] = mat[0][3] + other;
	
	result[1][0] = mat[1][0] + other;
	result[1][1] = mat[1][1] + other;
	result[1][2] = mat[1][2] + other;
	result[1][3] = mat[1][3] + other;
	
	result[2][0] = mat[2][0] + other;
	result[2][1] = mat[2][1] + other;
	result[2][2] = mat[2][2] + other;
	result[2][3] = mat[2][3] + other;
	
	result[3][0] = mat[3][0] + other;
	result[3][1] = mat[3][1] + other;
	result[3][2] = mat[3][2] + other;
	result[3][3] = mat[3][3] + other;
	
	return result;
};
mat4& mat4::operator += (const mat4& other) {
	mat[0][0] += other[0][0];
	mat[0][1] += other[0][1];
	mat[0][2] += other[0][2];
	mat[0][3] += other[0][3];
	
	mat[1][0] += other[1][0];
	mat[1][1] += other[1][1];
	mat[1][2] += other[1][2];
	mat[1][3] += other[1][3];
	
	mat[2][0] += other[2][0];
	mat[2][1] += other[2][1];
	mat[2][2] += other[2][2];
	mat[2][3] += other[2][3];
	
	mat[3][0] += other[3][0];
	mat[3][1] += other[3][1];
	mat[3][2] += other[3][2];
	mat[3][3] += other[3][3];
	
	return *this;
};
mat4& mat4::operator += (const float& other) {
	mat[0][0] += other;
	mat[0][1] += other;
	mat[0][2] += other;
	mat[0][3] += other;
	
	mat[1][0] += other;
	mat[1][1] += other;
	mat[1][2] += other;
	mat[1][3] += other;
	
	mat[2][0] += other;
	mat[2][1] += other;
	mat[2][2] += other;
	mat[2][3] += other;
	
	mat[3][0] += other;
	mat[3][1] += other;
	mat[3][2] += other;
	mat[3][3] += other;
	
	return *this;
};

mat4 mat4::operator - (const mat4& other) const {
	mat4 result;
	
	result[0][0] = mat[0][0] - other[0][0];
	result[0][1] = mat[0][1] - other[0][1];
	result[0][2] = mat[0][2] - other[0][2];
	result[0][3] = mat[0][3] - other[0][3];
	
	result[1][0] = mat[1][0] - other[1][0];
	result[1][1] = mat[1][1] - other[1][1];
	result[1][2] = mat[1][2] - other[1][2];
	result[1][3] = mat[1][3] - other[1][3];
	
	result[2][0] = mat[2][0] - other[2][0];
	result[2][1] = mat[2][1] - other[2][1];
	result[2][2] = mat[2][2] - other[2][2];
	result[2][3] = mat[2][3] - other[2][3];
	
	result[3][0] = mat[3][0] - other[3][0];
	result[3][1] = mat[3][1] - other[3][1];
	result[3][2] = mat[3][2] - other[3][2];
	result[3][3] = mat[3][3] - other[3][3];
	
	return result;
};
mat4 mat4::operator - (const float& other) const {
	mat4 result;
	
	result[0][0] = mat[0][0] - other;
	result[0][1] = mat[0][1] - other;
	result[0][2] = mat[0][2] - other;
	result[0][3] = mat[0][3] - other;
	
	result[1][0] = mat[1][0] - other;
	result[1][1] = mat[1][1] - other;
	result[1][2] = mat[1][2] - other;
	result[1][3] = mat[1][3] - other;
	
	result[2][0] = mat[2][0] - other;
	result[2][1] = mat[2][1] - other;
	result[2][2] = mat[2][2] - other;
	result[2][3] = mat[2][3] - other;
	
	result[3][0] = mat[3][0] - other;
	result[3][1] = mat[3][1] - other;
	result[3][2] = mat[3][2] - other;
	result[3][3] = mat[3][3] - other;
	
	return result;
};
mat4& mat4::operator -= (const mat4& other) {
	mat[0][0] -= other[0][0];
	mat[0][1] -= other[0][1];
	mat[0][2] -= other[0][2];
	mat[0][3] -= other[0][3];
	
	mat[1][0] -= other[1][0];
	mat[1][1] -= other[1][1];
	mat[1][2] -= other[1][2];
	mat[1][3] -= other[1][3];
	
	mat[2][0] -= other[2][0];
	mat[2][1] -= other[2][1];
	mat[2][2] -= other[2][2];
	mat[2][3] -= other[2][3];
	
	mat[3][0] -= other[3][0];
	mat[3][1] -= other[3][1];
	mat[3][2] -= other[3][2];
	mat[3][3] -= other[3][3];
	
	return *this;
};
mat4& mat4::operator -= (const float& other) {
	mat[0][0] -= other;
	mat[0][1] -= other;
	mat[0][2] -= other;
	mat[0][3] -= other;
	
	mat[1][0] -= other;
	mat[1][1] -= other;
	mat[1][2] -= other;
	mat[1][3] -= other;
	
	mat[2][0] -= other;
	mat[2][1] -= other;
	mat[2][2] -= other;
	mat[2][3] -= other;
	
	mat[3][0] -= other;
	mat[3][1] -= other;
	mat[3][2] -= other;
	mat[3][3] -= other;
	
	return *this;
};

mat4 mat4::operator * (const mat4& other) const {
	mat4 result;
			
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			float element = 0;
			for (int k = 0; k < 4; k++)
				element += mat[i][k] * other[k][j];
			
			result[i][j] = element;
		}
	
	return result;
};
mat4 mat4::operator * (const float& other) const {
	mat4 result;
	
	result[0][0] = mat[0][0] * other;
	result[0][1] = mat[0][1] * other;
	result[0][2] = mat[0][2] * other;
	result[0][3] = mat[0][3] * other;
	
	result[1][0] = mat[1][0] * other;
	result[1][1] = mat[1][1] * other;
	result[1][2] = mat[1][2] * other;
	result[1][3] = mat[1][3] * other;
	
	result[2][0] = mat[2][0] * other;
	result[2][1] = mat[2][1] * other;
	result[2][2] = mat[2][2] * other;
	result[2][3] = mat[2][3] * other;
	
	result[3][0] = mat[3][0] * other;
	result[3][1] = mat[3][1] * other;
	result[3][2] = mat[3][2] * other;
	result[3][3] = mat[3][3] * other;
	
	return result;
};
vec4 mat4::operator * (const vec4& other) const {
	vec4 result;
			
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result[i] += mat[i][j] * other[j];
	
	return result;
};
mat4& mat4::operator *= (const mat4& other) {
	mat[0][0] *= other[0][0];
	mat[0][1] *= other[0][1];
	mat[0][2] *= other[0][2];
	mat[0][3] *= other[0][3];
	
	mat[1][0] *= other[1][0];
	mat[1][1] *= other[1][1];
	mat[1][2] *= other[1][2];
	mat[1][3] *= other[1][3];
	
	mat[2][0] *= other[2][0];
	mat[2][1] *= other[2][1];
	mat[2][2] *= other[2][2];
	mat[2][3] *= other[2][3];
	
	mat[3][0] *= other[3][0];
	mat[3][1] *= other[3][1];
	mat[3][2] *= other[3][2];
	mat[3][3] *= other[3][3];
	
	return *this;
};
mat4& mat4::operator *= (const float& other) {
	mat[0][0] *= other;
	mat[0][1] *= other;
	mat[0][2] *= other;
	mat[0][3] *= other;
	
	mat[1][0] *= other;
	mat[1][1] *= other;
	mat[1][2] *= other;
	mat[1][3] *= other;
	
	mat[2][0] *= other;
	mat[2][1] *= other;
	mat[2][2] *= other;
	mat[2][3] *= other;
	
	mat[3][0] *= other;
	mat[3][1] *= other;
	mat[3][2] *= other;
	mat[3][3] *= other;
	
	return *this;
};

float* mat4::operator[](size_t i) {
	if (i < 0 || i > 3)
		throw std::out_of_range("mat4: index out of range");
	
	return mat[i];
}
const float* mat4::operator[](size_t i) const {
	if (i < 0 || i > 3)
		throw std::out_of_range("mat4: index out of range");
	
	return mat[i];
}
