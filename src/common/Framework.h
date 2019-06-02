#ifndef _CORE_FRAMEWORK_H
#define _CORE_FRAMEWORK_H

#include <map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <cassert>

namespace Sapphire
{

  class Framework
  {
    using TypenameToObject = std::map< std::type_index, std::shared_ptr< void > >;
    TypenameToObject ObjectMap;

  public:
    template< typename T >
    std::shared_ptr< T > get()
    {
      auto iType = ObjectMap.find( typeid( T ) );
      assert( !( iType == ObjectMap.end() ) );
      return std::static_pointer_cast< T >( iType->second );
    }

    template< typename T >
    void set( std::shared_ptr< T > value )
    {
      assert( value ); // why would anyone store nullptrs....
      ObjectMap[ typeid( T ) ] = value;
    }
  };

}

#endif // _CORE_FRAMEWORK_H
