//
//  model.cpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#include "model.hpp"
#include "cgl_shaders.hpp"

#include "texture.hpp"

#include "projection.hpp"
#include "shadow.hpp"
#include "light.hpp"
#include "camera.hpp"


RawObject::RawObject() {
	vertex_count = 0;
	indices.clear();
	positions.clear();

	face_positions.clear();
	parametric_texture_coords.clear();
	volumetric_texture_coords.clear();

	load_vertex_normals.clear();
	calc_vertex_normals.clear();

	load_surface_normals.clear();
	calc_surface_normals.clear();
	
	bounding_box_indices = {0, 1, 3,1, 2, 3,4, 0, 5,0, 3, 5,6, 4, 7,4, 5, 7,1, 6, 2,6, 7, 2,0, 4, 1,4, 6, 1,2, 7, 3,7, 5, 3};
}

Object::Object(): RawObject() {
	
	scale = {1, 1, 1};
	
	draw_bounding_box = false;
	
	polygon_mode_front = FILL;
	polygon_mode_back = FILL;
	
	face_culling = false;
	culling_mode = 0;
	
	diffuse_factor = 0.3f;
	specular_factor = 0.2f;
	specular_exp = 2.f;
	
	silhouette_enable = false;
	silhouette_depth_top = false;
	silhouette_color = {1, 1, 1};
	
	front_color = {0, 1, 0};
	back_color = {0, 1, 0};
	
	draw_vertex_normals = false;
	vertex_normal_color = {0, 0, 1};
	use_calc_vertex_normals = false;
	
	draw_plane_normals = false;
	plane_normal_color = {0, 1, 0};
	use_calc_plane_normals = false;
	
	shader_type = PHONG_SHADER;
};

