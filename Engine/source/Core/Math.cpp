#include"Math.hpp"

#include<cmath>

namespace Hero
{

HERO float deg2rad(float degree)
{
    return (degree * PI)/180.0f;
}

HERO float rad2deg(float radians)
{
    return (180.0f * radians)/PI;
}

HERO int clamp(int value, int min, int max)
{
    return (value < min)? min : (value > max)? max : value;
}

HERO float clamp(float value, float min, float max)
{
    return (value < min)? min : (value > max)? max : value;
}

HERO float lerpF(float a, float b, float t)
{
    return (1 - t)*a + t*b;
}

HERO void Int2::operator+=(const Int2& rhs)
{ 
    x += rhs.x;
    y += rhs.y;
}

HERO void Int2::operator-=(const Int2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

HERO bool Int2::operator==(const Int2& rhs)
{ 
    return x == rhs.x && y == rhs.y; 
}

HERO bool Int2::operator!=(const Int2& rhs)
{ 
    return !(*this == rhs); 
}

HERO Int2 operator+(const Int2& lhs, const Int2& rhs)
{ 
    return (Int2){ lhs.x + rhs.x, lhs.y + rhs.y }; 
}

HERO Int2 operator-(const Int2& lhs, const Int2& rhs)
{ 
    return (Int2){ lhs.x - rhs.x, lhs.y - rhs.y }; 
}

HERO std::ostream& operator<< (std::ostream& stream, const Int2& v)
{ 
    stream << "{"<<v.x<<","<<v.y<<"}"; 
    return stream; 
}

HERO int dotProduct(Int2 A, Int2 B)
{
    return (A.x * B.x) + (A.y * B.y);
}

HERO float distance(Int2 A, Int2 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    return sqrtf(x2 + y2);
}

HERO void Int3::operator+=(const Int3& rhs)
{ 
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
}

HERO void Int3::operator-=(const Int3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
}

HERO bool Int3::operator==(const Int3& rhs)
{ 
    return x == rhs.x && y == rhs.y && z == rhs.z; 
}

HERO bool Int3::operator!=(const Int3& rhs)
{ 
    return !(*this == rhs); 
}

HERO Int3 operator+(const Int3& lhs, const Int3& rhs)
{ 
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z }; 
}

HERO Int3 operator-(const Int3& lhs, const Int3& rhs)
{ 
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z}; 
}

HERO std::ostream& operator<< (std::ostream& stream, const Int3& v)
{ 
    stream << "{"<<v.x<<","<<v.y<<","<<v.z<<"}"; 
    return stream; 
}

HERO int dotProduct(Int3 A, Int3 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

HERO float distance(Int3 A, Int3 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    float z2 = (A.z - B.z)*(A.z - B.z); 
    return sqrtf(x2 + y2 + z2);
}

HERO void Int4::operator+=(const Int4& rhs)
{ 
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
}

HERO void Int4::operator-=(const Int4& rhs)
{ 
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;   
}

HERO bool Int4::operator==(const Int4& rhs)
{ 
    return x == rhs.x && y == rhs.y && z == rhs.z; 
}

HERO bool Int4::operator!=(const Int4& rhs)
{ 
    return !(*this == rhs); 
}

HERO Int4 operator+(Int4 lhs, const Int4& rhs)
{ 
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w}; 
}

HERO Int4 operator-(Int4 lhs, const Int4& rhs)
{ 
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w}; 
}

HERO std::ostream& operator<< (std::ostream& stream, const Int4& v)
{ 
    stream << "{"<<v.x<<","<<v.y<<","<<v.z<<","<<v.w<<"}"; 
    return stream; 
}

HERO float Float2::length()
{
    return sqrtf(x*x + y*y);
}

HERO void Float2::normalize()
{
    float len = length();
    x /= len;
    y /= len;
}

HERO Float2 Float2::normalized()
{
    float len = length();
    float nx = x / len;
    float ny = y / len;
    return (Float2){nx, ny};
}

HERO Float2& Float2::operator+=(const Float2& rhs)
{ 
    x += rhs.x;
    y += rhs.y; 
    return *this;
}

