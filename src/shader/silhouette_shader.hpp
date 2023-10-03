//
//  silhouette_shader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 06/01/2023.
//

#ifndef silhouette_shader_hpp
#define silhouette_shader_hpp

#include <stdio.h>

#include "shader.hpp"


class SilhouetteShader : public ShaderProgram {
	
	
	
	struct {
		vec3 position;
	} input;
	
public:
	mat4 model_matrix;
	mat4 view_matrix;
	mat4 projection_matrix;
	
	SilhouetteShader();
	
	virtual size_t GetVertexShaderInputSize() const;
	virtual size_t GetFragmentShaderInputSize() const;
	
	virtual void SetVertexInput(const u_int8_t* data);
	virtual void SetFragmentInput(const float* data);
	
	virtual void GetVertexOutput(float* data) const;
	
	virtual void VertexShader();
	virtual void FragmentShader();
};


#endif /* silhouette_shader_hpp */