void Object::DrawRawObject(const vec3& view_position, const vec3& parent_position, const mat4& model_matrix, const mat4& rotation_matrix) {
	
	ModelUniforms *model_uniforms = CGL::GetModelUniforms(shader_type);
	ShaderProgram *model_shader = CGL::GetShaderProgram(shader_type);
	
	model_uniforms->model_matrix = model_matrix;
	model_uniforms->inverse_model_matrix = rotation_matrix;
	model_uniforms->reverse_normals = reverse_normals;
	model_uniforms->projection_matrix = CGL::GenerateProjectionMatrix(parent_position + position - view_position);
	model_uniforms->view_matrix = CGL::MAIN_CAMERA_VIEW_MATRIX ;
	
	model_uniforms->object_front_color = front_color;
	model_uniforms->object_back_color = back_color;
	
	model_uniforms->object_selected = is_selected;
	model_uniforms->diffuse_factor = diffuse_factor;
	model_uniforms->specular_factor = specular_factor;
	model_uniforms->specular_exp = specular_exp;
	model_uniforms->camera_position = CGL::camera.position;
	
	if (!texture_name.empty() && CGL::textures.count(texture_name)) {
		model_uniforms->color_texture = CGL::textures[texture_name];
	} else {
		model_uniforms->color_texture = nullptr;
	}
	
	for (int i = 0; i < MAX_LIGHTS; i++) {
		if (!CGL::lights[i].enabled)
			continue;
		
		CGL::shadows[i]->mvp = CGL::GenerateShadowProjection(parent_position + position - CGL::shadows[i]->view_position) * CGL::shadows[i]->view_matrix;
	}
	
	CGL::shader = model_shader;
	// vertex stage
	// first we calc the vertex shader for all the vertices in the object
	std::vector<CGL::Vertex> vertices;
	for (size_t i = 0; i < vertex_count; i++) {
		u_int8_t *vertex_input = new u_int8_t[model_shader->GetVertexShaderInputSize()];
		GenerateVertexInput(i, vertex_input, shader_type);
	
		model_shader->SetVertexInput(vertex_input);
		model_shader->VertexShader();
	
		CGL::Vertex vertex;
		CGL::GenerateShaderVertex(vertex);
	
		vertices.push_back(vertex);
	}
	
	if ((model_uniforms->silhouette_enabled = silhouette_enable)) {
	
		// the silhouette shader doesn't care about the vertex output, only the pixel to draw
		CGL::shader = &CGL::SILHOUETTE_SHADER;
		
		// disable color and depth buffers
		CGL::DisableBuffer(COLOR_BUFFER | DEPTH_BUFFER);
		CGL::EnableBuffer(STENCIL_BUFFER);
		
		CGL::StencilFunction(ALWAYS, 0xff, 0xff);
		CGL::StencilOperator(REPLACE, REPLACE, REPLACE);
		
		CGL::Clear(STENCIL_BUFFER);
		
		// set front and back polygon mode to fill
		CGL::PolygonMode(FRONT, FILL);
		CGL::PolygonMode(BACK, FILL);
		
		// draw the silhouette and save it in texture
		CGL::DrawElements(TRIANGLES, vertices);
		
		// make texture from the current stencil buffer
		CGL::GetFrameBufferTexture(STENCIL_BUFFER, &model_uniforms->silhouette_texture);
		
		// set the silhouette settings
		model_uniforms->silhouette_color = silhouette_color;
		model_uniforms->silhouette_depth_top = silhouette_depth_top;
		
		// enable color and depth buffers
		CGL::EnableBuffer(COLOR_BUFFER | DEPTH_BUFFER);
		CGL::DisableBuffer(STENCIL_BUFFER);
	}
	
	model_uniforms->object_front_color = front_color;
	model_uniforms->object_back_color = back_color;
	
	model_uniforms->object_selected = is_selected;
	model_uniforms->diffuse_factor = diffuse_factor;
	model_uniforms->specular_factor = specular_factor;
	model_uniforms->specular_exp = specular_exp;
	model_uniforms->camera_position = CGL::camera.position;
	
	CGL::PolygonMode(FRONT, polygon_mode_front);
	CGL::PolygonMode(BACK, polygon_mode_back);
	
	if (face_culling) {
		CGL::EnableCullFace();
		CGL::CullFace(culling_mode);
	}
	
	CGL::shader = model_shader;
	CGL::DrawElements(TRIANGLES, vertices);
	
	std::for_each(vertices.begin(), vertices.end(), [](CGL::Vertex& vertex) {
		delete[] vertex.vertex_out;
	});
	
	if (silhouette_enable && model_uniforms->silhouette_texture != nullptr) {
		delete model_uniforms->silhouette_texture;
		model_uniforms->silhouette_texture = nullptr;
	}
	
	
	CGL::DisableCullFace();
}
void Object::DrawShadowRawObject(const vec3& view_position, const vec3& parent_position, const mat4& model_matrix) {
	
	CGL::shader = &CGL::SHADOW_SHADER;
	CGL::SHADOW_SHADER.model_matrix = model_matrix;
	
	CGL::SHADOW_SHADER.mvp = CGL::GenerateShadowProjection(parent_position + position - view_position) * CGL::SHADOW_SHADER.view_matrix;
	
	// vertex stage
	// first we calc the vertex shader for all the vertices in the object
	std::vector<CGL::Vertex> vertices;
	for (size_t i = 0; i < vertex_count; i++) {
		u_int8_t *vertex_input = new u_int8_t[CGL::SHADOW_SHADER.GetVertexShaderInputSize()];
		GenerateVertexInput(i, vertex_input, SHADOW_SHADER);
		
		CGL::SHADOW_SHADER.SetVertexInput(vertex_input);
		CGL::SHADOW_SHADER.VertexShader();
		
		CGL::Vertex vertex;
		CGL::GenerateShaderVertex(vertex);
		
		vertices.push_back(vertex);
	}
	
	CGL::DrawElements(TRIANGLES, vertices);
	
	std::for_each(vertices.begin(), vertices.end(), [](CGL::Vertex& vertex) {
		delete[] vertex.vertex_out;
	});
}

