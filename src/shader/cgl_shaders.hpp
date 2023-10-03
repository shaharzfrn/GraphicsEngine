//
//  cgl_shaders.h
//  CGApp
//
//  Created by Shahar Zafran on 02/01/2023.
//

#ifndef cgl_shaders_h
#define cgl_shaders_h

#include "shader.hpp"

#include "phong_shader.hpp"
#include "gouraud_shader.hpp"
#include "flat_shader.hpp"

#include "silhouette_shader.hpp"
#include "shadow_shader.hpp"
#include "line_shader.hpp"
#include "bounding_box_shader.hpp"

#include "uniforms.h"

namespace CGL {

// this is the selected shader to use inside CGL functions
inline ShaderProgram *shader;

inline ModelUniforms *model_uniforms;

inline PhongShader PHONG_SHADER;
inline GouraudShader GOURAUD_SHADER;
inline FlatShader FLAT_SHADER;

inline SilhouetteShader SILHOUETTE_SHADER;

inline ShadowShader SHADOW_SHADER;

inline LineShader LINE_SHADER;
inline BoundingBoxShader BOUNDING_BOX_SHADER;

ShaderProgram* GetShaderProgram(const ShaderType type);
ModelUniforms* GetModelUniforms(const ShaderType type);

/*
 TODO: add:
		- flat shader
		- bounding box shader
 */
}



#endif /* cgl_shaders_h */
