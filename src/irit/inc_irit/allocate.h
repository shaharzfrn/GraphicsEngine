/*****************************************************************************
* Definitions, visible to others, of the dynamic allocator module.	     *
******************************************************************************
* (C) Gershon Elber, Technion, Israel Institute of Technology                *
******************************************************************************
* Written by:  Gershon Elber				Ver 0.2, Mar. 1990   *
*****************************************************************************/

#ifndef	IRIT_ALLOCATE_GH
#define	IRIT_ALLOCATE_GH

#include "inc_irit/iritprsr.h"
#include "inc_irit/obj_dpnd.h"
#include "inc_irit/cagd_lib.h"
#include "inc_irit/trim_lib.h"
#include "inc_irit/triv_lib.h"

#define IP_SET_OBJ_NAME2(PObj, Name) { \
    const char *_p = (Name); \
    if ((PObj) -> ObjName != NULL) \
	IritFree((PObj) -> ObjName); \
    (PObj) -> ObjName = (_p && _p[0] != 0 ? IritStrdup(_p) : NULL); }
#define IP_CAT_OBJ_NAME(PObj, Apndx) { \
    char Name[IRIT_LINE_LEN_VLONG]; \
    strcpy(Name, (PObj) -> ObjName ? (PObj) -> ObjName : ""); \
    strcat(Name, Apndx); \
    IP_SET_OBJ_NAME2(PObj, Name); }
#define IP_SET_OBJ_NAME(PObj, Str, Param) { \
    char Name[IRIT_LINE_LEN_VLONG]; \
    sprintf(Name, Str, Param); \
    IP_SET_OBJ_NAME2(PObj, Name); }
#define IP_CLR_OBJ_NAME(PObj) { \
    if ((PObj) -> ObjName != NULL) \
	IritFree((PObj) -> ObjName); \
    (PObj) -> ObjName = NULL; }
#define IP_VALID_OBJ_NAME(PObj) ((PObj) -> ObjName != NULL && \
				 (PObj) -> ObjName[0] != 0)
#define IP_GET_OBJ_NAME(PObj) (IP_VALID_OBJ_NAME(PObj) ? (PObj) -> ObjName : "")

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

const char *IPObjTypeAsString(const IPObjectStruct *PObj);
void IPFreeObjectSlots(IPObjectStruct *PObj);
void IPFreeObjectGeomData(IPObjectStruct *PObj);
void IPFreeObjectBase(IPObjectStruct *O);
IPVertexStruct *IPAllocVertex(IrtBType Tags,
			      IPPolygonStruct *PAdj,
			      IPVertexStruct *Pnext);
IPVertexStruct *IPAllocVertex2(IPVertexStruct *Pnext);
IPPolygonStruct *IPAllocPolygon(IrtBType Tags,
				IPVertexStruct *V,
				IPPolygonStruct *Pnext);
IPObjectStruct *IPAllocObject(const char *Name,
			      IPObjStructType ObjType,
			      IPObjectStruct *Pnext);
void IPFreeVertex(IPVertexStruct *V);
void IPFreePolygon(IPPolygonStruct *P);
void IPFreeObject(IPObjectStruct *O);
void IPFreeVertexList(IPVertexStruct *VFirst);
void IPFreePolygonList(IPPolygonStruct *PPoly);
void IPFreeObjectList(IPObjectStruct *O);

#ifdef DEBUG
#define IPFreeVertex(V)          { IPFreeVertex(V); V = NULL; }
#define IPFreePolygon(P)         { IPFreePolygon(P); P = NULL; }
#define IPFreeObject(O)          { IPFreeObject(O); O = NULL; }
#define IPFreeVertexList(VFirst) { IPFreeVertexList(VFirst); VFirst = NULL; }
#define IPFreePolygonList(PPoly) { IPFreePolygonList(PPoly); PPoly = NULL; }
#define IPFreeObjectList(O)      { IPFreeObjectList(O); O = NULL; }
#endif /* DEBUG */

IPPolyVrtxArrayStruct *IPPolyVrtxArrayNew(int NumVrtcs, int NumPlys);
IPPolyVrtxArrayStruct *IPPolyVrtxArrayNew2(IPObjectStruct *PObj);
void IPPolyVrtxArrayFree(IPPolyVrtxArrayStruct *PVIdx);

