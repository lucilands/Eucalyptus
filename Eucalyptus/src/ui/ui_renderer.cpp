#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Eucalyptus/ui/ui_renderer.h>
#include <Eucalyptus/ui/panel.h>

#include <Eucalyptus/window.h>
#include <Eucalyptus/ecs/scene.h>
#include <Eucalyptus/components/transform2d.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ui_shaders.h"



namespace Eucalyptus {
    UI_Renderer::UI_Renderer(Object *_) : Component(_), m_shader(vert_src, frag_src) {
        RequireComponent<Transform2D>();
        //static_assert(std::is_same_v<decltype(*_), Panel>, "UI_Renderer compoenent can only be attached to subclasses of or the class Panel");
        
        unsigned int VBO;
        float vertices[] = { 
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 
    
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &this->m_VAO);
        glGenBuffers(1, &VBO);
    
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->m_VAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);  
        glBindVertexArray(0);
    }

    void UI_Renderer::Update() {
        m_shader.Use();
        Transform2D *t = m_parent->GetComponent<Transform2D>();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(t->position.x, t->position.y, 0.0f));  

        model = glm::translate(model, glm::vec3(0.5f * t->size.x, 0.5f * t->size.y, 0.0f)); 
        model = glm::rotate(model, glm::radians(t->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * t->size.x, -0.5f * t->size.y, 0.0f));

        model = glm::scale(model, glm::vec3(t->size.x, t->size.y, 1.0f)); 
        m_projection = glm::ortho(0.0f, static_cast<float>(Eucalyptus::window->size.x), static_cast<float>(Eucalyptus::window->size.y), 0.0f, -1.0f, 1.0f);

        m_shader.SetMat4("model", model);
        m_shader.SetMat4("projection", m_projection);
        m_shader.SetVec4("color", this->color);
        m_shader.SetVec2("resolution", Vector2f(Eucalyptus::window->size.x, Eucalyptus::window->size.y));
        m_shader.SetVec2("size", t->size);
        m_shader.SetFloat("radius", this->radius);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}