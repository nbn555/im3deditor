#ifndef IMTOOLPATH_TOOLPATH_CLPATH_H_
#define IMTOOLPATH_TOOLPATH_CLPATH_H_
#pragma once
#include <gl\gl.h>

class ImClData;

class ImClPath
{
private:
   ImClData* m_path;
   int m_ncl;
   double m_clWidth;
   float m_clColor[3];
   GLuint m_uiCLDisplayList;
   double m_minCoord[3];
   double m_maxCoord[3];
public:
   ImClPath(void);
public:
   ~ImClPath(void);
public:
   int draw();
   void deleteCurrentPath();
   int readClData(const char* filename);
   int readClData3Axis(const char* filename);
   int readClData5Axis(const char* filename);
   void getBoundingBox(double *minCoord, double *maxCoord);
   ImClData* getPath(){ return m_path; };
};

#endif