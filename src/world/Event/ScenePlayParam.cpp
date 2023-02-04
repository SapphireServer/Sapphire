#include <utility>

#include "EventHandler.h"

using namespace Sapphire::Event;

void ScenePlayParam::setParam( uint16_t sceneId, uint32_t value )
{
  params[ sceneId ].push_back( value );
}

void ScenePlayParam::setParams( uint16_t sceneId, std::vector< uint32_t > values )
{
  params[ sceneId ] = std::move( values );
}

std::vector< uint32_t > *ScenePlayParam::getParams( uint16_t sceneId )
{
  auto it = params.find( sceneId );
  if( it != params.end() )
    return &it->second;

  return nullptr;
}