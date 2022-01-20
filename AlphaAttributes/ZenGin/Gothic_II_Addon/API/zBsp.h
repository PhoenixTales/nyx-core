// Supported with union (c) 2018 Union team

#ifndef __ZBSP_H__VER3__
#define __ZBSP_H__VER3__

#include "z3d.h"
#include "zBVolume.h"
#include "zPluecker.h"

namespace Gothic_II_Addon {
  const int zEMaxPolyThreshold        = 500;
  const int zBSP_LEAF_LIGHT_UNDEFINED = -99;

  enum zTBspPolyCont {
    zBSP_CONT_NOTHING = 0,
    zBSP_CONT_MESH    = -1,
    zBSP_CONT_BSP     = -2
  };

  enum zTBspNodeType {
    zBSP_LEAF = 1,
    zBSP_NODE = 0
  };

  enum zTBspTreeMode {
    zBSP_MODE_INDOOR,
    zBSP_MODE_OUTDOOR
  };

  enum zTBspBuildType {
    zBSP_TYPE_OCTREE,
    zBSP_TYPE_OCTREE_SOLID,
    zBSP_TYPE_LEAFY_BSP
  };

  class zCMeshOctreeNode {
  public:
    enum zEOctreeChild {
      zEOctreeChild_Min = 0,
      zEOctreeChild_1   = zEOctreeChild_Min,
      zEOctreeChild_2,
      zEOctreeChild_3,
      zEOctreeChild_4,
      zEOctreeChild_5,
      zEOctreeChild_6,
      zEOctreeChild_7,
      zEOctreeChild_8,
      zEOctreeChild_Max
    };

    zCMeshOctreeNode* m_parrChildren[8];
    zTBBox3D m_Box;
    unsigned char m_bIsRoot : 1;
    unsigned char m_bIsNode : 1;
    unsigned char m_bIsLeaf : 1;
    zCArray<zCPolygon*> m_arrPolys;

    zCMeshOctreeNode() {}
    void zCMeshOctreeNode_OnInit( int )                                                                    zCall( 0x0053B190 );
    zCMeshOctreeNode( int a0 )                                                                             zInit( zCMeshOctreeNode_OnInit( a0 ));
    ~zCMeshOctreeNode()                                                                                    zCall( 0x0053B1E0 );
    void EnlargeBox( zCArray<zCPolygon*> const& )                                                          zCall( 0x0053B280 );
    void CopyPolys( zCArray<unsigned char> const&, zCArray<zCPolygon*> const&, int, zCArray<zCPolygon*>& ) zCall( 0x0053B3F0 );
    void Build( zCArray<zCPolygon*> const&, int )                                                          zCall( 0x0053B550 );
  };

  class zCRayTurbo {
  public:
    const zCBspNode* m_BspNode;
    zCMeshOctreeNode m_MeshOctreeRoot;

    zCRayTurbo() {}
    void zCRayTurbo_OnInit( zCBspNode const& )                         zCall( 0x0053ADE0 );
    zCRayTurbo( zCBspNode const& a0 )                                  zInit( zCRayTurbo_OnInit( a0 ));
    ~zCRayTurbo()                                                      zCall( 0x0053AF50 );
    void CalculateOptimizedPolyList( zCArray<zCPolygon*>& )            zCall( 0x0053AFD0 );
    void TraverseTree( zCArray<zCPolygon*>&, zCMeshOctreeNode const& ) zCall( 0x0053AFF0 );
  };

  class zCRayTurboAdmin {
  public:

    zTRayTurboValMap<zCBspNode*, zCRayTurbo*> m_mapRayTurbos;

    void zCRayTurboAdmin_OnInit()                         zCall( 0x0053A650 );
    zCRayTurboAdmin()                                     zInit( zCRayTurboAdmin_OnInit() );
    ~zCRayTurboAdmin()                                    zCall( 0x0053A7C0 );
    zCRayTurbo* GetRayTurboItem( zCBspNode const* ) const zCall( 0x0053A9C0 );
    zCRayTurbo* CreateRayTurboItem( zCBspNode const* )    zCall( 0x0053AA00 );
    zCRayTurbo* GetOrCreate( zCBspNode const* )           zCall( 0x0053AB90 );
    int CanHaveSpatialInfo( zCBspNode const* )            zCall( 0x0053AC00 );
    void ReleaseSpatialDatabase()                         zCall( 0x0053AC30 );
    static zCRayTurboAdmin& GetInstance()                 zCall( 0x0053A970 );
    static void SetPolyTreshold( int )                    zCall( 0x0053ADC0 );
    static int GetPolyTreshold()                          zCall( 0x0053ADD0 );

