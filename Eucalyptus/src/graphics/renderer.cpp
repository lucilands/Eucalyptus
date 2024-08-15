#include "renderer.h"
#include "log/logger.h"

#include "globals.h"

#include "error/error.h"

#include "meshloader/loader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Eucalyptus {
    MeshRenderer::MeshRenderer(Mesh _mesh, Shader _shader, Color _color, Texture _texture): mesh(_mesh), shader(_shader) {
        if (!_GLINIT){
            _EUC_LOG_ERR(EUCInitError("Cannot create MeshRenderer because: Eucalyptus window is not initialized yet").ToString().c_str());
            _EUC_LOG_INFO("Aborting shader creation");
            return;
        }
        _EUC_LOG_INFO("Creating mesh renderer");
        material = LoadMaterialFromMTLFile(mesh.MTLpath.c_str());
        material.color = _color;
        material.texture = _texture;

        mesh._SetObjects();
    }
    MeshRenderer::MeshRenderer(Mesh _mesh, Shader _shader, Color _color): mesh(_mesh), shader(_shader) {
        if (!_GLINIT){
            _EUC_LOG_ERR(EUCInitError("Cannot create MeshRenderer because: Eucalyptus window is not initialized yet").ToString().c_str());
            _EUC_LOG_INFO("Aborting shader creation");
            return;
        }
        _EUC_LOG_INFO("Creating mesh renderer");
        material = LoadMaterialFromMTLFile(mesh.MTLpath.c_str());
        material.color = _color;

        mesh._SetObjects();
    }
    MeshRenderer::MeshRenderer(Mesh _mesh, Shader _shader, Texture _texture): mesh(_mesh), shader(_shader) {
        if (!_GLINIT){
            _EUC_LOG_ERR(EUCInitError("Cannot create MeshRenderer because: Eucalyptus window is not initialized yet").ToString().c_str());
            _EUC_LOG_INFO("Aborting shader creation");
            return;
        }
        _EUC_LOG_INFO("Creating mesh renderer");
        material = LoadMaterialFromMTLFile(mesh.MTLpath.c_str());
        material.texture = _texture;
        
        mesh._SetObjects();
    }
    MeshRenderer::MeshRenderer(Mesh _mesh, Shader _shader): mesh(_mesh), shader(_shader) {
        if (!_GLINIT){
            _EUC_LOG_ERR(EUCInitError("Cannot create MeshRenderer because: Eucalyptus window is not initialized yet").ToString().c_str());
            _EUC_LOG_INFO("Aborting shader creation");
            return;
        }
        _EUC_LOG_INFO("Creating mesh renderer");
        material = LoadMaterialFromMTLFile(mesh.MTLpath.c_str());
        mesh._SetObjects();    }

    void MeshRenderer::Render(Window& window) {
        material.texture.Bind();

        shader.Use();
        shader.SetUniformVector3f("_color", material.color.ToVector3f());
        shader.SetUniformVector3f("_emission_color", {1.0f, 1.0f, 1.0f});

        shader.SetUniformView("_view", transform.GetView());
        shader.SetUniformMat4("_transform", transform.GetTransform());
        shader.SetUniformMat4("_projection", transform.GetProjection(window));
        

        mesh._Draw();
    }
}
