#ifndef SAPPHIRE_CONFIGDEF_H
#define SAPPHIRE_CONFIGDEF_H

namespace Sapphire::Common
{
  struct Configuration
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

    struct GlobalParameters
    {
      std::string serverSecret;
      std::string dataPath;
    } globalParameters;

    struct GlobalNetwork
    {
      std::string zoneHost;
      uint16_t zonePort;

      std::string lobbyHost;
      uint16_t lobbyPort;

      std::string restHost;
      uint16_t restPort;
    } globalNetwork;

    struct Lobby
    {
      uint16_t worldID;
      bool allowNoSessionConnect;
      std::string worldName;
    } lobby;

    struct LobbyNetwork
    {
      std::string listenIp;
      uint16_t listenPort;
    } lobbyNetwork;

    struct CharacterCreation
    {
      uint8_t defaultGMRank;
    } characterCreation;

    struct RestNetwork
    {
      std::string listenIP;
      uint16_t listenPort;
    } restNetwork;

    struct Scripts
    {
      std::string path;
      std::string cachePath;
      bool hotSwap;
    } scripts;

    struct Network
    {
      Network() :
        disconnectTimeout( 20 )
      {}

      uint16_t disconnectTimeout;
    } network;

    struct ZoneNetwork
    {
      std::string listenIp;
      uint16_t listenPort;
    } zoneNetwork;

    struct General
    {
      std::string motd;
    } general;

    struct Housing
    {
      std::string defaultEstateName;
    } housing;
  };
}

#endif //SAPPHIRE_CONFIGDEF_H
