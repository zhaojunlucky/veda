#pragma once
#include "Point.hpp"
namespace geo
{
	class Vector
	{
	public:
		Vector::Vector(double x, double y)
		{
			this->x = x;
			this->y = y;
		}


		Vector::~Vector(void)
		{
		}

		double Vector::length() const
		{
			double l = sqrt(pow(2, x) + pow(2, y));
			return l;
		}

		const Vector& Vector::operator+(const Vector& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		const Vector& Vector::operator-(const Vector& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		const Vector& Vector::operator+=(const Vector& v)
		{
			return *this + v;
		}

		const Vector& Vector::operator-=(const Vector& v)
		{
			return *this - v;
		}

		const Vector& Vector::operator*(double factor)
		{
			x *= factor;
			y *= factor;
			return *this;
		}
		double Vector::operator*(const Vector& v) const
		{
			return x*v.x + y*v.y;
		}

		double Vector::angle(const Vector& v) const
		{
			double cos_val = abs((*this*v) / (this->length() * v.length()));
			return acos(cos_val);
		}

		double Vector::product(const Vector& v) const
		{
			return *this*v;
		}

		double Vector::crossProduct(const Vector& v) const
		{
			return x*v.y - v.x*y;
		}

		double Vector::cross(const Point& c1, const Point& c2, const Point& c3)
		{
			return (c2.x - c1.x) * (c3.y - c1.y) - (c2.y - c1.y) * (c3.x - c1.x);
		}
	//private:
		double x;
		double y;
	};


	
}