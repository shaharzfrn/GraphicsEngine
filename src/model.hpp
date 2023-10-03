//
//  model.hpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#ifndef model_hpp
#define model_hpp

#include <stdio.h>

#include <vector>
#include <map>
#include <string>

#include "cgl.hpp"
#include "math.hpp"

#include "shader.hpp"
#include "uniforms.h"

#include "model_shader.hpp"
#include "texture.hpp"

#include "miscattr.h"

using namespace std;

struct RawObject {
	// the object draw info only
	vector<size_t> indices;
	vector<size_t> face_indices;

	// the positions of the vertices in the object
	vector<vec3> positions;

	// the positions of the center of each surface in the object
	vector<vec3> face_positions;

	size_t parametric_texture_index;
	vector<vec2> parametric_texture_coords;

	size_t volumetric_texture_index;
	vector<vec3> volumetric_texture_coords;

	vector<vec3> load_vertex_normals;
	vector<vec3> calc_vertex_normals;

	vector<vec3> load_surface_normals;
	vector<vec3> calc_surface_normals;

	std::vector<size_t> bounding_box_indices;
	std::vector<vec3> bounding_box_positions;
	
	size_t vertex_count;
	
	RawObject();
};


class Object : public RawObject {
	
	bool silhouette_enable;
	bool silhouette_depth_top;
	vec3 silhouette_color;
	
	bool draw_bounding_box;
	u_int8_t bounding_box_polygon_mode;
	vec3 bounding_box_color;
	box3 bounding_box;
	
	bool face_culling;
	u_int8_t culling_mode;
	vec3 front_color;
	vec3 back_color;
	
	bool reverse_normals;
	
	bool draw_vertex_normals;
	bool use_calc_vertex_normals;
	vec3 vertex_normal_color;
	
	bool draw_plane_normals;
	bool use_calc_plane_normals;
	vec3 plane_normal_color;
	
	u_int8_t polygon_mode_front;
	u_int8_t polygon_mode_back;
	
	float diffuse_factor;
	float specular_factor;
	float specular_exp;
	
	bool is_selected = false;
	
	ShaderType shader_type;
	
	std::string texture_name;
	
	void DrawRawObject(const vec3& view_position, const vec3& parent_position, const mat4& parent_model_matrix, const mat4& parent_rotation_matrix);
	void DrawShadowRawObject(const vec3& view_position, const vec3& parent_position, const mat4& parent_model_matrix);
	
	void Draw(const vec3& view_position, const vec3& parent_position, const mat4& parent_model_matrix, const mat4& parent_rotation_matrix);
	void DrawShadow(const vec3& view_position, const vec3& parent_position, const mat4& parent_model_matrix);
	
	void DrawNormals(const vec3& view_position, const vec3& parent_position, const mat4& parent_model_matrix);
	void DrawBoundingBox(const vec3& view_position, const vec3& parent_position, const mat4& parent_model_matrix);
	
	
	void GenerateVertexInput(const size_t& index, u_int8_t *buffer, const ShaderType& type);
	void GenerateNormalInput(const size_t& index, u_int8_t *buffer, const bool& edge_1, const bool& plane);
	friend bool StoreObjectData(IPObjectStruct *object);
	
public:
	
	vec3 position;
	vec3 rotation;
	vec3 scale;
	
	string name;
	map<string, Object> objects;
	
	Object();
	
	void Draw(const vec3& view_position);
	void DrawShadow(const vec3& view_position);
	
	/* =================================================== */
	/* Get & Set Functions*/
	/* =================================================== */
	
	// Silhouette Settings
	/* =================================================== */
	virtual void EnableSilhouette();
	virtual void DisableSilhouette();
	virtual bool IsSilhouetteEnable();
	
	virtual void EnableSilhouetteDepth();
	virtual void DisableSilhouetteDepth();
	virtual bool IsSilhouetteDepthEnable();
	
	virtual void SetSilhouetteColor(const vec3& color);
	virtual vec3& GetSilhouetteColor();
	
	// Bounding Box Settings
	/* =================================================== */
	virtual void EnableBoundingBox();
	virtual void DisableBoundingBox();
	virtual bool IsBoundingBoxEnabled() {
		return draw_bounding_box;
	}
	
	
	virtual void SetBoundingBoxColor(const vec3& color);
	virtual vec3& GetBoundingBoxColor();
	
	virtual void SetBoundingBoxPolygonMode(const u_int8_t& mode);
	virtual u_int8_t& GetBoundingBoxPolygonMode();
	
	
	// Face Culling Settings
	/* =================================================== */
	virtual void EnableFaceCulling();
	virtual void DisableFaceCulling();
	
	virtual void SetFaceCullingMode(const u_int8_t& mode);
	virtual u_int8_t& GetFaceCullingMode();
	
	virtual void SetFrontFaceColor(const vec3& color);
	virtual vec3& GetFrontFaceColor();
	
	virtual void SetBackFaceColor(const vec3& color);
	virtual vec3& GetBackFaceColor();
	
	virtual void EnableReverseNormals();
	virtual void DisableReverseNormals();
	
	
	// Vertex Normals Settings
	/* =================================================== */
	virtual void EnableVertexNormals();
	virtual void DisableVertexNormals();
	
	virtual void EnableLoadVertexNormals();
	virtual void EnableCalcVertexNormals();
	
	virtual void SetVertexNormalsColor(const vec3& color);
	virtual vec3& GetVertexNormalsColor();
	
	// Plane Normals Settings
	/* =================================================== */
	virtual void EnablePlaneNormals();
	virtual void DisablePlaneNormals();
	
	virtual void EnableLoadPlaneNormals();
	virtual void EnableCalcPlaneNormals();
	
	virtual void SetPlaneNormalsColor(const vec3& color);
	virtual vec3& GetPlaneNormalsColor();
	
	
	// Polygon Draw Mode Settings
	/* =================================================== */
	virtual void SetFrontPolygonMode(const u_int8_t& mode);
	virtual u_int8_t& GetFrontPolygonMode();
	
	virtual void SetBackPolygonMode(const u_int8_t& mode);
	virtual u_int8_t& GetBackPolygonMode();
	
	// Light Settings
	/* =================================================== */
	virtual void SetDiffuseFactor(const float& kd);
	virtual float& GetDiffuseFactor();
	
	virtual void SetSpecularFactor(const float& ks);
	virtual float& GetSpecularFactor();
	
	virtual void SetSpecularExponent(const float& ns);
	virtual float& GetSpecularExponent();
	
	// Select Settings
	/* =================================================== */
	virtual void Select();
	virtual void Diselect();
	
	// Shader Settings
	/* =================================================== */
	virtual void SetShaderProgram(const ShaderType& type);
	virtual ShaderType GetShaderProgram();
	
	// Texture Settings
	/* =================================================== */
	virtual void SetTexture(const std::string& texture_name);
	virtual std::string& GetTexture();
	
		
	// list of the direct sub object of the current object
	const vector<string> GetObjects() const;
};


namespace CGL {

inline std::map<std::string, Object> objects;

inline bool is_object_selected = false;

inline Object* selected_object = nullptr;
}


#endif /* model_hpp */
