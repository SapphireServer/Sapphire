#ifndef _NPC_H_
#define _NPC_H_

#include <Common.h>
#include <boost/enable_shared_from_this.hpp>

#include "Forwards.h"
#include "Chara.h"
#include <set>
#include <map>
#include <queue>

namespace Core {
namespace Entity {

/*!
\class Npc
\brief Base class for all Npcs

*/
class Npc : public Chara
{

public:
  Npc( Common::ObjKind type );

  virtual ~Npc() override;

};

}
}
#endif
