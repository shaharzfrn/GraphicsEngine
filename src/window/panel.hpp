//
//  panel.hpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//

#ifndef panel_hpp
#define panel_hpp

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aui/aui.h>

#include <stdio.h>

#include "application.hpp"

class Panel : public wxPanel {
public:
	Panel(wxFrame* frame);
		
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);
	void Update();
	
	void OnMouseMove(wxMouseEvent &event);
	
	void OnKeyPress(wxKeyEvent &event);
	void OnKeyRelese(wxKeyEvent &event);
};


#endif /* panel_hpp */
