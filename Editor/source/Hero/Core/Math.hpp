#pragma once

#include<cstdint>
#include<iostream>
#include<cmath>

namespace Hero
{

#define COMP_EPSILON 0.0001f
#define PI 3.141596f

template<typename T>
inline T min(T a, T b)
{
    return (a < b)? a : b;
}

template<typename T>
inline T max(T a, T b)
{
    return (a > b)? a : b;
}

HERO float deg2rad(float degree);
HERO float rad2deg(float radians);
HERO int clamp(int value, int min, int max);
HERO float clamp(float value, float min, float max);
HERO float lerp(float a, float b, float t);

struct Int2
{
    int x, y;

    constexpr Int2():x(0),y(0){}
    constexpr Int2(int _x, int _y):x(_x),y(_y){}

    constexpr static inline Int2 zero(){return Int2(0, 0); } 
    constexpr static inline Int2 one(){return Int2(1, 1); } 
    constexpr static inline Int2 right(){return Int2(1, 0); } 
    constexpr static inline Int2 up(){return Int2(0, 1); } 

    HERO void operator+=(const Int2& rhs);
    HERO void operator-=(const Int2& rhs);
    HERO bool operator==(const Int2& rhs);
    HERO bool operator!=(const Int2& rhs);
};

HERO Int2 operator+(const Int2& lhs, const Int2& rhs);
HERO Int2 operator-(const Int2& lhs, const Int2& rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Int2& v);

HERO int dotProduct(Int2 A, Int2 B);
HERO float distance(Int2 A, Int2 B);

struct Int3
{
    int x, y, z;

    constexpr Int3():x(0),y(0),z(0){}
    constexpr Int3(int _x, int _y, int _z):x(_x),y(_y),z(_z){}

    constexpr static inline Int3 zero(){return Int3(0, 0, 0); } 
    constexpr static inline Int3 one(){return Int3(1, 1, 1); }

    HERO void operator+=(const Int3& rhs);
    HERO void operator-=(const Int3& rhs);
    HERO bool operator==(const Int3& rhs);
    HERO bool operator!=(const Int3& rhs);
};

HERO Int3 operator+(const Int3& lhs, const Int3& rhs);
HERO Int3 operator-(const Int3& lhs, const Int3& rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Int3& v);

HERO int dotProduct(Int3 A, Int3 B);
HERO float distance(Int3 A, Int3 B);

struct Int4
{
    int x, y, z, w;

    constexpr Int4():x(0),y(0),z(0),w(0){}
    constexpr Int4(int _x, int _y, int _z, int _w):x(_x),y(_y),z(_z),w(_w){}

    constexpr static inline Int4 zero(){return Int4(0, 0, 0, 0); } 
    constexpr static inline Int4 one(){return Int4(1, 1, 1, 1); };

    HERO void operator+=(const Int4& rhs);
    HERO void operator-=(const Int4& rhs);
    HERO bool operator==(const Int4& rhs);
    HERO bool operator!=(const Int4& rhs);
};

HERO Int4 operator+(const Int4& lhs, const Int4& rhs);
HERO Int4 operator-(const Int4& lhs, const Int4& rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Int4& v);

struct Float2
{
    float x, y;
    
    constexpr Float2():x(0.0f),y(0.0f){}
    constexpr Float2(float _x, float _y):x(_x),y(_y){}

    constexpr static inline Float2 zero(){return Float2(0.0f, 0.0f); } 
    constexpr static inline Float2 one(){return Float2(1.0f, 1.0f); } 
    constexpr static inline Float2 right(){return Float2(1.0f, 0.0f); } 
    constexpr static inline Float2 up(){return Float2(0.0f, 1.0f); } 

    HERO float length();
    HERO void normalize();
    HERO Float2 normalized(); 

    HERO Float2& operator+=(const Float2& rhs);
    HERO Float2& operator-=(const Float2& rhs);
    HERO Float2& operator*=(float rhs);
    HERO Float2& operator/=(float rhs);
    HERO bool operator==(const Float2& rhs);
    HERO bool operator!=(const Float2& rhs);
};

HERO Float2 operator+(const Float2& lhs, const Float2& rhs);
HERO Float2 operator-(const Float2& lhs, const Float2& rhs);
HERO Float2 operator*(const Float2& lhs, float rhs);
HERO Float2 operator/(const Float2& lhs, float rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Float2& v);

HERO float dotProduct(Float2 A,Float2 B);
HERO float distance(Float2 A, Float2 B);
HERO Float2 rotate(Float2 vector, float angle);

struct Float4;

struct Float3
{
    float x, y, z;

