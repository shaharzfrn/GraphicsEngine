//
//  vec.cpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#include "vec.hpp"

vec2::Vector2f(const float& x, const float& y): x(x), y(y) {};
vec2::Vector2f(const Vector2f& other): x(other.x), y(other.y) {};
vec2::Vector2f(const float arr[2]): x(arr[0]), y(arr[1]) {};

vec2& Vector2f::operator = (const Vector2f& other) {
	
	if (this == &other) return *this;
		
	this->x = other.x;
	this->y = other.y;
		
	return *this;
}

vec2 Vector2f::operator + (const Vector2f& other) const {
	return {this->x + other.x, this->y + other.y};
};
vec2 Vector2f::operator + (const float& other) const {
	return {this->x + other, this->y + other};
};
vec2& Vector2f::operator += (const Vector2f& other) {
	this->x += other.x;
	this->y += other.y;
	
	return *this;
};
vec2& Vector2f::operator += (const float& other) {
	this->x += other;
	this->y += other;
	
	return *this;
};

vec2 Vector2f::operator - () const {
	return {-this->x, -this->y};
};
vec2 Vector2f::operator - (const Vector2f& other) const {
	return {this->x - other.x, this->y - other.y};
};
vec2 Vector2f::operator - (const float& other) const {
	return {this->x - other, this->y - other};
};
vec2& Vector2f::operator -= (const Vector2f& other) {
	
	this->x -= other.x;
	this->y -= other.y;
	
	return *this;
};
vec2& Vector2f::operator -= (const float& other) {
	
	this->x -= other;
	this->y -= other;
	
	return *this;
};

vec2 Vector2f::operator * (const Vector2f& other) const {
	return {this->x * other.x, this->y * other.y};
};
vec2 Vector2f::operator * (const float& other) const {
	return {this->x * other, this->y * other};
};
vec2& Vector2f::operator *= (const Vector2f& other) {
	this->x *= other.x;
	this->y *= other.y;
	
	return *this;
};
vec2& Vector2f::operator *= (const float& other) {
	this->x *= other;
	this->y *= other;
	
	return *this;
};


vec2 Vector2f::operator / (const Vector2f& other) const {
	return {this->x / other.x, this->y / other.y};
};
vec2 Vector2f::operator / (const float& other) const {
	return {this->x / other, this->y / other};
};
vec2& Vector2f::operator /= (const Vector2f& other) {
	this->x /= other.x;
	this->y /= other.y;
	
	return *this;
};
vec2& Vector2f::operator /= (const float& other) {
	this->x /= other;
	this->y /= other;
	
	return *this;
};

float& Vector2f::operator[](size_t index) {
	
	switch (index) {
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		default:
			break;
	};
	throw std::out_of_range("Vector2f: index out of range");
};
const float& Vector2f::operator[](size_t index) const {
	switch (index) {
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		default:
			break;
	};
	throw std::out_of_range("Vector2f: index out of range");
};



vec3::Vector3f(const float& x, const float& y, const float& z): x(x), y(y), z(z) {};
vec3::Vector3f(const Vector3f& other): x(other.x), y(other.y), z(other.z) {};
vec3::Vector3f(const float arr[3]): x(arr[0]), y(arr[1]), z(arr[2]) {};

vec3& vec3::operator = (const Vector3f& other) {
	
	if (this == &other) return *this;
		
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
		
	return *this;
}

vec3 vec3::operator + (const Vector3f& other) const {
	return {this->x + other.x, this->y + other.y, this->z + other.z};
};
vec3 vec3::operator + (const float& other) const {
	return {this->x + other, this->y + other, this->z + other};
};
vec3& vec3::operator += (const Vector3f& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	
	return *this;
};
vec3& vec3::operator += (const float& other) {
	this->x += other;
	this->y += other;
	this->z += other;
	
	return *this;
};

vec3 vec3::operator - () const {
	return {-this->x, -this->y, -this->z};
};
vec3 vec3::operator - (const Vector3f& other) const {
	return {this->x - other.x, this->y - other.y, this->z - other.z};
};
vec3 vec3::operator - (const float& other) const {
	return {this->x - other, this->y - other, this->z - other};
};
vec3& vec3::operator -= (const Vector3f& other) {
	
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	
	return *this;
};
vec3& vec3::operator -= (const float& other) {
	
	this->x -= other;
	this->y -= other;
	this->z -= other;
	
	return *this;
};


