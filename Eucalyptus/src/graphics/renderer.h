#pragma once
#include "shader/shader.h"
#include "mesh.h"

#include "color/color.h"
#include "material.h"

#include "window/window.h"

#include "math/transform.h"

#include "api.h"


namespace Eucalyptus {
    class _EUCAPI MeshRenderer {
    public:
        MeshRenderer(Mesh _mesh, Shader _shader, Color _color, Texture _texture);
        MeshRenderer(Mesh _mesh, Shader _shader, Color _color);
        MeshRenderer(Mesh _mesh, Shader _shader, Texture _texture);
        MeshRenderer(Mesh _mesh, Shader _shader);

        void Render(Window& window);
        Mesh mesh;
        Shader shader;
        Math::Transform transform = Math::Transform();

        Material material;
    };
}