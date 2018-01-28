#ifndef SAPPHIRE_PREINCLUDE_H
#define SAPPHIRE_PREINCLUDE_H

// fixes an issue where winsock is included before asio causing builds to fail
#include <boost/asio.hpp>

#endif //SAPPHIRE_PREINCLUDE_H
