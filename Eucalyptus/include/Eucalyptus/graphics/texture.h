#pragma once




namespace Eucalyptus {
    class Texture {
        public:
            Texture(const char *path);
            Texture(const unsigned char *data);

            void Use();

        private:
            unsigned int m_ID;
    };
}