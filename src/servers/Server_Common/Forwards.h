#ifndef _COMMON_FORWARDS_H
#define _COMMON_FORWARDS_H

#include <boost/shared_ptr.hpp>
#include <chrono>

using namespace std::chrono_literals;
using time_point = std::chrono::steady_clock::time_point;
using duration = std::chrono::steady_clock::duration;

namespace Core 
{

   class XMLConfig;

   typedef boost::shared_ptr<XMLConfig> XMLConfigPtr;


   namespace Network 
   {
      class Hive;
      class Acceptor;
      class Connection;

      typedef boost::shared_ptr<Hive> HivePtr;
      typedef boost::shared_ptr<Acceptor> AcceptorPtr;
      typedef boost::shared_ptr<Connection> ConnectionPtr;

      namespace Packets
      {
         class GamePacket;

         typedef boost::shared_ptr<GamePacket> GamePacketPtr;
      }

   }



}


#endif