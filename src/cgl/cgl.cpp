//
//  draw.cpp
//  CGApp
//
//  Created by Shahar Zafran on 01/01/2023.
//



#include <stdio.h>

#include "cgl.hpp"
#include "math.hpp"

#include "clip.hpp"
#include "interpolate.hpp"

#include "buffer.hpp"

#include "cgl_shaders.hpp"
#include "projection.hpp"


using namespace CGL;

typedef void (*DrawTriangleFunc)(Vertex&, Vertex&, Vertex&);

static bool StencilTest(const u_int8_t& dest);
static u_int8_t StencilOperator(const bool& stencil, const bool& depth, const u_int8_t& dest);

/* ================================================================================= */
// inner clip functions
/* ================================================================================= */
static inline int ClipCode(const vec4& v) {
	//	add 1E-5 to the w component (EPSILON)
	
	float w = v.w * (1.0 + 1E-5);
	return	(((v.z < -w) | ((v.z > w) << 1)) & (!CGL::depth_clamp | !CGL::depth_clamp << 1)) |
			((v.x < -w) << 2) |
			((v.x >  w) << 3) |
			((v.y < -w) << 4) |
			((v.y >  w) << 5);
	
//	return	(((v.z < -1) | ((v.z > 1) << 1)) & (CGL::depth_clamp | CGL::depth_clamp << 1)) |s
//			((v.x < -1) << 2) |
//			((v.x >  1) << 3) |
//			((v.y < -1) << 4) |
//			((v.y >  1) << 5);
}

/* ================================================================================= */
// inner clip functions
/* ================================================================================= */
static bool IsFrontFacing(const vec4& v1, const vec4& v2, const vec4& v3) {
	vec3 a = (v2 - v1).xyz();
	vec3 b = (v3 - v1).xyz();
	vec3 normal = Cross(a, b);

	return -(Dot(v1.xyz(), normal) * (CGL::projection_type == OTHOGRAPHIC_PROJECTION ? -1 : 1)) >= 0;
	
//	return -Dot(v1.xyz(), normal) >= 0;
}

/* ================================================================================= */
// inner Draw function
/* ================================================================================= */

void DrawPixel(const vec4& color, const int& x, const int& y, const float& z);

void DrawPoint(const Vertex& vertex);

void DrawLineClip(Vertex& v1, Vertex& v2, int clip_bit=0);
void DrawLineShader(const vec4& v1, const vec4& v2, float* v1_out, float* v2_out, const bool& reflect=false, const bool& swap=false);


void DrawTriangle(Vertex& v1, Vertex& v2, Vertex& v3);
void DrawTriangleClip(Vertex& v1, Vertex& v2, Vertex& v3, int clip_bit=0);
void DrawTriangleFit(Vertex& v1, Vertex& v2, Vertex& v3);

void DrawTrianglePoint(Vertex& v1, Vertex& v2, Vertex& v3);
void DrawTriangleLine(Vertex& v1, Vertex& v2, Vertex& v3);
void DrawTriangleFill(Vertex& v1, Vertex& v2, Vertex& v3);


