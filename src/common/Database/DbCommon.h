#pragma once

#include <string>
#include <cstdint>

namespace Sapphire::Db
{
  struct ConnectionInfo
  {
    std::string user;
    std::string password;
    std::string database;
    std::string host;
    uint16_t port;
    uint8_t syncThreads;
    uint8_t asyncThreads;
  };
}

