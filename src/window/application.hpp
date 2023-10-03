//
//  application.hpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//

#ifndef application_hpp
#define application_hpp

#include <stdio.h>
#include <functional>


class Application {
	std::function<void()> refresh;
	
public:
	
	
	virtual void OnInit() = 0;
	
	// Screen events
	virtual void OnRender() = 0;
	virtual void OnResize(const int& width, const int& height, const int& dpi) = 0;
	
	// Keyboard events
	virtual void OnKeyPress(const char& key, const bool& shift, const bool& ctlr) = 0;
	virtual void OnKeyRelese(const char& key, const bool& shift, const bool& ctlr) = 0;
	
	// Mouse events
	virtual void OnMouseMove(const float& px, const float& py, const bool& left, const bool& dragging) = 0;
	virtual void OnMouseScroll(const int& scroll) = 0;
	
	virtual void OnClose() = 0;
	
	// Function to be able to refresh the wxWindow that hold the app
	virtual void SetUpdateFunc(std::function<void()> refresh) final;
	virtual void Refresh() final;
};

namespace CGL {
inline Application *app;
}


#endif /* application_hpp */