void Object::Draw(const vec3& view_position, const vec3& parent_position, const mat4& parent_model_matrix, const mat4& parent_rotation_matrix) {
	mat4 model_matrix = parent_model_matrix * CGL::GenerateModelMatrix(position, rotation, scale);
	mat4 rotation_matrix = parent_rotation_matrix * CGL::Transpose(CGL::Inverse(CGL::Rotate(-rotation)));
	for (auto& [_, object] : objects) {
		object.Draw(view_position, parent_position + position, model_matrix, rotation_matrix);
	}
	
	if (vertex_count != 0) {
		DrawRawObject(view_position, parent_position, model_matrix, rotation_matrix);
		DrawNormals(view_position, parent_position, model_matrix);
		DrawBoundingBox(view_position, parent_position, model_matrix);
	}
}

void Object::DrawShadow(const vec3& view_position, const vec3& parent_position, const mat4& parent_model_matrix) {
	mat4 model_matrix = parent_model_matrix * CGL::GenerateModelMatrix(position, rotation, scale);
	for (auto& [_, object] : objects) {
		object.DrawShadow(view_position, parent_position + position, model_matrix);
	}
	
	if (vertex_count != 0) {
		DrawShadowRawObject(view_position, parent_position, model_matrix);
	}
}


void Object::DrawNormals(const vec3& view_position, const vec3& parent_position, const mat4& model_matrix) {
	
	CGL::shader = CGL::GetShaderProgram(LINE_SHADER);
	LineShader *line_shader = (LineShader*)CGL::shader;
	
	line_shader->mvp = CGL::GenerateProjectionMatrix(parent_position + position - view_position) * CGL::MAIN_CAMERA_VIEW_MATRIX * model_matrix;;
	
	// vertex stage
	std::vector<CGL::Vertex> vertices;
	
	
	if (draw_vertex_normals) {
		vertices.clear();
		for (size_t i = 0; i < positions.size(); i++) {
			
			u_int8_t *vertex_input = new u_int8_t[line_shader->GetVertexShaderInputSize()];
			
			// calc the position of the vertex itself;
			GenerateNormalInput(i, vertex_input, true, false);
			
			line_shader->SetVertexInput(vertex_input);
			line_shader->VertexShader();
			
			CGL::Vertex edge_1;
			CGL::GenerateShaderVertex(edge_1);
			
			vertices.push_back(edge_1);
			
			// calc the position of the edge of the normal;
			GenerateNormalInput(i, vertex_input, false, false);
			
			line_shader->SetVertexInput(vertex_input);
			line_shader->VertexShader();
			
			CGL::Vertex edge_2;
			CGL::GenerateShaderVertex(edge_2);
			
			vertices.push_back(edge_2);
		}
		
		line_shader->color = vertex_normal_color;
		CGL::DrawElements(LINES, vertices);
		
		std::for_each(vertices.begin(), vertices.end(), [](CGL::Vertex& vertex) {
			delete[] vertex.vertex_out;
		});
	}
	
	
	if (draw_plane_normals) {
		vertices.clear();
		for (size_t i = 0; i < face_positions.size(); i++) {
			
			u_int8_t *vertex_input = new u_int8_t[line_shader->GetVertexShaderInputSize()];
			
			// calc the position of the vertex itself;
			GenerateNormalInput(i, vertex_input, true, true);
			
			line_shader->SetVertexInput(vertex_input);
			line_shader->VertexShader();
			
			CGL::Vertex edge_1;
			CGL::GenerateShaderVertex(edge_1);
			
			vertices.push_back(edge_1);
			
			// calc the position of the edge of the normal;
			GenerateNormalInput(i, vertex_input, false, true);
			
			line_shader->SetVertexInput(vertex_input);
			line_shader->VertexShader();
			
			CGL::Vertex edge_2;
			CGL::GenerateShaderVertex(edge_2);
			
			vertices.push_back(edge_2);
		}
		
		line_shader->color = plane_normal_color;
		CGL::DrawElements(LINES, vertices);
		
		std::for_each(vertices.begin(), vertices.end(), [](CGL::Vertex& vertex) {
			delete[] vertex.vertex_out;
		});
	}
}


