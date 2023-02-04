#include "EventHandler.h"

using namespace Sapphire::Event;

uint32_t SceneResult::getResult( uint32_t index ) const
{
  if( index >= results.size() )
  {
    return 0;
  }

  return results[ index ];
}