namespace CGL {

/* ================================================================================= */
// context settings
/* ================================================================================= */
//FrameBuffer color_buffer;
//FrameBuffer depth_buffer;
//FrameBuffer stencil_buffer;

Buffer *color_buffer;
Buffer *depth_buffer;
Buffer *stencil_buffer;

u_int8_t defaults_buffers = 0b000;
u_int8_t enable_buffers = 0b000;

vec4 clear_color;
float clear_depth;
float clear_stencil;

u_int8_t culling_mode;

u_int8_t back_polygon_mode;
u_int8_t front_polygon_mode;

u_int8_t stencil_func;
u_int8_t stencil_ref;
u_int8_t stencil_mask;

u_int8_t stencil_sfail;
u_int8_t stencil_dpfail;
u_int8_t stencil_dppass;

DrawTriangleFunc triangle_front;
DrawTriangleFunc triangle_back;

u_int8_t interpolation_mode;


bool enable_depth_test;

bool polygon_offset_enabled;
inline float polygon_offset_factor;
inline float polygon_offset_units;

void InitContext(const int& width, const int& height) {

	CGL::display_width = width;
	CGL::display_height = height;

	CGL::width = width;
	CGL::height = height;
	
	viewport = CGL::GenerateViewPortMatrix(0, 0, width, height, CGL::near, CGL::far);
	
	clear_color = {0, 0, 0, 1};
	clear_depth = 1;
	clear_stencil = 0;
	
	CGL::color_buffer = ColorBuffer::CreateColorBuffer(width, height);
	CGL::depth_buffer = Buffer::CreateBuffer<float>(width, height);
	CGL::stencil_buffer = Buffer::CreateBuffer<u_int8_t>(width, height);
	
	defaults_buffers = COLOR_BUFFER | DEPTH_BUFFER | STENCIL_BUFFER;
	
	cull_face_enable = false;

	culling_mode = BACK;

	back_polygon_mode = FILL;
	front_polygon_mode = FILL;

	triangle_front = DrawTriangleFill;
	triangle_back = DrawTriangleFill;
	
	polygon_offset_factor = 1.0f;
	polygon_offset_units = 0.0f;
	
}

void ResizeContext(const int& width, const int& height) {
	CGL::display_width = width;
	CGL::display_height = height;
	
	if (defaults_buffers & COLOR_BUFFER) {
		delete CGL::color_buffer;
		CGL::color_buffer = ColorBuffer::CreateColorBuffer(width, height);
	}
	
	if (defaults_buffers & DEPTH_BUFFER) {
		delete CGL::depth_buffer;
		CGL::depth_buffer = Buffer::CreateBuffer<float>(width, height);
	}
	
	if (defaults_buffers & STENCIL_BUFFER) {
		delete CGL::stencil_buffer;
		CGL::stencil_buffer = Buffer::CreateBuffer<u_int8_t>(width, height);
	}
}

void Viewport(const int& width, const int& height, const float& near, const float& far) {
	CGL::width = width;
	CGL::height = height;
	CGL::near = near;
	CGL::far = far;
	
	viewport = CGL::GenerateViewPortMatrix(0, 0, width, height, CGL::near, CGL::far);
}

void DestroyContext() {
//	delete color_buffer;
//	delete depth_buffer;
//	delete stencil_buffer;
}

/* ================================================================================= */
// buffers settings
/* ================================================================================= */

// enable or disable buffer
void EnableBuffer(const int& buffer_mask) {
	CGL::enable_buffers |= buffer_mask;
}
void DisableBuffer(const int& buffer_mask) {
	CGL::enable_buffers &= ~buffer_mask;
}

// clear the buffer, 'reset' them
void Clear(const int& buffer_mask){ // then which buffer to clear with the default value of them
	
	if (buffer_mask & COLOR_BUFFER && color_buffer != nullptr) {
		CGL::color_buffer->Clear<vec4>(CGL::clear_color * 255);
	}
	
	if (buffer_mask & DEPTH_BUFFER && depth_buffer != nullptr) {
		CGL::depth_buffer->Clear<float>(CGL::clear_depth);
	}
	
	if (buffer_mask & STENCIL_BUFFER && stencil_buffer != nullptr) {
		CGL::stencil_buffer->Clear<u_int8_t>(CGL::clear_stencil);
//		CGL::stencil_buffer->Clear(vec4(CGL::clear_stencil, CGL::clear_stencil, CGL::clear_stencil, CGL::clear_stencil) * 255);
	}
}
void ClearColor(const float& r, const float& g, const float& b, const float& a) {
	CGL::clear_color = {r, g, b, a};
}
void ClearDepth(const float& d) {
	CGL::clear_depth = d;
}
void ClearStencil(const float& d) {
	CGL::clear_stencil = d;
}

void StencilFunction(const u_int8_t& function, const u_int8_t& ref, const u_int8_t& mask) {
	
	CGL::stencil_func = function;
	CGL::stencil_ref = ref;
	CGL::stencil_mask = mask;
}
void StencilOperator(const u_int8_t& sfail, const u_int8_t& dpfail, const u_int8_t& dppass) {
	
	CGL::stencil_sfail = sfail;
	CGL::stencil_dpfail = dpfail;
	CGL::stencil_dppass = dppass;
}


void BindFrameBuffer(const size_t& mask, Buffer *buffer) {
	if (buffer == nullptr) {
		CGL::defaults_buffers |= mask;
	} else {
		CGL::defaults_buffers &= ~mask;
		
	}
	
	if (mask & COLOR_BUFFER) {
		if (buffer == nullptr)
			CGL::color_buffer = ColorBuffer::CreateColorBuffer(CGL::display_width, CGL::display_width);
		else
			CGL::color_buffer = buffer;
		
	} else if (mask & DEPTH_BUFFER) {
		if (buffer == nullptr)
			CGL::depth_buffer = Buffer::CreateBuffer<float>(CGL::display_width, CGL::display_width);
		else
			CGL::depth_buffer = buffer;
		
	} else if (mask & STENCIL_BUFFER) {
		if (buffer == nullptr)
			CGL::stencil_buffer = Buffer::CreateBuffer<u_int8_t>(CGL::display_width, CGL::display_width);
		else
			CGL::stencil_buffer = buffer;
	}
}

void GetFrameBuffer(const size_t& mask, Buffer **buffer) {
	if (mask & COLOR_BUFFER) {
		*buffer = CGL::color_buffer;
	} else if (mask & DEPTH_BUFFER) {
		*buffer = CGL::depth_buffer;
	} else if (mask & STENCIL_BUFFER) {
		*buffer = CGL::stencil_buffer;
	}
}
void GetFrameBufferTexture(const size_t& mask, Texture **texture) {
	Buffer *buffer;
	GetFrameBuffer(mask, &buffer);

	*texture = new Texture(buffer);
}

/* ================================================================================= */
// polygon mode and face culling
/* ================================================================================= */

// enable or disable cull face
void EnableCullFace() {
	CGL::cull_face_enable = true;
}
void DisableCullFace() {
	CGL::cull_face_enable = false;
}

/// Specify whether front- or back-facing facets can be culled.
/// - Parameter mode: Specifies whether front- or back-facing facets are candidates for culling.
void CullFace(const u_int8_t& mode) {
	CGL::culling_mode = mode;
}

// polygon mode
/// Select a polygon rasterization mode.
/// - Parameters:
///   - face_mode: Specifies the polygons that mode applies to.
///   - polygon_mode: Specifies how polygons will be rasterized. Accepted values are POINT , LINE , and FILL. The initial value is FILL for both FRONT and BACK
void PolygonMode(const u_int8_t& face_mode, const u_int8_t& polygon_mode) {
	if ((polygon_mode & LINE) == LINE) {
		if ((face_mode & BACK) == BACK) {
			CGL::triangle_back = DrawTriangleLine;
			CGL::back_polygon_mode = polygon_mode;
		}
		
		if ((face_mode & FRONT) == FRONT) {
			CGL::triangle_front = DrawTriangleLine;
			CGL::front_polygon_mode = polygon_mode;
		}
		
	} else if (polygon_mode == FILL) {
		if ((face_mode & BACK) == BACK) {
			CGL::triangle_back = DrawTriangleFill;
			CGL::back_polygon_mode = polygon_mode;
		}
		
		if ((face_mode & FRONT) == FRONT) {
			CGL::triangle_front = DrawTriangleFill;
			CGL::front_polygon_mode = polygon_mode;
		}
	} else if ((polygon_mode & POINT) == POINT) {
		if ((face_mode & BACK) == BACK) {
			CGL::triangle_back = DrawTrianglePoint;
			CGL::back_polygon_mode = polygon_mode;
		}
		
		if ((face_mode & FRONT) == FRONT) {
			CGL::triangle_front = DrawTrianglePoint;
			CGL::front_polygon_mode = polygon_mode;
		}
	};
}


void EnablePolygonOffset() {
	polygon_offset_enabled = true;
}
void DisablePolygonOffset() {
	polygon_offset_enabled = false;
}
void PolygonOffset(const float& factor, const float& units) {
	CGL::polygon_offset_factor = factor;
	CGL::polygon_offset_units = units;
}



void EnableDepthTest() { enable_depth_test = true; }
void DisableDepthTest() { enable_depth_test = false; }

/* ================================================================================= */
// draw elements
/* ================================================================================= */

void GenerateShaderVertex(Vertex& vertex) {
	vertex.clip_space = CGL::shader->out_position;
	vertex.clip_code = ClipCode(vertex.clip_space);
	vertex.edge_flag = true;
	vertex.vertex_out = new float[CGL::shader->GetFragmentShaderInputSize()];
	CGL::shader->GetVertexOutput(vertex.vertex_out);
}

void InterpolationMode(const u_int8_t& mode) {
	
}

void DrawElements(const u_int8_t& mode, const vector<Vertex>& const_vertices) {
	
	vector<Vertex> vertices;
	std::copy(const_vertices.begin(), const_vertices.end(), back_inserter(vertices));
	
	if (mode == POINTS) {
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices[i].clip_code != 0)
				continue;
			
			vertices[i].screen_space = vertices[i].clip_space / vertices[i].clip_space.w;
			vertices[i].screen_space = viewport * vertices[i].screen_space;
			
			DrawPoint(vertices[i]);
		}
	} else if(mode == LINES) {
		for (int i = 0; i < vertices.size() - 1; i += 2) {
			DrawLineClip(vertices[i], vertices[i + 1]);
		}
	} else if (mode == LINE_STRIP) {
		for (int i = 0; i < vertices.size() - 1; i++) {
			DrawLineClip(vertices[i], vertices[i + 1]);
		}
	} else if (mode == LINE_LOOP) {
		for (int i = 0; i < vertices.size(); i++) {
			DrawLineClip(vertices[i], vertices[(i + 1) % vertices.size()]);
		}
	} else if (mode == TRIANGLES) {
		for (int i = 0; i < vertices.size() - 2; i += 3) {
			DrawTriangle(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
		}
	}
}
}


