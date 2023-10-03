//
//  window.cpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//

#include "window.hpp"
#include "init.hpp"

wxIMPLEMENT_APP(Window);

bool Window::OnInit() {
	
	wxSize size = wxGetDisplaySize();
	
	wxSizerFlags::DisableConsistencyChecks();
	
	InitApplication();
	
	Frame *main_frame = new Frame("CGApp", wxSize(size.x / 2.f, size.y / 2.f), wxPoint(size.x / 4.f, size.y / 4.f));
	main_frame->Show(true);
	
	return true;
}
