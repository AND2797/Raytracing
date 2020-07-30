#ifndef LIGHT_H
#define LIGHT_H
#include "Vec3.hpp"
#include "Color.hpp"
class Light{

    public:
        Vec3 source;
        Color color;

    public:
        Light(Vec3 light_source, Color light_color);

};

#endif