static bool StencilTest(const u_int8_t& dest) {
	u_int8_t ref = CGL::stencil_ref;
	u_int8_t mask = CGL::stencil_mask;
	
	switch (CGL::stencil_func) {
		case NEVER: 	return false;
		case LESS: 		return (ref & mask) <  (dest & mask);
		case LEQUAL: 	return (ref & mask) <= (dest & mask);
		case GREATER: 	return (ref & mask) >  (dest & mask);
		case GEQUAL: 	return (ref & mask) >= (dest & mask);
		case EQUAL: 	return (ref & mask) == (dest & mask);
		case NOTEQUAL: 	return (ref & mask) == (dest & mask);
		case ALWAYS:	return true;
		default:
			break;
	}
	
	return false;
}

static u_int8_t StencilOperator(const bool& stencil, const bool& depth, const u_int8_t& dest) {
	
	u_int8_t op = !stencil ? CGL::stencil_sfail : (depth ? CGL::stencil_dpfail : CGL::stencil_dppass);
	
	switch (op) {
		case KEEP: return dest;
		case ZERO: return 0;
		case REPLACE: return CGL::stencil_ref;
		case INCR: return dest + 1;
		case INCR_WRAP: return (dest < 255) ? dest + 1 : dest;
		case DECR: return dest - 1;
		case DECR_WRAP:	return (dest > 0) ? dest - 1 : dest;
		default:
			break;
	}
	
	return dest;
}


