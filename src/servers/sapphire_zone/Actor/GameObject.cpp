#include "GameObject.h"

#include "Player.h"
#include "Actor.h"
#include "BattleNpc.h"
#include "EventNpc.h"

Core::Entity::GameObject::GameObject( ObjKind type ) :
   m_objKind( type )
{

}

uint32_t Core::Entity::GameObject::getId() const
{
   return m_id;
}

Core::Entity::GameObject::ObjKind Core::Entity::GameObject::getObjKind() const
{
   return m_objKind;
}

Core::Common::FFXIVARR_POSITION3& Core::Entity::GameObject::getPos()
{
   return m_pos;
}

void Core::Entity::GameObject::setPos( float x, float y, float z )
{
   m_pos.x = x;
   m_pos.y = y;
   m_pos.z = z;
}

void Core::Entity::GameObject::setPos( const Core::Common::FFXIVARR_POSITION3& pos )
{
   m_pos = pos;
}

float Core::Entity::GameObject::getRot() const
{
   return m_rot;
}

void Core::Entity::GameObject::setRot( float rot )
{
   m_rot = rot;
}

bool Core::Entity::GameObject::isPlayer() const
{
   return m_objKind == ObjKind::Player;
}

bool Core::Entity::GameObject::isBattleNpc() const
{
   return m_objKind == ObjKind::BattleNpc;
}

bool Core::Entity::GameObject::isEventNpc() const
{
   return m_objKind == ObjKind::EventNpc;
}

/*! \return pointer to this instance as ActorPtr */
Core::Entity::ActorPtr Core::Entity::GameObject::getAsActor()
{
   return boost::dynamic_pointer_cast< Entity::Actor, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
Core::Entity::PlayerPtr Core::Entity::GameObject::getAsPlayer()
{
   if( !isPlayer() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::Player, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as BattleNpcPtr */
Core::Entity::BattleNpcPtr Core::Entity::GameObject::getAsBattleNpc()
{
   if( !isBattleNpc() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::BattleNpc, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as EventNpcPtr */
Core::Entity::EventNpcPtr Core::Entity::GameObject::getAsEventNpc()
{
   if( !isEventNpc() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::EventNpc, Entity::GameObject >( shared_from_this() );
}
