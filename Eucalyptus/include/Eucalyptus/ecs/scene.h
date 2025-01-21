#pragma once
#include "object.h"

#include "../graphics/camera.h"

#include <vector>


namespace Eucalyptus {
    class Scene {
        public:
            Scene() {}

            void Awake();
            void Update();
            void AddObject(Object *obj);

            Camera *GetCamera() {return &m_camera;};

        private:
            std::vector<Object*> m_objects;
            Camera m_camera;
    };
}