void DrawPixel(const vec4& color, const int& x, const int& y, const float& z) {
	
	u_int8_t stencil_dest = CGL::stencil_buffer->Get<u_int8_t>(x, y);
	bool stencil_buffer_enabled = CGL::enable_buffers & STENCIL_BUFFER;
	if (stencil_buffer_enabled && !StencilTest(stencil_dest)) {
		stencil_dest = StencilOperator(false, true, stencil_dest);
		CGL::stencil_buffer->Set<u_int8_t>(x, y, stencil_dest);
		
		return;
	}
	
	if (CGL::enable_buffers & DEPTH_BUFFER || enable_depth_test) {
		float dest_depth = CGL::depth_buffer->Get<float>(x, y);
		
		float offset_z = z;
		if (polygon_offset_enabled)
			offset_z = (z * polygon_offset_factor + 0.005f * polygon_offset_units);
		
		bool depth_result = (dest_depth >= offset_z);
		
		if (stencil_buffer_enabled) {
			stencil_dest = StencilOperator(true, depth_result, stencil_dest);
			CGL::stencil_buffer->Set<u_int8_t>(x, y, stencil_dest);
		}
		
		if (!depth_result) {
			return;
		}
		
		if (CGL::enable_buffers & DEPTH_BUFFER)
			CGL::depth_buffer->Set(x, y, offset_z);
		
	}else if (stencil_buffer_enabled) {
		stencil_dest = StencilOperator(true, true, stencil_dest);
  		CGL::stencil_buffer->Set<u_int8_t>(x, y, stencil_dest);
  	}
	
	if (CGL::enable_buffers & COLOR_BUFFER) {
		CGL::color_buffer->Set<vec4>(x, y, color * 255);
	}
}

