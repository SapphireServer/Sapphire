#ifndef _COMMON_FORWARDS_H
#define _COMMON_FORWARDS_H

#include <boost/shared_ptr.hpp>

namespace Core 
{

   class ConfigMgr;

   typedef boost::shared_ptr< ConfigMgr > ConfigMgrPtr;


   namespace Network 
   {
      class Hive;
      class Acceptor;
      class Connection;

      typedef boost::shared_ptr< Hive > HivePtr;
      typedef boost::shared_ptr< Acceptor > AcceptorPtr;
      typedef boost::shared_ptr< Connection > ConnectionPtr;

      namespace Packets
      {
         class GamePacket;

         typedef boost::shared_ptr< GamePacket > GamePacketPtr;
      }

   }



}


#endif