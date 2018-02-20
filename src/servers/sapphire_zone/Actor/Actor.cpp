#include "Actor.h"

#include "Player.h"
#include "Chara.h"
#include "BattleNpc.h"
#include "EventNpc.h"

Core::Entity::Actor::Actor( ObjKind type ) :
   m_objKind( type )
{

}

uint32_t Core::Entity::Actor::getId() const
{
   return m_id;
}

Core::Entity::Actor::ObjKind Core::Entity::Actor::getObjKind() const
{
   return m_objKind;
}

Core::Common::FFXIVARR_POSITION3& Core::Entity::Actor::getPos()
{
   return m_pos;
}

void Core::Entity::Actor::setPos( float x, float y, float z )
{
   m_pos.x = x;
   m_pos.y = y;
   m_pos.z = z;
}

void Core::Entity::Actor::setPos( const Core::Common::FFXIVARR_POSITION3& pos )
{
   m_pos = pos;
}

float Core::Entity::Actor::getRot() const
{
   return m_rot;
}

void Core::Entity::Actor::setRot( float rot )
{
   m_rot = rot;
}

bool Core::Entity::Actor::isPlayer() const
{
   return m_objKind == ObjKind::Player;
}

bool Core::Entity::Actor::isBattleNpc() const
{
   return m_objKind == ObjKind::BattleNpc;
}

bool Core::Entity::Actor::isEventNpc() const
{
   return m_objKind == ObjKind::EventNpc;
}

/*! \return pointer to this instance as ActorPtr */
Core::Entity::CharaPtr Core::Entity::Actor::getAsChara()
{
   return boost::dynamic_pointer_cast< Entity::Chara, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
Core::Entity::PlayerPtr Core::Entity::Actor::getAsPlayer()
{
   if( !isPlayer() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::Player, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as BattleNpcPtr */
Core::Entity::BattleNpcPtr Core::Entity::Actor::getAsBattleNpc()
{
   if( !isBattleNpc() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::BattleNpc, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as EventNpcPtr */
Core::Entity::EventNpcPtr Core::Entity::Actor::getAsEventNpc()
{
   if( !isEventNpc() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::EventNpc, Entity::Actor >( shared_from_this() );
}
