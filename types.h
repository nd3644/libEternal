#ifndef TYPES_H
#define TYPES_H

namespace Eternal {

    struct RGBA {
        RGBA() {
            r = g = b = a = 1.0f;
        }
        RGBA(float r, float g, float b, float a) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
        float r;
        float g;
        float b;
        float a;
    };

    struct Vec2 {
        Vec2() {
            x = y = 0;
        }
        float x, y;
    };

    struct Vec3 {
        Vec3() {
            x = y = z = 0;
        }
        float x, y, z;
    };

    struct Quad {
        public:
            Quad() {
                v[0].x = v[0].y = 0;
                v[1].x = v[1].y = 0;
                v[2].x = v[2].y = 0;
                v[3].x = v[3].y = 0;
            }
            Quad(float x, float y, float w, float h) {
                v[0].x = x;      v[0].y = y;
                v[1].x = x + w;  v[1].y = y;
                v[2].x = x + w;  v[2].y = y + h;
                v[3].x = x;      v[3].y = y + h;
            }
            Vec2 v[4];
    };

    struct Triangle {
        public:
            Vec2 v[3];
    };
}

#endif