HERO Float2& Float2::operator-=(const Float2& rhs)
{ 
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

HERO Float2& Float2::operator*=(float rhs)
{  
    x *= rhs;
    y *= rhs;
    return *this; 
}

HERO Float2& Float2::operator/=(float rhs)
{
    x /= rhs;
    y /= rhs;
    return *this; 
}

HERO bool Float2::operator==(const Float2& rhs)
{ 
    return (fabs(x - rhs.x) < COMP_EPSILON) && 
        (fabs(y - rhs.y) < COMP_EPSILON); 
}

HERO bool Float2::operator!=(const Float2& rhs)
{ 
    return !(*this == rhs); 
}

HERO Float2 operator+(const Float2& lhs, const Float2& rhs)
{ 
    return (Float2){ lhs.x + rhs.x, lhs.y + rhs.y }; 
}

HERO Float2 operator-(const Float2& lhs, const Float2& rhs)
{ 
    return (Float2){ lhs.x - rhs.x, lhs.y - rhs.y }; 
}

HERO Float2 operator*(const Float2& lhs, float rhs)
{ 
    return (Float2){lhs.x * rhs, lhs.y * rhs}; 
}

HERO Float2 operator/(const Float2& lhs, float rhs)
{ 
    return (Float2){lhs.x / rhs, lhs.y / rhs}; 
}

HERO std::ostream& operator<< (std::ostream& stream, const Float2& v)
{ 
    stream << "{"<<v.x<<","<<v.y<<"}"; 
    return stream; 
}

HERO float dotProduct(Float2 A, Float2 B)
{
    return (A.x * B.x) + (A.y * B.y);
}

HERO float distance(Float2 A, Float2 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    return sqrtf(x2 + y2);
}

HERO Float2 rotateM2x2F2(Float2 vector, float angle)
{
    float x = vector.x * cos(angle) - vector.y * sin(angle);
    float y = vector.x * sin(angle) + vector.y * cos(angle);
    return (Float2){x, y};
}

HERO Float3::Float3(const Float4& vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
}

HERO float Float3::length()
{
    return sqrtf(x*x + y*y + z*z);
}

HERO void Float3::normalize()
{
    float len = length();
    x /= len;
    y /= len;
    z /= len;
}

HERO Float3 Float3::normalized()
{
    float len = length();
    float nx = x / len;
    float ny = y / len;
    float nz = z / len;
    return (Float3){nx, ny, nz};
}

HERO Float3& Float3::operator+=(const Float3& rhs)
{ 
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

HERO Float3& Float3::operator-=(const Float3& rhs)
{ 
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

HERO Float3& Float3::operator*=(float rhs)
{  
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this; 
}

HERO Float3& Float3::operator/=(float rhs)
{  
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this; 
}

HERO bool Float3::operator==(const Float3& rhs)
{ 
    return (fabs(x - rhs.x) < COMP_EPSILON) 
    && (fabs(y - rhs.y) < COMP_EPSILON)
    && (fabs(z - rhs.z) < COMP_EPSILON); 
}

HERO bool Float3::operator!=(const Float3& rhs)
{ 
    return !(*this == rhs); 
}

HERO Float3 operator+(const Float3& lhs, const Float3& rhs)
{ 
    return (Float3){ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z }; 
}

HERO Float3 operator-(const Float3& lhs, const Float3& rhs)
{ 
    return (Float3){ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z}; 
}

HERO Float3 operator*(const Float3& lhs, float rhs)
{ 
    return (Float3){lhs.x * rhs, lhs.y * rhs, lhs.z * rhs}; 
}

HERO Float3 operator*(const Float3& lhs, const Float3& rhs)
{
    return (Float3){lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

HERO Float3 operator/(const Float3& lhs, float rhs)
{ 
    return (Float3){lhs.x / rhs, lhs.y / rhs, lhs.z / rhs}; 
}

HERO std::ostream& operator<< (std::ostream& stream, const Float3& v)
{ 
    stream << "{"<<v.x<<","<<v.y<<","<<v.z<<"}"; 
    return stream; 
}

HERO float dotProduct(Float3 A, Float3 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

HERO Float3 crossProduct(Float3 A, Float3 B)
{
    return Float3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x);
}

HERO Float3 lerp(Float3 A, Float3 B, float t)
{
    float x = (1 - t)*A.x + t*B.x;
    float y = (1 - t)*A.y + t*B.y;
    float z = (1 - t)*A.z + t*B.z;
    return (Float3){x, y, z};
}

HERO float distance(Float3 A, Float3 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    float z2 = (A.z - B.z)*(A.z - B.z); 
    return sqrtf(x2 + y2 + z2);
}

HERO Float4::Float4(const Float3& vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = 0.0f;
}

HERO float Float4::length()
{
    return sqrtf(x*x + y*y + z*z + w*w);
}

HERO void Float4::normalize()
{
    float len = length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
}

HERO Float4 Float4::normalized()
{
    float len = length();
    float nx = x / len;
    float ny = y / len;
    float nz = z / len;
    float nw = w / len;
    return (Float4){nx, ny, nz, nw};
}

HERO Float4& Float4::operator+=(const Float4& rhs)
{ 
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

HERO Float4& Float4::operator-=(const Float4& rhs)
{ 
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

HERO Float4& Float4::operator*=(float rhs)
{  
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

HERO Float4& Float4::operator/=(float rhs)
{  
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this; 
}

HERO bool Float4::operator==(const Float4& rhs)
{ 
    return (fabs(x - rhs.x) < COMP_EPSILON) 
    && (fabs(y - rhs.y) < COMP_EPSILON)
    && (fabs(z - rhs.z) < COMP_EPSILON)
    && (fabs(w - rhs.w) < COMP_EPSILON); 
}

HERO bool Float4::operator!=(const Float4& rhs)
{
    return !(*this == rhs);
}

HERO Float4 operator+(Float4 lhs, const Float4& rhs)
{ 
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w}; 
}

HERO Float4 operator-(Float4 lhs, const Float4& rhs)
{ 
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w}; 
}

HERO Float4 operator*(Float4 lhs, float rhs)
{ 
    return (Float4){lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs}; 
}

HERO Float4 operator/(Float4 lhs, float rhs)
{
    return (Float4){lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs}; 
}

HERO std::ostream& operator<< (std::ostream& stream, const Float4& v)
{ 
    stream << "{"<<v.x<<","<<v.y<<","<<v.z<<","<<v.w<<"}"; 
    return stream;
}

HERO Quaternion::Quaternion(float rotX, float rotY, float rotZ)
{
    double cy = cos(rotZ * 0.5);
    double sy = sin(rotZ * 0.5);
    double cp = cos(rotY * 0.5);
    double sp = sin(rotY * 0.5);
    double cr = cos(rotX * 0.5);
    double sr = sin(rotX * 0.5);

    w = cr * cp * cy + sr * sp * sy;
    x = sr * cp * cy - cr * sp * sy;
    y = cr * sp * cy + sr * cp * sy;
    z = cr * cp * sy - sr * sp * cy;
}

HERO Quaternion::Quaternion(const Float3& vector)
{
    double cy = cos(vector.z * 0.5);
    double sy = sin(vector.z * 0.5);
    double cp = cos(vector.y * 0.5);
    double sp = sin(vector.y * 0.5);
    double cr = cos(vector.x * 0.5);
    double sr = sin(vector.x * 0.5);

    w = cr * cp * cy + sr * sp * sy;
    x = sr * cp * cy - cr * sp * sy;
    y = cr * sp * cy + sr * cp * sy;
    z = cr * cp * sy - sr * sp * cy;
}

HERO Quaternion::Quaternion(float angle, const Float3& axis)
{
    w = cosf(angle * 0.5f);
    x = sinf(angle * 0.5f) * axis.x;
    y = sinf(angle * 0.5f) * axis.y;
    z = sinf(angle * 0.5f) * axis.z;
}

HERO Float3 Quaternion::ToEuler() const
{
    Float3 result;

    double sinr_cosp = 2 *( w * x + y * z);
    double cosr_cosp = 1 - 2 * (x * x + y * y);
    result.x = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = 2 * (w * y - z * x);
    if (std::abs(sinp) >= 1)
        result.y = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        result.y = std::asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (w * z + x * y);
    double cosy_cosp = 1 - 2 * (y * y + z * z);
    result.z = std::atan2(siny_cosp, cosy_cosp);

    return result;
}

HERO Quaternion& Quaternion::operator+=(const Quaternion& rhs)
{
    w += rhs.w;
    x += rhs.x;
    y += rhs.y;
    z += rhs.z; 
}

HERO Quaternion& Quaternion::operator-=(const Quaternion& rhs)
{
    w -= rhs.w;
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z; 
}

HERO Quaternion& Quaternion::operator*=(const Quaternion& rhs)
{
    w = w*rhs.w - x*rhs.x - y*rhs.y - z*rhs.z;
    x = w*rhs.x + x*rhs.w + y*rhs.z - z*rhs.y;
    y = w*rhs.y - x*rhs.z + y*rhs.w + z*rhs.x;
    z = w*rhs.z + x*rhs.y - y*rhs.x + z*rhs.w;
}

HERO bool Quaternion::operator==(const Quaternion& rhs)
{
    return w == rhs.w && x == rhs.x && y == rhs.y && z == rhs.z;
}

HERO bool Quaternion::operator!=(const Quaternion& rhs)
{
    return w != rhs.w && x != rhs.x && y != rhs.y && z != rhs.z;
}

HERO Quaternion operator~(const Quaternion& rhs)
{
    Quaternion q;
    q.w = rhs.w;
    q.x = -rhs.x;
    q.y = -rhs.y;
    q.z = -rhs.z;
    return q;
}

HERO Quaternion operator+(Quaternion lhs, const Quaternion& rhs)
{
    Quaternion q;
    q.w = lhs.w + rhs.w;
    q.x = lhs.x + rhs.x;
    q.y = lhs.y + rhs.w;
    q.z = lhs.z + rhs.z;
    return q;
}

HERO Quaternion operator-(Quaternion lhs, const Quaternion& rhs)
{
    Quaternion q;
    q.w = lhs.w - rhs.w;
    q.x = lhs.x - rhs.x;
    q.y = lhs.y - rhs.w;
    q.z = lhs.z - rhs.z;
    return q;
}

HERO Quaternion operator*(Quaternion lhs, const Quaternion& rhs)
{
    Quaternion q;
    q.w = lhs.w*rhs.w - lhs.x*rhs.x - lhs.y*rhs.y - lhs.z*rhs.z;
    q.x = lhs.w*rhs.x + lhs.x*rhs.w + lhs.y*rhs.z - lhs.z*rhs.y;
    q.y = lhs.w*rhs.y - lhs.x*rhs.z + lhs.y*rhs.w + lhs.z*rhs.x;
    q.z = lhs.w*rhs.z + lhs.x*rhs.y - lhs.y*rhs.x + lhs.z*rhs.w;
    return q;
}

HERO Quaternion operator*(const Quaternion& lhs, const Float3& rhs)
{
    Quaternion q = lhs;
    Quaternion lhs2 = ~lhs;

    q *= rhs;
    q *= lhs2;

    return q;
}

HERO std::ostream& operator<< (std::ostream& stream, Quaternion& q)
{
    stream << "{ "<<q.w<<" + "<<q.x<<"i + "<<q.y<<"j + "<<q.z<<"k }"; 
    return stream;
}

HERO float Matrix2x2::determinant()
{
    return (col[0].x * col[1].y) - (col[0].y * col[1].x);
}

HERO Matrix2x2 Matrix2x2::tansponed()
{
    return (Matrix2x2){(Float2){col[0].x, col[1].x},
                        (Float2){col[0].y, col[1].y}};
}

HERO Matrix2x2 Matrix2x2::inverted()
{
    float det = 1.0f / determinant();
    return (Matrix2x2){(Float2){det * col[1].y, det * (-col[0].y)},
            (Float2){det * (-col[1].x), det * col[0].x}};
}

HERO Matrix2x2& Matrix2x2::operator*=(float rhs)
{
    col[0] *= rhs;
    col[1] *= rhs;
    return *this;
}

HERO Matrix2x2 operator+(const Matrix2x2& lhs, const Matrix2x2& rhs)
{
    Matrix2x2 result;
    result.col[0] = lhs.col[0] + rhs.col[0];
    result.col[1] = lhs.col[1] + rhs.col[1];
    return result;
}

HERO Matrix2x2 operator-(const Matrix2x2& lhs, const Matrix2x2& rhs)
{
    Matrix2x2 result;
    result.col[0] = lhs.col[0] - rhs.col[0];
    result.col[1] = lhs.col[1] - rhs.col[1];
    return result;
}

HERO Matrix2x2 operator*(const Matrix2x2& lhs, const Matrix2x2& rhs)
{
    Matrix2x2 result;
    result.col[0].x = lhs.col[0].x * rhs.col[0].x + lhs.col[1].x * rhs.col[0].y;
    result.col[0].y = lhs.col[0].y * rhs.col[0].x + lhs.col[1].y * rhs.col[0].y;
    result.col[1].x = lhs.col[0].x * rhs.col[1].x + lhs.col[1].x * rhs.col[1].y;
    result.col[1].y = lhs.col[0].y * rhs.col[1].x + lhs.col[1].y * rhs.col[1].y;
    return result;
}

HERO Float2 operator*(const Matrix2x2& lhs, const Float2& rhs)
{
    Float2 result;
    result.x = lhs.col[0].x * rhs.x + lhs.col[1].x * rhs.y;
    result.y = lhs.col[0].y * rhs.x + lhs.col[1].y * rhs.y;
    return result;
}

HERO Matrix2x2 operator*(const Matrix2x2& lhs, float rhs)
{
    Matrix2x2 result = lhs;
    result *= rhs;
    return result;
}

HERO std::ostream& operator<< (std::ostream& stream, const Matrix2x2& m)
{
    stream<<"{"<<m.col[0]<<","<<m.col[1]<<"}";
    return stream;
}

HERO Matrix3x3::Matrix3x3(const Matrix4x4& matrix)
{
    col[0] = Float3(matrix.col[0]);
    col[1] = Float3(matrix.col[1]);
    col[2] = Float3(matrix.col[2]);
}

HERO float Matrix3x3::determinant()
{
    return col[0].x*col[1].y*col[2].z + 
            col[1].x*col[2].y*col[0].z + 
            col[2].x*col[0].y*col[1].z -
            col[2].x*col[1].y*col[0].z - 
            col[1].x*col[0].y*col[2].z - 
            col[0].x*col[2].y*col[1].z;
}

HERO Matrix3x3 Matrix3x3::tansponed()
{
    Matrix3x3 matrix;

    matrix.col[0].x = col[0].x;
    matrix.col[1].x = col[0].y;
    matrix.col[2].x = col[0].z;
    matrix.col[0].y = col[1].x;
    matrix.col[1].y = col[1].y;
    matrix.col[2].y = col[1].z;
    matrix.col[0].z = col[2].x;
    matrix.col[1].z = col[2].y;
    matrix.col[2].z = col[2].z;

    return matrix;
}

HERO Matrix3x3 Matrix3x3::inverted()
{
    float det = 1.0f / determinant();

    Matrix3x3 matrix;

    matrix.col[0].x = (col[1].y * col[2].z) - (col[2].y * col[1].z);
    matrix.col[0].x *= det;
    matrix.col[0].y = (col[0].y * col[2].z) - (col[2].y * col[0].z);
    matrix.col[0].y *= -det;
    matrix.col[0].z = (col[0].y * col[1].z) - (col[1].y * col[0].z);
    matrix.col[0].z *= det;

    matrix.col[1].x = (col[1].x * col[2].z) - (col[2].x * col[1].z);
    matrix.col[1].x *= -det;
    matrix.col[1].y = (col[0].x * col[2].z) - (col[2].x * col[0].z);
    matrix.col[1].y *= det;
    matrix.col[1].z = (col[0].x * col[1].z) - (col[1].x * col[0].z);
    matrix.col[1].z *= -det;

    matrix.col[2].x = (col[1].x * col[2].y) - (col[2].x * col[1].y);
    matrix.col[2].x *= det;
    matrix.col[2].y = (col[0].x * col[2].y) - (col[2].x * col[0].y);
    matrix.col[2].y *= -det;
    matrix.col[2].z = (col[0].x * col[1].y) - (col[1].x * col[0].y);
    matrix.col[2].z *= det;

    return matrix;
}

HERO Matrix3x3 Matrix3x3::operator*=(float rhs)
{
    col[0] *= rhs;
    col[1] *= rhs;
    col[2] *= rhs;
    return *this;
}

HERO Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
    Matrix3x3 result;
    result.col[0] = lhs.col[0] + rhs.col[0];
    result.col[1] = lhs.col[1] + rhs.col[1];
    result.col[2] = lhs.col[2] + rhs.col[2];
    return result;
}

HERO Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
    Matrix3x3 result;
    result.col[0] = lhs.col[0] - rhs.col[0];
    result.col[1] = lhs.col[1] - rhs.col[1];
    result.col[2] = lhs.col[2] - rhs.col[2];
    return result;
}

HERO Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
    Matrix3x3 matrix;

    matrix.col[0].x = lhs.col[0].x * rhs.col[0].x + lhs.col[1].x * rhs.col[0].y + lhs.col[2].x * rhs.col[0].z;
    matrix.col[0].y = lhs.col[0].y * rhs.col[0].x + lhs.col[1].y * rhs.col[0].y + lhs.col[2].y * rhs.col[0].z;
    matrix.col[0].z = lhs.col[0].z * rhs.col[0].x + lhs.col[1].z * rhs.col[0].y + lhs.col[2].z * rhs.col[0].z;

    matrix.col[1].x = lhs.col[0].x * rhs.col[1].x + lhs.col[1].x * rhs.col[1].y + lhs.col[2].x * rhs.col[1].z;
    matrix.col[1].y = lhs.col[0].y * rhs.col[1].x + lhs.col[1].y * rhs.col[1].y + lhs.col[2].y * rhs.col[1].z;
    matrix.col[1].z = lhs.col[0].z * rhs.col[1].x + lhs.col[1].z * rhs.col[1].y + lhs.col[2].z * rhs.col[1].z;

    matrix.col[2].x = lhs.col[0].x * rhs.col[2].x + lhs.col[1].x * rhs.col[2].y + lhs.col[2].x * rhs.col[2].z;
    matrix.col[2].y = lhs.col[0].y * rhs.col[2].x + lhs.col[1].y * rhs.col[2].y + lhs.col[2].y * rhs.col[2].z;
    matrix.col[2].z = lhs.col[0].z * rhs.col[2].x + lhs.col[1].z * rhs.col[2].y + lhs.col[2].z * rhs.col[2].z;

    return matrix;
}

HERO Float3 operator*(const Matrix3x3& lhs, const Float3& rhs)
{
    Float3 vec;
    vec.x = lhs.col[0].x * rhs.x + lhs.col[1].x * rhs.y + lhs.col[2].x * rhs.z;
    vec.y = lhs.col[0].y * rhs.x + lhs.col[1].y * rhs.y + lhs.col[2].y * rhs.z;
    vec.z = lhs.col[0].z * rhs.x + lhs.col[2].z * rhs.y + lhs.col[2].z * rhs.z;
    return vec;
}

HERO Matrix3x3 operator*(const Matrix3x3& lhs, float rhs)
{
    Matrix3x3 result;
    result.col[0] *= rhs;
    result.col[1] *= rhs;
    result.col[2] *= rhs;
    return result;
}

HERO std::ostream& operator<< (std::ostream& stream, const Matrix3x3& m)
{
    stream<<"{"<<m.col[0]<<","<<m.col[1]<<","<<m.col[2]<<"}";
    return stream;
}

HERO Matrix4x4::Matrix4x4(const Matrix3x3& matrix)
{
    col[0] = Float4(matrix.col[0]);
    col[1] = Float4(matrix.col[1]);
    col[2] = Float4(matrix.col[2]);
    col[3] = Float4(0.0f, 0.0f, 0.0f, 1.0f);
}

HERO float Matrix4x4::determinent()
{
    Matrix4x4 matrix = Matrix4x4::identity();

    float mul = col[0].y / col[0].x;
    matrix.col[1].y = col[1].y - mul * col[1].x;
    matrix.col[2].y = col[2].y - mul * col[2].x;
    matrix.col[3].y = col[3].y - mul * col[3].x;

    mul = col[0].z / col[0].y;
    matrix.col[2].z = col[2].z - mul * col[2].y;
    matrix.col[3].z = col[3].z - mul * col[3].y;

    mul = col[0].w / col[0].z;
    matrix.col[2].w = col[2].w - mul * col[2].z;

    return matrix.col[0].x * matrix.col[1].y * matrix.col[2].z *matrix.col[3].w;
}

HERO Matrix4x4 Matrix4x4::tansponed()
{
    Matrix4x4 matrix;

    matrix.col[0].x = col[0].x;
    matrix.col[1].x = col[0].y;
    matrix.col[2].x = col[0].z;
    matrix.col[3].x = col[0].w;

    matrix.col[0].y = col[1].x;
    matrix.col[1].y = col[1].y;
    matrix.col[2].y = col[1].z;
    matrix.col[3].y = col[1].w;

    matrix.col[0].z = col[2].x;
    matrix.col[1].z = col[2].y;
    matrix.col[2].z = col[2].z;
    matrix.col[3].z = col[2].w;

    matrix.col[0].w = col[3].x;
    matrix.col[1].w = col[3].y;
    matrix.col[2].w = col[3].z;
    matrix.col[3].w = col[3].w;

    return matrix;
}

HERO Matrix4x4 Matrix4x4::inverted()
{
    return Matrix4x4::identity();
}

HERO Matrix4x4& Matrix4x4::operator*=(float rhs)
{
    col[0] *= rhs;
    col[1] *= rhs;
    col[2] *= rhs;
    col[3] *= rhs;
    return *this;
}

HERO Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
    Matrix4x4 result;
    result.col[0] = lhs.col[0] + rhs.col[0];
    result.col[1] = lhs.col[1] + rhs.col[1];
    result.col[2] = lhs.col[2] + rhs.col[2];
    result.col[3] = lhs.col[3] + rhs.col[3];
    return result;
}

HERO Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
    Matrix4x4 result;
    result.col[0] = lhs.col[0] - rhs.col[0];
    result.col[1] = lhs.col[1] - rhs.col[1];
    result.col[2] = lhs.col[2] - rhs.col[2];
    result.col[3] = lhs.col[3] - rhs.col[3];
    return result;
}

HERO Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
    Matrix4x4 matrix;

    matrix.col[0].x = lhs.col[0].x * rhs.col[0].x + lhs.col[1].x * rhs.col[0].y + lhs.col[2].x * rhs.col[0].z + lhs.col[3].x * rhs.col[0].w;
    matrix.col[0].y = lhs.col[0].y * rhs.col[0].x + lhs.col[1].y * rhs.col[0].y + lhs.col[2].y * rhs.col[0].z + lhs.col[3].y * rhs.col[0].w;
    matrix.col[0].z = lhs.col[0].z * rhs.col[0].x + lhs.col[1].z * rhs.col[0].y + lhs.col[2].z * rhs.col[0].z + lhs.col[3].z * rhs.col[0].w;
    matrix.col[0].w = lhs.col[0].w * rhs.col[0].x + lhs.col[1].w * rhs.col[0].y + lhs.col[2].w * rhs.col[0].z + lhs.col[3].w * rhs.col[0].w;

    matrix.col[1].x = lhs.col[0].x * rhs.col[1].x + lhs.col[1].x * rhs.col[1].y + lhs.col[2].x * rhs.col[1].z + lhs.col[3].x * rhs.col[1].w;
    matrix.col[1].y = lhs.col[0].y * rhs.col[1].x + lhs.col[1].y * rhs.col[1].y + lhs.col[2].y * rhs.col[1].z + lhs.col[3].y * rhs.col[1].w;
    matrix.col[1].z = lhs.col[0].z * rhs.col[1].x + lhs.col[1].z * rhs.col[1].y + lhs.col[2].z * rhs.col[1].z + lhs.col[3].z * rhs.col[1].w;
    matrix.col[1].w = lhs.col[0].w * rhs.col[1].x + lhs.col[1].w * rhs.col[1].y + lhs.col[2].w * rhs.col[1].z + lhs.col[3].w * rhs.col[1].w;

    matrix.col[2].x = lhs.col[0].x * rhs.col[2].x + lhs.col[1].x * rhs.col[2].y + lhs.col[2].x * rhs.col[2].z + lhs.col[3].x * rhs.col[2].w;
    matrix.col[2].y = lhs.col[0].y * rhs.col[2].x + lhs.col[1].y * rhs.col[2].y + lhs.col[2].y * rhs.col[2].z + lhs.col[3].y * rhs.col[2].w;
    matrix.col[2].z = lhs.col[0].z * rhs.col[2].x + lhs.col[1].z * rhs.col[2].y + lhs.col[2].z * rhs.col[2].z + lhs.col[3].z * rhs.col[2].w;
    matrix.col[2].w = lhs.col[0].w * rhs.col[2].x + lhs.col[1].w * rhs.col[2].y + lhs.col[2].w * rhs.col[2].z + lhs.col[3].w * rhs.col[2].w;

    matrix.col[3].x = lhs.col[0].x * rhs.col[3].x + lhs.col[1].x * rhs.col[3].y + lhs.col[2].x * rhs.col[3].z + lhs.col[3].x * rhs.col[3].w;
    matrix.col[3].y = lhs.col[0].y * rhs.col[3].x + lhs.col[1].y * rhs.col[3].y + lhs.col[2].y * rhs.col[3].z + lhs.col[3].y * rhs.col[3].w;
    matrix.col[3].z = lhs.col[0].z * rhs.col[3].x + lhs.col[1].z * rhs.col[3].y + lhs.col[2].z * rhs.col[3].z + lhs.col[3].z * rhs.col[3].w;
    matrix.col[3].w = lhs.col[0].w * rhs.col[3].x + lhs.col[1].w * rhs.col[3].y + lhs.col[2].w * rhs.col[3].z + lhs.col[3].w * rhs.col[3].w;

    return matrix;
}

