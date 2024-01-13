#include "mesh.h"

#include "log/logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iterator>




namespace Eucalyptus {
    Mesh Mesh::Cube = Mesh();
    Mesh Mesh::Quad = Mesh();

    Mesh::Mesh(Math::Vector3f Vertices[], size_t vertexArraySize, unsigned int Indices[], size_t indiceArraySize ) {
        //_EUC_LOG_INFO("Creating mesh");
        if (vertexArraySize != 0)
            SetVertices(Vertices, vertexArraySize);
        if (indiceArraySize != 0)
            SetIndices(Indices, indiceArraySize);
        else
            m_indiceSize = 0;
        //_EUC_LOG_INFO("Created mesh");
        for (size_t i = 0; i < vertexArraySize; i++) {
            Vertex v;
            v.position = Vertices[i];
            vertices.at(i).color = Math::Vector3f(1.0f, 1.0f, 1.0f);
            vertices.at(i).texture_coordinate = Math::Vector2f(1.0f, 1.0f);
            vertices.push_back(v);
        }
            
        
    }

    void Mesh::SetVertices(Math::Vector3f vertice_array[], size_t size)
    {        
        _EUC_LOG_INFO("Updating mesh vertice array");
        m_verticeSize = size;

        vertices.clear();
        for (size_t i = 0; i < size; i++) {
            Vertex v;
            v.position = vertice_array[i];
            vertices.push_back(v);
        }
    }
    void Mesh::SetIndices(unsigned int indice_array[], size_t size)
    {        
        _EUC_LOG_INFO("Updating mesh indice array");
        m_indiceSize = size;

        indices.clear();
        for (size_t i = 0; i < size; i++)
            indices.push_back(indice_array[i]);
    }
    void Mesh::SetVertexColors(Math::Vector3f vertexColors[], size_t size) {
        _EUC_LOG_INFO("Updating mesh vertex color array");

        for (size_t i = 0; i < size; i++)
            vertices.at(i).color = vertexColors[i];
            
    }
    void Mesh::SetTextureCoordinates(Math::Vector2f textureCoords[], size_t size) {
        _EUC_LOG_INFO("Updating mesh texture coordinates");

        for (size_t i = 0; i < size; i++)
            vertices.at(i).texture_coordinate = textureCoords[i];
    }
    void Mesh::SetVertexNormals(Math::Vector3f norms[], size_t size) {
        _EUC_LOG_INFO("Updating mesh normals");

        for (size_t i = 0; i < size; i++)
            vertices.at(i).normal = norms[i];
    }
    void Mesh::_SetObjects()
    {
        _EUC_LOG_INFO("Creating mesh in memory");

        glGenVertexArrays(1, &vertexArrayObject);
        glGenBuffers(1, &vertexBufferObject);
        glGenBuffers(1, &elementArrayBuffer);

        glBindVertexArray(vertexArrayObject);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);  
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indiceSize * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); 
        

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coordinate));


        glBindVertexArray(0);
    }
    void Mesh::_Draw() {
        glBindVertexArray(vertexArrayObject);
        

        if (m_indiceSize != 0)
            glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, m_verticeSize);
    }
    void Mesh::_InitializeMeshes() {
        Math::Vector3f vertices_quad[] = {
            { 0.5f,  0.5f, 0.0f},
            { 0.5f, -0.5f, 0.0f},
            {-0.5f, -0.5f, 0.0f},
            {-0.5f,  0.5f, 0.0f}
        };
        Math::Vector2f texture_coordinates_quad[] = {
            {1.0f, 1.0f},
            {1.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 1.0f}
        };
        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        Quad = Mesh(vertices_quad, 4, indices, 6);
        Quad.SetTextureCoordinates(texture_coordinates_quad, 4);


        // TODO: Fix texture mapping, rather without adding more vertices
        unsigned int indices_cube[] {
            0, 1, 3,
            1, 2, 3,

            4, 5, 7,
            5, 6, 7,

            7, 3, 4,
            3, 0, 4,

            6, 2, 5,
            2, 1, 5,

            0, 1, 4,
            1, 5, 4,

            3, 2, 7,
            2, 6, 7
        };

        Math::Vector3f vertices_cube[] = {
            { -0.5f, -0.5f, -0.5f },
            {  0.5f, -0.5f, -0.5f },
            {  0.5f,  0.5f, -0.5f },
            { -0.5f,  0.5f, -0.5f },

            { -0.5f, -0.5f,  0.5f },
            {  0.5f, -0.5f,  0.5f },
            {  0.5f,  0.5f,  0.5f },
            { -0.5f,  0.5f,  0.5f }
        };
        
        Math::Vector2f texture_coordinates_cube[] {
            { 0.0f, 0.0f },
            { 0.0f, 1.0f },
            { 1.0f, 1.0f },
            { 1.0f, 0.0f },

            { 0.0f, 0.0f },
            { 0.0f, 1.0f },
            { 1.0f, 1.0f },
            { 1.0f, 0.0f }
        };

        Cube = Mesh(vertices_cube, 8, indices_cube, 36);
        Cube.SetTextureCoordinates(texture_coordinates_cube, 8);
    }
}