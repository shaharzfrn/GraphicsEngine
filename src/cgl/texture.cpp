//
//  texture.cpp
//  CGApp
//
//  Created by Shahar Zafran on 06/01/2023.
//

#include "texture.hpp"
#include <memory>


//Texture::Texture(const int& width, const int& height, u_int8_t *data): width(width), height(height) {
//	texture = new u_int8_t[width * height * 4];
//	memcpy(texture, data, width * height * 4 * sizeof(u_int8_t));
//}

//Texture::Texture(const Buffer& buffer): width(buffer.width), height(buffer.height) {
//	texture = new u_int8_t[width * height * 4];
//	memcpy(texture, buffer.p_buffer, width * height * 4 * sizeof(u_int8_t));
//}

Texture::Texture(const Buffer* buffer): width(buffer->width), height(buffer->height), type_size(buffer->type_size) {
	texture = new u_int8_t[width * height * buffer->type_size];
	memcpy(texture, buffer->p_buffer, width * height * buffer->type_size);
}

Texture::~Texture() {
	if (texture != nullptr)
		delete[] texture;
	
	texture = nullptr;
}