HERO Float4 operator*(const Matrix4x4& lhs, const Float4& rhs)
{
    float x = rhs.x*lhs.col[0].x + rhs.y*lhs.col[1].x + rhs.z*lhs.col[2].x + rhs.w*lhs.col[3].x;
    float y = rhs.x*lhs.col[0].y + rhs.y*lhs.col[1].y + rhs.z*lhs.col[2].y + rhs.w*lhs.col[3].y;
    float z = rhs.x*lhs.col[0].z + rhs.y*lhs.col[1].z + rhs.z*lhs.col[2].z + rhs.w*lhs.col[3].z;
    float w = rhs.x*lhs.col[0].w + rhs.y*lhs.col[1].w + rhs.z*lhs.col[2].w + rhs.w*lhs.col[3].w;

    return (Float4){x, y, z, w};
}

HERO Matrix4x4 operator*(const Matrix4x4& lhs, float rhs)
{
    Matrix4x4 result;
    result.col[0] *= rhs;
    result.col[1] *= rhs;
    result.col[2] *= rhs;
    result.col[3] *= rhs;
    return result;
}

HERO std::ostream& operator<< (std::ostream& stream, const Matrix4x4& m)
{
    stream<<"{"<<m.col[0]<<","<<m.col[1]<<","<<m.col[2]<<","<<m.col[3]<<"}";
    return stream;
}

