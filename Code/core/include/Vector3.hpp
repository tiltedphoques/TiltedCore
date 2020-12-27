#pragma once

#include "Math.hpp"

namespace TiltedPhoques
{
    template <typename T>
    struct Vector3
    {
        Vector3() noexcept : m_x(0), m_y(0), m_z(0) {}
        Vector3(T aX, T aY, T aZ) noexcept : m_x(aX), m_y(aY), m_z(aZ) {}
        Vector3(const Vector3&) noexcept = default;
        Vector3(Vector3&&) noexcept = default;
        ~Vector3() noexcept = default;

        Vector3& operator=(const Vector3&) noexcept = default;
        Vector3& operator=(Vector3&&) noexcept = default;

        bool operator==(const Vector3& acRhs) const noexcept
        {
            return m_x == acRhs.m_x && m_y == acRhs.m_y && acRhs.m_z == m_z;
        }

        bool operator!=(const Vector3& acRhs) const noexcept
        {
            return !operator==(acRhs);
        }

        Vector3 operator+(const Vector3& acRhs) const noexcept
        {
            return Vector3(m_x + acRhs.m_x, m_y + acRhs.m_y, m_z + acRhs.m_z);
        }

        Vector3& operator+=(const Vector3& acRhs) noexcept
        {
            m_x += acRhs.m_x;
            m_z += acRhs.m_y;
            m_z += acRhs.m_z;

            return *this;
        }

        Vector3 operator-(const Vector3& acRhs) const noexcept
        {
            return Vector3(m_x - acRhs.m_x, m_y - acRhs.m_y, m_z - acRhs.m_z);
        }

        Vector3& operator-=(const Vector3& acRhs) noexcept
        {
            m_x -= acRhs.m_x;
            m_z -= acRhs.m_y;
            m_z -= acRhs.m_z;

            return *this;
        }

        Vector3 operator*(T aRhs) const noexcept
        {
            return Vector3(m_x * aRhs, m_y * aRhs, m_z * aRhs);
        }

        Vector3& operator*=(T aRhs) noexcept
        {
            m_x *= aRhs;
            m_z *= aRhs;
            m_z *= aRhs;

            return *this;
        }

        Vector3 operator/(T aRhs) const noexcept
        {
            const auto reverse = T(1) / aRhs;
            return operator*(reverse);
        }

        Vector3& operator/=(T aRhs) noexcept
        {
            const auto reverse = T(1) / aRhs;
            return operator*=(reverse);
        }

        [[nodiscard]] T LengthSquared() const noexcept
        {
            return m_x * m_x + m_y * m_y + m_z * m_z;
        }

        [[nodiscard]] T Length() const noexcept
        {
            return Sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        }

        [[nodiscard]] Vector3 Normalize() const noexcept
        {
            return *this / Length();
        }

        void Decompose(T& aX, T& aY, T& aZ) const noexcept
        {
            aX = m_x;
            aY = m_y;
            aZ = m_z;
        }

        T m_x;
        T m_y;
        T m_z;
    };

#ifndef TP_VECTOR3_FORCE_INSTANTIATION
    extern template struct Vector3<float>;
    extern template struct Vector3<double>;
#endif
}