void Object::DrawBoundingBox(const vec3& view_position, const vec3& parent_position, const mat4& model_matrix) {
	
	if (!draw_bounding_box)
		return;
	
	CGL::shader = CGL::GetShaderProgram(BOUNDING_BOX_SHADER);
	BoundingBoxShader *bounding_box_shader = (BoundingBoxShader*) CGL::shader;
	
	bounding_box_shader->mvp = CGL::GenerateProjectionMatrix(parent_position + position - view_position) * CGL::MAIN_CAMERA_VIEW_MATRIX * model_matrix;
	
	std::vector<CGL::Vertex> vertices;
	
	for (size_t i = 0; i < bounding_box_indices.size(); i++) {
		u_int8_t *vertex_input = new u_int8_t[CGL::BOUNDING_BOX_SHADER.GetVertexShaderInputSize()];
		GenerateVertexInput(i, vertex_input, BOUNDING_BOX_SHADER);
		
		CGL::BOUNDING_BOX_SHADER.SetVertexInput(vertex_input);
		CGL::BOUNDING_BOX_SHADER.VertexShader();
		
		CGL::Vertex vertex;
		CGL::GenerateShaderVertex(vertex);
		
		vertices.push_back(vertex);
	}
	
	bounding_box_shader->color = bounding_box_color;
	
	CGL::DisableCullFace();
	CGL::PolygonMode(FRONT | BACK, bounding_box_polygon_mode);
	
	CGL::DrawElements(TRIANGLES, vertices);
	
	std::for_each(vertices.begin(), vertices.end(), [](CGL::Vertex& vertex) {
		delete[] vertex.vertex_out;
	});
	
}


void Object::GenerateVertexInput(const size_t& index, u_int8_t *buffer, const ShaderType& type) {
	size_t buffer_index = indices[index];
	size_t face_index = face_indices[index];
	
	if (type == BOUNDING_BOX_SHADER) {
		memcpy(buffer, &bounding_box_positions[bounding_box_indices[index]], sizeof(vec3));
		return;
	} else {
		memcpy(buffer, &positions[buffer_index], sizeof(vec3));
		buffer += sizeof(vec3);
	}
	
	
	
	if (type == SHADOW_SHADER)
		return;
	
	vec3 normal;
	switch (type) {
		case ShaderType::PHONG_SHADER:
			normal = use_calc_vertex_normals ? calc_vertex_normals[buffer_index] : load_vertex_normals[buffer_index];
			break;
		
		case ShaderType::GOURAUD_SHADER:
			normal = use_calc_vertex_normals ? calc_vertex_normals[buffer_index] : load_vertex_normals[buffer_index];
			break;
			
		case ShaderType::FLAT_SHADER:
			normal = use_calc_vertex_normals ? calc_surface_normals[face_index] : load_surface_normals[face_index];
			break;
			
		default:
			break;
	}
	memcpy(buffer, &normal, sizeof(vec3));
	buffer += sizeof(vec3);
	
	if (parametric_texture_coords.size() > 0) {
		memcpy(buffer, &parametric_texture_coords[buffer_index], sizeof(vec2));
	}
	buffer += sizeof(vec2);
}

void Object::GenerateNormalInput(const size_t& index, u_int8_t *buffer, const bool& edge_1, const bool& plane) {
	vec3 data;
	if(plane) {
		data = face_positions[index];
	} else {
		data = positions[index];
	}
	
	if (!edge_1) {
		if (plane) {
			data += (use_calc_plane_normals ? calc_surface_normals[index] : load_surface_normals[index]) * (reverse_normals ? -1.0f : 1.0f);
		} else {
			data += (use_calc_vertex_normals ? calc_vertex_normals[index] : load_vertex_normals[index]) * (reverse_normals ? -1.0f : 1.0f);
		}
	}
	
	memcpy(buffer, &data, sizeof(vec3));
}


void Object::Draw(const vec3& view_position) {
	Draw(view_position, {}, CGL::Identity(), CGL::Identity());
}
void Object::DrawShadow(const vec3& view_position) {
	DrawShadow(view_position, {}, CGL::Identity());
}


