#pragma once
#include <stdlib.h>
#include <vector>

#include "math/vector.h"

#include "graphics/material.h"
#include "api.h"

namespace Eucalyptus{
    struct _EUCAPI Vertex {
        Math::Vector3f position;
        Math::Vector3f normal;
        Math::Vector3f color;
        Math::Vector2f texture_coordinate;
    };

    // TODO: Implement preset meshes
    class _EUCAPI Mesh {
    public:
        Mesh(Math::Vector3f Vertices[] = {0}, size_t vertexArraySize = 0, unsigned int Indices[] = {0}, size_t indiceArraySize = 0);
        std::vector<unsigned int> indices;

        std::vector<Vertex> vertices;


        void SetVertices(Math::Vector3f new_vertice_array[], size_t size);
        void SetIndices(unsigned int new_indice_array[], size_t size);

        void SetVertexColors(Math::Vector3f vertexColors[], size_t size);
        void SetTextureCoordinates(Math::Vector2f textureCoords[], size_t size);

        void SetVertexNormals(Math::Vector3f norms[], size_t size);

        void _SetObjects();
        void _Draw();
        static void _InitializeMeshes();

        unsigned int vertexArrayObject, vertexBufferObject, elementArrayBuffer;

        static Mesh Cube;
        static Mesh Quad;

        // Temporary value, mainly to fix a seg-fault
        std::string MTLpath;
    private:
        size_t m_verticeSize;
        size_t m_indiceSize = 0;
    };
}