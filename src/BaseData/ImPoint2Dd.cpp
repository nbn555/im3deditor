#include "ImPoint2Dd.h"
#include "ImDefConst.h"
#include <math.h>
ImPoint2Dd::ImPoint2Dd(void)
{
	m_v[0] = 0.0;
	m_v[1] = 0.0;
}

ImPoint2Dd::ImPoint2Dd(const double x, const double y)
{
	m_v[0] = x;
	m_v[1] = y;
}
ImPoint2Dd::ImPoint2Dd(const double* coord)
{
	m_v[0] = coord[0];
	m_v[1] = coord[1];
}
ImPoint2Dd::ImPoint2Dd(const ImPoint2Dd &p)
{
	m_v[0] = p.m_v[0];
	m_v[1] = p.m_v[1];
}
ImPoint2Dd::ImPoint2Dd(const ImPoint2Dd* p)
{
	m_v[0] = p->m_v[0];
	m_v[1] = p->m_v[1];
}
ImPoint2Dd::~ImPoint2Dd(void)
{
}

const ImPoint2Dd& ImPoint2Dd::operator = (const ImPoint2Dd* p) {
	if (this != p) {
		m_v[0] = p->m_v[0];
		m_v[1] = p->m_v[1];
	}
	return *this;
}

ImPoint2Dd ImPoint2Dd::operator +(const ImPoint2Dd& v) const
{
	ImPoint2Dd temp(this);
	temp.m_v[0] += v.m_v[0];
	temp.m_v[1] += v.m_v[1];
	return temp;
}

ImPoint2Dd ImPoint2Dd::operator +(double d) const
{
	ImPoint2Dd temp(this);
	temp.m_v[0] += d;
	temp.m_v[1] += d;
	return temp;
}

const ImPoint2Dd& ImPoint2Dd::operator +=(const ImPoint2Dd& v) 
{
	m_v[0] += v.m_v[0];
	m_v[1] += v.m_v[1];
	return *this;
}

const ImPoint2Dd& ImPoint2Dd::operator +=(double d) 
{
	m_v[0] += d;
	m_v[1] += d;
	return *this;
}

ImPoint2Dd ImPoint2Dd::operator -() const 
{
	ImPoint2Dd temp(-m_v[0],-m_v[1]);
	return temp;
}

ImPoint2Dd ImPoint2Dd::operator -(const ImPoint2Dd& v) const 
{
	ImPoint2Dd temp(this);
	temp.m_v[0] -= v.m_v[0];
	temp.m_v[1] -= v.m_v[1];
	return temp;
}

ImPoint2Dd ImPoint2Dd::operator -(double d) const
{
	ImPoint2Dd temp(this);
	temp.m_v[0] -= d;
	temp.m_v[1] -= d;
	return temp;
}

const ImPoint2Dd& ImPoint2Dd::operator -=(const ImPoint2Dd& v)
{
	m_v[0] -= v.m_v[0];
	m_v[1] -= v.m_v[1];
	return *this;
}

const ImPoint2Dd& ImPoint2Dd::operator -=(double d)
{
	m_v[0] -= d;
	m_v[1] -= d;
	return *this;
}

ImPoint2Dd ImPoint2Dd::operator *(int i) const 
{
	ImPoint2Dd temp(this);
	temp.m_v[0] *= i;
	temp.m_v[1] *= i;
	return temp;
}

ImPoint2Dd ImPoint2Dd::operator *(double d) const
{
	ImPoint2Dd temp(this);
	temp.m_v[0] *= d;
	temp.m_v[1] *= d;
	return temp;
}

const ImPoint2Dd& ImPoint2Dd::operator *=(double d)
{
	m_v[0] *= d;
	m_v[1] *= d;
	return *this;
}

ImPoint2Dd ImPoint2Dd::operator /(int i) const
{
	ImPoint2Dd temp(this);
	temp.m_v[0] /= i;
	temp.m_v[1] /= i;
	return temp;
}

ImPoint2Dd ImPoint2Dd::operator /(double d) const 
{
	ImPoint2Dd temp(this);
	temp.m_v[0] /= d;
	temp.m_v[1] /= d;
	return temp;
}

const ImPoint2Dd& ImPoint2Dd::operator /=(double d)
{
	m_v[0] /= d;
	m_v[1] /= d;
	return *this;
}

double ImPoint2Dd::unit()
{
	double d = m_v[0]*m_v[0] + m_v[1]*m_v[1];
	if(fabs(d - 1.0) > IM_EPSILON){
		d = sqrt(d);
		m_v[0] /= d;
		m_v[1] /= d;
	}
	return d;
}
double ImPoint2Dd::scalarProduct(const ImPoint2Dd& v)
{
	double dret = m_v[0]*v.m_v[0] + m_v[1]*v.m_v[1];
	return dret;
}

double ImPoint2Dd::crossProduct(const ImPoint2Dd& v)
{
	double dret = m_v[0]*v.m_v[1] - m_v[1]*v.m_v[0];
	return dret;
}

bool ImPoint2Dd::isEqual(const ImPoint2Dd& v)
{
	if(fabs(m_v[0] - v.m_v[0]) < IM_EPSILON &&
		fabs(m_v[1] - v.m_v[1]) < IM_EPSILON){
			return true;
	}
	return false;
}