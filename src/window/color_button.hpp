//
//  color_button.hpp
//  CGApp
//
//  Created by Shahar Zafran on 16/01/2023.
//

#ifndef color_button_hpp
#define color_button_hpp

#include <wx/bmpbuttn.h>
#include <string>

#include "math.hpp"

class ColorButton : public wxBitmapButton {
	
	
public:
	
	ColorButton(wxWindow *parent, wxWindowID Id, const wxPoint& pos=wxDefaultPosition, const std::string &name = "button", const wxBitmap *bitmap = NULL, const wxSize &size = wxDefaultSize, long style = wxBU_AUTODRAW);
	
};


namespace CGL {



}

#endif /* color_button_hpp */
