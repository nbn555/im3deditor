//#include "StdAfx.h"
#include "ImPoint3Dd.h"
#include "ImDefConst.h"

   
ImPoint3Dd::ImPoint3Dd(const double& mx, const double& my, const double& mz)
{
  v[0] = mx;
  v[1] = my;
  v[2] = mz;
}

ImPoint3Dd::ImPoint3Dd(const double *mv)
{
  v[0] = mv[0];
  v[1] = mv[1];
  v[2] = mv[2];
}
ImPoint3Dd::ImPoint3Dd(const float *mv)
{
  v[0] = (double)mv[0];
  v[1] = (double)mv[1];
  v[2] = (double)mv[2];
}
void ImPoint3Dd::vector_product(const ImPoint3Dd *v0, const ImPoint3Dd *v1)
{
  v[0] = v0->v[1] * v1->v[2] - v0->v[2] * v1->v[1];
  v[1] = v0->v[2] * v1->v[0] - v0->v[0] * v1->v[2];
  v[2] = v0->v[0] * v1->v[1] - v0->v[1] * v1->v[0];
}

  
ImPoint3Dd ImPoint3Dd::vector_product(const ImPoint3Dd &v1) const
{
  ImPoint3Dd temp;
  temp.v[0] = v[1] * v1.v[2] - v[2] * v1.v[1];
  temp.v[1] = v[2] * v1.v[0] - v[0] * v1.v[2];
  temp.v[2] = v[0] * v1.v[1] - v[1] * v1.v[0];
  return temp;
}



/*inline double ImPoint3Dd::unit()
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
}*/
  
double ImPoint3Dd::abs() const
{
  double dd = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
  double d = sqrt(dd);
  return d;
}

 bool ImPoint3Dd::operator == (const ImPoint3Dd& v1) const
  {
	  if( (fabs(v[0] - v1.v[0]) <= IM_EPSILON) && (fabs(v[1] - v1.v[1]) <= IM_EPSILON) && (fabs(v[2] - v1.v[2]) <= IM_EPSILON) ) {
		  return true;
	  } else {
		  double l = sqrt(((v[0] - v1.v[0])*(v[0] - v1.v[0])) + ((v[1] - v1.v[1])*(v[1] - v1.v[1])) + ((v[2] - v1.v[2])*(v[2] - v1.v[2])));
		  if( l <= IM_EPSILON ) 
			  return true;
	  }
	  return false;
  }; 
 bool ImPoint3Dd::isEqualTo(const ImPoint3Dd &v1) const
{
	bool result = false;
	double dx = fabs(this->v[0] - v1.v[0]);
	double dy = fabs(this->v[1] - v1.v[1]);
	double dz = fabs(this->v[2] - v1.v[2]);
	if(dx <= IM_EPSILON && dx <= IM_EPSILON && dz <= IM_EPSILON){
		double dist = sqrt(dx * dx + dy * dy + dz * dz);
		if(dist <= IM_EPSILON){
			result = true;
		}
	}
	return result;
}

  
inline void ImPoint3Dd::rotate(const ImPoint3Dd& av, const double& theta)
{

	double costh, sinth, v0_av, dd;
	ImPoint3Dd nv;
	ImPoint3Dd temp_v;
	temp_v.v[0] = v[0];
	temp_v.v[1] = v[1];
	temp_v.v[2] = v[2];
	costh = cos(theta);
	sinth = sin(theta);
	v0_av = temp_v.scalar_product(av);
	nv = av * temp_v;
	dd = v0_av * ( 1 - costh );
	*this = temp_v * costh + av * dd + nv * sinth;
}

/*
return: 1 out
        0 on wall
		-1 in
*/
int ImPoint3Dd::checkPositionCapsule(const double r, const double leng)
{
	if((v[2] < -r) || (v[2] > (leng + r))){
		return 1;
	}
	double d2 = v[0]*v[0] + v[1]*v[1];
	double r2 = r*r;
	if ((d2 - r2) > IM_EPSILON){
		return 1;
	}
	else if ((d2 - r2) < -IM_EPSILON){
		if(v[2] > 0 && v[2] < leng){
			return -1;
		}
		double del = sqrt(r2 - d2);
		if (v[2] < (-del - IM_EPSILON)){
			return 1;
		}
		else if (v[2] < (-del + IM_EPSILON)){
			return 0;
		}
		else{
			if (v[2] > (del + leng + IM_EPSILON)){
				return 1;
			}
			else if (v[2] > (del + leng - IM_EPSILON)){
				return 0;
			}
			else
			{
				return -1;
			}
		}
	}
	else{
		if (v[2] > (leng + IM_EPSILON) || v[2] < -IM_EPSILON){
			return 1;
		}
		else{
			return 0;
		}
	}
	return 1;
}

