#include <Eucalyptus/components/mesh.h>

#include <Eucalyptus/components/transform.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


namespace Eucalyptus {
    Mesh::Mesh(Object *_, Shader sh) : Component(_), m_shader(sh) {
        glGenBuffers(1, &m_VBO);
        glGenVertexArrays(1, &m_VAO);

        this->RequireComponent<Transform>();
    }

    void Mesh::Awake() {
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void Mesh::Update() {
        m_shader.SetMat4("transform", m_parent->GetComponent<Transform>()->_get_transform());
        m_shader.Use();
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}