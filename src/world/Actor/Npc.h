#pragma once

#include <Common.h>

#include "Forwards.h"
#include "Chara.h"
#include <set>
#include <map>
#include <queue>

namespace Sapphire::Entity
{

  /*!
  \class Npc
  \brief Base class for all Npcs

  */
  class Npc : public Chara
  {

  public:
    Npc( Common::ObjKind type );

    virtual ~Npc() override;
    bool pathingActive() const;
    void setPathingActive( bool pathing );

  private:
    bool m_bPathingActive{false};


  };

}