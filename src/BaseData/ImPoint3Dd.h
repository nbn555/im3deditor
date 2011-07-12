#ifndef BASEDATA_BASEDATA_IMPOINT3DD_H_
#define BASEDATA_BASEDATA_IMPOINT3DD_H_
#pragma once
#include <math.h>
#include "stdio.h"
#include "afx.h"
#include "ImDefConst.h"
class ImPoint3Dd
{
public:
  double v[3];
  ImPoint3Dd(){
    v[0] = 0.0; v[1] = 0.0; v[2] = 0.0;
  }
  
  ImPoint3Dd(const double *mv);
  ImPoint3Dd(const float *mv);
   
  ImPoint3Dd(const double& mx, const double& my, const double& mz);
  
  void vector_product(const ImPoint3Dd *v, const ImPoint3Dd *pv);
  
  ImPoint3Dd(const ImPoint3Dd& other) {
	  v[0] = other.v[0], v[1] = other.v[1], v[2] = other.v[2];
  }
 
  ImPoint3Dd(const ImPoint3Dd* other) {
	  v[0] = other->v[0], v[1] = other->v[1], v[2] = other->v[2];
  }  
  
  ImPoint3Dd vector_product(const ImPoint3Dd &v1) const;
	
  double unit()
  {
     double dd = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
     if(dd < IM_EPSILON * IM_EPSILON){
       v[0] = 0.0;
       v[1] = 0.0;
       v[2] = 0.0;
       return 0.0;
     } else if (fabs(dd - 1.0) < IM_EPSILON) {
       return 1.0;
     }
     double d = sqrt(dd);
     v[0] /= d;
     v[1] /= d;
     v[2] /= d;
     return d;
   };
  
  double abs() const;  
  double abs2() const
	{
		double dd = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
		return dd;
	}
  double scalar_product(const ImPoint3Dd &v1) const
  {
    double d = v[0] * v1.v[0] + v[1] * v1.v[1] + v[2] * v1.v[2];
    return d;
  };
 
  bool isEqualTo(const ImPoint3Dd &v1) const;

  const ImPoint3Dd& operator = (const ImPoint3Dd& other) {
	if (this != (&other)) {
		v[0] = other.v[0], v[1] = other.v[1], v[2] = other.v[2];
	}
	return *this;
  }

  /*
  Operator for copying from a pointer
  */   
  const ImPoint3Dd& operator = (const ImPoint3Dd* other) {
	if (this != other) {
		v[0] = other->v[0], v[1] = other->v[1], v[2] = other->v[2];
	}
	return *this;
  }
     
  ImPoint3Dd operator *(int i) const {
    ImPoint3Dd temp;
    temp.v[0] = v[0] * i;
    temp.v[1] = v[1] * i;
    temp.v[2] = v[2] * i;
    return temp;
  }; 
   
  ImPoint3Dd operator *(double d) const {
    ImPoint3Dd temp;
    temp.v[0] = v[0] * d;
    temp.v[1] = v[1] * d;
    temp.v[2] = v[2] * d;
    return temp;
  };
  
  const ImPoint3Dd& operator *=(double d) {
    v[0] *= d;
    v[1] *= d;
    v[2] *= d;
    return *this;
  };
  
  ImPoint3Dd operator /(int i) const {
    ImPoint3Dd temp;
    temp.v[0] = v[0] / i;
    temp.v[1] = v[1] / i;
    temp.v[2] = v[2] / i;
    return temp;
  }; 
    
  ImPoint3Dd operator /(double d) const {
    ImPoint3Dd temp;
    temp.v[0] = v[0] / d;
    temp.v[1] = v[1] / d;
    temp.v[2] = v[2] / d;
    return temp;
  };
  
  const ImPoint3Dd& operator /=(double d){
    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
    return *this;
  };

  ImPoint3Dd operator +(const ImPoint3Dd& v1) const {
    ImPoint3Dd temp;
    temp.v[0] = v[0] + v1.v[0];
    temp.v[1] = v[1] + v1.v[1];
    temp.v[2] = v[2] + v1.v[2];
    return temp;
  };

  const ImPoint3Dd& operator +=(const ImPoint3Dd& v1) {
    v[0] += v1.v[0];
    v[1] += v1.v[1];
    v[2] += v1.v[2];
    return *this;
  };
  
  ImPoint3Dd operator +(double d) const {
    ImPoint3Dd temp;
    temp.v[0] = v[0] + d;
    temp.v[1] = v[1] + d;
    temp.v[2] = v[2] + d;
    return temp;
  };

