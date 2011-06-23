#include "StdAfx.h"
#include "CAMSim.h"
#include "ClPath.h"
#include "objStore.h"
#include "ImPoint3Dd.h"
#include "ClData.h"
#include "ClSegment.h"
#include "ClCircle.h"
#include <process.h>  /* _beginthread, _endthread */


ImCAMSim::ImCAMSim(void):
m_clPath(NULL)
,m_pViewHandle(NULL)
,m_currentID(0)
,m_thread(NULL)
{
}

ImCAMSim::~ImCAMSim(void)
{
   if(m_clPath){
      delete m_clPath;
      m_clPath = NULL;
   }
}

int ImCAMSim::drawToolPath()
{
   if(m_clPath){
      m_clPath->draw();
   }
   return 0;
}

int ImCAMSim::readClData(const char *filename)
{
   if(NULL == m_clPath){
      m_clPath = new ImClPath();
   }
      return m_clPath->readClData(filename);
   
   return 0;
}

bool ImCAMSim::getBoundingBox(double *minCoord, double *maxCoord)
{
   if(NULL == m_clPath){
      return false;
   }
   m_clPath->getBoundingBox(minCoord, maxCoord);
   return true;
}

void ImCAMSim::drawTool(){
   //::EnterCriticalSection(&m_cs);
   m_cs_.Lock();
   g_Store.drawTool(m_currentID);
   m_cs_.Unlock();
   //::LeaveCriticalSection(&m_cs);
}

void ImCAMSim::drawWork(int flag){
  // ::EnterCriticalSection(&m_cs);
   m_cs_.Lock();
   g_Store.drawAnObject(m_currentID,flag);
   m_cs_.Unlock();
 //  ::LeaveCriticalSection(&m_cs);
}

struct ThreadFuncForSimulationParam {
  ImCAMSim* CamSim;
} g_thread_func_for_simulation_param;
unsigned int __stdcall g_threadStartSimulation(void* param){

   ThreadFuncForSimulationParam* thread_param = (ThreadFuncForSimulationParam*)param;

  ImCAMSim* camsim = thread_param->CamSim;
  camsim->doSimulation();
  return 0;
}


int ImCAMSim::doSimulation()
{
   ImClData *sp,*ep;
   sp = m_clPath->getPath();
   ImPoint3Dd nv(0.0,0.0,1.0);
   ImPoint3Dd *nv1 = NULL;
   ImPoint3Dd *nv2 = NULL;
   for(ep = sp->getNextCl(); ep != NULL; ep = ep->getNextCl()){
      // segment
      
      if(IM_CL_SEGMENT == ep->getType()){
         nv1 = sp->getDirection();
         if(NULL == nv1){
            nv1 = &nv;
         }
         nv2 = ep->getDirection();
         if(NULL == nv2){
            nv2 = &nv;
         }
         //::EnterCriticalSection(&m_cs);
         m_cs_.Lock();
         g_Store.simCutBySegment(m_currentID,*(sp->getEndPoint()), *nv1,
            *(ep->getEndPoint()),*nv2);
         m_cs_.Unlock();
        //  ::LeaveCriticalSection(&m_cs);
      }
      sp = ep;
      ::SendMessage(m_pViewHandle, IM3DEDITOR_SIMULATION_UPDATEVIEW, (WPARAM)0/*idx*/, (LPARAM)0);
   }
   ::SendMessage(m_pViewHandle, IM3DEDITOR_SIMULATION_UPDATEVIEW, (WPARAM)0/*idx*/, (LPARAM)0);
   return 0;
}


void ImCAMSim::startSimulation()
{
   g_thread_func_for_simulation_param.CamSim = this;
    m_thread = (HANDLE)_beginthreadex(NULL,
                                      0,
                                      g_threadStartSimulation,
                                      &g_thread_func_for_simulation_param,
                                      0,
                                      NULL);
}
void ImCAMSim::pauseSimulation()
{
  // ::EnterCriticalSection(&m_cs);
    ::SuspendThread(m_thread);
  //  ::LeaveCriticalSection(&m_cs);
}
void ImCAMSim::resumeSimulation()
{
  // ::LeaveCriticalSection(&m_cs);
    ::ResumeThread(m_thread);
  //  ::LeaveCriticalSection(&m_cs);
}
void ImCAMSim::stopSimulation()
{
 //  ::EnterCriticalSection(&m_cs);
  if (m_thread) {
    // Cutting thread exit code.
    DWORD exit_code = 0xF0F0F0F0;
    ::TerminateThread(m_thread, exit_code);
    CloseHandle(m_thread);
    m_thread = NULL;
  }
 // ::LeaveCriticalSection(&m_cs);
}