//
//  cgl.h
//  CGApp
//
//  Created by Shahar Zafran on 27/12/2022.
//

#ifndef cgl_h
#define cgl_h


#include <vector>

#include "math.hpp"
#include "shader.hpp"
#include "buffer.hpp"
#include "texture.hpp"

using namespace std;

// Polygon modes
#define POINT 	0
#define LINE 	1
#define FILL 	2

// Draw modes
#define POINTS		1
#define LINES		2
#define LINE_STRIP	3
#define LINE_LOOP	4
#define TRIANGLES	5

// Buffers bits, can be use to enable, disable, and clear
#define COLOR_BUFFER	0b001
#define DEPTH_BUFFER 	0b010
#define STENCIL_BUFFER 	0b100

// Face culling
#define FRONT			0b01
#define BACK			0b10
#define FRONT_AND_BACK	0b11

// depth and stencil functions
#define ALWAYS		0
#define NEVER		1
#define EQUAL		2
#define NOTEQUAL	3
#define LESS		4
#define LEQUAL		5
#define GREATER		6
#define GEQUAL		7

// stencil operator
#define KEEP		0
#define ZERO		1
#define REPLACE		2
#define INCR		3
#define INCR_WRAP	4
#define DECR		5
#define DECR_WRAP	6

namespace CGL {

typedef struct Vertex {
	vec4 clip_space;
	vec4 screen_space;
	
	int clip_code;
	int edge_flag;
	
	float *vertex_out = nullptr;
} Vertex;

inline int width;
inline int height;

inline int display_width;
inline int display_height;

inline mat4 viewport;

inline float depth_range_near;
inline float depth_range_far;


inline float far = 50.0f;
inline float near = 0.5f;
inline float fov = 45.f;


inline bool depth_clamp;

// face culling settings
inline bool cull_face_enable;



/* ================================================================================= */
// context settings
/* ================================================================================= */

void InitContext(const int& width, const int& height);
void ResizeContext(const int& width, const int& height);
void DestroyContext();

void Viewport(const int& width, const int& height, const float& near=CGL::near, const float& far=CGL::far);

/* ================================================================================= */
// buffers settings
/* ================================================================================= */

// enable or disable buffer
void EnableBuffer(const int& buffer_mask);
void DisableBuffer(const int& buffer_mask);

// clear the buffer 'reset' them
void Clear(const int& buffer_mask); // then which buffer to clear with the default value of them
void ClearColor(const float& r, const float& g, const float& b, const float& a);
void ClearDepth(const float& d);
void ClearStencil(const float& d);

void StencilFunction(const u_int8_t& function, const u_int8_t& ref, const u_int8_t& mask);
void StencilOperator(const u_int8_t& sfail, const u_int8_t& dpfail, const u_int8_t& dppass);

void BindFrameBuffer(const size_t& mask, Buffer *buffer);

void GetFrameBuffer(const size_t& mask, Buffer **buffer);
void GetFrameBufferTexture(const size_t& mask, Texture **texture);


/* ================================================================================= */
// polygon mode and face culling
/* ================================================================================= */

// enable or disable cull face
void EnableCullFace();
void DisableCullFace();

/// Specify whether front- or back-facing facets can be culled.
/// - Parameter mode: Specifies whether front- or back-facing facets are candidates for culling.
void CullFace(const u_int8_t& mode);

// polygon mode
/// Select a polygon rasterization mode.
/// - Parameters:
///   - face_mode: Specifies the polygons that mode applies to.
///   - polygon_mode: Specifies how polygons will be rasterized. Accepted values are POINT , LINE , and FILL. The initial value is FILL for both FRONT and BACK
void PolygonMode(const u_int8_t& face_mode, const u_int8_t& polygon_mode);

void EnablePolygonOffset();
void DisablePolygonOffset();
void PolygonOffset(const float& factor, const float& units);


void EnableDepthTest();
void DisableDepthTest();


/* ================================================================================= */
// draw elements
/* ================================================================================= */

void GenerateShaderVertex(Vertex& vertex);

void InterpolationMode(const u_int8_t& mode);

void DrawElements(const u_int8_t& mode, const vector<Vertex>& vertices);
}










#endif /* cgl_h */
