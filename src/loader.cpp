//
//  loader.cpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#include "loader.hpp"

#include <wx/bitmap.h>
#include <wx/rawbmp.h>

#include "irit_sm.h"
#include "iritprsr.h"
#include "attribut.h"
#include "allocate.h"
#include "ip_cnvrt.h"
#include "symb_lib.h"
#include "misc_lib.h"
#include "miscattr.h"

#include "math.hpp"
#include "buffer.hpp"

#include <iostream>


using namespace CGL;

IPFreeformConvStateStruct state_struct = {
	FALSE,          				/* Talkative */
	FALSE,          				/* DumpObjsAsPolylines */
	TRUE,           				/* DrawFFGeom */
	FALSE,          				/* DrawFFMesh */
	{ 10, 10, 10 }, 				/* 10 isocurves peru/v/w direction. */
	100,            				/* 100 point samples along a curve. */
	SYMB_CRV_APPROX_UNIFORM,  		/* CrvApproxMethod */
	FALSE,   						/* ShowIntrnal */
	FALSE,   						/* CubicCrvsAprox */
	20,      						/* Polygonal FineNess */
	FALSE,   						/* ComputeUV */
	TRUE,    						/* ComputeNrml */
	FALSE,   						/* FourPerFlat */
	0,       						/* OptimalPolygons */
	FALSE,   						/* BBoxGrid */
	TRUE,    						/* LinearOnePolyFlag */
	FALSE
};


typedef long long unsigned v_hash;
static inline v_hash HashVertex(const vec3& vec) {
	short packed[4] = {
		(short) (vec.x * 1e4),
		(short) (vec.y * 1e4),
		(short) (vec.z * 1e4),
		(short) 0
	};
	
	return *(long long unsigned*) &packed;
}


std::map<std::string, Object> objects_map;
inline std::vector<std::string> loaded_objects;


void LoadObject(IPObjectStruct *object, IrtHmgnMatType matrix, void *data);
bool StoreObjectData(IPObjectStruct *object);

// object attributes
int GetObjectColor(IPObjectStruct *object, double rgb[3]);
int GetObjectTransparency(IPObjectStruct *object, double *transparency);
const char *GetObjectVolumetricTexture(IPObjectStruct *object);
const char *GetObjectParametricTexture(IPObjectStruct *object);


bool CGL::LoadModel(const std::string& file_name) {
	IrtHmgnMatType curr_view_mat;
	IPTraverseObjHierarchyStruct state;
	
	/* Get the data files: */
	IPSetFlattenObjects(false);
	
	IPObjectStruct *objects = IPGetDataFiles((const char* const*)&file_name, 1, TRUE, FALSE);
	if (objects == nullptr) {
		return false;
	}
	
	objects = IPResolveInstances(objects);
	
	if (IPWasPrspMat)
		MatMultTwo4by4(curr_view_mat, IPViewMat, IPPrspMat);
	else
		IRIT_GEN_COPY(curr_view_mat, IPViewMat, sizeof(IrtHmgnMatType));
	
	state_struct.FineNess = CGL::polygon_fineness;   /* Res. of tesselation, larger is finer. */
	state_struct.ComputeUV = TRUE;   				/* Wants UV coordinates for textures. */
	state_struct.FourPerFlat = TRUE;				/* 4 poly per ~flat patch, 2 otherwise.*/
	state_struct.LinearOnePolyFlag = TRUE;    		/* Linear srf gen. one poly. */
	
	//clean the models map;
	objects_map.clear();
	
	size_t name_start = file_name.find_last_of("/") + 1;
	size_t name_end = file_name.find_last_of(".itd");
	size_t length = name_end != string::npos ? name_end - name_start - 3 : file_name.size() - name_start;
	
	std::string model_name = file_name.substr(name_start, length);
	size_t count = std::count(loaded_objects.begin(), loaded_objects.end(), model_name) + 1;
	loaded_objects.push_back(model_name);
	
	IPTraverseObjHierarchyInitState(&state);
	state.ApplyFunc = (IPApplyObjFuncType) LoadObject;
	IRIT_GEN_COPY(state.Mat, curr_view_mat, sizeof(IrtHmgnMatType));
	IPTraverseObjListHierarchy(objects, &state);
	
	Object main_object;
	main_object.name = std::string(model_name + to_string(count));
	for (auto& [name, object] : objects_map) {
		main_object.objects[name] = object;
	}
	
	CGL::objects[main_object.name] = main_object;
	
	return true;
}
bool CGL::LoadTexture(const std::string& file_name) {
	
	wxBitmap bitmap(file_name, wxBITMAP_TYPE_PNG);
	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();
	
	wxImage img = bitmap.ConvertToImage();
	
//	width = img.GetWidth();
//	width = img.GetHeight();
	
	size_t name_start = file_name.find_last_of("/") + 1;
	size_t name_end = file_name.find_last_of(".png");
	size_t length = name_end != string::npos ? name_end - name_start - 3 : file_name.size() - name_start;
	
	std::string texture_name = file_name.substr(name_start, length);
	
	
	
	Buffer *buffer = Buffer::CreateBuffer<vec4>(width, height);
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			
			vec4 color;
			
			color.x = ((float)img.GetRed(i, j)) / 255.0f;
			color.y = ((float)img.GetGreen(i, j)) / 255.0f;
			color.z = ((float)img.GetBlue(i, j)) / 255.0f;
			color.w = img.HasAlpha() ? ((float)img.GetAlpha(i, j)) / 255.0f : 1.0f;
			
			buffer->Set<vec4>(i, j, color);
		}
	}

	textures[texture_name] = new Texture(buffer);
	
	return true;
	
}



