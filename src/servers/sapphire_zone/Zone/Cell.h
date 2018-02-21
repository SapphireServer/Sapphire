
#ifndef _CELL_H
#define _CELL_H

#include <stdint.h>

#include "Forwards.h"
#include <set>

namespace Core {

   typedef std::set< Entity::CharaPtr > CharaSet;

   class Cell 
   {
      friend class Zone;

   private:
      bool m_bForcedActive;
      uint16_t m_posX;
      uint16_t m_posY;
      CharaSet m_charas;
      bool m_bActive;
      bool m_bLoaded;
      bool m_bUnloadPending;

      uint16_t m_playerCount;
      ZonePtr m_pZone;

   public:
      Cell();
      ~Cell();

      void init( uint32_t x, uint32_t y, ZonePtr pZone );

      void addChara( Entity::CharaPtr pAct );

      void removeChara( Entity::CharaPtr pAct );

      bool hasChara( Entity::CharaPtr pAct )
      { 
         return (m_charas.find(pAct) != m_charas.end());
      }

      bool hasPlayers() const
      { 
         return ((m_playerCount > 0) ? true : false); 
      }

      size_t getCharaCount() const
      { 
         return m_charas.size();
      }

      void removeCharas();

      CharaSet::iterator begin()
      {
         return m_charas.begin();
      }

      CharaSet::iterator end()
      {
         return m_charas.end();
      }

      void setActivity(bool state);

      bool isActive() const
      {
         return m_bActive; 
      }

      bool isLoaded() const
      { 
         return m_bLoaded; 
      }

      uint32_t getPlayerCount() const
      {
         return m_playerCount; 
      }

      bool isUnloadPending() const
      {
         return m_bUnloadPending; 
      }

      void setUnloadPending(bool up) 
      {
         m_bUnloadPending = up; 
      }

      void queueUnloadPending();
      void cancelPendingUnload();
      void unload();

      void setPermanentActivity(bool val) 
      {
         m_bForcedActive = val; 
      }

      bool isForcedActive() const
      {
         return m_bForcedActive; 
      }

      uint16_t getPosX() const
      { 
         return m_posX; 
      }

      uint16_t getPosY() const
      { 
         return m_posY; 
      }
   };

}
#endif
