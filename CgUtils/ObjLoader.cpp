#include "ObjLoader.h"

#include <iostream>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include <map>

#define TINYOBJLOADER_IMPLEMENTATION
#include <CgUtils/tiny_obj_loader.h>

ObjLoader::ObjLoader() {}

ObjLoader::~ObjLoader() {
    clear();
}

void ObjLoader::load(std::string filename) {
    clear();

    tinyobj::ObjReader reader;

    reader.ParseFromFile(filename);
    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    for (size_t i = 0; i < attrib.vertices.size(); i += 3) {
        Vertecies.push_back(glm::vec3(attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2]));
        if (attrib.normals.size() > 0) {
            Normals.push_back(glm::vec3(attrib.normals[i], attrib.normals[i + 1], attrib.normals[i + 2]));
        }
    }

    //convert attrib to temp_indicies and temp_verticies
    for (size_t s = 0; s < shapes.size(); s++) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[v + index_offset];
                Indices.push_back(idx.vertex_index);
            }
            index_offset += fv;
        }
    }
}

int ObjLoader::getIndexCount() { return (int)Indices.size(); }

int ObjLoader::getVertCount() { return (int)Vertecies.size(); }

void ObjLoader::clear() {
    Indices.clear();
    Vertecies.clear();
    Normals.clear();
}

void ObjLoader::getFaceIndexData(std::vector<unsigned int> &arg_indices) {
    arg_indices.clear();
    arg_indices = Indices;
}

void ObjLoader::getPositionData(std::vector<glm::vec3> &arg_verts) {
    arg_verts.clear();
    arg_verts = Vertecies;
}

void ObjLoader::getNormalData(std::vector<glm::vec3> &arg_normals) {
    arg_normals.clear();
    arg_normals = Normals;
}