HERO void translate(Matrix4x4& matrix, Float3 translation)
{
    matrix.col[3].x += translation.x;
    matrix.col[3].y += translation.y;
    matrix.col[3].z += translation.z;
}

HERO void scale(Matrix4x4& matrix, Float3 scale)
{
    matrix.col[0].x = scale.x;
    matrix.col[1].y = scale.y;
    matrix.col[2].z = scale.z;
}

HERO void rotateX(Matrix4x4& matrix, float radians)
{
    float a = matrix.col[0].y;
    float b = matrix.col[0].z;
    matrix.col[0].y = a*cosf(radians) - b*sinf(radians);
    matrix.col[0].z = a*sinf(radians) + b*cosf(radians);
    a = matrix.col[1].y;
    b = matrix.col[1].z;
    matrix.col[1].y = a*cosf(radians) - b*sinf(radians);
    matrix.col[1].z = a*sinf(radians) + b*cosf(radians);
    a = matrix.col[2].y;
    b = matrix.col[2].z;
    matrix.col[2].y = a*cosf(radians) - b*sinf(radians);
    matrix.col[2].z = a*sinf(radians) + b*cosf(radians);
    a = matrix.col[3].y;
    b = matrix.col[3].z;   
    matrix.col[3].y = a*cosf(radians) - b*sinf(radians);
    matrix.col[3].z = a*sinf(radians) + b*cosf(radians);
}

