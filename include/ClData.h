#ifndef IMTOOLPATH_TOOLPATH_CLDATA_H_
#define IMTOOLPATH_TOOLPATH_CLDATA_H_
#pragma once
#include "ClPathDefData.h"

class ImPoint3Dd;
class ImClData
{
private:
   IM_CLDATA_TYPE m_type;
   ImClData* m_next;
   ImClData* m_last;
   ImPoint3Dd* m_ep;
   ImPoint3Dd* m_nv;
public:
   ImClData(void);
   ImClData(IM_CLDATA_TYPE type);
public:
   virtual ~ImClData(void);
public:
   void setType(IM_CLDATA_TYPE type){m_type = type;};
   void setNextCl(ImClData* next){m_next = next;};
   void setLastCl(ImClData* last){m_last = last;};
   void setEndPoint(ImPoint3Dd *ep){ m_ep = ep; };
   void setDirection(ImPoint3Dd *nv){ m_nv = nv; };
   IM_CLDATA_TYPE getType() { return m_type; };
   ImClData* getNextCl(){ return m_next; };
   ImClData* getLastCl(){ return m_last; };
   ImPoint3Dd* getEndPoint(){ return m_ep; };
   ImPoint3Dd* getDirection() { return m_nv; };
};

#endif