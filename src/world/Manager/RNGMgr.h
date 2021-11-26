#pragma once

#include "Forwards.h"

#include <array>
#include <algorithm>
#include <chrono>
#include <random>
#include <memory>
#include <type_traits>

namespace Sapphire::World::Manager
{
  /*!
   * @brief Generator object that is used on multiple state situations
   */
  template< typename T, typename = typename std::enable_if< std::is_arithmetic< T >::value, T >::type >
  class RandGenerator
  {
  public:
    RandGenerator( std::shared_ptr< std::mt19937 > pEngine, T minRange = std::numeric_limits< T >::min(), T maxRange = std::numeric_limits< T >::max() )
      : m_engine( pEngine ), m_dist( minRange, maxRange )
    {

    }

    T next()
    {
      return m_dist( *m_engine );
    }

  private:
    std::uniform_real_distribution< T > m_dist;
    std::shared_ptr< std::mt19937 > m_engine;
  };

  class RNGMgr
  {
  public:
    RNGMgr()
    {
      m_engine = std::make_shared< std::mt19937 >( *engineSeed< std::mt19937::state_size >() );
    }

    virtual ~RNGMgr() = default;

    RNGMgr( const RNGMgr& pRNGMgr ) = delete;
    RNGMgr& operator=( const RNGMgr& pRNGMgr ) = delete;

    /*!
     * @brief Creates a RNG with specified parameters for multiple uses
     * @tparam Numeric type to be used for the generator
     * @param Minimum value possible for the random value
     * @param Maximum value possible for the random value
     * @return Random number generator object 
     */
    template< typename T, typename = typename std::enable_if< std::is_arithmetic< T >::value, T >::type >
    RandGenerator< T > getRandGenerator( T minRange, T maxRange )
    {
      return RandGenerator< T >( m_engine, minRange, maxRange );
    }

  private:

    template< std::size_t STATE_SIZE >
    std::unique_ptr< std::seed_seq > engineSeed()
    {
      // initialize mt engine with manually seeded random_device

      std::array< uint32_t, STATE_SIZE > seedArray;
      std::random_device rd;

      std::generate_n( seedArray.data(), seedArray.size(), std::ref( rd ) );
      auto pSeq = std::make_unique< std::seed_seq >( std::begin( seedArray ), std::end( seedArray ) );

      return pSeq;
    }

    std::shared_ptr< std::mt19937 > m_engine;
  };

}