HERO void rotateY(Matrix4x4& matrix, float radians)
{
    float a = matrix.col[0].x;
    float b = matrix.col[0].z;
    matrix.col[0].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[0].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[1].x;
    b = matrix.col[1].z;
    matrix.col[1].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[1].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[2].x;
    b = matrix.col[2].z;
    matrix.col[2].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[2].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[3].x;
    b = matrix.col[3].z;   
    matrix.col[3].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[3].z = -a*sinf(radians) + b*cosf(radians);
}

HERO void rotateZ(Matrix4x4& matrix, float radians)
{
    float a = matrix.col[0].x;
    float b = matrix.col[0].y;
    matrix.col[0].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[0].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[1].x;
    b = matrix.col[1].y;
    matrix.col[1].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[1].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[2].x;
    b = matrix.col[2].y;
    matrix.col[2].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[2].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[3].x;
    b = matrix.col[3].y;   
    matrix.col[3].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[3].y = -a*sinf(radians) + b*cosf(radians);
}

HERO void rotateXYZ(Matrix4x4& matrix, Float3 rotation)
{
    if(rotation.x != 0.0f)
        rotateX(matrix, rotation.x);
    if(rotation.y != 0.0f)
        rotateY(matrix, rotation.y);
    if(rotation.z != 0.0f)
        rotateZ(matrix, rotation.z);
}