    // static properties
    static int& s_iPolyTreshold;
  };

  class zCBspBase {
  public:
    zCBspNode* parent;
    zTBBox3D bbox3D;
    zCPolygon** polyList;
    int numPolys;
    zTBspNodeType nodeType;

    zCBspBase() {}
    void DescribeTree( int )                                                                               zCall( 0x00529A10 );
    int CountNodes()                                                                                       zCall( 0x0052CBC0 );
    void __fastcall AddVobsToRenderListSubtree( int )                                                      zCall( 0x0052EA40 );
    zTBBox2D GetScreenBBox2D() const                                                                       zCall( 0x0052EB10 );
    void CollectNodeLights()                                                                               zCall( 0x0052ED80 );
    void RenderTrivInIndoor()                                                                              zCall( 0x0052F0A0 );
    void __fastcall RenderIndoor( int )                                                                    zCall( 0x0052F0E0 );
    void __fastcall RenderNodeOutdoor( int )                                                               zCall( 0x0052F180 );
    void __fastcall AddVobToLeafs( zCVob* )                                                                zCall( 0x00530B10 );
    void __fastcall AddVobLightToLeafs( zCVobLight* )                                                      zCall( 0x00530C50 );
    void __fastcall RemoveVobFromLeafs( zCVob* )                                                           zCall( 0x00530F60 );
    void __fastcall CollectVobsSubtree( zCArray<zCVob*>& ) const                                           zCall( 0x00531100 );
    void __fastcall CollectVobsInBBox3D( zCArray<zCVob*>&, zTBBox3D const& ) const                         zCall( 0x00531110 );
    void __fastcall CollectVobsSubtree_I( zCArray<zCVob*>& ) const                                         zCall( 0x00531120 );
    void __fastcall CollectLightVobsSubtree( zCArray<zCVob*>& ) const                                      zCall( 0x00531300 );
    void __fastcall CollectLightVobsSubtree_I( zCArray<zCVob*>& ) const                                    zCall( 0x00531310 );
    void __fastcall CollectVobsInBBox3D_I( zCArray<zCVob*>&, zTBBox3D const& ) const                       zCall( 0x005314F0 );
    zCBspLeaf* FindLeaf( zVEC3 const& )                                                                    zCall( 0x00531930 );
    int __fastcall CheckRayAgainstPolys( zVEC3 const&, zVEC3 const&, zVEC3&, zCRayTurbo* ) const           zCall( 0x00531AA0 );
    int __fastcall CheckRayAgainstPolysNearestHit( zVEC3 const&, zVEC3 const&, zVEC3&, zCRayTurbo* ) const zCall( 0x00531D30 );
    int __fastcall CheckRayAgainstPolysCache( zVEC3 const&, zVEC3 const&, zVEC3& ) const                   zCall( 0x00532040 );
    int __fastcall RayIntersection( zVEC3 const&, zVEC3 const&, zVEC3& ) const                             zCall( 0x005321F0 );
    void CollectPolysInBBox3DRec() const                                                                   zCall( 0x00532C80 );
    int __fastcall CollectPolysInBBox3D( zTBBox3D const&, zCPolygon**&, int& ) const                       zCall( 0x00532EB0 );
    void SortNodePolys( zCBspTree* )                                                                       zCall( 0x005344C0 );
    void SaveBINRec( zCFileBIN& )                                                                          zCall( 0x00537DA0 );
    void LoadBINRec( zCFileBIN& )                                                                          zCall( 0x00537E90 );
    static void ReleaseStaticReferences()                                                                  zCall( 0x00528FD0 );
    static void __fastcall RenderOutdoor( zCBspBase*, zTBBox3D, int, int )                                 zCall( 0x0052F490 );
  };

  class zCBspNode : public zCBspBase {
  public:
    zTPlane plane;
    zCBspBase* front;
    zCBspBase* back;
    zCBspLeaf* leafList;
    int numLeafs;
    unsigned char planeSignbits;

    void zCBspNode_OnInit()              zCall( 0x0052C6A0 );
    zCBspNode()                          zInit( zCBspNode_OnInit() );
    void CalcPlaneSignbits( zCBspTree* ) zCall( 0x00530AD0 );
  };

  class zCBspLeaf : public zCBspBase {
  public:

