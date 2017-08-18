#include <chaiscript/chaiscript_stdlib.hpp>
#include <chaiscript/chaiscript.hpp>
#include "ChaiscriptStdLib.h"
#include <boost/make_shared.hpp>

std::shared_ptr< chaiscript::Module > Core::Scripting::create_chaiscript_stdlib()
{
   return chaiscript::Std_Lib::library();
}

boost::shared_ptr< chaiscript::ChaiScript > Core::Scripting::create_chaiscript()
{
   auto chai = boost::make_shared< chaiscript::ChaiScript >();
   //create_chaiscript_bindings( chai );
   return chai;
}