HERO Matrix4x4 Rotation(Quaternion& quaternion)
{
    Matrix4x4 matrix;

    matrix.col[0].x = 1.0f - 2.0f*(powf(quaternion.z, 2.0f) + powf(quaternion.y, 2.0f));
    matrix.col[0].y = 2.0f*(quaternion.x*quaternion.y + quaternion.w*quaternion.z);
    matrix.col[0].z = 2.0f*(quaternion.z*quaternion.x - quaternion.w*quaternion.y);
    matrix.col[0].w = 0.0f;

    matrix.col[1].x = 2.0f*(quaternion.x*quaternion.y - quaternion.w*quaternion.z);
    matrix.col[1].y = 1.0f - 2.0f*(powf(quaternion.x, 2.0f) + powf(quaternion.z, 2.0f));
    matrix.col[1].z = 2.0f*(quaternion.y*quaternion.z + quaternion.w*quaternion.x);
    matrix.col[1].w = 0.0f;

    matrix.col[2].x = 2.0f*(quaternion.z*quaternion.x + quaternion.w*quaternion.y);
    matrix.col[2].y = 2.0f*(quaternion.y*quaternion.z - quaternion.w*quaternion.x);
    matrix.col[2].z = 1.0f - 2.0f*(powf(quaternion.x, 2.0f) + powf(quaternion.y, 2.0f));
    matrix.col[2].w = 0.0f;

    matrix.col[3].x = 0.0f;
    matrix.col[3].y = 0.0f;
    matrix.col[3].z = 0.0f;
    matrix.col[3].w = 1.0f;

    return matrix;
}

