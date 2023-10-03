//
//  buffer.cpp
//  CGApp
//
//  Created by Shahar Zafran on 08/01/2023.
//

#include "buffer.hpp"

/*
Buffer::Buffer(const int& width, const int& height) {
	
	this->width = width;
	this->height = height;
	
	bitmap.CreateWithDIPSize(width, height, 2);
	
	if (buffer != nullptr) delete buffer;
	buffer = new wxMemoryDC(bitmap);
	
	if (data != nullptr) delete[] data;
	data = new T[width * height];
	
}
Buffer::~Buffer() {
	if (buffer != nullptr) delete buffer;
		buffer = nullptr;
}

void Buffer::Clear(const vec4 clear) {
	buffer->SetBackground(wxBrush(wxColour(clear.x, clear.y, clear.z, clear.w)));
	buffer->Clear();
	
	for (int i = 0; i  < width * height; i++) {
		data[i * 4 + 0] = clear.x;
		data[i * 4 + 1] = clear.y;
		data[i * 4 + 2] = clear.z;
		data[i * 4 + 3] = clear.w;
	}
}

void Buffer::Set(const int& x, const int& y, const vec4 color) {
	buffer->SetPen(wxColour(color.x, color.y, color.z, color.w));
	buffer->DrawPoint(x, y);
	
	int i = y * width + x * 4;
	data[i + 0] = color[0];
	data[i + 1] = color[1];
	data[i + 2] = color[2];
	data[i + 3] = color[3];
}
vec4 Buffer::Get(const int& x, const int& y) {
	int i = y * width + x * 4;
	return {data[i + 0], data[i + 1], data[i + 2], data[i + 3]};
}
*/