void DrawPoint(const Vertex& vertex) {
	
	// clip need to be done before
	vec3 point = (vertex.screen_space).xyz();
	
	float x = point.x + 0.5f;
	float y = point.y + 0.5f;
	
	float p_size = 1;
	float half_p_size = p_size / 2.f;
	float origin = -1.0f; // UPPER_LEFT
	
	// if the point size(radius) is 1 or less and the point is outside the screen there is not
	// point to draw it
	if (p_size <= 1) {
		if (x < 0 || y < 0)
			return;
		
		if (x >= CGL::width || y >= CGL::height)
			return;
	}
	
	for (float i = y - half_p_size; i < y + half_p_size; ++i) {
		if (i < 0 || i >= CGL::height)
			continue;
		
		for (float j = x - half_p_size; j < x + half_p_size; ++j) {
			if (j < 0 || j >= CGL::width)
				continue;
			
//			if (Distance(point, {x, y}) > half_p_size)
//				continue;
			
			CGL::shader->point_coord.x = 0.5f + ((int)j + 0.5f - point.x) / p_size;
			CGL::shader->point_coord.y = 0.5f + origin * ((int)i + 0.5f - point.y) / p_size;
			CGL::shader->frag_coords = {j, i, point.z, 1/vertex.screen_space.w};
			CGL::shader->discard = false;
			CGL::shader->frag_depth = point.z;
			
			// call fragment
			CGL::shader->SetFragmentInput(vertex.vertex_out);
			CGL::shader->FragmentShader();
			
			if (!CGL::shader->discard) {
				DrawPixel(CGL::shader->frag_color, j, i, CGL::shader->frag_depth);
			}
		}
	}
}


