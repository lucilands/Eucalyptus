#pragma once


#include "material.h"
#include "shader.h"
#include "mesh.h"


namespace Eucalyptus {
    class Model {
        public:
            Model(Material mt, Mesh mh) : m_material(mt), m_mesh(mh) {};

            Material GetMaterial() {return m_material;}
            Mesh GetMesh() {return m_mesh;}
        private:
            Material m_material;
            Mesh m_mesh;
    };
}