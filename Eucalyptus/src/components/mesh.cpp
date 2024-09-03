#include <Eucalyptus/ecs/object.h>
#include <Eucalyptus/components/mesh.h>

#include <Eucalyptus/components/transform.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


namespace Eucalyptus {
    Mesh::Mesh(Object *_, Material mat, Model md) : Component(_), m_material(mat), m_model(md) {
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
        glGenVertexArrays(1, &m_VAO);

        this->RequireComponent<Transform>();
    }

    void Mesh::Awake() {
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_model.vert_len * sizeof(Vertex), m_model.verts_data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.indices_len * sizeof(unsigned int), m_model.indices_data(), GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, tex_coord)));
        glEnableVertexAttribArray(1);
    }

    void Mesh::Update() {
        m_material.GetShader().SetMat4("_transform", m_parent->GetComponent<Transform>()->_get_transform());
        m_material.Use();
        glBindVertexArray(m_VAO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        if (m_model.indices_len > 0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glDrawElements(GL_TRIANGLES, m_model.indices_len, GL_UNSIGNED_INT, 0);
        }
        else glDrawArrays(GL_TRIANGLES, 0, m_model.vert_len);
    }
}