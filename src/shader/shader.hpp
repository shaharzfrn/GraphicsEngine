//
//  shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 29/12/2022.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>
#include "math.hpp"


#define SHADER(name, type, input_val, pass_val)\
name(): ShaderProgram(type) {\
input_size = sizeof(input_val);\
pass_size = sizeof(pass_val);\
};

#define SHADER_VERTEX_SIZE()\
virtual size_t GetVertexShaderInputSize() const {\
return sizeof(input);\
};

#define SHADER_FRAGMENT_SIZE()\
virtual size_t GetFragmentShaderInputSize() const {\
return sizeof(pass);\
};

#define SHADER_VERTEX_INPUT()\
virtual void SetVertexInput(const u_int8_t* data) {\
memcpy(&input, data, sizeof(input));\
};

#define SHADER_VERTEX_OUTPUT()\
virtual void GetVertexOutput(float* data) const {\
memcpy(data, &pass, sizeof(pass));\
};

#define SHADER_FRAGMENT_INPUT()\
virtual void SetFragmentInput(const float* data) {\
memcpy(&pass, data, sizeof(pass));\
};

typedef enum {
	PHONG_SHADER,
	GOURAUD_SHADER,
	FLAT_SHADER,
	SILHOUETTE_SHADER,
	LINE_SHADER,
	BOUNDING_BOX_SHADER,
	SHADOW_SHADER,
} ShaderType;

class ShaderProgram {

protected:
	size_t input_size;
	size_t pass_size;
	
public:
	
	const ShaderType type;
	
	vec4 out_position;
	vec2 point_coord;
	int instance_id;
	
	bool front_facing;
	vec4 frag_coords;
	vec4 frag_color;
	
	float frag_depth;
	bool discard;
	
	ShaderProgram(const ShaderType type);
	
	virtual size_t GetVertexShaderInputSize() const = 0;
	virtual size_t GetFragmentShaderInputSize() const = 0;
	
	virtual void SetVertexInput(const u_int8_t* data) = 0;
	virtual void SetFragmentInput(const float* data) = 0;
	
	virtual void InterpolateFragment(const float* v1, const float* v2, const float& t, float* out);
	virtual void InterpolateFragment(const float* v1, const float* v2, const vec2& perspective, float* out);
	virtual void InterpolateFragment(const float* v1, const float* v2, const float* v3, const vec3& perspective, float* out);
	
	virtual void GetVertexOutput(float* data) const = 0;
	
	virtual void VertexShader() = 0;
	virtual void FragmentShader() = 0;
};


#endif /* shader_hpp */
