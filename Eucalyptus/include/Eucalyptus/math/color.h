#pragma once


namespace Eucalyptus {
    class Color {
        public:
            Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

            float r;
            float g;
            float b;
            float a;
    };
    namespace Colors {
         const Color White(1.0, 1.0, 1.0, 1.0);
         const Color Black(0.0, 0.0, 0.0, 1.0);

         const Color Red(1.0, 0.0, 0.0, 1.0);
         const Color Green(0.0, 1.0, 0.0, 1.0);
         const Color Blue(0.0, 0.0, 1.0, 1.0);

         const Color LearnOpenGL(0.2, 0.3, 0.3, 1.0);
         
         const Color DarkGray(0.1, 0.1, 0.1, 1.0);
         const Color LightGray(0.6, 0.6, 0.6, 1.0);
    }
}