/* calculate orthogonal projection of point to plane
 *  param:
 *        pv - a point of plane
 *		 nv - normal vector of plane
 *		 orth - orthogonal projection of point (output)
 * outhor: Nghi
*/
int ImPoint3Dd::orthoToPlane(const ImPoint3Dd &pv, const ImPoint3Dd &nv,
	 ImPoint3Dd &orth) const
{
	//ImPoint3Dd ret;

	//ImPoint3Dd aPoint = pv; // a point on triangle
	ImPoint3Dd v = *this;
		v -= pv;
	double dis2 = v.scalar_product(v);
	if (dis2 < IM_EPSILON)
	{
		orth = pv;
		return 0;
	}
	
	

	if (fabs(v.scalar_product(nv)) < IM_EPSILON)
	{
		orth = *this;
		return 0;
	}
#if 0
	ImPoint3Dd norm2; // normal vector of new plane
	ImPoint3Dd dir; // direction vector of intersection line
	norm2 = v*nv;
	if (norm2.scalar_product(norm2) < IM_EPSILON)
	{
		orth = pv;
		return 0;
	}
	dir = norm2*nv;
	dir = -dir;
	double num,den;
	num = v.scalar_product(dir);
	den = dir.scalar_product(dir);
	double scale = num/den;
	ImPoint3Dd proj = dir*scale;	// projection of A_point on intersection line
	orth = proj + pv;
#else // Nghi: 20/09/10/28/
	double num = v.scalar_product(nv);
	double den = nv.scalar_product(nv);
	double t = -num/den;
	orth = *this + nv*t;
#endif
	return 0;
}

/*! Calculate square minimum distance from a point to a segment.
    @param sp - start point of segment
	@param ep - end point of segment
	@return square minimum distance
	@author Nghi
*/
const double ImPoint3Dd::calcSquareMinDistanceToSeg(const ImPoint3Dd &sp, const ImPoint3Dd &ep) const
{
	double ret=0.0;
	ImPoint3Dd v(ep);
	v -= sp;
	ImPoint3Dd s(this);
	s -= sp;
	double num = v.scalar_product(s);
	if (num < 0){
		ret = distance2(sp);
	}
	else{
		double den = v.scalar_product(v);
		if ( num > den){
			ret = distance2(ep);
		}
		else{
			ret = (den*(s.scalar_product(s)) - num*num)/den;
		}
	}
	return ret;
		
}
/*! Orthorgonal projection vector to a direction.
    @param dir - direction vector
	@author Nghi
*/
void ImPoint3Dd::orthorToVector(const double dir[3])
{
	double num = v[0]*dir[0] + v[1]*dir[1] + v[2]*dir[2];
	double den = dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2];
	double t = num/den;
	v[0] = t*dir[0];
	v[1] = t*dir[1];
	v[2] = t*dir[2];
}

/* Calculate projection of point onto a line.
   @param pv - a point on line
	@param dir - direction vector of line
	@param proj - contain projection point
*/
void ImPoint3Dd::calcProjectionOntoLine(const ImPoint3Dd &pv,
									 const ImPoint3Dd &dir, ImPoint3Dd &proj)
{
	proj = *this;
	proj -= pv;
	proj.orthorToVector(dir.v);
	proj += pv;

}
/*! Calculate square minimum distance from a point to a line.
*   @param pv - a point on line
*	 @param nv - direction vector of line
*	 @return square minimum distance
* 	 @author Nghi
*/
const double ImPoint3Dd::calcSquareDistanceToLine(const ImPoint3Dd &pv,
																	 const ImPoint3Dd &nv) const
{
	ImPoint3Dd u(pv);
	u -= *this;
	double u2 = u.scalar_product(u);
	double v2 = nv.scalar_product(nv);
	double uv = u.scalar_product(nv);
	double dis2 = (u2*v2 - uv*uv)/v2;
	return dis2;
}

/*! Check whether point collision with a voxel
*   @param ov - origin of voxel
*	 @param sz - size of voxel
*	 @return -1 if not collision
             0 if point is on wall of voxel
				 1 if point is inside voxel
* 	 @author Nghi
*/
const int ImPoint3Dd::isInVoxel(const ImPoint3Dd &ov, const double sz) const
{
	if(v[0] < (ov.v[0] - IM_EPSILON) ||
		v[1] < (ov.v[1] - IM_EPSILON) ||
		v[2] < (ov.v[2] - IM_EPSILON) ||
		v[0] > (ov.v[0] + sz + IM_EPSILON) ||
		v[1] > (ov.v[1] + sz + IM_EPSILON) ||
		v[2] > (ov.v[2] + sz + IM_EPSILON)){
			return -1;
	}
	if(v[0] < (ov.v[0] + IM_EPSILON) &&
		v[1] < (ov.v[1] + IM_EPSILON) &&
		v[2] < (ov.v[2] + IM_EPSILON) &&
		v[0] > (ov.v[0] - sz + IM_EPSILON) &&
		v[1] > (ov.v[1] - sz + IM_EPSILON) &&
		v[2] > (ov.v[2] - sz + IM_EPSILON)){
			return 1;
	}
	return 0;
}
