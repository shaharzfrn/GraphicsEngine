//
//  bitmap_utils.cpp
//  CGApp
//
//  Created by Shahar Zafran on 16/01/2023.
//

#include "bitmap_utils.hpp"
#include <wx/dcmemory.h>




void CGL::SetButtonBackground(wxButton *button, const vec3& color, const std::string& title) {
	vec3 map_color = color * 255.0f;
	SetButtonBackground(button, wxColour(map_color.x, map_color.y, map_color.z), title);
}
void CGL::SetButtonBackground(wxButton *button, const wxColour& color, const std::string& title) {
	
	wxSize size = button->GetSize();
	button->SetBitmapLabel(CreateColorBitmap(size.GetWidth() - 8, size.GetHeight() - 4, color, title));
}




wxBitmap CGL::CreateColorBitmap(const int& width, const int& height, const wxColour& color, std::string title) {
	
	wxBitmap bitmap(width, height);
	wxMemoryDC dc;
	
	wxColour text_color;
	int text_intensity = (int) (color.GetRed() * 0.3 + color.GetGreen() * 0.6 + color.GetBlue() * 0.1);
	
	if (text_intensity > 128)
		text_color.Set(0, 0, 0);
	else
		text_color.Set(255, 255, 255);
	
	dc.SelectObject(bitmap);
	dc.SetBackground(wxBrush(color));
	dc.SetTextForeground(text_color);
	dc.Clear();
	
//	dc.SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	wxSize text_size = dc.GetTextExtent(title);
	
	dc.DrawText(title, (width - text_size.GetWidth()) / 2.0f, (height - text_size.GetHeight()) / 2.0f);
	
	dc.SelectObject(wxNullBitmap);
	
	return bitmap;
}

wxBitmap CGL::CreateColorBitmap(const int& width, const int& height, const vec3& color, std::string title) {
	vec3 map_color = color * 255.0f;
	return CreateColorBitmap(width, height, wxColour(map_color.x, map_color.y, map_color.z), title);
}
