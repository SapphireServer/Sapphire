#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <common/Common.h>
#include <boost/enable_shared_from_this.hpp>

#include "Forwards.h"
#include <set>
#include <map>
#include <queue>

namespace Core {
namespace Entity {

/*!
\class GameObject
\brief Base class for all actor/objects

*/
   class GameObject : public boost::enable_shared_from_this< GameObject >
   {
   public:
      enum ObjKind : uint8_t
      {
         None = 0x00,
         Player = 0x01,
         BattleNpc = 0x02,
         EventNpc = 0x03,
         Treasure = 0x04,
         Aetheryte = 0x05,
         GatheringPoint = 0x06,
         EventObj = 0x07,
         Mount = 0x08,
         Companion = 0x09,
         Retainer = 0x0A,
         Area = 0x0B,
         Housing = 0x0C,
         Cutscene = 0x0D,
         CardStand = 0x0E,
      };

   protected:
      /*! Position of the object */
      Common::FFXIVARR_POSITION3 m_pos;
      /*! Rotation of the object */
      float m_rot;
      /*! Id of the actor */
      uint32_t             m_id;
      /*! Type of the actor */
      ObjKind              m_objKind;

   public:
      explicit GameObject( ObjKind type );
      virtual ~GameObject() {};

      virtual void spawn( PlayerPtr pTarget ) {}
      virtual void despawn( PlayerPtr pTarget ) {}

      uint32_t getId() const;

      ObjKind getObjKind() const;

      Common::FFXIVARR_POSITION3& getPos();
      void setPos( const Common::FFXIVARR_POSITION3& pos );
      void setPos( float x, float y, float z );

      float getRot() const;
      void setRot( float rot );

      bool isPlayer() const;
      bool isBattleNpc() const;
      bool isEventNpc() const;

      ActorPtr getAsActor();
      PlayerPtr getAsPlayer();
      BattleNpcPtr getAsBattleNpc();
      EventNpcPtr getAsEventNpc();
   };

}
}
#endif
