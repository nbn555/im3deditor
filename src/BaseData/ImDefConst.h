#ifndef IMBASEDATA_BASEDATA_IMDEFCONST_H_
#define IMBASEDATA_BASEDATA_IMDEFCONST_H_
#include "stdio.h"

#define IM_REALLOC_STEP_2D 2
#define IM_REALLOC_STEP 3
#ifndef IM_EPSILON
#define IM_EPSILON 1e-7
#endif

#ifndef IM_MICRO_VALUE
#define IM_MICRO_VALUE 1e-3
#endif

#ifndef IM_PI
#define IM_PI 3.14159265358979323846
#endif

#ifndef IM_SQRT_3_
#define IM_SQRT_3_ 1.732050807568877
#endif

#ifndef IM_SQRT_2_
#define IM_SQRT_2_ 1.414213562373095
#endif

#ifndef IM_MAX_ANGLE_MARK_EDGE
#define IM_MAX_ANGLE_MARK_EDGE 0.9396926 // cos(20 degree)
#endif 

#ifndef IM_MIN_ANGLE_OF_MESH
#define IM_MIN_ANGLE_OF_MESH 0.866025 // cos (46 degree)
#endif

#define IM_FIRST_BIT 1
#define IM_SECOND_BIT 2
#define IM_THIRD_BIT 4

#define IM_VOXEL_WALL_POLYGON 0
#define IM_VOXEL_SIM_POLYGON 1
#define IM_VOXEL_WORK_POLYGON 2

#define MIN(a,b) ((a < b) ? a:b)
#define MAX(a,b) ((a > b) ? a:b)

#define MIN3(a,b,c) ((((a)<(b))&&((a)<(c))) ? (a) : (((b)<(c)) ? (b) : (c)))
#define MAX3(a,b,c) ((((a)>(b))&&((a)>(c))) ? (a) : (((b)>(c)) ? (b) : (c)))

extern double im_epsl;
extern double im_epsl_small;
extern double im_Sq_epsl;

extern int debug_var;

#endif