void LoadObject(IPObjectStruct *object, IrtHmgnMatType matrix, void *data) {
	IPObjectStruct *objects = object;
	
	if (IP_IS_FFGEOM_OBJ(object))
		objects = IPConvertFreeForm(object, &state_struct);

	for (object = objects; object != NULL; object = object -> Pnext) {
		if (!StoreObjectData(object))
			exit(1);
	}
}
bool StoreObjectData(IPObjectStruct *object_struct) {
	const char *str;
	double rgb[3];
	double transp;
	
	const IPAttributeStruct *attribute = AttrTraceAttributes(object_struct->Attr, object_struct->Attr);
	
	if (object_struct->ObjType != IP_OBJ_POLY) { return true; }
	
	// map of the indexes of all the vertex of the polygon
	std::map<v_hash, size_t> vertices_map;
	
	// map for all the faces in the polygon
	std::map<v_hash, size_t> face_map;
	
	// map of the vertex calculate normals
	std::map<v_hash, vec3> vertex_normal_map;
	
	// map the all the vertex of a given face
	std::map<v_hash, std::vector<size_t>> face_vertices_map;
	
	Object object;
	object.name = object_struct->ObjName;
	vec3 object_color {1, 0, 0};
	box3 bounding_box = { INFINITY, INFINITY, INFINITY, -INFINITY, -INFINITY, -INFINITY };
	
	if (GetObjectColor(object_struct, rgb)) {
		object_color = { rgb[0], rgb[1], rgb[2] };
	}
	
	object.front_color = object_color;
	object.back_color = object_color;
	
	if (GetObjectTransparency(object_struct, &transp)) {}
	
	if ((str = GetObjectVolumetricTexture(object_struct)) != NULL) {
		// Generate Volumetric Texture
		// add it to the global textures
		// save it's id for later use
		printf("Volumetric Texture: %s\n", str);
	}
	
	if ((str = GetObjectParametricTexture(object_struct)) != NULL) {
		// Generate Parametric Texture
		// add it to the global textures
		// save it's id for later use
		printf("Parametric Texture: %s\n", str);
	}
	
	if (attribute != NULL) {
		while (attribute) {
			/* attributes code */
			attribute = AttrTraceAttributes(attribute, NULL);
		}
	}
	
	IPPolygonStruct *polygon;
	IPVertexStruct *vertex;
	box2 texture_box = {INFINITY, INFINITY, -INFINITY, -INFINITY};
	
	for (polygon = object_struct->U.Pl; polygon != NULL; polygon = polygon->Pnext) {
		
		if (polygon->PVertex == NULL) { return false; }
		
		vec3 polygon_center {0, 0, 0};
		vec3 polygon_s_normal {0, 0, 0};
		std::vector<vec3> polygon_points;
		
		float max_x = 0;
		float max_y = 0;
		
		if (IP_HAS_PLANE_POLY(polygon)) {
			polygon_s_normal = { polygon->Plane[0], polygon->Plane[1], polygon->Plane[2] };
		}
		
		vertex = polygon->PVertex;
		
		do {
			
			vec3 vertex_pos {vertex->Coord[0], vertex->Coord[1], vertex->Coord[2]};
			vec3 vertex_normal {0, 1, 0};
			vec2 texture_coords {0, 0};
			
			if(IP_HAS_NORMAL_VRTX(vertex)) {
				vertex_normal = { vertex->Normal[0], vertex->Normal[1], vertex->Normal[2] };
			}
			
			float *UV;
			if ((UV = AttrGetUVAttrib(vertex->Attr, "uvvals")) != NULL) {
				/* UV values are in UV[0] and UV[1]. */
				texture_coords = {UV[0], UV[1]};
				texture_box.Join(texture_coords);
			}
			
			v_hash hash = HashVertex(vertex_pos);
			size_t index = vertices_map.count(hash) != 0 ? vertices_map[hash] : -1;
			if (index == -1) {
				index = vertices_map.size();
				vertices_map[hash] = index;
				
				vertex_normal_map[hash] = {0, 0, 0};

				object.positions.push_back(vertex_pos);
				object.load_vertex_normals.push_back(Normolize(vertex_normal));
				object.parametric_texture_coords.push_back(texture_coords);
			}
			
			polygon_points.push_back(vertex_pos);
			polygon_center = polygon_center + vertex_pos;
			
			bounding_box.Join(vertex_pos);
			
			// next vertex
			vertex = vertex->Pnext;
		} while(vertex != polygon->PVertex && vertex != NULL);
		
		polygon_center = polygon_center / (float) polygon_points.size();
		polygon_s_normal = Normolize(polygon_s_normal);
		
		v_hash face_hash = HashVertex(polygon_center);
		size_t face_index = face_map.count(face_hash) != 0 ? face_map[face_hash] : -1;
		if (face_index == -1) {
			face_index = face_map.size();
			face_map[face_hash] = face_index;
			face_vertices_map[face_hash] = std::vector<size_t>();
			
			object.face_positions.push_back(polygon_center);
			object.load_surface_normals.push_back(polygon_s_normal);
			object.calc_surface_normals.push_back({0 ,0 ,0});
		}
		
		// update the object vertices calculated normals
		/* ============================================================================================================ */
		size_t vertices_count = polygon_points.size();
		for (size_t i = 0; i < vertices_count; i++) {
			vec3 a = polygon_points[(i - 1) % vertices_count] - polygon_points[i];
			vec3 b = polygon_points[(i + 1) % vertices_count] - polygon_points[i];
			
			v_hash hash = HashVertex(polygon_points[i]);
			vertex_normal_map[hash] = vertex_normal_map[hash] + Cross(a,b);
		}
		
		/* convert the polygon into triangles */
		/* ============================================================================================================ */
		auto push_vertex = [&](const vec3& position) {
			v_hash hash = HashVertex(position);
			size_t index = vertices_map[hash];
			
			object.indices.push_back(index);
			object.face_indices.push_back(face_index);
			face_vertices_map[face_hash].push_back(index);
		};
		
		if (vertices_count == 3) {
			// the polygon is already triangle, just push it in
			std::for_each(polygon_points.begin(), polygon_points.end(), push_vertex);
		} else if (vertices_count == 4) {
			// the polygon is rectangle, cut it into 2 triangles
			int triangles[] = {0, 1, 3, 1, 2, 3};
			for (int i = 0; i < 6; i++) {
				push_vertex(polygon_points[triangles[i]]);
			}
		} else {
			// the polygon has mode then 4 vertices
			// in that case create new vertex at the center of the polygon and connect all the vertices to it
			printf("More then 4 vertices\n");
			const v_hash center_hash = HashVertex(polygon_center);
			size_t center_index = vertices_map.count(center_hash) != 0 ? vertices_map[center_hash] : -1;
			if (center_index == -1) {
				center_index = vertices_map.size();
				vertices_map[center_hash] = center_index;
				
				object.positions.push_back(polygon_center);
//				object.colors.push_back(object_color);
				object.load_vertex_normals.push_back(polygon_s_normal);
			}
			
			for (int i = 0; i < vertices_count; i++) {
				push_vertex(polygon_center);
				push_vertex(polygon_points[i]);
				push_vertex(polygon_points[(i + 1) % vertices_count]);
			}
		}
	}
	
	
	for (const vec3& pos : object.positions) {
		object.calc_vertex_normals.push_back(vertex_normal_map[HashVertex(pos)]);
	}
	for (const auto& [hash, face_vertices] : face_vertices_map) {
		vec3 surface_normal;
		
		for (const size_t& vertex_index : face_vertices) {
			surface_normal = surface_normal + object.calc_vertex_normals[vertex_index];
		}
		object.calc_surface_normals[face_map[hash]] = Normolize(surface_normal);
	}
	
	for (vec2& texture_coords : object.parametric_texture_coords) {
		texture_coords.x = CGL::Map(texture_coords.x, texture_box.min_x, texture_box.max_x, 0.0f, 1.0f);
		texture_coords.y = CGL::Map(texture_coords.y, texture_box.min_y, texture_box.max_y, 0.0f, 1.0f);
	}
	
	object.vertex_count = object.indices.size();
	object.bounding_box = bounding_box;
	object.bounding_box_color = object_color;
	object.bounding_box_positions = {
		{ bounding_box.min_x, bounding_box.max_y, bounding_box.max_z},
		{ bounding_box.min_x, bounding_box.min_y, bounding_box.max_z},
		{ bounding_box.min_x, bounding_box.min_y, bounding_box.min_z},
		{ bounding_box.min_x, bounding_box.max_y, bounding_box.min_z},
		
		{ bounding_box.max_x, bounding_box.max_y, bounding_box.max_z},
		{ bounding_box.max_x, bounding_box.max_y, bounding_box.min_z},
		{ bounding_box.max_x, bounding_box.min_y, bounding_box.max_z},
		{ bounding_box.max_x, bounding_box.min_y, bounding_box.min_z}
	};
	
	
	objects_map[object.name] = object;

	return true;
}

