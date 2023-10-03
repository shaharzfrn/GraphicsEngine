//
//  bitmap_utils.hpp
//  CGApp
//
//  Created by Shahar Zafran on 16/01/2023.
//

#ifndef bitmap_utils_hpp
#define bitmap_utils_hpp

#include <stdio.h>

#include <wx/bmpbuttn.h>
#include <string>

#include "math.hpp"

namespace CGL {


void SetButtonBackground(wxButton *button, const vec3& color, const std::string& title);
void SetButtonBackground(wxButton *button, const wxColour& color, const std::string& title);



wxBitmap CreateColorBitmap(const int& width, const int& height, const vec3& color, std::string title="ColorBitmap");
wxBitmap CreateColorBitmap(const int& width, const int& height, const wxColour& color, std::string title="ColorBitmap");

};


#endif /* bitmap_utils_hpp */