    constexpr Float3():x(0.0f),y(0.0f),z(0.0f){}
    constexpr Float3(float _x, float _y, float _z):x(_x),y(_y),z(_z){}
    HERO Float3(const Float4& vector);

    constexpr static inline Float3 zero(){return Float3(0.0f, 0.0f, 0.0f); } 
    constexpr static inline Float3 one(){return Float3(1.0f, 1.0f, 1.0f); } 
    constexpr static inline Float3 forward(){return Float3(0.0f, 0.0f, 1.0f); } 
    constexpr static inline Float3 up(){return Float3(0.0f, 1.0f, 0.0f); } 
    constexpr static inline Float3 right(){return Float3(1.0f, 0.0f, 0.0f); } 

    HERO float length();
    HERO void normalize();
    HERO Float3 normalized(); 

    HERO Float3& operator+=(const Float3& rhs);
    HERO Float3& operator-=(const Float3& rhs);
    HERO Float3& operator*=(float rhs);
    HERO Float3& operator/=(float rhs);
    HERO bool operator==(const Float3& rhs);
    HERO bool operator!=(const Float3& rhs);
};

HERO Float3 operator+(const Float3& lhs, const Float3& rhs);
HERO Float3 operator-(const Float3& lhs, const Float3& rhs);
HERO Float3 operator*(const Float3& lhs, float rhs);
HERO Float3 operator*(const Float3& lhs, const Float3& rhs);
HERO Float3 operator/(const Float3& lhs, float rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Float3& v);

HERO float dotProduct(Float3 A, Float3 B);
HERO Float3 crossProduct(Float3 A, Float3 B);
HERO Float3 lerp(Float3 A, Float3 B, float t);
HERO float distance(Float3 A, Float3 B);

struct Float4
{
    float x, y, z, w;

    constexpr Float4():x(0.0f),y(0.0f),z(0.0f),w(0.0f){}
    constexpr Float4(float _x, float _y, float _z, float _w):x(_x),y(_y),z(_z),w(_w){}
    HERO Float4(const Float3& vector);

    constexpr static inline Float4 zero(){return Float4(0.0f, 0.0f, 0.0f, 0.0f); } 
    constexpr static inline Float4 one(){return Float4(1.0f, 1.0f, 1.0f, 1.0f); } 

    HERO float length();
    HERO void normalize();
    HERO Float4 normalized(); 

    HERO Float4& operator+=(const Float4& rhs);
    HERO Float4& operator-=(const Float4& rhs);
    HERO Float4& operator*=(float rhs);
    HERO Float4& operator/=(float rhs);
    HERO bool operator==(const Float4& rhs);
    HERO bool operator!=(const Float4& rhs);
};

HERO Float4 operator+(Float4 lhs, const Float4& rhs);
HERO Float4 operator-(Float4 lhs, const Float4& rhs);
HERO Float4 operator*(Float4 lhs, float rhs);
HERO Float4 operator/(Float4 lhs, float rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Float4& v);

struct Quaternion
{
    float w, x, y, z;

    Quaternion():w(1.0f), x(0.0f), y(0.0f), z(0.0f){}
    HERO Quaternion(float rotX, float rotY, float rotZ);
    HERO Quaternion(const Float3& vector);
    HERO Quaternion(float angle, const Float3& axis);

    HERO Float3 ToEuler() const;

    HERO Quaternion& operator+=(const Quaternion& rhs);
    HERO Quaternion& operator-=(const Quaternion& rhs);
    HERO Quaternion& operator*=(const Quaternion& rhs);
    HERO bool operator==(const Quaternion& rhs);
    HERO bool operator!=(const Quaternion& rhs);
};

HERO Quaternion operator~(const Quaternion& rhs);
HERO Quaternion operator+(Quaternion lhs, const Quaternion& rhs);
HERO Quaternion operator-(Quaternion lhs, const Quaternion& rhs);
HERO Quaternion operator*(Quaternion lhs, const Quaternion& rhs);
HERO Quaternion operator*(const Quaternion& lhs, const Float3& rhs);
HERO std::ostream& operator<< (std::ostream& stream, Quaternion& q);

struct Matrix2x2
{
    Float2 col[2];