void DrawLineClip(Vertex& v1, Vertex& v2, int clip_bit) {
	
	if ((v1.clip_code & v2.clip_code) != 0) { // the line is completly outside of the screen
		return;
	}
	
	int c_or = v1.clip_code | v2.clip_code;
	if (c_or == 0) {
		
		// the line is completly inside the screen
		vec4 p1 = v1.clip_space / v1.clip_space.w;
		vec4 p2 = v2.clip_space / v2.clip_space.w;
		
		p1 = CGL::viewport * p1;
		p2 = CGL::viewport * p2;
		
		DrawLineShader(p1, p2, v1.vertex_out, v2.vertex_out);
		
	} else {
		Vertex *q[2];
		
		Vertex *ver1;
		Vertex *ver2;
		
		Vertex tmp1;
		tmp1.vertex_out = new float[CGL::shader->GetFragmentShaderInputSize()];
		/* find the next direction to clip */
		while (clip_bit < 6 && (c_or & (1 << clip_bit)) == 0)  {
			++clip_bit;
		}
		
		int clip_mask = 1 << clip_bit;
		
		if (v1.clip_code & clip_mask) {
			ver1 = &v1;
			ver2 = &v2;
		} else {
			ver1 = &v2;
			ver2 = &v1;
		}
		
		float tt = clip_proc[clip_bit](ver1->clip_space, ver2->clip_space, tmp1.clip_space);
		CGL::shader->InterpolateFragment(ver1->vertex_out, ver2->vertex_out, tt, tmp1.vertex_out);
		tmp1.clip_code = ClipCode(tmp1.clip_space);
		
		DrawLineClip(tmp1, *ver2, clip_bit+1);
		
		delete[] tmp1.vertex_out;
	}
}
void DrawLineShader(const vec4& v1, const vec4& v2, float* v1_out, float* v2_out, const bool& reflect, const bool& swap) {
	
	if(v1.x > v2.x) {
		DrawLineShader(v2, v1, v2_out, v1_out, reflect, swap);
		return;
	}
	
	if(v1.y > v2.y) {
		vec4 reflect_v2 { v2 };
		reflect_v2.y = 2 * v1.y - v2.y;
		
		DrawLineShader(v1, reflect_v2, v1_out, v2_out, true, swap);
		return;
	}
	
	int x = v1.x;
	int y = v1.y;
	
	int delta_x = v2.x - v1.x;
	int delta_y = v2.y - v1.y;
	
	if((!delta_x && delta_y) || (delta_x && ((delta_y / (float) delta_x) > 1.0f))) {
		
		vec4 swap_v1 {v1.y, v1.x, v1.z, v1.w};
		vec4 swap_v2 {v2.y, v2.x, v2.z, v2.w};
		
		DrawLineShader(swap_v1, swap_v2, v1_out, v2_out, reflect, true);
		return;
	}
	
	int d = 2 * delta_y - delta_x;
	
	int delta_p = 2 * delta_y;
	int delta_n = 2 * (delta_y - delta_x);
	
	int *point_x = swap ? &y : &x;
	int *point_y = swap ? &x : &y;
	
	int plan = (reflect && swap) ? x : y;
	
	float *fragment_in = new float[CGL::shader->GetFragmentShaderInputSize()];
	
	const float distance = Distance(v1.xyz().xy(), v2.xyz().xy());
	if (distance <= 1e-4) {
		return;
	}
	
	const float denom = 1.f / distance;
	
	vec2 v1_point {v1.x, v1.y};
	vec2 v2_point {v2.x, v2.y};
	
	do {
		vec2 point { *point_x, reflect ? (2 * plan - *point_y) : (*point_y)};
		
		float barycentric_x = Distance(point, v1_point);
		float barycentric_y = distance - barycentric_x;
		
		vec2 barycentric = vec2(barycentric_x, barycentric_y) * denom;
		
		float z = v1.z * barycentric[0] + v2.z * barycentric[1];
		float w = v1.w * barycentric[0] + v2.w * barycentric[1];

		vec2 perspective = 1 / w * barycentric * vec2(v1.w, v2.w);
		
		CGL::shader->InterpolateFragment(v1_out, v2_out, perspective, fragment_in);
		
		CGL::shader->frag_coords = {point.x, point.y, z, 1/w};
		CGL::shader->discard = false;
		CGL::shader->frag_depth = z;
	
		CGL::shader->SetFragmentInput(fragment_in);
		CGL::shader->FragmentShader();
		
		if (!CGL::shader->discard)
			DrawPixel(CGL::shader->frag_color, point.x, point.y, CGL::shader->frag_depth);
		
		if (d < 0) {
			d += delta_p;
		} else {
			d += delta_n;
			y++;
		}
		
		x++;
	} while(x <= v2.x);
	
	delete[] fragment_in;
}