int IPListObjectLength(const IPObjectStruct *PObj);
int IPListObjectFind(const IPObjectStruct *PObjList,
		     const IPObjectStruct *PObj);
void IPListObjectInsert(IPObjectStruct *PObjList,
			int Index,
			IPObjectStruct *PObjItem);
void IPListObjectInsert2(IPObjectStruct *PObj,
			 int Index,
			 IPObjectStruct *PObjItem);
void IPListObjectAppend(IPObjectStruct *PObjList, IPObjectStruct *PObjItem);
void IPListObjectAppendList(IPObjectStruct *PObj, IPObjectStruct *PObjNew);
IPObjectStruct *IPListObjectDelete(IPObjectStruct *PObj, 
				   int Index,
				   int FreeItem);
void IPListObjectDelete2(IPObjectStruct *PObj,
			 IPObjectStruct *PObjToDel,
			 int FreeItem);
IPObjectStruct *IPListObjectGet(const IPObjectStruct *PObjList, int Index);
void IPPropagateObjectName(IPObjectStruct *Obj,
			   const char *ObjName,
			   int ForceRename);
void IPReallocNewTypeObject(IPObjectStruct *PObj, IPObjStructType ObjType);

IPObjectStruct *IPGenPolyObject(const char *Name,
				IPPolygonStruct *Pl,
				IPObjectStruct *Pnext);
IPObjectStruct *IPGenPOLYObject(IPPolygonStruct *Pl);
IPObjectStruct *IPGenPolylineObject(const char *Name,
				    IPPolygonStruct *Pl,
				    IPObjectStruct *Pnext);
IPObjectStruct *IPGenPOLYLINEObject(IPPolygonStruct *Pl);
IPObjectStruct *IPGenPointListObject(const char *Name,
				     IPPolygonStruct *Pl,
				     IPObjectStruct *Pnext);
IPObjectStruct *IPGenPOINTLISTObject(IPPolygonStruct *Pl);
IPObjectStruct *IPGenCrvObject(const char *Name,
			       CagdCrvStruct *Crv,
			       IPObjectStruct *Pnext);
IPObjectStruct *IPGenCRVObject(CagdCrvStruct *Crv);
IPObjectStruct *IPGenSrfObject(const char *Name,
			       CagdSrfStruct *Srf,
			       IPObjectStruct *Pnext);
IPObjectStruct *IPGenSRFObject(CagdSrfStruct *Srf);
IPObjectStruct *IPGenTrimSrfObject(const char *Name,
				   TrimSrfStruct *TrimSrf,
				   IPObjectStruct *Pnext);
IPObjectStruct *IPGenTRIMSRFObject(TrimSrfStruct *TrimSrf);
IPObjectStruct *IPGenTrivarObject(const char *Name,
				  TrivTVStruct *Triv,
				  IPObjectStruct *Pnext);
IPObjectStruct *IPGenTRIVARObject(TrivTVStruct *Triv);
IPObjectStruct *IPGenTriSrfObject(const char *Name,
				  TrngTriangSrfStruct *TriSrf,
				  IPObjectStruct *Pnext);
IPObjectStruct *IPGenTRISRFObject(TrngTriangSrfStruct *TriSrf);
IPObjectStruct *IPGenModelObject(const char *Name,
				 MdlModelStruct *Model,
				 IPObjectStruct *Pnext);
IPObjectStruct *IPGenMODELObject(MdlModelStruct *Model);
IPObjectStruct *IPGenVModelObject(const char *Name,
				  VMdlVModelStruct *VModel,
				  IPObjectStruct *Pnext);
IPObjectStruct *IPGenVMODELObject(VMdlVModelStruct *VModel);
IPObjectStruct *IPGenVxlVMdlObject(const char *Name,
				   VMdlVoxelVModelStruct *VxlVModel,
				   IPObjectStruct *Pnext);
