#ifndef VEC3_H
#define VEC3_H
#include <cmath>

class Vec3{
    public:
        double x;
        double y; 
        double z;
        

    public:
        Vec3();
        Vec3(double x_val, double y_val, double z_val);
        // Vec3(double x_val, double y_val, double z_val, double x_d, double y_d, double z_d);
        static double magnitude(Vec3 vec);
        static Vec3 normalize(Vec3 vec);
        static double dot(Vec3 vec1, Vec3 vec2);
        static Vec3 add(Vec3 vec1, Vec3 vec2);
        static Vec3 sub(Vec3 vec1, Vec3 vec2);
        static Vec3 scalar_sub(Vec3 vec1, double scalar);
        static Vec3 scalar_mul(Vec3 vec, double val);
        static Vec3 scalar_div(Vec3 vec, double val);
        static void print(Vec3 vec);
};


#endif


