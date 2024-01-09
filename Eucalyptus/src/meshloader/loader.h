#pragma once
#include "api.h"

#include "graphics/mesh.h"
#include "graphics/material.h"



namespace Eucalyptus {
    std::vector<std::string> split_cstr(std::string& s);
    std::vector<std::string> split_cstr_by_delim(std::string& s, char delim);

    Mesh _EUCAPI LoadMeshFromOBJ(const char* path);
    Material LoadMaterialFromMTLFile(const char* path);
}