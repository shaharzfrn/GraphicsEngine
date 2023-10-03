//
//  panel.cpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//

#include "panel.hpp"
#include "init.hpp"
#include "cgl.hpp"
#include "texture.hpp"


Panel::Panel(wxFrame* frame): wxPanel(frame) {
	auto refresh_func = std::bind(&Panel::Update, this);
	CGL::app->SetUpdateFunc(refresh_func);
		
	int width;
	int height;
	
	GetClientSize(&width, &height);
	CGL::InitContext(width, height);
	
	CGL::app->OnInit();
	
	Bind(wxEVT_PAINT, &Panel::OnPaint, this);
	Bind(wxEVT_SIZE, &Panel::OnSize, this);
	Bind(wxEVT_MOTION, &Panel::OnMouseMove, this);
	Bind(wxEVT_CHAR_HOOK, &Panel::OnKeyPress, this);
}

void Panel::OnPaint(wxPaintEvent &event) {
	
	CGL::app->OnRender();
	
	wxPaintDC paint_dc(this);
	
	Buffer *buffer;
	CGL::GetFrameBuffer(COLOR_BUFFER, &buffer);
	
	if (buffer != nullptr)
		paint_dc.DrawBitmap(((ColorBuffer*)buffer)->buffer, 0, 0);
	
	event.Skip();
}

void Panel::OnSize(wxSizeEvent &event) {
	CGL::ResizeContext(event.GetSize().GetWidth(), event.GetSize().GetHeight());
	CGL::app->OnResize(event.GetSize().GetWidth(), event.GetSize().GetHeight(), GetDPIScaleFactor());
}

void Panel::Update() {
	Refresh();
}


void Panel::OnMouseMove(wxMouseEvent &event) {
	wxPoint mouse_pos = wxGetMousePosition();
	mouse_pos = ScreenToClient(mouse_pos);
	CGL::app->OnMouseMove(mouse_pos.x, mouse_pos.y, event.LeftIsDown(), event.Dragging());
}

void Panel::OnKeyPress(wxKeyEvent &event) {
	char key_code = event.GetKeyCode();
	bool is_shift_down = event.ShiftDown();
	bool is_control_down = event.ControlDown();
	
	CGL::app->OnKeyPress(key_code, is_shift_down, is_control_down);
}

void Panel::OnKeyRelese(wxKeyEvent &event){}
