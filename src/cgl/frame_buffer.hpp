//
//  frame_buffer.hpp
//  CGApp
//
//  Created by Shahar Zafran on 09/01/2023.
//

#ifndef frame_buffer_hpp
#define frame_buffer_hpp

#include <stdio.h>
#include <map>



namespace CGL {

inline const int COLOR_ATTACHMENT_0 = 0;
inline const int COLOR_ATTACHMENT_1 = 1;
inline const int COLOR_ATTACHMENT_2 = 2;
inline const int COLOR_ATTACHMENT_3 = 3;
inline const int COLOR_ATTACHMENT_4 = 4;
inline const int COLOR_ATTACHMENT_5 = 5;
inline const int COLOR_ATTACHMENT_6 = 6;

inline const int DEPTH_ATTACHMENT = 7;
inline const int STENCIL_ATTACHMENT = 8;

inline const int COLOR_COMPONENET = sizeof(u_int8_t) * 4;
inline const int DEPTH_COMPONENET = sizeof(float);




}



struct TextureBuffer {
	
};

class Texture {
	
	int width;
	int height;
	
	u_int8_t type;
	
	u_int8_t *p_data;
	
	
public:
	Texture(const int& width, const int& height, const u_int8_t& type);
	
	
	void Set(const int& x, const int& y, const u_int8_t* p_val) {
		
	}
	
	static Texture& Create(const int& width, const int& height, const u_int8_t& type);
	
};

// void c() {
// 	Texture t(128, 128, sizeof(float));
	
// 	float val = 123.0f;
// 	t.Set(0, 0, reinterpret_cast<u_int8_t *>(&val));
// }


// textures:
// ------------------------------------------------------
//
// color texture	: with 3/4 componenets with type u_int8_t
// depth texture	: with 1 componenet with type float
// stencil texture	: with 1 componenet with type u_int8_t
//
// ------------------------------------------------------
//
// all have Set values
// all have Get values -> return vec4 (duplicate the values if needed)


class Buffer {

	
	
	
};

class RenderBuffer : Buffer {
	
	
	
};


class Attachment {};


template<typename T>
class TextureAttachment : public Attachment {
	Texture *texture;
};


// color buffer
class RenderbufferAttachment : public Attachment {
	RenderBuffer *buffer;
};


class FrameBuffer {
	
	int width;
	int height;
	
	std::map<int, Attachment> attachments;
	
public:
	void BindTexture(Texture& texture);
	void BindRenderBuffer();
};





#endif /* frame_buffer_hpp */
