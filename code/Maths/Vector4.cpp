#include "Maths/Vector4.hpp"
#include "Maths/MathUtils.hpp"

#include <algorithm> // std::max

Vector4::Vector4() : x(0), y(0), z(0), w(0)
{
}

Vector4::Vector4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w)
{
}

Vector4::Vector4(CNS Vector4 &other) : x(other.x), y(other.y), z(other.z), w(other.w)
{
}

Vector4::Vector4(CNS Vector3 &other) : x(other.x), y(other.y), z(other.z), w(0)
{
}

Vector4::Vector4(CNS Vector2 &other) : x(other.x), y(other.y), z(0), w(0)
{
}

Vector4::Vector4(CNS Vector3 &other, f32 w) : x(other.x), y(other.y), z(other.z), w(w)
{
}

Vector4::Vector4(CNS Vector2 &other, f32 z, f32 w) : x(other.x), y(other.y), z(z), w(w)
{
}

Vector4 &Vector4::set(f32 x, f32 y, f32 z, f32 w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

Vector4 &Vector4::set(CNS Vector2 &rhs)
{
	this->set(rhs.x, rhs.y, 0, 0);
	return *this;
}

Vector4 &Vector4::set(CNS Vector3 &rhs)
{
	this->set(rhs.x, rhs.y, rhs.z, 0);
	return *this;
}

Vector4 &Vector4::set(CNS Vector4 &rhs)
{
	this->set(rhs.x, rhs.y, rhs.z, rhs.w);
	return *this;
}

Vector4 &Vector4::add(CNS Vector4 &rhs)
{
	// can be parallelized with SIMD auto-vectorization
	x = x + rhs.x;
	y = y + rhs.y;
	z = z + rhs.z;
	w = w + rhs.w;
	return *this;
}

Vector4 &Vector4::sub(CNS Vector4 &rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
	z = z - rhs.z;
	w = w - rhs.w;
	return *this;
}

Vector4 &Vector4::mul(CNS Vector4 &rhs)
{
	x = x * rhs.x;
	y = y * rhs.y;
	z = z * rhs.z;
	w = w * rhs.w;
	return *this;
}

Vector4 &Vector4::div(CNS Vector4 &rhs)
{
	ASSERT_MSG(rhs.x != 0, "Division by zero.");
	ASSERT_MSG(rhs.y != 0, "Division by zero.");
	ASSERT_MSG(rhs.z != 0, "Division by zero.");
	ASSERT_MSG(rhs.w != 0, "Division by zero.");
	x = x / rhs.x;
	y = y / rhs.y;
	z = z / rhs.z;
	w = w / rhs.w;
	return *this;
}

Vector4 &Vector4::add(f32 rhs)
{
	x = x + rhs;
	y = y + rhs;
	z = z + rhs;
	w = w + rhs;
	return *this;
}

Vector4 &Vector4::sub(f32 rhs)
{
	x = x - rhs;
	y = y - rhs;
	z = z - rhs;
	w = w - rhs;
	return *this;
}

Vector4 &Vector4::mul(f32 rhs)
{
	x = x * rhs;
	y = y * rhs;
	z = z * rhs;
	w = w * rhs;
	return *this;
}

Vector4 &Vector4::div(f32 rhs)
{
	ASSERT_MSG(rhs != 0, "Division by zero.");
	x = x / rhs;
	y = y / rhs;
	z = z / rhs;
	w = w / rhs;
	return *this;
}

f32 Vector4::dot(CNS Vector4 &v) CNS
{
	// SIMD-optimized
	f32 xx = x * v.x;
	f32 yy = y * v.y;
	f32 zz = z * v.z;
	f32 ww = w * v.w;

	f32 dot = xx;
	dot = dot + yy;
	dot = dot + zz;
	dot = dot + ww;

	return dot;
}

f32 Vector4::sqrlen() CNS
{
	return this->dot(*this);
}

f32 Vector4::sqrdst(CNS Vector4 &v) CNS
{
	Vector4 sub = Vector4(v) - (*this);
	return sub.dot(sub);
}

f32 Vector4::len() CNS
{
	return sqrtf(this->sqrlen());
}

f32 Vector4::max() CNS
{
	return std::max(x, std::max(y, std::max(z, w)));
}

f32 Vector4::min() CNS
{
	return std::min(x, std::min(y, std::min(z, w)));
}

Vector4 &Vector4::nor()
{
	f32 len = this->len();

	ASSERT_MSG(len > 0, "Length is zero.");
	this->div(len);

	return *this;
}

f32 Vector4::dst(CNS Vector4 &v) CNS
{
	return sqrtf(this->sqrdst(v));
}

bool Vector4::eq(CNS Vector4 &v, f32 e) CNS
{
	return MathUtils::eqf(this->x, v.x, e) && MathUtils::eqf(this->y, v.y, e) && MathUtils::eqf(this->z, v.z, e) && MathUtils::eqf(this->w, v.w, e);
}

bool Vector4::eq(CNS Vector4 &v) CNS
{
	return MathUtils::eqf(this->x, v.x) && MathUtils::eqf(this->y, v.y) && MathUtils::eqf(this->z, v.z) && MathUtils::eqf(this->w, v.w);
}

Vector4 &Vector4::lerp(CNS Vector4 &target, f32 t)
{
	//start + percent*(end - start)
	(*this) += (Vector4(target) - (*this)) * t;
	return *this;
}

Vector4 &Vector4::clamp(f32 maxLength)
{
	if (this->sqrlen() > maxLength * maxLength)
	{
		this->nor();
		this->mul(maxLength);
	}

	return *this;
}

SERIALIZE_IMPL(Vector4)
{
	DO_SERIALIZE("x", x)
	DO_SERIALIZE("y", y)
	DO_SERIALIZE("z", z)
	DO_SERIALIZE("w", w)
}

DESERIALIZE_IMPL(Vector4)
{
	DO_DESERIALIZE("x", x);
	DO_DESERIALIZE("y", y);
	DO_DESERIALIZE("z", z);
	DO_DESERIALIZE("w", w);
}