HERO Matrix4x4 TRS(Float3 position, Float3 rotation, Float3 scale)
{
    Matrix4x4 matrix;

    float cosx = cosf(rotation.x);
    float sinx = sinf(rotation.x);
    float cosy = cosf(rotation.y);
    float siny = sinf(rotation.y);
    float cosz = cosf(rotation.z);
    float sinz = sinf(rotation.z);

    matrix.col[0].x = scale.x*cosy*cosz;
    matrix.col[0].y = scale.x*cosx*sinz;
    matrix.col[0].z = scale.x*(-siny);
    matrix.col[0].w = 0.0f;

    matrix.col[1].x = scale.y*(sinx*siny*cosz-cosx*sinz);
    matrix.col[1].y = scale.y*(sinx*siny*sinz+cosx*cosz);
    matrix.col[1].z = scale.y*sinx*cosy;
    matrix.col[1].w = 0.0f;

    matrix.col[2].x = scale.z*(cosx*siny*cosz+sinx*sinz);
    matrix.col[2].y = scale.z*(cosx*siny*sinz-sinx*cosz);
    matrix.col[2].z = scale.z*cosx*cosy;
    matrix.col[2].w = 0.0f;

    matrix.col[3].x = position.x;
    matrix.col[3].y = position.y;
    matrix.col[3].z = position.z;
    matrix.col[3].w = 1.0f;

    return matrix;
}

