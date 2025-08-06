#pragma once

#include "Forwards.h"
#include <Logging/Logger.h>

#include <array>
#include <algorithm>
#include <chrono>
#include <random>
#include <memory>
#include <type_traits>
#include <vector>

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
      : m_engine( pEngine ), m_fpuDist( minRange, maxRange ), m_intDist( minRange, maxRange )
    {

    }

    // returns a single value for T type on set ranges, deducing real or integer distribution from given numeric type
    T next()
    {
      if constexpr( std::is_integral< T >::value )
        return m_intDist( *m_engine );

      return static_cast< T >( m_fpuDist( *m_engine ) );
    }

    // returns an array of size nSize with values type T on set ranges, deducing real or integer distribution from given numeric type
    template< std::size_t nSize >
    const std::array< T, nSize > nextCount()
    {
      std::array< T, nSize > _valPush;

      for( auto i = 0; i < nSize; ++i )
      {
        if constexpr( std::is_integral< T >::value )
          _valPush[ i ] = ( m_intDist( *m_engine ) );
        else
          _valPush[ i ] = ( m_fpuDist( *m_engine ) );
      }

      return _valPush;
    }

  protected:
    std::uniform_real_distribution<> m_fpuDist;
    std::uniform_int_distribution<> m_intDist;
    std::shared_ptr< std::mt19937 > m_engine;
  };

  class RNGMgr
  {
  public:
    // Constructs a manager to supply states for random integer and float distribution using a Mersenne Twister engine
    RNGMgr()
    {
      m_engine = std::make_shared< std::mt19937 >( *engineSeed< std::mt19937::state_size >() );
    }

    virtual ~RNGMgr() = default;

    RNGMgr( const RNGMgr& pRNGMgr ) = delete;
    RNGMgr& operator=( const RNGMgr& pRNGMgr ) = delete;

    /*!
     * @brief Creates a state with specified parameters for multiple uses
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

    /*!
     * @brief Creates a state with only typed data arithmetic range
     * @tparam Numeric type to be used for the generator and range (::min(), ::max() of numeric type)
     * @return Random number generator object
     */
    template< typename T, typename = typename std::enable_if< std::is_arithmetic< T >::value, T >::type >
    RandGenerator< T > getRandGenerator()
    {
      return RandGenerator< T >( m_engine );
    }

  private:

    template< std::size_t STATE_SIZE >
    std::unique_ptr< std::seed_seq > engineSeed()
    {
      // initialize mt engine with manually seeded random_device

      std::array< uint32_t, STATE_SIZE > seedArray;
      std::random_device rd;

      // check if kernel can supply sufficiently non-deterministic output

      if( rd.entropy() == 0.f )
        Logger::error( "Kernel random device entropy reported zero - Random number generator may be poor quality" );

      std::generate_n( seedArray.data(), seedArray.size(), std::ref( rd ) );
      auto pSeq = std::make_unique< std::seed_seq >( std::begin( seedArray ), std::end( seedArray ) );

      return pSeq;
    }

    std::shared_ptr< std::mt19937 > m_engine;
  };

}
