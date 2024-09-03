#pragma once

#include <vector>



namespace Eucalyptus {
    class Model {
        public:
            Model() {}
            Model(std::vector<float> verts) : m_verts(verts) {vert_len = verts.size();}
            Model(std::vector<float> verts, std::vector<unsigned int> indices) : m_verts(verts), m_indices(indices) {vert_len = verts.size(); indices_len = indices.size();}
            float *verts_data() {return m_verts.data();}
            unsigned int *indices_data() {return m_indices.data();}

            int vert_len = 0;
            int indices_len = 0;
        private:
            std::vector<float> m_verts;
            std::vector<unsigned int> m_indices;
    };

    namespace Prefabs {
        static Model Triangle({0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f});
        static Model Quad({ 0.5f,  0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           -0.5f,  0.5f, 0.0f}, 
                        {0, 1, 3,
                         1, 2, 3});
        
        static Model Cube({
             0.5f,  0.5f, 0.5f,
             0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f,  0.5f, 0.5f,

             0.5f,   0.5f, -0.5f,
             0.5f,  -0.5f, -0.5f,
            -0.5f,  -0.5f, -0.5f,
            -0.5f,   0.5f, -0.5f
        },
        {0, 1, 3,
         1, 2, 3,

         4, 5, 7,
         5, 6, 7,
         
         0, 1, 4,
         4, 5, 1,
         
         2, 3, 6,
         6, 7, 3,
         
         0, 3, 7,
         0, 5, 7,
         
         1, 2, 6});
    }
}