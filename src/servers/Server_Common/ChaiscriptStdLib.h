#ifndef CHAISCRIPT_STDLIB
#define CHAISCRIPT_STDLIB

#include <boost/shared_ptr.hpp>

namespace chaiscript 
{
  class Module;
  class ChaiScript;
}

namespace Core { namespace Scripting {

std::shared_ptr<chaiscript::Module> create_chaiscript_stdlib();
boost::shared_ptr< chaiscript::ChaiScript > create_chaiscript();

} }

#endif
