#ifndef SAPPHIRE_CONFIGDEF_H
#define SAPPHIRE_CONFIGDEF_H

#include <Database/DbCommon.h>

namespace Sapphire::Common::Config
{
  struct GlobalConfig
  {
    Sapphire::Db::ConnectionInfo database;

    struct General
    {
      std::string serverSecret;
      std::string dataPath;
      uint16_t worldID;

      uint8_t defaultGMRank;
      uint8_t logLevel;
      uint32_t logFilter;
    } general;

    struct Network
    {
      std::string zoneHost;
      uint16_t zonePort;

      std::string lobbyHost;
      uint16_t lobbyPort;

      std::string restHost;
      uint16_t restPort;
    } network;
  };


  struct WorldConfig
  {
    GlobalConfig global;

    struct Network
    {
      std::string listenIp;
      uint16_t listenPort;

      uint16_t disconnectTimeout;

      float inRangeDistance;
    } network;

    struct Housing
    {
      std::string defaultEstateName;
    } housing;

    struct Scripts
    {
      std::string path;
      std::string cachePath;
      bool hotSwap;
    } scripts;

    struct Navigation
    {
      std::string meshPath;
    } navigation;

    std::string motd;
  };

  struct LobbyConfig
  {
    GlobalConfig global;

    struct Network
    {
      std::string listenIp;
      uint16_t listenPort;
    } network;

    bool allowNoSessionConnect;
    std::string worldName;
  };

  struct ApiConfig
  {
    GlobalConfig global;

    struct Network
    {
      std::string listenIP;
      uint16_t listenPort;
    } network;
  };
}

#endif //SAPPHIRE_CONFIGDEF_H