IPObjectStruct *IPGenVXLVMDLObject(VMdlVoxelVModelStruct *VxlVModel);
IPObjectStruct *IPGenMultiVarObject(const char *Name,
				    MvarMVStruct *MultiVar,
				    IPObjectStruct *Pnext);
IPObjectStruct *IPGenMULTIVARObject(MvarMVStruct *MultiVar);
IPObjectStruct *IPGenInstncObject(const char *Name,
				  const char *InstncName,
				  const IrtHmgnMatType *Mat,
				  IPObjectStruct *Pnext);
IPObjectStruct *IPGenINSTNCObject(const char *InstncName,
				  const IrtHmgnMatType *Mat);
IPObjectStruct *IPGenCtlPtObject(const char *Name,
				 CagdPointType PtType,
				 const IrtRType *Coords,
				 IPObjectStruct *Pnext);
IPObjectStruct *IPGenCTLPTObject(CagdPointType PtType, const IrtRType *Coords);
IPObjectStruct *IPGenNumObject(const char *Name,
			       const IrtRType *R,
			       IPObjectStruct *Pnext);
IPObjectStruct *IPGenNUMObject(const IrtRType *R);
IPObjectStruct *IPGenNUMValObject(IrtRType R);
IPObjectStruct *IPGenPtObject(const char *Name,
			      const IrtRType *Pt0,
			      const IrtRType *Pt1,
			      const IrtRType *Pt2,
			      IPObjectStruct *Pnext);
IPObjectStruct *IPGenPTObject(const IrtRType *Pt0,
			      const IrtRType *Pt1,
			      const IrtRType *Pt2);
IPObjectStruct *IPGenVecObject(const char *Name,
			       const IrtRType *Vec0,
			       const IrtRType *Vec1,
			       const IrtRType *Vec2,
			       IPObjectStruct *Pnext);
IPObjectStruct *IPGenVECObject(const IrtRType *Vec0,
			       const IrtRType *Vec1,
			       const IrtRType *Vec2);
IPObjectStruct *IPGenStrObject(const char *Name,
			       const char *Str,
			       IPObjectStruct *Pnext);
IPObjectStruct *IPGenSTRObject(const char *Str);
IPObjectStruct *IPGenListObject(const char *Name,
				IPObjectStruct *First,
				IPObjectStruct *Pnext);
IPObjectStruct *IPGenLISTObject(IPObjectStruct *First);
IPObjectStruct *IPGenPlaneObject(const char *Name,
				 const IrtRType *Plane0,
				 const IrtRType *Plane1,
				 const IrtRType *Plane2,
				 const IrtRType *Plane3,
				 IPObjectStruct *Pnext);
IPObjectStruct *IPGenPLANEObject(const IrtRType *Plane0,
				 const IrtRType *Plane1,
				 const IrtRType *Plane2,
				 const IrtRType *Plane3);
IPObjectStruct *IPGenMatObject(const char *Name,
			       IrtHmgnMatType Mat,
			       IPObjectStruct *Pnext);
IPObjectStruct *IPGenMATObject(IrtHmgnMatType Mat);

void IPCopyObjectAuxInfo(IPObjectStruct *Dest, const IPObjectStruct *Src);
IPObjectStruct *IPCopyObject(IPObjectStruct *Dest,
			     const IPObjectStruct *Src,
			     int CopyAll);
IPObjectStruct *IPCopyObject2(IPObjectStruct *Dest,
			      const IPObjectStruct *Src,
			      int CopyNext,
			      int CopyName);
IPObjectStruct *IPCopyObjectGeomData(IPObjectStruct *Dest,
				     const IPObjectStruct *Src,
				     int CopyNext,
				     int CopyName);
int IPSetCopyObjectReferenceCount(int RefCount);

IPObjectStruct *IPCopyObjectList(const IPObjectStruct *PObjs, int CopyAll);
IPPolygonStruct *IPCopyPolygon(const IPPolygonStruct *Src);
IPPolygonStruct *IPCopyPolygonList(const IPPolygonStruct *Src);
IPVertexStruct *IPCopyVertex(const IPVertexStruct *Src);
IPVertexStruct *IPCopyVertexList(const IPVertexStruct *Src);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif	/* IRIT_ALLOCATE_GH */
