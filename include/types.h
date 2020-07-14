#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <math.h>

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

    struct Vec2i {
        Vec2i() {
            x = y = 0;
        }
        Vec2i(int ix, int iy) {
            x = ix;
            y = iy;
        }
        int x, y;
    };

    class Vec2 {
        public:

        Vec2() {
            x = y = 0;
        }
        Vec2(float fx, float fy) {
            x = fx;
            y = fy;
        }

        void Normalize() {
            float f = Magnitude();
            if(f != 0) {
             x /= f;
                y /= f;
            }
        }

        float Magnitude() {
            return sqrtf((x * x) + (y * y));
        }

        float Dot(Vec2 b) {
            return (x * b.x) + (y * b.y);
        }

        void operator+=(Vec2 b) {
            x += b.x;
            y += b.y;
        }

        void operator-=(Vec2 b) {
            x -= b.x;
            y -= b.y;
        }

        void operator/=(Vec2 b) {
            x /= b.x;
            y /= b.y;
        }

        void operator*=(Vec2 b) {
            x *= b.x;
            y *= b.y;
        }

        Vec2 operator+(Vec2 b) {

            Vec2 tmp;

            tmp.x = x + b.x;
            tmp.y = y + b.y;

            return tmp;
        }

        Vec2 operator-(Vec2 b) {

            Vec2 tmp;

            tmp.x = x - b.x;
            tmp.y = y - b.y;

            return tmp;
        }
        
        Vec2 operator*(float scalar) {
            Vec2 tmp;
            tmp.x = x * scalar;
            tmp.y = y * scalar;

            return tmp;
        }

        Vec2 operator/(float scalar) {
            Vec2 tmp;
            tmp.x = x / scalar;
            tmp.y = y / scalar;
            return tmp;
        }

        float x, y;
    };

    struct Vec3 {
        Vec3() {
            x = y = z = 0;
        }
        float x, y, z;
    };

    struct Rect {
        Rect() {
            x = y = 0;
            w = h = 32;
        }
        Rect(float fx, float fy, float fw, float fh) {
            x = fx;
            y = fy;
            w = fw;
            h = fh;
        }
        float x, y;
        float w, h;

        bool IsColliding(Rect &b) {
            if (x > b.x + b.w
                || x + w < b.x
                || y > b.y + b.h
                || y + h < b.y) {
                return false;
            }
            return true;
        }
        
        bool IsColliding(Rect &b, Vec2 &normal) {

            if (x > b.x + b.w
                || x + w < b.x
                || y > b.y + b.h
                || y + h < b.y) {
                return false;
            }

            // temporary translate to center origin
            x += w / 2;
            y += h / 2;

            b.x += b.w / 2;
            b.y += b.h / 2;


            normal.x = 0;
            normal.y = 0;

            Vec2 Distance;
            Vec2 absDistance;

            float XMagnitute;
            float YMagnitute;

            Distance.x = b.x - x;
            Distance.y = b.y - y;

            float XAdd = (b.w + w) / 2.0f;
            float YAdd = (b.h + h) / 2.0f;


            absDistance.x = (Distance.x < 0.0f) ? -Distance.x : Distance.x;
            absDistance.y = (Distance.y < 0.0f) ? -Distance.y : Distance.y;

            XMagnitute = XAdd - absDistance.x;
            YMagnitute = YAdd - absDistance.y;


            // check most significant overlap
            if (XMagnitute < YMagnitute) {
                normal.x = (Distance.x > 0) ? -XMagnitute : XMagnitute;
            }
            else {
                normal.y = (Distance.y > 0) ? -YMagnitute : YMagnitute;
            }


            // put back origin
            x -= w / 2;
            y -= h / 2;
            
            b.x -= b.w / 2;
            b.y -= b.h / 2;
            return true;
        }
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

            void FromRect(Eternal::Rect &r) {
                v[0].x = r.x;  v[0].y = r.y;
                v[1].x = r.x + r.w;  v[1].y = r.y;
                v[2].x = r.x + r.w;  v[2].y = r.y + r.h;
                v[3].x = r.x;  v[3].y = r.y + r.h;
            }

            Vec2 v[4];
    };

    struct Triangle {
        public:
            Vec2 v[3];
    };
}

#endif
