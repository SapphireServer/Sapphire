#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <algorithm>


namespace Engine
{
  using vec2 = glm::vec2;
  using vec3 = glm::vec3;
  using vec4 = glm::vec4;
  using ivec4 = glm::ivec4;
  using ivec3 = glm::ivec3;
  using ivec2 = glm::ivec2;
  using i8vec2 = glm::i8vec2;
  using i8vec3 = glm::i8vec3;
  using i8vec4 = glm::i8vec4;
  using mat3 = glm::mat3;
  using mat4 = glm::mat4;
  using dmat4 = glm::dmat4;
  
  struct AABB
  {
    vec3 min{};
    vec3 max{};
  };

}

template< typename T >
inline void hash_combine( std::size_t& seed, const T& v )
{
  seed ^= std::hash< T >{}( v ) + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 );
}

namespace std
{
  template<>
  struct hash< glm::vec3 >
  {
    size_t operator()( const glm::vec3& v ) const
    {
      // You can use a simple hash function like this
      size_t hash = 0;
      hash_combine( hash, std::hash< float >{}( v.x ) );
      hash_combine( hash, std::hash< float >{}( v.y ) );
      hash_combine( hash, std::hash< float >{}( v.z ) );
      return hash;
    }
  };
}

namespace std
{
  template<>
  struct ::std::hash< glm::ivec3 >
  {
    size_t operator()( const glm::vec3& v ) const
    {
      // You can use a simple hash function like this
      size_t hash = 0;
      hash_combine( hash, std::hash< int >{}( v.x ) );
      hash_combine( hash, std::hash< int >{}( v.y ) );
      hash_combine( hash, std::hash< int >{}( v.z ) );
      return hash;
    }
  };
}