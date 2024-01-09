#include "loader.h"
#include "graphics/texture.h"
#include "internal.h"


#include <string>
#include <sstream>
#include <fstream>


#define _SIZEOFARRAY(arr) sizeof(arr) / sizeof(arr[0])

namespace Eucalyptus {

    /*      String splitting function
            Taken from https://favtutor.com/blogs/split-string-cpp
            On December 19th 2023 20:39 
    */
    std::vector<std::string> split_cstr(std::string& s){
        std::vector<std::string> out;

        std::stringstream ss(s);  
        std::string word;
        while (ss >> word) { // Extract word from the stream.
            out.push_back(word);
        }

        return out;
    }
    std::vector<std::string> split_cstr_by_delim(std::string& s, char delim) {
        std::string tmp; 
        std::stringstream ss(s);
        std::vector<std::string> words;

        while(getline(ss, tmp, delim)){
            words.push_back(tmp);
        }

        return words;
    }

    Mesh _EUCAPI LoadMeshFromOBJ(const char *path)
    {
        std::ifstream obj_file(path);

        std::vector<Math::Vector3f> vertices;
        std::vector<Math::Vector3f> normals;
        std::vector<Math::Vector2f> texture_coordinates;
        std::vector<unsigned int> indices;

        std::string line;

        std::string MTLpath;

        if (obj_file.is_open()){
            // TODO: Change OBJ loading from using to many loops
            while (getline(obj_file, line)) {
                std::vector<std::string> _line = split_cstr(line);
                
                if (_line.size() > 1){
                    // Parse the line
                    if (_line.at(0) == "v" && _line.size() > 2) {
                        vertices.push_back(Math::Vector3f(std::stof(_line[1]), std::stof(_line[2]), std::stof(_line[3])));
                    }
                    if (_line.at(0) == "f") {
                        for (size_t i = 1; i < _line.size(); i++) {
                            std::vector<std::string> indices_str = split_cstr_by_delim(_line.at(i), '/');
                            unsigned int val = std::stoi(indices_str.at(0));
                            indices.push_back(val-1);
                        }
                    }
                    if (_line.at(0) == "vt") {
                        texture_coordinates.push_back(Math::Vector2f(std::stof(_line.at(1)), std::stof(_line.at(2))));
                    }
                    if (_line.at(0) == "vn") {
                        normals.push_back(Math::Vector3f(std::stof(_line[1]), std::stof(_line[2]), std::stof(_line[3])));
                    }
                    if (_line.at(0) == "mtllib") {
                        std::string s_path = path;
                        std::vector<std::string> path_split = split_cstr_by_delim(s_path, '\\');
                        path_split.pop_back();

                        std::stringstream ss;
                        for (size_t i = 0; i < path_split.size(); i++) {
                            ss << path_split.at(i) << "\\";
                        }
                        ss << _line.at(1);

                        MTLpath = ss.str();
                    }
                }
            }
        }

        Math::Vector3f verts[vertices.size()];
        for (size_t i = 0; i < vertices.size(); i++){
            verts[i] = vertices.at(i);
        }

        Math::Vector3f norms[normals.size()];
        for (size_t i = 0; i < normals.size(); i++){
            norms[i] = normals.at(i);
        }

        Math::Vector2f texcoords[texture_coordinates.size()];
        for (size_t i = 0; i < texture_coordinates.size(); i++) {
            texcoords[i] = texture_coordinates.at(i);
        }

        unsigned int idxs[indices.size()];
        for (size_t i = 0; i < indices.size(); i++){
            idxs[i] = indices.at(i);
        }

        _internalLogger()->info("Loaded mesh from file");
        _internalLogger()->info(_SIZEOFARRAY(idxs));

        Mesh out(verts, _SIZEOFARRAY(verts), idxs, _SIZEOFARRAY(idxs));
        out.SetTextureCoordinates(texcoords, _SIZEOFARRAY(texcoords));
        out.SetVertexNormals(norms, _SIZEOFARRAY(norms));
        out.MTLpath = MTLpath;

        return out;
    }
    Material LoadMaterialFromMTLFile(const char *path)
    {   
        Material out;
        std::ifstream in(path);

        std::string line;

        if (in.is_open()) {
            while (getline(in, line)) {
                std::vector<std::string> _line = split_cstr(line);
                if (_line.size() > 0) {
                    if (_line.at(0) == "Ka") {
                        out.color = Color(
                            std::stof(_line.at(1)),
                            std::stof(_line.at(2)),
                            std::stof(_line.at(3)),
                            1.0f
                        );
                    }
                    if (_line.at(0) == "map_Kd") {
                        out.texture = Texture::LoadFromFile(_line.at(1).c_str());
                    }
                }
            }
        }
        else {
            std::stringstream ss;
            ss << "Could not open mtl file: " << path;
            _internalLogger()->error(ss.str());
        }
        
        return out;
    }
}