    int lastTimeLighted;
    zCArray<zCVob*> leafVobList;
    zCArray<zCVobLight*> lightVobList;
    int lastTimeActivated;
    unsigned short sectorIndex;
    unsigned short polyPlueckerRefCtr;
    zCPluecker* polyPluecker;
    zVEC3 lightPosition;

    void zCBspLeaf_OnInit()                                                             zCall( 0x0052BC50 );
    zCBspLeaf()                                                                         zInit( zCBspLeaf_OnInit() );
    ~zCBspLeaf()                                                                        zCall( 0x0052DD60 );
    void PolyPlueckerAddRef()                                                           zCall( 0x0052DFB0 );
    void PolyPlueckerRelease()                                                          zCall( 0x0052E2A0 );
    void __fastcall AddVobsToRenderList( zTBBox2D* )                                    zCall( 0x0052E2D0 );
    void AddVobsToRenderListOutdoor()                                                   zCall( 0x0052E4D0 );
    void __fastcall AddVobsToRenderListOutdoor( zCBspSector*, zTBBox2D const& )         zCall( 0x0052E840 );
    void __fastcall RenderLeafIndoor( int )                                             zCall( 0x0052EFF0 );
    void __fastcall TraceRayCollectVobs( zCArray<zCVob*>&, zTBBox3D const&, int ) const zCall( 0x00531720 );
  };

  class zCBspTree {
  public:
    zCBspNode* actNodePtr;
    zCBspLeaf* actLeafPtr;
    zCBspBase* bspRoot;
    zCMesh* mesh;
    zCPolygon** treePolyList;
    zCBspNode* nodeList;
    zCBspLeaf* leafList;
    int numNodes;
    int numLeafs;
    int numPolys;
    zCArray<zCVob*> renderVobList;
    zCArray<zCVobLight*> renderLightList;
    zCArray<zCBspSector*> sectorList;
    zCArray<zCPolygon*> portalList;
    zTBspTreeMode bspTreeMode;
    zTWld_RenderMode worldRenderMode;
    float vobFarClipZ;
    zTPlane vobFarPlane;
    int vobFarPlaneSignbits;
    int drawVobBBox3D;
    int leafsRendered;
    int vobsRendered;
    int m_bRenderedFirstTime;
    int masterFrameCtr;
    zCPolygon** actPolyPtr;
    int compiled;

    void zCBspTree_OnInit()                                                                                zCall( 0x0052B9E0 );
    zCBspTree()                                                                                            zInit( zCBspTree_OnInit() );
    ~zCBspTree()                                                                                           zCall( 0x0052BA50 );
    void InitTree()                                                                                        zCall( 0x0052BB70 );
    void DisposeTree()                                                                                     zCall( 0x0052BCD0 );
    zCBspBase* BuildRecursive( zCCBspNode* )                                                               zCall( 0x0052BFB0 );
    void Build( zCCBspTree* )                                                                              zCall( 0x0052C290 );
    void OptimizeLight()                                                                                   zCall( 0x0052C6C0 );
    void UpdateVertexDependencies( zCVertex* )                                                             zCall( 0x0052CC00 );
    int CollectPolysInBBox3DAngle( zTBBox3D const&, zVEC3 const&, float, float, zCPolygon**&, int& ) const zCall( 0x0052CE10 );
    void RenderLightList()                                                                                 zCall( 0x0052CF80 );
    void RenderVobList()                                                                                   zCall( 0x0052D0A0 );
    void Render()                                                                                          zCall( 0x00530080 );
    void RemoveVob( zCVob* )                                                                               zCall( 0x00531030 );
    void AddVob( zCVob* )                                                                                  zCall( 0x00531040 );
    void AdjustVob( zCVob* )                                                                               zCall( 0x005310A0 );
    zTBBox3D CalcLeafRealBBox3D( zVEC3 const& )                                                            zCall( 0x00531990 );
    int TraceRay( zVEC3 const&, zVEC3 const&, int, zVEC3&, zCPolygon*&, zCArray<zCVob*>* ) const           zCall( 0x00532550 );
    int FindLeaks( zCArray<zCPolygon*>& )                                                                  zCall( 0x005330E0 );
    void MarkOccluderPolys()                                                                               zCall( 0x00533430 );
    float GetOccluderAreaRec( zCPolygon const*, zCArray<zCPolygon*>& )                                     zCall( 0x00534210 );
    zSTRING const* GetSectorNameVobIsIn( zCVob const* ) const                                              zCall( 0x00535180 );
    zCBspSector* GetBspSectorByName( zSTRING const& ) const                                                zCall( 0x00537960 );
    void CreateBspSectors2( zCCBspTree* )                                                                  zCall( 0x00537A10 );
    void SaveBIN( zCFileBIN& )                                                                             zCall( 0x00538010 );
    void ConnectMaterialsToSectors()                                                                       zCall( 0x00538AA0 );
    int LoadBIN( zCFileBIN&, int )                                                                         zCall( 0x00538E10 );
    void CalcStaticLeafLightData()                                                                         zCall( 0x00539D20 );
    void PreprocessIndoorPortals( zCMesh*, zCArray<zCBuildPortal*>& )                                      zCall( 0x00541DF0 );
    void GetPolyNeighbours( zCPolygon*, zCPolygon**&, int& )                                               zCall( 0x005421A0 );
    void PostprocessIndoorPortals( zCArray<zCBuildPortal*>& )                                              zCall( 0x00542250 );
    static void SetRayCache( zCRayCache* )                                                                 zCall( 0x005327D0 );
    static unsigned short GetFileVersion()                                                                 zCall( 0x00537D90 );
    static int GetShowPortals()                                                                            zCall( 0x006370F0 );
    static void SetShowPortals( int )                                                                      zCall( 0x00637100 );