int GetObjectColor(IPObjectStruct *object, double rgb[3]) {
	static int color_table[][4] = {
		{ /* BLACK	*/   0,    0,   0,   0 },
		{ /* BLUE	*/   1,    0,   0, 255 },
		{ /* GREEN	*/   2,    0, 255,   0 },
		{ /* CYAN	*/   3,    0, 255, 255 },
		{ /* RED	*/   4,  255,   0,   0 },
		{ /* MAGENTA 	*/   5,  255,   0, 255 },
		{ /* BROWN	*/   6,   50,   0,   0 },
		{ /* LIGHTGRAY	*/   7,  127, 127, 127 },
		{ /* DARKGRAY	*/   8,   63,  63,  63 },
		{ /* LIGHTBLUE	*/   9,    0,   0, 255 },
		{ /* LIGHTGREEN	*/   10,   0, 255,   0 },
		{ /* LIGHTCYAN	*/   11,   0, 255, 255 },
		{ /* LIGHTRED	*/   12, 255,   0,   0 },
		{ /* LIGHTMAGENTA */ 13, 255,   0, 255 },
		{ /* YELLOW	*/   14, 255, 255,   0 },
		{ /* WHITE	*/   15, 255, 255, 255 },
		{ /* BROWN	*/   20,  50,   0,   0 },
		{ /* DARKGRAY	*/   56,  63,  63,  63 },
		{ /* LIGHTBLUE	*/   57,   0,   0, 255 },
		{ /* LIGHTGREEN	*/   58,   0, 255,   0 },
		{ /* LIGHTCYAN	*/   59,   0, 255, 255 },
		{ /* LIGHTRED	*/   60, 255,   0,   0 },
		{ /* LIGHTMAGENTA */ 61, 255,   0, 255 },
		{ /* YELLOW	*/   62, 255, 255,   0 },
		{ /* WHITE	*/   63, 255, 255, 255 },
		{		     -1,   0,   0,   0 }
	};
	
	int i;
	int j;
	int color;
	int rgb_color[3] = {0, 0, 0};
	
	if(AttrGetObjectRGBColor(object, &rgb_color[0], &rgb_color[1], &rgb_color[2])) {
		rgb[0] = rgb_color[0] / 255.f;
		rgb[1] = rgb_color[1] / 255.f;
		rgb[2] = rgb_color[2] / 255.f;
		
		return true;
		
	} else if ((color = AttrGetObjectColor(object)) != IP_ATTR_NO_COLOR) {
		
		for (int i = 0; i < 25; i++) {
			if (color_table[i][0] == color) {
				rgb[0] = color_table[i][1] / 255.f;
				rgb[1] = color_table[i][2] / 255.f;
				rgb[2] = color_table[i][3] / 255.f;
				
				return true;
			}
		}
	}
	return false;
};
int GetObjectTransparency(IPObjectStruct *object, double *transparency) {
	*transparency = AttrGetObjectRealAttrib(object, "transp");
	return !IP_ATTR_IS_BAD_REAL(*transparency);
};
const char *GetObjectVolumetricTexture(IPObjectStruct *object) {
	return AttrGetObjectStrAttrib(object, "texture");
};
const char *GetObjectParametricTexture(IPObjectStruct *object) {
	return AttrGetObjectStrAttrib(object, "ptexture");
};
