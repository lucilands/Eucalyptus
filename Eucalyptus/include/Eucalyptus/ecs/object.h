#pragma once
//#include "component.h"

#include "../vendor/clog/clog.h"

#include <vector>
#include <typeinfo>
#include <memory>



namespace Eucalyptus {
    class Component;

    class Object {
        public:
            Object() {};

            void Update();
            void Awake();

            template <class T> void AddComponent() {
                static_assert(std::is_base_of<Component, T>::value, "AddComponent needs a Component");
                m_components.push_back(std::make_unique<T>(T(this)));
            }

            template <class T, typename ...Args> void AddComponent(Args &&...args) {
                static_assert(std::is_base_of<Component, T>::value, "AddComponent needs a Component");
                m_components.push_back(std::make_unique<T>(T(this, std::forward<Args>(args)...)));
            }

            template <class T> T* GetComponent() {
                for (unsigned int i = 0; i < m_components.size(); i++) {
                    if (typeid(*m_components[i]) == typeid(T)) {
                        return static_cast<T*>(m_components[i].get());
                    }
                }
                clog(CLOG_WARNING, "Component %s is not attached to object!", typeid(T).name());
                return NULL;
            }

            template <class T> bool HasComponent() {
                for (unsigned int i = 0; i < m_components.size(); i++) {
                    if (typeid(*m_components[i]) == typeid(T)) return true;
                }
                return false;
            }

            void Enable() {enabled = true;}
            void Disable() {enabled = false;}
            void Toggle() {enabled = !enabled;}

            bool enabled = true;
        private:
            std::vector<std::unique_ptr<Component>> m_components;
    };

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

        protected:
            Object *m_parent;
    };
}