    // static properties
    static int& s_showPortals;
    static int& s_renderAllPortals;
  };

  class zTPolyNode {
  public:
    zCPolygon* poly;
    zTPolyNode* next;
    int marked;
    char isCompleteInside;

    zTPolyNode() {}
  };

  class zCCBspNode {
  public:
    zTPlane plane;
    zCCBspNode* front;
    zCCBspNode* back;
    zCCBspNode* parent;
    zTBBox3D bbox3D;
    zTBBox3D bbox3DCell;
    zCList2<zTPolyNode> polyList;

    zCCBspNode() {}
    void zCCBspNode_OnInit( zCCBspNode* )                                                       zCall( 0x00540E60 );
    int CheckRayAgainstPolysNearestHit( zVEC3 const&, zVEC3 const&, zVEC3&, zCRayTurbo* ) const zCall( 0x005327E0 );
    int RayIntersectionOctree( zVEC3 const&, zVEC3 const&, zVEC3& )                             zCall( 0x00532900 );
    int TraceRay( zVEC3 const&, zVEC3 const&, zCPolygon*&, zVEC3& )                             zCall( 0x00532C10 );
    int TraceRay( zVEC3 const&, zVEC3 const&, zCPolygon*& )                                     zCall( 0x00532C40 );
    void CollectPolysInBBox3DRec()                                                              zCall( 0x00532F00 );
    int CollectPolysInBBox3D( zTBBox3D const&, zCPolygon**&, int& )                             zCall( 0x00533090 );
    ~zCCBspNode()                                                                               zCall( 0x0053CFC0 );
    void RemovePoly( zCPolygon* )                                                               zCall( 0x0053DF70 );
    int DoesNodeContainPoly( zCPolygon* )                                                       zCall( 0x0053E050 );
    int CheckPortalConsistency()                                                                zCall( 0x0053E120 );
    void SplitPortals()                                                                         zCall( 0x0053E890 );
    zCPortal* SplitPortalByAllPortals( zCPortal* )                                              zCall( 0x0053EDA0 );
    void EnumeratePortals()                                                                     zCall( 0x0053F030 );
    void ClassifyPortals()                                                                      zCall( 0x0053F160 );
    void Portalize()                                                                            zCall( 0x0053F1F0 );
    void SelectPlane( zTPlane&, zTPolyNode*&, int& )                                            zCall( 0x0053F5E0 );
    void SelectPlaneOctree( zCCBspTree*, zTPlane&, int )                                        zCall( 0x0053F830 );
    int ClassifyRayToNode( zVEC3 const&, zVEC3 const& )                                         zCall( 0x0053FA50 );
    int ClassifyPolyToNode2( zCPolygon* )                                                       zCall( 0x0053FD10 );
    int OutdoorKillRedundantLeafs()                                                             zCall( 0x0053FF80 );
    void AddPoly( zCPolygon* )                                                                  zCall( 0x005401D0 );
    void BuildTree( int )                                                                       zCall( 0x00540210 );
    zCCBspNode( zCCBspNode* a0 )                                                                zInit( zCCBspNode_OnInit( a0 ));
    void PushPolyFront( zTPolyNode* )                                                           zCall( 0x00540E80 );
    void CalcBBox3D()                                                                           zCall( 0x00540F10 );
    void CalcSubtreeBBox3D()                                                                    zCall( 0x00541010 );
    void CalcSubtreeBBox3DCell()                                                                zCall( 0x00541200 );
    int CountNodes()                                                                            zCall( 0x005412F0 );
    int CountLeafs()                                                                            zCall( 0x00541320 );
    int CountPolys()                                                                            zCall( 0x00541360 );
    void CountDepthRec( int, int&, int&, int& )                                                 zCall( 0x00541390 );
    void CountDepth( int&, int&, int& )                                                         zCall( 0x00541400 );
    void DescribeTree( int )                                                                    zCall( 0x005414B0 );
  };

