//
//  buffer.hpp
//  CGApp
//
//  Created by Shahar Zafran on 08/01/2023.
//

#ifndef buffer_hpp
#define buffer_hpp

#include <stdio.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>

#include "math.hpp"

class Buffer {
	
protected:
	int width;
	int height;
	
	u_int8_t type_size;
	u_int8_t *p_buffer = nullptr;
	u_int8_t *p_empty = nullptr;
	
	Buffer(const int& width, const int& height, const u_int8_t& type_size): width(width), height(height), type_size(type_size) {
		p_buffer = new u_int8_t[width * height * type_size];
		p_empty = new u_int8_t[type_size];
		
		memset(p_empty, 0, type_size);
	};
	
	virtual void Clear(const u_int8_t* clear) {
		for (int i = 0; i < width * height; i++) {
			memcpy(p_buffer + i * type_size, clear, type_size);
		}
	};
	
	virtual void Set(const int& x, const int& y, const u_int8_t* value) {
		
		if (x < 0 || x >= width || y < 0 || y >= height) {
			return;
		}
		
		int i = (y * width + x) * type_size;
		memcpy(p_buffer + i, value, type_size);
	};
	
	friend class Texture;
	
public:
	
	~Buffer() {
		if (p_buffer != nullptr) delete[] p_buffer;
		p_buffer = nullptr;
	};
	
	template<class T>
	void Clear(const T& clear) {
		Clear(reinterpret_cast<const u_int8_t *>(&clear));
	};
	
	template<class T>
	void Set(const int& x, const int& y, const T& value) {
		Set(x, y, reinterpret_cast<const u_int8_t *>(&value));
	};
	
	template<class T>
	T Get(const int& x, const int& y) {
		if (x < 0 || x >= width || y < 0 || y >= height) {
			return T(0);
		}
		
		int i = (y * width + x) * type_size;
		return *(reinterpret_cast<T*>(p_buffer + i));
	};
	
	template<class T>
	static Buffer* CreateBuffer(const int& width, const int& height) {
		return new Buffer(width, height, sizeof(T));
	}
};


class ColorBuffer : public Buffer {
	
	wxMemoryDC *p_bitmap;
	wxMemoryDC p_bitmap_b;
	
	ColorBuffer(const int& width, const int& height): Buffer(width, height, sizeof(vec4)) {
		buffer.CreateWithDIPSize(width, height, 2);
		p_bitmap_b.SelectObject(buffer);
	};

	virtual void Clear(const u_int8_t* clear) {
		
		Buffer::Clear(clear);
		
		const vec4 color = *(reinterpret_cast<const vec4*>(clear));
		
		p_bitmap_b.SetBackground(wxBrush(wxColour(color.x, color.y, color.z, color.w)));
		p_bitmap_b.Clear();
	};
	
	virtual void Set(const int& x, const int& y, const u_int8_t* value) {
		
		Buffer::Set(x, y, value);
		
		const vec4 color = *(reinterpret_cast<const vec4*>(value));
		
		p_bitmap_b.SetPen(wxColour(color.x, color.y, color.z, color.w));
		p_bitmap_b.DrawPoint(x, y);
		
	};

public:
	wxBitmap buffer;
	~ColorBuffer() {
		if (p_bitmap != nullptr) delete p_bitmap;
		p_bitmap = nullptr;
	}
	
	void SetBackgroundImage(const wxBitmap* background) {
		p_bitmap_b.DrawBitmap(*background, 0, 0);
	}
	
	
	static ColorBuffer* CreateColorBuffer(const int& width, const int& height) {
		return new ColorBuffer(width, height);
	}
};






#endif /* buffer_hpp */
