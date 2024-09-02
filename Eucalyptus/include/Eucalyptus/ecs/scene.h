#pragma once
#include "object.h"

#include <vector>


namespace Eucalyptus {
    class Scene {
        public:
            Scene() {}

            void Awake();
            void Update();
            void AddObject(Object *obj);

        private:
            std::vector<Object*> m_objects;
    };
}