    constexpr static inline Matrix2x2 identity(){
    return {Float2(1.0f,0.0f),
            Float2(0.0f,1.0f)};
    }

    HERO float determinant();
    HERO Matrix2x2 tansponed();
    HERO Matrix2x2 inverted();

    HERO Matrix2x2& operator*=(float rhs);
};

HERO Matrix2x2 operator+(const Matrix2x2& lhs, const Matrix2x2& rhs);
HERO Matrix2x2 operator-(const Matrix2x2& lhs, const Matrix2x2& rhs);
HERO Matrix2x2 operator*(const Matrix2x2& lhs, const Matrix2x2& rhs);
HERO Float2 operator*(const Matrix2x2& lhs, const Float2& rhs);
HERO Matrix2x2 operator*(const Matrix2x2& lhs, float rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Matrix2x2& m);


struct Matrix4x4;

struct Matrix3x3
{
    Float3 col[3];

    Matrix3x3(){}
    constexpr Matrix3x3(Float3 v1, Float3 v2, Float3 v3){
        col[0] = v1;
        col[1] = v2;
        col[2] = v3;
    }
    HERO Matrix3x3(const Matrix4x4& matrix);

    constexpr static inline Matrix3x3 identity(){
    return Matrix3x3(Float3(1.0f,0.0f,0.0f),
                    Float3(0.0f,1.0f,0.0f),
                    Float3(0.0f,0.0f,1.0f));
    }

    HERO float determinant();
    HERO Matrix3x3 tansponed();
    HERO Matrix3x3 inverted();

    HERO Matrix3x3 operator*=(float rhs);
};

HERO Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs);
HERO Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs);
HERO Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);
HERO Float3 operator*(const Matrix3x3& lhs, const Float3& rhs);
HERO Matrix3x3 operator*(const Matrix3x3& lhs, float rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Matrix3x3& m);

struct Matrix4x4
{
    Float4 col[4];
    Matrix4x4(){}
    constexpr Matrix4x4(Float4 v1, Float4 v2, Float4 v3, Float4 v4){
        col[0] = v1;
        col[1] = v2;
        col[2] = v3;
        col[3] = v4;
    }
    HERO Matrix4x4(const Matrix3x3& matrix);

    constexpr static inline Matrix4x4 identity(){
        return {Float4(1.0f,0.0f,0.0f,0.0f),
                Float4(0.0f,1.0f,0.0f,0.0f),
                Float4(0.0f,0.0f,1.0f,0.0f),
                Float4(0.0f,0.0f,0.0f,1.0f)};
    }

    HERO float determinent();
    HERO Matrix4x4 tansponed();
    HERO Matrix4x4 inverted();

    HERO Matrix4x4& operator*=(float rhs);
};

HERO Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs);
HERO Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs);
HERO Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
HERO Float4 operator*(const Matrix4x4& lhs, const Float4& rhs);
HERO Matrix4x4 operator*(const Matrix4x4& lhs, float rhs);
HERO std::ostream& operator<< (std::ostream& stream, const Matrix4x4& m);

HERO void translate(Matrix4x4& matrix, Float3 translation);
HERO void scale(Matrix4x4& matrix, Float3 scale);
HERO void rotateX(Matrix4x4& matrix, float radians);
HERO void rotateY(Matrix4x4& matrix, float radians);
HERO void rotateZ(Matrix4x4& matrix, float radians);
HERO void rotateXYZ(Matrix4x4& matrix, Float3 rotation);
HERO Matrix4x4 Rotation(Quaternion& quaternion);

HERO Matrix4x4 TRS(Float3 position, Float3 rotation, Float3 scale);
HERO Matrix4x4 TRS(Float3 position, Quaternion& rotation, Float3 scale);

HERO Matrix4x4 pixelScreenMatrix(int width, int height, float near, float far);
HERO Matrix4x4 projectionMatrix(int width, int height, float FOV, float near, float far);
HERO Matrix4x4 lookAtMatrix(Float3 eye, Float3 target, Float3 up);
HERO Matrix4x4 orthographicMatrix(int width, int height, float near, float far); // need to be rework, no idea if work
HERO Matrix4x4 lookAtMatrix(Float3 eye, Float3 forward, Float3 up, Float3 right);

HERO bool pointBoxIntersection(Int2 point, Int2 boxPosition, Int2 boxSize);

}
