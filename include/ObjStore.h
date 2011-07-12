#pragma once

#include <vector>
class ImPoint3Dd;
class ImBaseObject;
class ObjStore
{
public:
   int m_objectType;// 0 - view stl
                    // 1 - sim CAM
                    // 2 - FEM
	std::vector<ImBaseObject*> m_Object;
public:
	ObjStore(void);
public:
	~ObjStore(void);
public:
   void clearAllObject();
	int drawAnObject(const int wID, const int flag = 0);
	void drawAllObject(const int flag = 0);
   void drawTool(const int wID);
	int createAnObject();
	int createAnObjectFromStl(const char *filename);
	int deleteAObject(const int i);
   int getBoundingBoxOfObject(const int wID, double *ov, double *lv);
   int splitMesh(const int ind = 0);
   int createSimWorkWithMakeWall(const double ov[3], const double lv[3]);
   int createBallTool(const int wID, const int toolID, const double r, 
      const double height, const double cuttingH, const bool tip = false);
   int simCutBySegment(const int wID, const ImPoint3Dd &sp, const ImPoint3Dd &nsp,
      const ImPoint3Dd &ep, const ImPoint3Dd &nep);

};
extern ObjStore g_Store;