#ifndef OPEN_GL_H
#define OPEN_GL_H

class OpenGL {
    public:
        enum Colour {
            WHITE = 0xFFFFFF,
            BLACK = 0x000000,
            RED = 0xFF0000,
            GREEN = 0x008000,
            BLUE = 0x0000FF,
        };

        OpenGL(int size_pixels, int size_meters, const char* name);
        void draw_square(Colour colour, float x, float y, float size);
        void draw_circle(Colour colour, float x, float y, float r);
        void update();
        void clear();

    private:
        float m_to_pix(float m);
        void set_colour(Colour colour);

        int size_meters;
};

#endif
