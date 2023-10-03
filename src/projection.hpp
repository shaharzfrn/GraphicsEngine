//
//  projection.hpp
//  CGApp
//
//  Created by Shahar Zafran on 04/01/2023.
//

#ifndef projection_hpp
#define projection_hpp

#include <stdio.h>
#include "math.hpp"

namespace CGL {
const int PRESPECTIVE_PROJECTION = 0;
const int OTHOGRAPHIC_PROJECTION = 1;

inline int projection_type = OTHOGRAPHIC_PROJECTION;

mat4 GenerateProjectionMatrix(const vec3& position);
mat4 GenerateProjectionMatrix();

mat4 GenerateShadowProjection(const vec3& position);

};



#endif /* projection_hpp */