// Silhouette Settings
/* =================================================== */
void Object::EnableSilhouette() {
	silhouette_enable = true;
	for (auto& [name, object] : objects) {
		object.EnableSilhouette();
	}
}
void Object::DisableSilhouette() {
	silhouette_enable = false;
	for (auto& [name, object] : objects) {
		object.DisableSilhouette();
	}
}
bool Object::IsSilhouetteEnable() {
	return silhouette_enable;
}

void Object::EnableSilhouetteDepth() {
	silhouette_depth_top = true;
	for (auto& [name, object] : objects) {
		object.EnableSilhouetteDepth();
	}
}
void Object::DisableSilhouetteDepth() {
	silhouette_depth_top = false;
	for (auto& [name, object] : objects) {
		object.DisableSilhouetteDepth();
	}
}
bool Object::IsSilhouetteDepthEnable() {
	return silhouette_depth_top;
}


void Object::SetSilhouetteColor(const vec3& color) {
	silhouette_color = color;
	for (auto& [name, object] : objects) {
		object.SetSilhouetteColor(color);
	}
}
vec3& Object::GetSilhouetteColor() {
	return silhouette_color;
}


// Bounding Box Settings
/* =================================================== */
void Object::EnableBoundingBox() {
	draw_bounding_box = true;
	for (auto& [name, object] : objects) {
		object.EnableBoundingBox();
	}
}
void Object::DisableBoundingBox() {
	draw_bounding_box = false;
	for (auto& [name, object] : objects) {
		object.DisableBoundingBox();
	}
}

void Object::SetBoundingBoxColor(const vec3& color) {
	bounding_box_color = color;
	for (auto& [name, object] : objects) {
		object.SetBoundingBoxColor(color);
	}
}
vec3& Object::GetBoundingBoxColor() {
	return bounding_box_color;
}

void Object::SetBoundingBoxPolygonMode(const u_int8_t& mode) {
	bounding_box_polygon_mode = mode;
	for (auto& [name, object] : objects) {
		object.SetBoundingBoxPolygonMode(mode);
	}
}
u_int8_t& Object::GetBoundingBoxPolygonMode() {
	return bounding_box_polygon_mode;
}


// Face Culling Settings
/* =================================================== */
void Object::EnableFaceCulling() {
	face_culling = true;
	for (auto& [name, object] : objects) {
		object.EnableFaceCulling();
	}
}
void Object::DisableFaceCulling() {
	face_culling = false;
	for (auto& [name, object] : objects) {
		object.DisableFaceCulling();
	}
}

void Object::SetFaceCullingMode(const u_int8_t& mode) {
	culling_mode = mode;
	for (auto& [name, object] : objects) {
		object.SetFaceCullingMode(mode);
	}
}
u_int8_t& Object::GetFaceCullingMode() {
	return culling_mode;
}

void Object::SetFrontFaceColor(const vec3& color) {
	front_color = color;
	for (auto& [name, object] : objects) {
		object.SetFrontFaceColor(color);
	}
}
vec3& Object::GetFrontFaceColor() {
	return front_color;
}

void Object::SetBackFaceColor(const vec3& color) {
	back_color = color;
	for (auto& [name, object] : objects) {
		object.SetBackFaceColor(color);
	}
}
vec3& Object::GetBackFaceColor() {
	return back_color;
}



void Object::EnableReverseNormals() {
	reverse_normals = true;
	for (auto& [name, object] : objects) {
		object.EnableReverseNormals();
	}
};
void Object::DisableReverseNormals() {
	reverse_normals = false;
	for (auto& [name, object] : objects) {
		object.DisableReverseNormals();
	}
};


// Vertex Normals Settings
/* =================================================== */
void Object::EnableVertexNormals() {
	draw_vertex_normals = true;
	for (auto& [name, object] : objects) {
		object.EnableVertexNormals();
	}
}
void Object::DisableVertexNormals() {
	draw_vertex_normals = false;
	for (auto& [name, object] : objects) {
		object.DisableVertexNormals();
	}
}

