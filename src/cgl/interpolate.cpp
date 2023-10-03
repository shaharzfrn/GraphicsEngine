//
//  interpolate.cpp
//  CGApp
//
//  Created by Shahar Zafran on 02/01/2023.
//

#include "interpolate.hpp"


void Interpolate(const float* v1, const float* v2, float* out, const float& t, const size_t& size) {
	for(size_t i = 0; i < size; i++) {
		out[i] = v1[i] + (v2[i] - v1[i]) * t;
	}
}


void InterpolateFragment(const float* v1_out, const float* v2_out, float* output, const vec2& w, const size_t& size) {
	for (int i = 0; i < size; i++) {
		output[i] = v1_out[i] * w[0] + v2_out[i] * w[1];
	}
}
