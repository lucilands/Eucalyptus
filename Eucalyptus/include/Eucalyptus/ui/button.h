#include "panel.h"




namespace Eucalyptus {
    typedef void(*ButtonFunc)(Object*);
    class Button : public Component {
        public:
            Button(Object *_);
            Button(Object *_, ButtonFunc on_click);
            void Update();
            bool is_hovered;
            ButtonFunc on_click;
    };
}