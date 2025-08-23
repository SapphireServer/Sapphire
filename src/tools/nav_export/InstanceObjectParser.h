#pragma once
#include "DatCommon.h"
#include "InstanceObject.h"


class InstanceObjectEntry
{
public:
  char* m_buf;
  uint32_t m_offset;
  InstanceObject header;

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
  };

  const eAssetType getType() const
  {
    return static_cast< eAssetType >( header.AssetType );
  };

  virtual ~InstanceObjectEntry()
  {
  };
};


class SharedGroupEntry : public InstanceObjectEntry
{
public:
  SGData header;
  std::string name;
  std::string AssetPath;

  SharedGroupEntry( char* buf, uint32_t offset ) :
    InstanceObjectEntry( buf, offset )
  {
    header = *reinterpret_cast< SGData* >( buf + offset );
    name = std::string( buf + offset + header.Name );
    AssetPath = std::string( buf + offset + header.AssetPath );
  };
};

class BGEntry : public InstanceObjectEntry
{
public:
  BgData header;
  std::string name;
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
  };
};