void Object::EnableLoadVertexNormals() {
	use_calc_vertex_normals = false;
	for (auto& [name, object] : objects) {
		object.EnableLoadVertexNormals();
	}
}
void Object::EnableCalcVertexNormals() {
	use_calc_vertex_normals = true;
	for (auto& [name, object] : objects) {
		object.EnableCalcVertexNormals();
	}
}

void Object::SetVertexNormalsColor(const vec3& color) {
	vertex_normal_color = color;
	for (auto& [name, object] : objects) {
		object.SetVertexNormalsColor(color);
	}
}
vec3& Object::GetVertexNormalsColor() {
	return vertex_normal_color;
}


// Plane Normals Settings
/* =================================================== */
void Object::EnablePlaneNormals() {
	draw_plane_normals = true;
	for (auto& [name, object] : objects) {
		object.EnablePlaneNormals();
	}
}
void Object::DisablePlaneNormals() {
	draw_plane_normals = false;
	for (auto& [name, object] : objects) {
		object.DisablePlaneNormals();
	}
}

void Object::EnableLoadPlaneNormals() {
	use_calc_plane_normals = false;
	for (auto& [name, object] : objects) {
		object.EnableLoadPlaneNormals();
	}
}
void Object::EnableCalcPlaneNormals() {
	use_calc_plane_normals = true;
	for (auto& [name, object] : objects) {
		object.EnableCalcPlaneNormals();
	}
}


void Object::SetPlaneNormalsColor(const vec3& color) {
	plane_normal_color = color;
	for (auto& [name, object] : objects) {
		object.SetPlaneNormalsColor(color);
	}
}
vec3& Object::GetPlaneNormalsColor() {
	return plane_normal_color;
}


// Polygon Draw Mode Settings
/* =================================================== */
void Object::SetFrontPolygonMode(const u_int8_t& mode) {
	polygon_mode_front = mode;
	for (auto& [name, object] : objects) {
		object.SetFrontPolygonMode(mode);
	}
}
u_int8_t& Object::GetFrontPolygonMode() {
	return polygon_mode_front;
}

void Object::SetBackPolygonMode(const u_int8_t& mode) {
	polygon_mode_back = mode;
	for (auto& [name, object] : objects) {
		object.SetBackPolygonMode(mode);
	}
}
u_int8_t& Object::GetBackPolygonMode() {
	return polygon_mode_back;
}


// Light Settings
/* =================================================== */
void Object::SetDiffuseFactor(const float& kd) {
	diffuse_factor = kd;
	for (auto& [name, object] : objects) {
		object.SetDiffuseFactor(kd);
	}
}
float& Object::GetDiffuseFactor() {
	return diffuse_factor;
}

void Object::SetSpecularFactor(const float& ks) {
	specular_factor = ks;
	for (auto& [name, object] : objects) {
		object.SetSpecularFactor(ks);
	}
}
float& Object::GetSpecularFactor() {
	return specular_factor;
}

void Object::SetSpecularExponent(const float& ns) {
	specular_exp = ns;
	for (auto& [name, object] : objects) {
		object.SetSpecularExponent(ns);
	}
}
float& Object::GetSpecularExponent() {
	return specular_exp;
}


// Select Settings
/* =================================================== */
void Object::Select() {
	is_selected = true;
	for (auto& [name, object] : objects) {
		object.Select();
	}
}
void Object::Diselect() {
	is_selected = false;
	for (auto& [name, object] : objects) {
		object.Diselect();
	}
}

// Select Settings
/* =================================================== */
void Object::SetShaderProgram(const ShaderType& type) {
	shader_type = type;
	for (auto& [name, object] : objects) {
		object.SetShaderProgram(type);
	}
}
ShaderType Object::GetShaderProgram() { return shader_type; }

void Object::SetTexture(const std::string& texture_name) {
	this->texture_name = texture_name;
	
	for (auto& [name, object] : objects) {
		object.SetTexture(texture_name);
	}
}
std::string& Object::GetTexture() {
	return texture_name;
}


const vector<string> Object::GetObjects() const {
	vector<string> objects_names;
	for (const auto& [object_name, _] : objects) {
		objects_names.push_back(object_name);
	}
	return objects_names;
}