  class zCCBspTree {
  public:
    enum zTSpanningMode {
      zSPANNING_SPLIT,
      zSPANNING_CENTER,
      zSPANNING_PUSHBOTH
    };

    zCCBspNode bspRoot;
    zCMesh* mesh;
    zTBspTreeMode bspTreeMode;
    zCArray<zCBspSector*> sectorList;
    zTSpanningMode cfg_spanningMode;
    int cfg_useAllPolys;
    int cfg_octree;
    zTBspBuildType cfg_bspType;
    float cfg_optimize;
    float cfg_wbalance;
    float cfg_wsplit;
    float cfg_wplanar;
    int cfg_portalize;

    void zCCBspTree_OnInit()                                 zCall( 0x0053CF10 );
    zCBspSector* GetBspSectorByName( zSTRING const& ) const  zCall( 0x005350D0 );
    void GetPolyNeighbours( zCPolygon*, zCPolygon**&, int& ) zCall( 0x005351A0 );
    void MarkGhostOccluder()                                 zCall( 0x00535280 );
    void CreateBspSectors()                                  zCall( 0x005354B0 );
    zCCBspTree()                                             zInit( zCCBspTree_OnInit() );
    void SetBspTreeMode( zTBspTreeMode const& )              zCall( 0x0053D030 );
    ~zCCBspTree()                                            zCall( 0x0053D0B0 );
    void DeleteTree()                                        zCall( 0x0053D190 );
    void AddMesh( zCMesh* )                                  zCall( 0x0053D2E0 );
    void AddMesh( zCMesh*, zMAT4 const& )                    zCall( 0x0053D310 );
    void BuildTree( float )                                  zCall( 0x0053D610 );
  };

  class zCBspSector {
  public:
    struct zTPortalInfo {
      unsigned char visible;
      unsigned char alpha;

      zTPortalInfo() {}
    };

    zSTRING sectorName;
    zCArray<zCBspBase*> sectorNodes;
    unsigned long sectorIndex;
    zCArray<zCPolygon*> sectorPortals;
    zCArray<zTPortalInfo> sectorPortalInfo;
    int activated;
    int rendered;
    zTBBox2D activePortal;
    zVEC3 sectorCenter;
    char hasBigNoFade;

    zCBspSector() {}
    void CalcCenterByPortals()                                         zCall( 0x005292B0 );
    int HasManyBigPortals() const                                      zCall( 0x00529350 );
    ~zCBspSector()                                                     zCall( 0x0052BF10 );
    void RenderSector()                                                zCall( 0x00534510 );
    void ActivateSectorRec( zTBBox2D const&, zCBspSector*, int )       zCall( 0x005345E0 );
    void ActivateSectorRecIndoor( zTBBox2D const&, zCBspSector*, int ) zCall( 0x00534B70 );
    static int CompareOutdoorPortalBBox2D( void const*, void const* )  zCall( 0x005290D0 );
    static void InitHorizonByOutdoorPortals()                          zCall( 0x00529110 );
    static void RenderActiveSectorList()                               zCall( 0x00535090 );

    // static properties
    static int& s_sectorsRendered;
    static int& s_startPointOutdoor;
    static int& s_outdoorPortal;
    static zCArray<zCBspSector*>& s_activeSectorList;
    static zCArray<zTBBox2D>& s_activeOutdoorPortals;
  };

  class zCBuildPortal {
  public:
    zCPolygon* portalPoly;
    zCPolygon* portalPolyBack;
    zCArray<zCPolygon*> borderPolyList;
    zCArray<zCPolygon*> polyBucket[2];
    zCArray<zCBuildPortal*> portalBucket[2];
    zCBspSector* sector[2];

    void zCBuildPortal_OnInit() zCall( 0x00541CE0 );
    zCBuildPortal()             zInit( zCBuildPortal_OnInit() );
    ~zCBuildPortal()            zCall( 0x00541D60 );
  };

} // namespace Gothic_II_Addon

#endif // __ZBSP_H__VER3__