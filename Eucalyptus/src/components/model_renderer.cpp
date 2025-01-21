#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Eucalyptus/ecs/object.h>

#include <Eucalyptus/components/model_renderer.h>
#include <Eucalyptus/components/transform.h>

#include <Eucalyptus/graphics/mesh.h>

#include <iostream>


namespace Eucalyptus {
    ModelRenderer::ModelRenderer(Object *_, Model md) : Component(_), m_model(md) {
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
        glGenVertexArrays(1, &m_VAO);

        this->RequireComponent<Transform>();
    }

    void ModelRenderer::Awake() {
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_model.GetMesh().vert_len * sizeof(Vertex), m_model.GetMesh().verts_data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.GetMesh().indices_len * sizeof(unsigned int), m_model.GetMesh().indices_data(), GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, tex_coord)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
        glEnableVertexAttribArray(2);
    }

    void ModelRenderer::Update() {
        m_model.GetMaterial().GetShader().SetMat4("_transform", m_parent->GetComponent<Transform>()->_get_transform());
        m_model.GetMaterial().GetShader().SetFloat("_time", glfwGetTime());
        m_model.GetMaterial().Use();
        glBindVertexArray(m_VAO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        if (m_model.GetMesh().indices_len > 0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glDrawElements(GL_TRIANGLES, m_model.GetMesh().indices_len, GL_UNSIGNED_INT, 0);
        }
        else glDrawArrays(GL_TRIANGLES, 0, m_model.GetMesh().vert_len);
    }
}