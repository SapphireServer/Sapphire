#pragma once
#include "DatCommon.h"
#include "InstanceObject.h"


class InstanceObjectEntry
{
public:
  char* m_buf;
  uint32_t m_offset;
  InstanceObject header;
  std::string name;

  InstanceObjectEntry()
  {
    m_buf = nullptr;
    m_offset = 0;
    memset( &header, 0, sizeof( header ) );
  };

  InstanceObjectEntry( char* buf, uint32_t offset )
  {
    m_buf = buf;
    m_offset = offset;
    header = *reinterpret_cast< InstanceObject* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };

  const eAssetType getType() const
  {
    return static_cast< eAssetType >( header.AssetType );
  };

  virtual ~InstanceObjectEntry()
  {
  };
};

class ExitRangeEntry : public InstanceObjectEntry
{
public:
  ExitRangeData header;

  ExitRangeEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< ExitRangeData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};

class PopRangeEntry : public InstanceObjectEntry
{
public:
  PopRangeData header;

  PopRangeEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< PopRangeData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};

class EventRangeEntry : public InstanceObjectEntry
{
public:
  EventRangeData header;

  EventRangeEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< EventRangeData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};

class SharedGroupEntry : public InstanceObjectEntry
{
public:
  SGData header;
  std::string AssetPath;

  SharedGroupEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< SGData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
    AssetPath = std::string( buf + offset + header.AssetPath );
  };
};

class EventNPCEntry : public InstanceObjectEntry
{
public:
  ENPCData header;

  EventNPCEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< ENPCData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};

class BattleNPCEntry : public InstanceObjectEntry
{
public:
  BNPCInstanceObject header;

  BattleNPCEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< BNPCInstanceObject* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};

class EventObjectEntry : public InstanceObjectEntry
{
public:
  EObjData header;

  EventObjectEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< EObjData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};

class BGEntry : public InstanceObjectEntry
{
public:
  BgData header;
  ModelCollisionConfig collisionConfig;
  std::string modelFileName;
  std::string collisionFileName;

  BGEntry()
  {
  };

  BGEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< BgData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
    modelFileName = std::string( buf + offset + header.AssetPath );
    collisionFileName = std::string( buf + offset + header.CollisionAssetPath );
    collisionConfig = *reinterpret_cast< ModelCollisionConfig* >( buf + offset + header.CollisionConfig );
  };
};

class CollisionBoxEntry : public InstanceObjectEntry
{
public:
  CollisionBoxData header;

  CollisionBoxEntry()
  {
  };

  CollisionBoxEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< CollisionBoxData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};

class MapRangeEntry : public InstanceObjectEntry
{
public:
  MapRangeData header;

  MapRangeEntry()
  {
  };

  MapRangeEntry( char* buf, uint32_t offset ) : InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< MapRangeData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
  };
};
