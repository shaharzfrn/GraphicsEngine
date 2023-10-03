//
//  cgl_environment.h
//  CGApp
//
//  Created by Shahar Zafran on 02/01/2023.
//

#ifndef cgl_environment_h
#define cgl_environment_h

#include <wx/bitmap.h>

#include "math.hpp"


namespace CGL {
inline float NEAR = .1f;
inline float FAR = 250.f;

inline vec4 background_color;
inline wxBitmap *background_image = nullptr;

};


#endif /* cgl_environment_h */
