//
//  texture.hpp
//  CGApp
//
//  Created by Shahar Zafran on 06/01/2023.
//

#ifndef texture_hpp
#define texture_hpp

#include <stdio.h>
#include <wx/bitmap.h>

#include <map>

#include "math.hpp"
#include "buffer.hpp"

class Texture {
	
	u_int8_t type_size;
	u_int8_t *texture;
	
	Texture(const int& width, const int& height, const u_int8_t type_size);
	
public:
	
	int width;
	int height;
	
	Texture(const Buffer* buffer);
	~Texture();
	
	
	Texture& operator = (const Texture& other) {
		if (&other == this)
			return *this;
		
		
		if (texture != nullptr) delete[] texture;
		
		width = other.width;
		height = other.height;
		type_size = other.type_size;
		
		texture = new u_int8_t[width * height * type_size];
		memcpy(texture, other.texture, width * height * type_size);
		
		return *this;
	}
	
	
//	virtual vec4 Get(const float& x, const float& y);
	
	template<typename T>
	T& Get(const int& x_coords, const int& y_coords) {
		int i = (y_coords * width + x_coords) * type_size;
		return *(reinterpret_cast<T*>(texture + i));
	}
	
	template<typename T>
	T& Get(const float& x, const float& y) {
		int x_coords = (1 + x) * width * 0.5;
		int y_coords = (1 + y) * height * 0.5;
		
		int i = (y_coords * width + x_coords) * type_size;
		return *(reinterpret_cast<T*>(texture + i));
	}
	
	template<typename T>
	T& Get(const vec2& coords) {
		return Get<T>(coords.x, coords.y);
	}
	
	bool InBounds(const vec2& coords) {
		return InBounds(coords.x, coords.y);
	}
	
	bool InBounds(const float& x, const float& y) {
		int x_coords = (1 + x) * width * 0.5;
		int y_coords = (1 + y) * height * 0.5;
		return InBounds(x_coords, y_coords);
	}
	bool InBounds(const int& x, const int& y) {
		bool x_bound = x >= 0 && x < width;
		bool y_bound = y >= 0 && y < height;

		return x_bound && y_bound;
	}
};

namespace CGL {
	inline std::map<std::string, Texture*> textures;
};

#endif /* texture_hpp */