HERO Matrix4x4 TRS(Float3 position, Quaternion& rotation, Float3 scale)
{
    Matrix4x4 matrix;

    matrix.col[0].x = scale.x*(1.0f - 2.0f*(powf(rotation.z, 2.0f) + powf(rotation.y, 2.0f)));
    matrix.col[0].y = scale.x*(2.0f*(rotation.x*rotation.y + rotation.w*rotation.z));
    matrix.col[0].z = scale.x*(2.0f*(rotation.z*rotation.x - rotation.w*rotation.y));
    matrix.col[0].w = 0.0f;

    matrix.col[1].x = scale.y*(2.0f*(rotation.x*rotation.y - rotation.w*rotation.z));
    matrix.col[1].y = scale.y*(1.0f - 2.0f*(powf(rotation.x, 2.0f) + powf(rotation.z, 2.0f)));
    matrix.col[1].z = scale.y*(2.0f*(rotation.y*rotation.z + rotation.w*rotation.x));
    matrix.col[1].w = 0.0f;

    matrix.col[2].x = scale.z*(rotation.z*rotation.x + rotation.w*rotation.y);
    matrix.col[2].y = scale.z*(rotation.y*rotation.z - rotation.w*rotation.x);
    matrix.col[2].z = scale.z*(1.0f - 2.0f*(powf(rotation.x, 2.0f) + powf(rotation.y, 2.0f)));
    matrix.col[2].w = 0.0f;

    matrix.col[3].x = position.x;
    matrix.col[3].y = position.y;
    matrix.col[3].z = position.z;
    matrix.col[3].w = 1.0f;

    return matrix;
}

HERO Matrix4x4 pixelScreenMatrix(int width, int height, float near, float far)
{
    Matrix4x4 matrix = Matrix4x4::identity();
    matrix.col[0].x = 2.0f/width;
    matrix.col[1].y = -2.0f/height;
    matrix.col[2].z = 1.0f;
    matrix.col[3].x = -1;
    matrix.col[3].y = 1;
    matrix.col[3].z = 0.0f;
    matrix.col[3].w = 1;
    return matrix;
}

HERO Matrix4x4 projectionMatrix(int width, int height, float FOV, float near, float far)
{
    float aspectRatio = (float)width/(float)height;
    float tg = tanf(FOV*0.5f*PI/180.0f);

    Matrix4x4 matrix = Matrix4x4::identity();

    matrix.col[0].x = 1.0f/(aspectRatio*tg);
    matrix.col[1].y = 1.0f/tg;
    matrix.col[2].z = (-far - near)/(far - near);
    matrix.col[2].w = -1.0f;
    matrix.col[3].z = (-far*near)/(far - near);
    matrix.col[3].w = 0.0f;

    return matrix;
}

HERO Matrix4x4 lookAtMatrix(Float3 eye, Float3 target, Float3 up)
{
    Float3 f = target - eye;
    f.normalize();
    f *= -1.0f;

    Float3 r = crossProduct(up, f);
    r.normalize();
    r *= -1.0f;

    Float3 u = crossProduct(f, r);
    u.normalize();
    u *= -1.0f;

    Matrix4x4 matrix;

    matrix.col[0].x = r.x;
    matrix.col[1].x = r.y;
    matrix.col[2].x = r.z;

    matrix.col[0].y = u.x;
    matrix.col[1].y = u.y;
    matrix.col[2].y = u.z;

    matrix.col[0].z = f.x;
    matrix.col[1].z = f.y;
    matrix.col[2].z = f.z;

    matrix.col[0].w = 0.0f;
    matrix.col[1].w = 0.0f;
    matrix.col[2].w = 0.0f;

    matrix.col[3].x = -dotProduct(r, eye);
    matrix.col[3].y = -dotProduct(u, eye);
    matrix.col[3].z = -dotProduct(f, eye);
    matrix.col[3].w = 1.0f;

    return matrix;
}

HERO Matrix4x4 orthographicMatrix(int width, int height, float near, float far)
{
    Matrix4x4 matrix = Matrix4x4::identity();
    matrix.col[0].x = 2.0f/width;
    matrix.col[1].y = -2.0f/height;
    matrix.col[2].z = -2.0f/(far - near);
    matrix.col[3].x = -1;
    matrix.col[3].y = 1;
    matrix.col[3].z = (far + near)/(far - near);
    matrix.col[3].w = 1;
    return matrix;
}

HERO bool pointBoxIntersection(Int2 point, Int2 boxPosition, Int2 boxSize)
{
    if(point.x < boxPosition.x || point.y < boxPosition.y) 
        return false;

    if(point.x > boxPosition.x + boxSize.x || point.y > boxPosition.y + boxSize.y) 
        return false;

    return true;
}

}