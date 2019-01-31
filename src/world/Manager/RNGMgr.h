#ifndef SAPPHIRE_RNGMGR_H
#define SAPPHIRE_RNGMGR_H

#include "Forwards.h"
#include "BaseManager.h"

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
    RandGenerator( T minRange = std::numeric_limits< T >::min(), T maxRange = std::numeric_limits< T >::max() )
      : m_engine( *engineSeed< std::mt19937::state_size >() ), m_dist( minRange, maxRange )
    {

    }

    T next()
    {
      return m_dist( m_engine );
    }
  private:
    template< std::size_t STATE_SIZE >
    std::unique_ptr< std::seed_seq > engineSeed()
    {
      std::array< uint32_t, STATE_SIZE > seedArray;
      std::random_device rd;

      std::generate_n( seedArray.data(), seedArray.size(), std::ref( rd ) );
      auto pSeq = std::make_unique< std::seed_seq >( std::begin( seedArray ), std::end( seedArray ) );

      return pSeq;
    }

    std::uniform_real_distribution< T > m_dist;
    std::mt19937 m_engine;
  };

  class RNGMgr : public BaseManager
  {

  public:


    RNGMgr( FrameworkPtr pFw );
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
      return RandGenerator< T >( minRange, maxRange );
    }

  private:

    template< std::size_t STATE_SIZE >
    std::unique_ptr< std::seed_seq > engineSeed()
    {
      std::array< uint32_t, STATE_SIZE > seedArray;
      std::random_device rd;

      std::generate_n( seedArray.data(), seedArray.size(), std::ref( rd ) );
      auto pSeq = std::make_unique< std::seed_seq >( std::begin( seedArray ), std::end( seedArray ) );

      return pSeq;
    }

    std::mt19937 m_engine;
  };

}

#endif // SAPPHIRE_RNGMGR_H
