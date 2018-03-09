#ifndef _CORE_FRAMEWORK_H
#define _CORE_FRAMEWORK_H

#include <map>
#include <typeindex>
#include <typeinfo>
#include <boost/shared_ptr.hpp>
#include <cassert>

namespace Core
{

   class Framework
   {
      using TypenameToObject = std::map< std::type_index, boost::shared_ptr< void > >;
      TypenameToObject ObjectMap;

   public:
      template< typename T >
      boost::shared_ptr< T > get()
      {
         auto iType = ObjectMap.find( typeid( T ) );
         assert( !( iType == ObjectMap.end() ) );
         return boost::static_pointer_cast< T >( iType->second );
      }

      template< typename T >
      void set( boost::shared_ptr< T > value )
      {
         assert( value ); // why would anyone store nullptrs....
         ObjectMap[typeid( T )] = value;
      }
   };

}

#endif // _CORE_FRAMEWORK_H
