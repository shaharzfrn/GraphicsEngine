//
//  vec.hpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#ifndef vec_hpp
#define vec_hpp

#include <stdio.h>
#include <stdexcept>

typedef struct Vector2f {
	
	float x;
	float y;
	
	Vector2f(const float& x=0, const float& y=0);
	Vector2f(const Vector2f& other);
	Vector2f(const float arr[2]);
	
	Vector2f& operator = (const Vector2f& other);

	Vector2f operator + (const Vector2f& other) const;
	Vector2f operator + (const float& other) const;
	Vector2f& operator += (const Vector2f& other);
	Vector2f& operator += (const float& other);
	friend Vector2f operator + (const float& left, const Vector2f& right) {
		return right + left;
	}
	
	Vector2f operator - () const;
	Vector2f operator - (const Vector2f& other) const;
	Vector2f operator - (const float& other) const;
	Vector2f& operator -= (const Vector2f& other);
	Vector2f& operator -= (const float& other);
	friend Vector2f operator - (const float& left, const Vector2f& right) {
		return -right + left;
	}

	
	Vector2f operator * (const Vector2f& other) const;
	Vector2f operator * (const float& other) const;
	Vector2f& operator *= (const Vector2f& other);
	Vector2f& operator *= (const float& other);
	friend Vector2f operator * (const float& left, const Vector2f& right) {
		return right * left;
	}
	
	
	Vector2f operator / (const Vector2f& other) const;
	Vector2f operator / (const float& other) const;
	Vector2f& operator /= (const Vector2f& other);
	Vector2f& operator /= (const float& other);
	friend Vector2f operator / (const float& left, const Vector2f& right) {
		return {left / right.x, left / right.y};
	}
	
	float& operator[](size_t index);
	const float& operator[](size_t index) const;
	
} vec2;
typedef struct Vector3f {
	float x;
	float y;
	float z;
	
	Vector3f(const float& x=0, const float& y=0, const float& z=0);
	Vector3f(const Vector3f& other);
	Vector3f(const float arr[3]);
	
	Vector3f& operator = (const Vector3f& other);
	
	Vector3f operator + (const Vector3f& other) const;
	Vector3f operator + (const float& other) const;
	Vector3f& operator += (const Vector3f& other);
	Vector3f& operator += (const float& other);
	friend Vector3f operator + (const float& left, const Vector3f& right) {
		return right + left;
	}
	
	Vector3f operator - () const;
	Vector3f operator - (const Vector3f& other) const;
	Vector3f operator - (const float& other) const;
	Vector3f& operator -= (const Vector3f& other);
	Vector3f& operator -= (const float& other);
	friend Vector3f operator - (const float& left, const Vector3f& right) {
		return -right + left;
	}

	
	Vector3f operator * (const Vector3f& other) const;
	Vector3f operator * (const float& other) const;
	Vector3f& operator *= (const Vector3f& other);
	Vector3f& operator *= (const float& other);
	friend Vector3f operator * (const float& left, const Vector3f& right) {
		return right * left;
	}
	
	
	Vector3f operator / (const Vector3f& other) const;
	Vector3f operator / (const float& other) const;
	Vector3f& operator /= (const Vector3f& other);
	Vector3f& operator /= (const float& other);
	friend Vector3f operator / (const float& left, const Vector3f& right) {
		return {left / right.x, left / right.y, left / right.z};
	}
	
	float& operator[](size_t index);
	const float& operator[](size_t index) const;
	
	vec2 xy() const;
} vec3;
typedef struct Vector4f {
	float x;
	float y;
	float z;
	float w;
	
	Vector4f(const float& x=0, const float& y=0, const float& z=0, const float& w=0);
	Vector4f(const Vector3f& other, const float& w);
	Vector4f(const Vector4f& other);
	Vector4f(const float arr[4]);
	
	Vector4f& operator = (const Vector4f& other);
	
	Vector4f operator + (const Vector4f& other) const;
	Vector4f operator + (const float& other) const;
	Vector4f& operator += (const Vector4f& other);
	Vector4f& operator += (const float& other);
	friend Vector4f operator + (const float& left, const Vector4f& right) {
		return right + left;
	}
	
	Vector4f operator - () const;
	Vector4f operator - (const Vector4f& other) const;
	Vector4f operator - (const float& other) const;
	Vector4f& operator -= (const Vector4f& other);
	Vector4f& operator -= (const float& other);
	friend Vector4f operator - (const float& left, const Vector4f& right) {
		return -right + left;
	}

	
	Vector4f operator * (const Vector4f& other) const;
	Vector4f operator * (const float& other) const;
	Vector4f& operator *= (const Vector4f& other);
	Vector4f& operator *= (const float& other);
	friend Vector4f operator * (const float& left, const Vector4f& right) {
		return right * left;
	}
	
	
	Vector4f operator / (const Vector4f& other) const;
	Vector4f operator / (const float& other) const;
	Vector4f& operator /= (const Vector4f& other);
	Vector4f& operator /= (const float& other);
	friend Vector4f operator / (const float& left, const Vector4f& right) {
		return {left / right.x, left / right.y, left / right.z, left / right.w};
	}
	
	float& operator[](size_t index);
	const float& operator[](size_t index) const;
	
	vec3 xyz() const;
	
} vec4;

#endif /* vec_hpp */
