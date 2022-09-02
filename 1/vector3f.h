#include <iostream>
#include <cmath>

struct Vector3f {
    float x;
    float y;
    float z;
};

Vector3f operator+(const Vector3f& a, const Vector3f& b) {
    Vector3f result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

Vector3f operator-(const Vector3f& a, const Vector3f& b) {
    Vector3f result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

Vector3f operator*(const Vector3f& a, float b) {
    Vector3f result = {a.x * b, a.y * b, a.z * b};
    return result;
}

Vector3f operator*(float b, const Vector3f& a) {
    Vector3f result = {a.x * b, a.y * b, a.z * b};
    return result;
}

float operator*(const Vector3f& a, const Vector3f& b) {
    float result = a.x * b.x + a.y * b.y + a.z * b.z;
    return result;
}

Vector3f operator/(const Vector3f& a, float b) {
    Vector3f result = {a.x / b, a.y / b, a.z / b};
    return result;
}

Vector3f operator-(const Vector3f& a) {
    Vector3f result = {-a.x, -a.y, -a.z};
    return result;
}

Vector3f operator+(const Vector3f& a) {
    Vector3f result = a;
    return result;
}

bool operator==(const Vector3f& a, const Vector3f& b) {
    bool result = false;
    if (a.x == b.x && a.y == b.y && a.z == b.z) {
        result = true;
    }
    return result;
}

bool operator!=(const Vector3f& a, const Vector3f& b) {
    return !(a == b);
}

Vector3f& operator+=(Vector3f &a, const Vector3f &b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

Vector3f& operator-=(Vector3f &a, const Vector3f &b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

Vector3f& operator*=(Vector3f &a, float b) {
    a.x *= b;
    a.y *= b;
    a.z *= b;
    return a;
}

Vector3f& operator/=(Vector3f &a, float b) {
    a.x /= b;
    a.y /= b;
    a.z /= b;
    return a;
}

std::ostream& operator<<(std::ostream& out, const Vector3f& a) {
    out << "(" << a.x << ", " << a.y << ", " << a.z << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Vector3f& c) {
    in >> c.x >> c.y >> c.z;
    return in;
}

float squared_norm(const Vector3f& a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

float norm(const Vector3f& a) {
    return sqrtf(squared_norm(a));
}

void normalize(Vector3f& a) {
    a /= norm(a);
}
