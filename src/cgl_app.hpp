//
//  cgl_app.hpp
//  CGApp
//
//  Created by Shahar Zafran on 02/01/2023.
//

#ifndef cgl_app_hpp
#define cgl_app_hpp

#include <stdio.h>

#include "application.hpp"
#include "cgl_environment.h"

class CGLApp : public Application {
	
public:
	
	virtual void OnInit();
	
	// Screen events
	virtual void OnRender();
	virtual void OnResize(const int& width, const int& height, const int& dpi);
	
	// Keyboard events
	virtual void OnKeyPress(const char& key, const bool& shift, const bool& ctlr);
	virtual void OnKeyRelese(const char& key, const bool& shift, const bool& ctlr);
	
	// Mouse events
	virtual void OnMouseMove(const float& px, const float& py, const bool& left, const bool& dragging);
	virtual void OnMouseScroll(const int& scroll);
	
	virtual void OnClose();
};

#endif /* cgl_app_hpp */
