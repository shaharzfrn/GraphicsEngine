//
//  interpolate.hpp
//  CGApp
//
//  Created by Shahar Zafran on 02/01/2023.
//

#ifndef interpolate_hpp
#define interpolate_hpp

#include <stdio.h>
#include "math.hpp"

void Interpolate(const float* v1, const float* v2, float* out, const float& t, const size_t& size);


void InterpolateFragment(const float* v1_out, const float* v2_out, float* output, const vec2& w, const size_t& size);

#endif /* interpolate_hpp */