void DrawTriangle(Vertex& v1, Vertex& v2, Vertex& v3) {
	
	int clip = v1.clip_code & v2.clip_code & v3.clip_code;
	if (clip != 0) {
		return;
	}

	clip = v1.clip_code | v2.clip_code | v3.clip_code;
	if (clip == 0) {
		DrawTriangleFit(v1, v2, v3);
	} else {
		DrawTriangleClip(v1, v2, v3);
	}
}
void DrawTriangleClip(Vertex& v1, Vertex& v2, Vertex& v3, int clip_bit) {
	
	Vertex tmp1, tmp2;
	Vertex *verts[3];
	
	int c_or = v1.clip_code | v2.clip_code | v3.clip_code;
	if (c_or == 0) { /* the triangle is completely inside */
		DrawTriangleFit(v1, v2, v3);
	} else {
		
		int c_and = v1.clip_code & v2.clip_code & v3.clip_code;
		if (c_and != 0) { /* the triangle is completely outside */
			return;
		}
		
		/* find the next direction to clip */
		while (clip_bit < 6 && (c_or & (1 << clip_bit)) == 0)  {
			++clip_bit;
		}
		
		if (clip_bit == 6) { return; }
		
		int clip_mask = 1 << clip_bit;
		int c_ex_or = (v1.clip_code ^ v2.clip_code ^ v3.clip_code) & clip_mask;
		
		tmp1.vertex_out = new float[CGL::shader->GetFragmentShaderInputSize()];
		tmp2.vertex_out = new float[CGL::shader->GetFragmentShaderInputSize()];
		
		if (c_ex_or)  {
			
			/* one point outside */
				
			if (v1.clip_code & clip_mask) {
				/* vertex 1 is outside */
				verts[0] = &v1;
				verts[1] = &v2;
				verts[2] = &v3;
				
			} else if (v2.clip_code & clip_mask) {
				/* vertex 2 is outside */
				verts[0] = &v2;
				verts[1] = &v3;
				verts[2] = &v1;
				
			} else {
				/* vertex 3 is outside */
				verts[0] = &v3;
				verts[1] = &v1;
				verts[2] = &v2;
			}
			
			float t1 = clip_proc[clip_bit](verts[0]->clip_space, verts[1]->clip_space, tmp1.clip_space);
			CGL::shader->InterpolateFragment(verts[0]->vertex_out, verts[1]->vertex_out, t1, tmp1.vertex_out);
			tmp1.clip_code = ClipCode(tmp1.clip_space);
			
			float t2 = clip_proc[clip_bit](verts[0]->clip_space, verts[2]->clip_space, tmp2.clip_space);
			CGL::shader->InterpolateFragment(verts[0]->vertex_out, verts[2]->vertex_out, t2, tmp2.vertex_out);
			tmp2.clip_code = ClipCode(tmp2.clip_space);
			
			DrawTriangleClip(tmp1, *verts[1], *verts[2], clip_bit + 1);
			DrawTriangleClip(tmp2, tmp1, *verts[2], clip_bit + 1);
			
		} else { /* two points outside */
			
			if ((v1.clip_code & clip_mask) == 0) {
				verts[0] = &v1;
				verts[1] = &v2;
				verts[2] = &v3;
			} else if ((v2.clip_code & clip_mask) == 0) {
				verts[0] = &v2;
				verts[1] = &v3;
				verts[2] = &v1;
			} else {
				verts[0] = &v3;
				verts[1] = &v1;
				verts[2] = &v2;
			}
			
			float t1 = clip_proc[clip_bit](verts[0]->clip_space, verts[1]->clip_space, tmp1.clip_space);
			CGL::shader->InterpolateFragment(verts[0]->vertex_out, verts[1]->vertex_out, t1, tmp1.vertex_out);
			tmp1.clip_code = ClipCode(tmp1.clip_space);
			
			float t2 = clip_proc[clip_bit](verts[0]->clip_space, verts[2]->clip_space, tmp2.clip_space);
			CGL::shader->InterpolateFragment(verts[0]->vertex_out, verts[2]->vertex_out, t2, tmp2.vertex_out);
			tmp2.clip_code = ClipCode(tmp2.clip_space);
			
			DrawTriangleClip(*verts[0], tmp1, tmp2, clip_bit + 1);
		}
		
		delete[] tmp1.vertex_out;
		delete[] tmp2.vertex_out;
	}
	
}
void DrawTriangleFit(Vertex& v1, Vertex& v2, Vertex& v3) {
	
	bool front_facing = IsFrontFacing(v1.clip_space, v2.clip_space, v3.clip_space);
	if (CGL::cull_face_enable) {
		if (CGL::culling_mode == BACK && front_facing) {
			return;
			
		} else if (CGL::culling_mode == FRONT && !front_facing) {
			return;
			
		} else if (CGL::culling_mode == FRONT_AND_BACK)
			return;
	}
	
	CGL::shader->front_facing = front_facing;
	if (front_facing) {
		CGL::triangle_front(v1, v2, v3);
	} else {
		CGL::triangle_back(v1, v2, v3);
	}
}

