#ifndef BASEDATA_BASEDATA_IMPOINT2DD_H_
#define BASEDATA_BASEDATA_IMPOINT2DD_H_
class ImPoint2Dd
{
public:
	double m_v[2];
public:
	ImPoint2Dd(void);
	ImPoint2Dd(const double x, const double y);
	ImPoint2Dd(const double* coord);
	ImPoint2Dd(const ImPoint2Dd &p);
	ImPoint2Dd(const ImPoint2Dd* p);
	~ImPoint2Dd(void);

	const ImPoint2Dd& operator = (const ImPoint2Dd* p);
	ImPoint2Dd operator +(const ImPoint2Dd& v1) const;
	ImPoint2Dd operator +(double d) const;
	const ImPoint2Dd& operator +=(const ImPoint2Dd& v1) ;
	const ImPoint2Dd& operator +=(double d) ;
	ImPoint2Dd operator -() const ;
    ImPoint2Dd operator -(const ImPoint2Dd& v1) const ;
    ImPoint2Dd operator -(double d) const;
    const ImPoint2Dd& operator -=(const ImPoint2Dd& v1);
    const ImPoint2Dd& operator -=(double d);
	ImPoint2Dd operator *(int i) const ;
    ImPoint2Dd operator *(double d) const;
    const ImPoint2Dd& operator *=(double d);
    ImPoint2Dd operator /(int i) const;
    ImPoint2Dd operator /(double d) const ;
    const ImPoint2Dd& operator /=(double d);
	double unit();
	double scalarProduct(const ImPoint2Dd& v);
	double crossProduct(const ImPoint2Dd& v);
	bool isEqual(const ImPoint2Dd& v);
};

#endif