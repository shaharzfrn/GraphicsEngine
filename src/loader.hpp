//
//  loader.hpp
//  CGApp
//
//  Created by Shahar Zafran on 28/12/2022.
//

#ifndef loader_hpp
#define loader_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "model.hpp"
#include "texture.hpp"
#include "buffer.hpp"


namespace CGL {

inline int polygon_fineness;

//inline std::map<std::string, Object> objects;
//inline std::map<std::string, Texture*> textures;

bool LoadModel(const std::string& file_name);

bool LoadTexture(const std::string& file_name);



};






#endif /* loader_hpp */