  const ImPoint3Dd& operator +=(double d) {
    v[0] += d;
    v[1] += d;
    v[2] += d;
    return *this;
  };
  
  ImPoint3Dd operator -() const {
    ImPoint3Dd temp;
    temp.v[0] = -v[0];
    temp.v[1] = -v[1] ;
    temp.v[2] = -v[2] ;
    return temp;
  };
  
  ImPoint3Dd operator -(const ImPoint3Dd& v1) const {
    ImPoint3Dd temp;
    temp.v[0] = v[0] - v1.v[0];
    temp.v[1] = v[1] - v1.v[1];
    temp.v[2] = v[2] - v1.v[2];
    return temp;
  };
  
  const ImPoint3Dd& operator -=(const ImPoint3Dd& v1){
    v[0] -= v1.v[0];
    v[1] -= v1.v[1];
    v[2] -= v1.v[2];
    return *this;
  };

  ImPoint3Dd operator -(double d) const {
    ImPoint3Dd temp;
    temp.v[0] = v[0] - d;
    temp.v[1] = v[1] - d;
    temp.v[2] = v[2] - d;
    return temp;
  };

  const ImPoint3Dd& operator -=(double d){
    v[0] -= d;
    v[1] -= d;
    v[2] -= d;
    return *this;
  };
  
  void add(const ImPoint3Dd& v1) {
    v[0] = v[0] + v1.v[0];
    v[1] = v[1] + v1.v[1];
    v[2] = v[2] + v1.v[2];
  }
  
  void sub(const ImPoint3Dd& v1) {
    v[0] = v[0] - v1.v[0];
    v[1] = v[1] - v1.v[1];
    v[2] = v[2] - v1.v[2];
  }
  
  ImPoint3Dd operator *(const ImPoint3Dd& v1) const {
    ImPoint3Dd temp;
    temp.v[0] = v[1] * v1.v[2] - v[2] * v1.v[1];
    temp.v[1] = v[2] * v1.v[0] - v[0] * v1.v[2];
    temp.v[2] = v[0] * v1.v[1] - v[1] * v1.v[0];
    return temp;
  };


  double& operator [](int i)
  {
	  return v[i];
  };

  /*<Kiempv 2007/09/04>*/
  double operator [](int i) const
  {
	  return v[i];
  };
  
    
  bool operator == (const ImPoint3Dd& v1) const;
  
  bool operator != (const ImPoint3Dd& v1) const
  {
	  if( (*this) == v1) 
		  return false;
	  else 
		  return true;
  };
  
  double angle(const ImPoint3Dd& v1) const
  {
	  double denominator = (v1.abs()) * (this->abs());
	  if (denominator > 1.0e-9) {
			double _cos = (v[0]*v1.v[0] + v[1]*v1.v[1] + v[2]*v1.v[2]) / denominator;
			return acos(_cos);
	  }
	  return 0.0;
  };
  
  
 inline void rotate(const ImPoint3Dd& av, const double& theta);
 
 const int getIndexOfMaxAbsCoord() const
 {
	 if (fabs(v[0]) >= fabs(v[1])){
		 if (fabs(v[0]) >= fabs(v[2])){
			 return 0;
		 }
		 else{
			 return 2;
		 }
	 }
	 else{
		 if (fabs(v[1]) >= fabs(v[2])){
			 return 1;
		 }
		 else{
			 return 2;
		 }
	 }
 }
 const double distance2(const ImPoint3Dd &vp) const
 {
	 double res;
	 ImPoint3Dd vec(vp);
	 vec -= *this;
	 res = (vec.v[0]*vec.v[0] + vec.v[1]*vec.v[1] + vec.v[2]*vec.v[2]);
	 return res;
 }
 int checkPositionCapsule(const double r,const double leng);
 int orthoToPlane(const ImPoint3Dd &pv, const ImPoint3Dd &nv,
	 ImPoint3Dd &orth) const;
 const double calcSquareMinDistanceToSeg(const ImPoint3Dd &sp, const ImPoint3Dd &ep) const;
 void orthorToVector(const double dir[3]);
 void calcProjectionOntoLine(const ImPoint3Dd &pv, const ImPoint3Dd &dir, ImPoint3Dd &proj);
 const double calcSquareDistanceToLine(const ImPoint3Dd &pv, const ImPoint3Dd &nv) const;
 const int isInVoxel(const ImPoint3Dd &ov, const double sz) const;
};
#endif