void DrawTrianglePoint(Vertex& v1, Vertex& v2, Vertex& v3) {
	v1.screen_space = viewport * (v1.clip_space / v1.clip_space.w);
	v2.screen_space = viewport * (v2.clip_space / v2.clip_space.w);
	v3.screen_space = viewport * (v3.clip_space / v3.clip_space.w);
	
	DrawPoint(v1);
	DrawPoint(v2);
	DrawPoint(v3);
}
void DrawTriangleLine(Vertex& v1, Vertex& v2, Vertex& v3) {
	DrawLineClip(v1, v2);
	DrawLineClip(v2, v3);
	DrawLineClip(v3, v1);
}
void DrawTriangleFill(Vertex& v1, Vertex& v2, Vertex& v3) {
	
	float *fragment_in = new float[CGL::shader->GetFragmentShaderInputSize()];
	
	v1.screen_space = viewport * (v1.clip_space / v1.clip_space.w);
	v2.screen_space = viewport * (v2.clip_space / v2.clip_space.w);
	v3.screen_space = viewport * (v3.clip_space / v3.clip_space.w);
	
	vec3 p1 = v1.screen_space.xyz();
	vec3 p2 = v2.screen_space.xyz();
	vec3 p3 = v3.screen_space.xyz();
	
	box2 bounding = {(float)width, (float)height, 0, 0};
	bounding.Join(p1.xy());
	bounding.Join(p2.xy());
	bounding.Join(p3.xy());
	
	const float denom = 1.f / Area(p1.xy(), p2.xy(), p3.xy());
	
	float x;
	float y;
	
	for (int j = bounding.min_y; j < bounding.max_y; j++) {
		y = j + 0.5f;
		
		for (int i = bounding.min_x; i < bounding.max_x; i++) {
			
			x = i + 0.5f;
			
			float area_1 = Area({x, y}, p2.xy(), p3.xy()) * denom;
			float area_2 = Area(p1.xy(), {x, y}, p3.xy()) * denom;
			float area_3 = Area(p1.xy(), p2.xy(), {x, y}) * denom;
			
			if(area_1 < 0 || area_2 < 0 || area_3 < 0)
				continue;
			
			vec3 barycentric = vec3(area_1, area_2, area_3);
			float z = p1.z * barycentric[0] + p2.z * barycentric[1] + p3.z * barycentric[2];
			float w = v1.screen_space.w * barycentric[0] + v2.screen_space.w * barycentric[1] + v3.screen_space.w * barycentric[2];
			
			vec3 perspective = 1 / w * barycentric * vec3(v1.screen_space.w, v2.screen_space.w, v3.screen_space.w);
			CGL::shader->InterpolateFragment(v1.vertex_out, v2.vertex_out, v3.vertex_out, perspective, fragment_in);
			
			CGL::shader->frag_coords = {x, y, z, 1/w};
			CGL::shader->discard = false;
			CGL::shader->frag_depth = z;
		
			CGL::shader->SetFragmentInput(fragment_in);
			CGL::shader->FragmentShader();
			
			if (!CGL::shader->discard)
				DrawPixel(CGL::shader->frag_color, x, y, CGL::shader->frag_depth);
		}
	}
	
}
