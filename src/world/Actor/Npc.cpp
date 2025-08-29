#include "Player.h"
#include "Npc.h"
#include "Common.h"

using namespace Sapphire::Entity;
using namespace Sapphire::Common;

Npc::Npc( ObjKind type ) : Chara( type )
{
}

Npc::~Npc()
{
}

bool Npc::pathingActive() const
{
  return m_bPathingActive;
}

void Npc::setPathingActive( bool pathing )
{
  m_bPathingActive = pathing;
}
