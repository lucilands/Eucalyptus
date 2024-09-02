#pragma once
#include "object.h"


/*
namespace Eucalyptus {
    class Object;

    class Component {
        public:
            virtual void Awake() {};
            virtual void Update() {};
            
            Component(Object *parent) : m_parent(parent) {}
            template <class T> void RequireComponent() {
                if (!m_parent->HasComponent<T>()) {
                    m_parent->AddComponent<T>();
                }
            }

        private:
            Object *m_parent;
    };
}*/