#include "MarketMgr.h"

Sapphire::World::Manager::MarketMgr::MarketMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{

}

bool Sapphire::World::Manager::MarketMgr::init()
{
  return true;
}

void Sapphire::World::Manager::MarketMgr::searchMarketboard( Entity::Player& player,
                                                             uint8_t itemSearchCategory, uint8_t maxEquipLevel,
                                                             uint8_t classJob )
{
  
}