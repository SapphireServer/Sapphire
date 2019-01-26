#ifndef NAVMESH_EXPORTER_H
#define NAVMESH_EXPORTER_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#include <chrono>

#include "exporter.h"
#include "nav/TiledNavmeshGenerator.h"

class NavmeshExporter
{
public:
  static void exportZone( const ExportedZone& zone )
  {
    auto start = std::chrono::high_resolution_clock::now();

    auto dir = std::experimental::filesystem::current_path().string() + "/pcb_export/" + zone.name + "/";
    auto fileName = dir + zone.name + ".obj";

    TiledNavmeshGenerator gen( fileName );

    if( !gen.buildNavmesh() )
    {
      printf( "[Navmesh] Failed to build navmesh for '%s'\n", zone.name.c_str() );
      return;
    }

    auto end = std::chrono::high_resolution_clock::now();
    printf( "[Navmesh] Finished exporting %s in %lu ms\n",
      fileName.c_str(),
      std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() );
  }

  static void exportGroup( const std::string& zoneName, const ExportedGroup& group )
  {

  }
private:
  /*/
  static unsigned char* buildTileMesh( const ExportedGroup& group, int tx, int ty )
  {
    unsigned char* navData;
    rcConfig cfg;
    cfg.ch = 0.2f;
    cfg.cs = 0.2f;
    cfg.walkableHeight = 2.f;
    cfg.walkableRadius = 0.5;
    cfg.walkableClimb = 0.6;
    cfg.walkableSlopeAngle = 58.f;
    cfg.minRegionArea = 8.0f;
    cfg.mergeRegionArea = 20.f;
    cfg.maxEdgeLen = 12.f;
    cfg.maxSimplificationError = 1.4f;
    cfg.maxVertsPerPoly = 6.f;
    cfg.detailSampleDist = 6.f;
    cfg.detailSampleMaxError = 1.f;
    cfg.tileSize = 160.f;

	  cfg.walkableHeight = (int)ceilf( cfg.walkableHeight / cfg.ch );
	  cfg.walkableClimb = (int)floorf( cfg.walkableClimb / cfg.ch );
	  cfg.walkableRadius = (int)ceilf( cfg.walkableRadius / cfg.cs );
	  cfg.maxEdgeLen = (int)( cfg.maxEdgeLen / cfg.cs );
	  cfg.minRegionArea = (int)rcSqr( cfg.minRegionArea );		// Note: area = size*size
	  cfg.mergeRegionArea = (int)rcSqr( cfg.mergeRegionArea );	// Note: area = size*size
	  cfg.borderSize = cfg.walkableRadius + 3; // Reserve enough padding.
	  cfg.width = cfg.tileSize + cfg.borderSize*2;
	  cfg.height = cfg.tileSize + cfg.borderSize*2;
	  cfg.detailSampleDist = cfg.detailSampleDist < 0.9f ? 0 : cfg.cs * cfg.detailSampleDist;
	  cfg.detailSampleMaxError = cfg.ch * cfg.detailSampleMaxError;

    rcContext ctx;
    auto hf = rcAllocHeightfield();
    auto chf = rcAllocCompactHeightfield();
    auto cs = rcAllocContourSet();
    auto pmesh = rcAllocPolyMesh();
    auto pdetailmesh = rcAllocPolyMeshDetail();

    std::vector< float > verts;
    std::vector< int > indices;

    int i = 0;
    int numIndices = 0;
    for( const auto& model : group.models )
    {
      for( const auto& mesh : model.second.meshes )
      {
        auto size = mesh.verts.size();
        rcCalcBounds( mesh.verts.data(), size / 3, &cfg.bmin[0], &cfg.bmax[0] );
        verts.reserve( verts.size() + size );
        memcpy( &verts[i], mesh.verts.data(), size );
        i += size;

        size = mesh.indices.size();
        indices.reserve( indices.size() + size );
        for( auto j = 0; j < mesh.indices.size(); j += 3 )
        {
          indices[j] = mesh.indices[j] + numIndices;
          indices[j + 1] = mesh.indices[j + 1] + numIndices;
          indices[j + 2] = mesh.indices[j + 2] + numIndices;
        }
        numIndices += size;
      }
    }

    auto chunkyMesh = new rcChunkyTriMesh;
    rcCreateChunkyTriMesh( &verts[0], &indices[0], verts.size() / 3, 256, chunkyMesh );
    if( !rcCreateHeightfield( &ctx, *hf, cfg.width, cfg.height, cfg.bmin, cfg.bmax, cfg.cs, cfg.ch ) )
    {
      
    }
    	float tbmin[2], tbmax[2];
	tbmin[0] = cfg.bmin[0];
	tbmin[1] = cfg.bmin[2];
	tbmax[0] = cfg.bmax[0];
	tbmax[1] = cfg.bmax[2];
	int cid[512];// TODO: Make grow when returning too many items.
	const int ncid = rcGetChunksOverlappingRect(chunkyMesh, tbmin, tbmax, cid, 512);
	if (!ncid)
		return 0;
	
	auto tileTriCount = 0;
  auto triareas = new unsigned char[chunkyMesh->maxTrisPerChunk];
	for (int i = 0; i < ncid; ++i)
	{
		const rcChunkyTriMeshNode& node = chunkyMesh->nodes[cid[i]];
		const int* ctris = &chunkyMesh->tris[node.i*3];
		const int nctris = node.n;
		
		tileTriCount += nctris;
		
		memset(triareas, 0, nctris*sizeof(unsigned char));
		rcMarkWalkableTriangles(&ctx, cfg.walkableSlopeAngle,
								&verts[0], verts.size() / 3, ctris, nctris, triareas);
		
		if (!rcRasterizeTriangles(&ctx, &verts[0], verts.size() / 3, ctris, triareas, nctris, *hf, cfg.walkableClimb))
			return 0;
	}
	
	{
		delete [] triareas;
		triareas = 0;
	}
	
	// Once all geometry is rasterized, we do initial pass of filtering to
	// remove unwanted overhangs caused by the conservative rasterization
	// as well as filter spans where the character cannot possibly stand.

		rcFilterLowHangingWalkableObstacles(&ctx, cfg.walkableClimb, *hf);

		rcFilterLedgeSpans(&ctx, cfg.walkableHeight, cfg.walkableClimb, *hf);
		rcFilterWalkableLowHeightSpans(&ctx, cfg.walkableHeight, *hf);
	
	// Compact the heightfield so that it is faster to handle from now on.
	// This will result more cache coherent data as well as the neighbours
	// between walkable cells will be calculated.
	chf = rcAllocCompactHeightfield();
	if (!chf)
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'chf'.");
		return 0;
	}
	if (!rcBuildCompactHeightfield(&ctx, cfg.walkableHeight, cfg.walkableClimb, *hf, *chf))
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build compact data.");
		return 0;
	}
	

	{
		rcFreeHeightField(hf);
		hf = 0;
	}

	// Erode the walkable area by agent radius.
	if (!rcErodeWalkableArea(&ctx, cfg.walkableRadius, *chf))
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Could not erode.");
		return 0;
	}

	
	// Partition the heightfield so that we can use simple algorithm later to triangulate the walkable areas.
	// There are 3 martitioning methods, each with some pros and cons:
	// 1) Watershed partitioning
	//   - the classic Recast partitioning
	//   - creates the nicest tessellation
	//   - usually slowest
	//   - partitions the heightfield into nice regions without holes or overlaps
	//   - the are some corner cases where this method creates produces holes and overlaps
	//      - holes may appear when a small obstacles is close to large open area (triangulation can handle this)
	//      - overlaps may occur if you have narrow spiral corridors (i.e stairs), this make triangulation to fail
	//   * generally the best choice if you precompute the nacmesh, use this if you have large open areas
	// 2) Monotone partioning
	//   - fastest
	//   - partitions the heightfield into regions without holes and overlaps (guaranteed)
	//   - creates long thin polygons, which sometimes causes paths with detours
	//   * use this if you want fast navmesh generation
	// 3) Layer partitoining
	//   - quite fast
	//   - partitions the heighfield into non-overlapping regions
	//   - relies on the triangulation code to cope with holes (thus slower than monotone partitioning)
	//   - produces better triangles than monotone partitioning
	//   - does not have the corner cases of watershed partitioning
	//   - can be slow and create a bit ugly tessellation (still better than monotone)
	//     if you have large open areas with small obstacles (not a problem if you use tiles)
	//   * good choice to use for tiled navmesh with medium and small sized tiles
	
	//if (m_partitionType == SAMPLE_PARTITION_WATERSHED)
	{
		// Prepare for region partitioning, by calculating distance field along the walkable surface.
		if (!rcBuildDistanceField(&ctx, *chf))
		{
			ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build distance field.");
			return 0;
		}
		
		// Partition the walkable surface into simple regions without holes.
		if (!rcBuildRegions(&ctx, *chf, cfg.borderSize, cfg.minRegionArea, cfg.mergeRegionArea))
		{
			ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build watershed regions.");
			return 0;
		}
	}
	//else if (m_partitionType == SAMPLE_PARTITION_MONOTONE)
  //{
  //	// Partition the walkable surface into simple regions without holes.
  //	// Monotone partitioning does not need distancefield.
  //	if (!rcBuildRegionsMonotone(&ctx, *chf, cfg.borderSize, cfg.minRegionArea, cfg.mergeRegionArea))
  //	{
  //		ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build monotone regions.");
  //		return 0;
  //	}
  //}
  //else // SAMPLE_PARTITION_LAYERS
  //{
  //	// Partition the walkable surface into simple regions without holes.
  //	if (!rcBuildLayerRegions(&ctx, *chf, cfg.borderSize, cfg.minRegionArea))
  //	{
  //		ctx.log(RC_LOG_ERROR, "buildNavigation: Could not build layer regions.");
  //		return 0;
  //	}
  //}

	// Create contours.
	cs = rcAllocContourSet();
	if (!cs)
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'cset'.");
		return 0;
	}
	if (!rcBuildContours(&ctx, *chf, cfg.maxSimplificationError, cfg.maxEdgeLen, *cs))
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Could not create contours.");
		return 0;
	}
	
	if (cs->nconts == 0)
	{
		return 0;
	}
	
	// Build polygon navmesh from the contours.
	pmesh = rcAllocPolyMesh();
	if (!pmesh)
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmesh'.");
		return 0;
	}
	if (!rcBuildPolyMesh(&ctx, *cs, cfg.maxVertsPerPoly, *pmesh))
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Could not triangulate contours.");
		return 0;
	}
	
	// Build detail mesh.
	pdetailmesh = rcAllocPolyMeshDetail();
	if (!pdetailmesh)
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Out of memory 'dmesh'.");
		return 0;
	}
	
	if (!rcBuildPolyMeshDetail(&ctx, *pmesh, *chf,
							   cfg.detailSampleDist, cfg.detailSampleMaxError,
							   *pdetailmesh))
	{
		ctx.log(RC_LOG_ERROR, "buildNavigation: Could build polymesh detail.");
		return 0;
	}
	
	{
		rcFreeCompactHeightfield(chf);
		chf = 0;
		rcFreeContourSet(cs);
		cs = 0;
	}
	
	unsigned char* navData = 0;
	int navDataSize = 0;
	if (cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
	{
		if (pmesh->nverts >= 0xffff)
		{
			// The vertex indices are ushorts, and cannot point to more than 0xffff vertices.
			ctx.log(RC_LOG_ERROR, "Too many vertices per tile %d (max: %d).", pmesh->nverts, 0xffff);
			return 0;
		}
		
		// Update poly flags from areas.
		for (int i = 0; i < pmesh->npolys; ++i)
		{
			//pmesh->flags[i] = sampleAreaToFlags(pmesh->areas[i]);
		}
		
		dtNavMeshCreateParams params;
		memset(&params, 0, sizeof(params));
		params.verts = pmesh->verts;
		params.vertCount = pmesh->nverts;
		params.polys = pmesh->polys;
		params.polyAreas = pmesh->areas;
		params.polyFlags = pmesh->flags;
		params.polyCount = pmesh->npolys;
		params.nvp = pmesh->nvp;
		params.detailMeshes = pdetailmesh->meshes;
		params.detailVerts = pdetailmesh->verts;
		params.detailVertsCount = pdetailmesh->nverts;
		params.detailTris = pdetailmesh->tris;
		params.detailTriCount = pdetailmesh->ntris;
		params.offMeshConVerts = 0;
		params.offMeshConRad = 0;
		params.offMeshConDir = 0;
		params.offMeshConAreas = 0;
		params.offMeshConFlags = 0;
		params.offMeshConUserID = 0;
		params.offMeshConCount = 0;
		params.walkableHeight = cfg.walkableHeight;
		params.walkableRadius = cfg.walkableRadius;
		params.walkableClimb = cfg.walkableClimb;
		params.tileX = 0;
		params.tileY = 0;
		params.tileLayer = 0;
		rcVcopy(params.bmin, pmesh->bmin);
		rcVcopy(params.bmax, pmesh->bmax);
		params.cs = cfg.cs;
		params.ch = cfg.ch;
		params.buildBvTree = true;
		
		if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
		{
			ctx.log(RC_LOG_ERROR, "Could not build Detour navmesh.");
			return 0;
		}		
	}
	auto tileMemUsage = navDataSize/1024.0f;
	
	ctx.stopTimer(RC_TIMER_TOTAL);
	
	// Show performance stats.
	//duLogBuildTimes(*&ctx, ctx.getAccumulatedTime(RC_TIMER_TOTAL));
	ctx.log(RC_LOG_PROGRESS, ">> Polymesh: %d vertices  %d polygons", pmesh->nverts, pmesh->npolys);
	
	auto tileBuildTime = ctx.getAccumulatedTime(RC_TIMER_TOTAL)/1000.0f;

	auto dataSize = navDataSize;
	return navData;

  }
  //*/
};
#endif // !OBJ_EXPORTER_H
