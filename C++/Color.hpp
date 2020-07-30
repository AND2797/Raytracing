#ifndef COLOR_H
#define COLOR_H
#include "Vec3.hpp"


class Color{
    public:
        double r;
        double g;
        double b;

    public:
        Color();
        Color(double r_val, double g_val, double b_val);
        static Color add(Color color1, Color color2);
        static Color scalar_mul(Color color1, double scalar);
};

#endif