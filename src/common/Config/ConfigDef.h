#ifndef SAPPHIRE_CONFIGDEF_H
#define SAPPHIRE_CONFIGDEF_H

namespace Sapphire::Common::Config
{
  struct GlobalConfig
  {
    struct Database
    {
      std::string host;
      uint16_t port;
      std::string database;
      std::string username;
      std::string password;
      uint8_t syncThreads;
      uint8_t asyncThreads;
    } database;

    struct Parameters
    {
      std::string serverSecret;
      std::string dataPath;
      uint16_t worldID;
    } parameters;

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

    uint8_t defaultGMRank;
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
