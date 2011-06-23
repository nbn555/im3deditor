#ifndef IM3DEDITOR_3DEDITOR_CAMSIM_H_
#define IM3DEDITOR_3DEDITOR_CAMSIM_H_
#pragma once
#include "afxmt.h"

#define IM3DEDITOR_SIMULATION_UPDATEVIEW (WM_APP + 100)
class ImClPath;

class ImCAMSim
{
private:
   ImClPath* m_clPath;
   int m_currentID;
   //CRITICAL_SECTION m_cs;
   CCriticalSection m_cs_;
   HWND m_pViewHandle;
   HANDLE m_thread;  // Handle simulation thread.
public:
   ImCAMSim(void);
public:
   ~ImCAMSim(void);
public:
   int readClData(const char* filename);
   int drawToolPath();
   bool getBoundingBox(double *minCoord, double *maxCoord);
   int doSimulation();
   void setCurrentID(int id){ m_currentID = id; };
   void setViewhandle(HWND pHd){ m_pViewHandle = pHd;};
   void drawTool();
   void drawWork(int flag);
   void stopSimulation();
   void startSimulation();
   void pauseSimulation();
   void resumeSimulation();
};

#endif