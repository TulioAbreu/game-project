#ifndef VECTOR2_HPP
#define VECTOR2_HPP

template <typename T>
struct Vector2 {
    T x, y;

    Vector2() {
        x = 0;
        y = 0;
    }

    Vector2(T x, T y) {
        this->x = x;
        this->y = y;
    }
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

template <typename T>
Vector2<T> operator+ (Vector2<T> v1, Vector2<T> v2) {
    return {v1.x + v2.x,
            v1.y + v2.y};
}

template <typename T>
Vector2<T> operator- (Vector2<T> v1, Vector2<T> v2) {
    return {v1.x - v2.x,
            v1.y - v2.y};
}

template <typename T>
Vector2<T> operator* (T value, Vector2<T> v) {
    return {v.x * value,
            v.y * value};
}

template <typename T>
Vector2<T> operator* (Vector2<T> v, T value) {
    return {v.x * value,
            v.y * value};
}

template <typename T>
Vector2<T> operator/ (Vector2<T> v, T value) {
    return {v.x / value,
            v.y / value};
}

#endif