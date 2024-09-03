#pragma once

#include <vector>
#include "../math/vertex.h"


namespace Eucalyptus {
    class Mesh {
        public:
            Mesh() {}
            Mesh(std::vector<Vertex> verts) : m_verts(verts) {vert_len = verts.size();}
            Mesh(std::vector<Vertex> verts, std::vector<unsigned int> indices) : m_verts(verts), m_indices(indices) {vert_len = verts.size(); indices_len = indices.size();}
            Vertex *verts_data() {return m_verts.data();}
            unsigned int *indices_data() {return m_indices.data();}

            int vert_len = 0;
            int indices_len = 0;
        private:
            std::vector<Vertex> m_verts;
            std::vector<unsigned int> m_indices;
    };

    namespace Prefabs {
        static Mesh Triangle({{0.5f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}});
        static Mesh Quad({ 
            {0.5f,   0.5f, 0.0f, 1.0f, 1.0f},
            {0.5f,  -0.5f, 0.0f, 1.0f, 0.0f},
            {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f},
            {-0.5f,  0.5f, 0.0f, 0.0f, 1.0f}
            }, 
            {0, 1, 3,
            1, 2, 3});

         static Mesh Cube({
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},

            {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},

            {{0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f, -0.5f,  0.5f}, {0.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},

            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f,  0.5f}, {1.0f, 1.0f}},
            {{0.5f, -0.5f,  0.5f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}}
         });
    }
}