vec3 vec3::operator * (const Vector3f& other) const {
	return {this->x * other.x, this->y * other.y, this->z * other.z};
};
vec3 vec3::operator * (const float& other) const {
	return {this->x * other, this->y * other, this->z * other};
};
vec3& vec3::operator *= (const Vector3f& other) {
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	
	return *this;
};
vec3& vec3::operator *= (const float& other) {
	this->x *= other;
	this->y *= other;
	this->z *= other;
	
	return *this;
};


vec3 vec3::operator / (const Vector3f& other) const {
	return {this->x / other.x, this->y / other.y, this->z / other.z};
};
vec3 vec3::operator / (const float& other) const {
	return {this->x / other, this->y / other, this->z / other};
};
vec3& vec3::operator /= (const Vector3f& other) {
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	
	return *this;
};
vec3& vec3::operator /= (const float& other) {
	this->x /= other;
	this->y /= other;
	this->z /= other;
	
	return *this;
};

float& vec3::operator[](size_t index) {
	
	switch (index) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
	};
	throw std::out_of_range("vec3: index out of range");
};
const float& vec3::operator[](size_t index) const {
	switch (index) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			break;
	};
	throw std::out_of_range("vec3: index out of range");
};


vec2 vec3::xy() const {
	return {x, y};
}



vec4::Vector4f(const float& x, const float& y, const float& z, const float& w): x(x), y(y), z(z), w(w) {};
vec4::Vector4f(const Vector3f& other, const float& w): x(other.x), y(other.y), z(other.z), w(w) {};
vec4::Vector4f(const Vector4f& other): x(other.x), y(other.y), z(other.z), w(other.w) {};
vec4::Vector4f(const float arr[2]): x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]) {};

vec4& vec4::operator = (const Vector4f& other) {
	
	if (this == &other) return *this;
		
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
	
	return *this;
}

vec4 vec4::operator + (const Vector4f& other) const {
	return {this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w};
};
vec4 vec4::operator + (const float& other) const {
	return {this->x + other, this->y + other, this->z + other, this->w + other};
};
vec4& vec4::operator += (const Vector4f& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
	
	return *this;
};
vec4& vec4::operator += (const float& other) {
	this->x += other;
	this->y += other;
	this->z += other;
	this->w += other;
	
	return *this;
};

vec4 vec4::operator - () const {
	return {-this->x, -this->y, -this->z, -this->w};
};
vec4 vec4::operator - (const Vector4f& other) const {
	return {this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w};
};
vec4 vec4::operator - (const float& other) const {
	return {this->x - other, this->y - other, this->z - other, this->w - other};
};
vec4& vec4::operator -= (const Vector4f& other) {
	
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;
	
	return *this;
};
vec4& vec4::operator -= (const float& other) {
	
	this->x -= other;
	this->y -= other;
	this->z -= other;
	this->w -= other;
	
	return *this;
};


vec4 vec4::operator * (const Vector4f& other) const {
	return {this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w};
};
vec4 vec4::operator * (const float& other) const {
	return {this->x * other, this->y * other, this->z * other, this->w * other};
};
vec4& vec4::operator *= (const Vector4f& other) {
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	this->w *= other.w;
	
	return *this;
};
vec4& vec4::operator *= (const float& other) {
	this->x *= other;
	this->y *= other;
	this->z *= other;
	this->w *= other;
	
	return *this;
};


vec4 vec4::operator / (const Vector4f& other) const {
	return {this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w};
};
vec4 vec4::operator / (const float& other) const {
	return {this->x / other, this->y / other, this->z / other, this->w / other};
};
vec4& vec4::operator /= (const Vector4f& other) {
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	this->w /= other.w;
	
	return *this;
};
vec4& vec4::operator /= (const float& other) {
	this->x /= other;
	this->y /= other;
	this->z /= other;
//	this->w /= other;
	
	return *this;
};

float& vec4::operator[](size_t index) {
	
	switch (index) {
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		case 3:
			return w;
			break;
		default:
			break;
	};
	throw std::out_of_range("vec4: index out of range");
};
const float& vec4::operator[](size_t index) const {
	switch (index) {
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		case 3:
			return w;
			break;
		default:
			break;
	};
	throw std::out_of_range("vec4: index out of range");
};


vec3 vec4::xyz() const {
	return {x, y, z};
}
