#include "GameObject.h"

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

bool Core::Entity::GameObject::isBNpc() const
{
   return m_objKind == ObjKind::BattleNpc;
}

bool Core::Entity::GameObject::isENpc() const
{
   return m_objKind == ObjKind::EventNpc;
}