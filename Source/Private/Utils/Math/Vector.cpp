#include "Vector.h"
#include <cstdlib>
#include "Rotator.h"
#include "Quat.h"
#include "MathDK.h"
#include <cmath>

Vector& Vector::operator+=(const Vector& other) noexcept
{
    Data.x += other.Data.x;
    Data.y += other.Data.y;
    Data.z += other.Data.z;
    return *this;
}

Vector Vector::operator+(const Vector& other) const noexcept
{
    Vector result;
    result.Data.x = Data.x + other.Data.x;
    result.Data.y = Data.y + other.Data.y;
    result.Data.z = Data.z + other.Data.z;
    return result;
}

Vector& Vector::operator-=(const Vector& other) noexcept
{
    Data.x -= other.Data.x;
    Data.y -= other.Data.y;
    Data.z -= other.Data.z;
    return *this;
}

Vector Vector::operator-(const Vector& other) const noexcept
{
    Vector result;
    result.Data.x = Data.x - other.Data.x;
    result.Data.y = Data.y - other.Data.y;
    result.Data.z = Data.z - other.Data.z;
    return result;
}

Vector& Vector::operator*=(const float& sc) noexcept
{
    DirectX::XMStoreFloat3A(&Data, (DirectX::XMVectorScale(DirectX::XMLoadFloat3A(&Data), sc)));
    return *this;
}

Vector Vector::operator*(const float& sc) const noexcept
{
    return Vector(DirectX::XMVectorScale(DirectX::XMLoadFloat3A(&Data), sc));
}

Vector& Vector::operator/=(const float& dv) noexcept
{
    if (dv != 0.0f)
    {
        DirectX::XMStoreFloat3A(&Data, (DirectX::XMVectorScale(DirectX::XMLoadFloat3A(&Data), 1 / dv)));
    }
    return *this;
}

Vector Vector::operator/(const float& dv) const noexcept
{
    if (dv != 0.0f)
    {
        return Vector(DirectX::XMVectorScale(DirectX::XMLoadFloat3A(&Data), 1 / dv));
    }
    return Vector::Zero();
}

bool Vector::operator==(const Vector& other) const noexcept
{
    const float epsilon = 0.001;
    return (std::abs(Data.x - other.Data.x) < epsilon) && (std::abs(Data.y - other.Data.y) < epsilon) &&
           (std::abs(Data.z - other.Data.z) < epsilon);
}

bool Vector::operator!=(const Vector& other) const noexcept
{
    return !(*this == other);
}

bool Vector::IsNearEqual(const Vector& other, float epsilon) const noexcept
{
    return (std::abs(Data.x - other.Data.x) < epsilon) && (std::abs(Data.y - other.Data.y) < epsilon) &&
           (std::abs(Data.z - other.Data.z) < epsilon);
}

Rotator Vector::ToRotator() const noexcept
{
    Rotator R;
    R.SetYaw(Math::RadiansToDegrees(Math::Atan2(Data.x, Data.z)));
    R.SetPitch(Math::RadiansToDegrees(Math::Atan2(Data.y, std::sqrt(Data.z * Data.z + Data.x * Data.x))));
    R.SetRoll(0.f);
    return R;
}

Vector Vector::Abs() const noexcept
{
    return Vector(DirectX::XMVectorAbs(ToSIMD()));
}

float Vector::Length() const noexcept
{
    return DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMLoadFloat3A(&Data)));
}

float Vector::LengthSq() const noexcept
{
    return DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(DirectX::XMLoadFloat3A(&Data)));
}

float Vector::LengthEst() const noexcept
{
    return DirectX::XMVectorGetX(DirectX::XMVector3LengthEst(DirectX::XMLoadFloat3A(&Data)));
}

Vector Vector::Normalize() const noexcept
{
    DirectX::XMVECTOR normalized = DirectX::XMVector3Normalize(ToSIMD());
    if (DirectX::XMVector3Equal(normalized, DirectX::XMVectorZero()))
    {
        return Vector::Zero();
    }
    return Vector(normalized);
}

Vector Vector::NormalizeEst() const noexcept
{
    DirectX::XMVECTOR normalized = DirectX::XMVector3NormalizeEst(ToSIMD());
    if (DirectX::XMVector3Equal(normalized, DirectX::XMVectorZero()))
    {
        return Vector::Zero();
    }
    return Vector(normalized);
}

float Vector::Dot(const Vector& other) const noexcept
{
    return DirectX::XMVectorGetX(DirectX::XMVector3Dot(DirectX::XMLoadFloat3A(&Data), DirectX::XMLoadFloat3A(&other.Data)));
}

Vector Vector::Cross(const Vector& other) const noexcept
{
    return Vector(DirectX::XMVector3Cross(ToSIMD(), other.ToSIMD()));
}

float Vector::Angle(const Vector& other) const noexcept
{
    return DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenVectors(ToSIMD(), other.ToSIMD()));
}

Vector Vector::Clamp(const Vector& min, const Vector& max) const noexcept
{
    return Vector(DirectX::XMVectorClamp(ToSIMD(), min.ToSIMD(), max.ToSIMD()));
}

Vector Vector::Rotate(DirectX::FXMVECTOR quat) const noexcept
{
    return Quat::RotateVector(*this, quat);
}

Vector Vector::Rotate(const Quat& quat) const noexcept
{
    return Quat::RotateVector(*this, quat);
}

Vector Vector::Rotate(const Rotator& rot) const noexcept
{
    return Quat::RotateVector(*this, rot.ToQuat());
}

Vector Vector::RotateInverse(DirectX::FXMVECTOR quat) const noexcept
{
    return Vector(DirectX::XMVector3InverseRotate(ToSIMD(), quat));
}

float Vector::Distance(const Vector& a, const Vector& b) noexcept
{
    return DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(a.ToSIMD(), b.ToSIMD())));
}

Vector Vector::Lerp(const Vector& start, const Vector& end, float t) noexcept
{
    return Vector(DirectX::XMVectorLerp(start.ToSIMD(), end.ToSIMD(), t));
}
