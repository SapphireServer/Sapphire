#ifndef _CELLHANDLER_H
#define _CELLHANDLER_H
#include <cassert>
#include <array>

#define TilesCount 32
#define TileSize 325.0f
#define _minY (-TilesCount*TileSize/2)
#define _minX (-TilesCount*TileSize/2)

#define _maxY (TilesCount*TileSize/2)
#define _maxX (TilesCount*TileSize/2)

#define CellsPerTile 4
#define _cellSize (TileSize/CellsPerTile)
#define _sizeX (TilesCount*CellsPerTile)
#define _sizeY (TilesCount*CellsPerTile)

#define GetRelatCoord( Coord, CellCoord ) ((_maxX-Coord)-CellCoord*_cellSize)
namespace Sapphire {

template< class T >
class CellHandler
{
public:
  CellHandler();

  ~CellHandler();

  std::shared_ptr< T > getCellPtr( uint32_t x, uint32_t y );

  std::shared_ptr< T > getCellByCoords( float x, float y );

  std::shared_ptr< T > create( uint32_t x, uint32_t y );

  std::shared_ptr< T > createByCoords( float x, float y );

  void remove( uint32_t x, uint32_t y );

  bool allocated( uint32_t x, uint32_t y )
  {
    return m_pCells[ x ][ y ] != nullptr;
  }

  static uint32_t getPosX( float x );

  static uint32_t getPosY( float y );

protected:
  void _init();


  std::array< std::array< std::shared_ptr< T >, _sizeY >, _sizeX > m_pCells;

};

template< class T >
CellHandler< T >::CellHandler()
{

  _init();
}


template< class T >
void CellHandler< T >::_init()
{
}

template< class T >
CellHandler< T >::~CellHandler()
{

}

template< class T >
std::shared_ptr< T > CellHandler< T >::create( uint32_t x, uint32_t y )
{
  if( x >= _sizeX || y >= _sizeY )
  {
    return nullptr;
  }

  if( !m_pCells[ x ][ y ] )
  {
    m_pCells[ x ][ y ] = std::make_shared< T >();
  }

  return  m_pCells[ x ][ y ];
}

template< class T >
std::shared_ptr< T > CellHandler< T >::createByCoords( float x, float y )
{
  return create( getPosX( x ), getPosY( y ) );
}

template< class T >
void CellHandler< T >::remove( uint32_t x, uint32_t y )
{
  if( x >= _sizeX || y >= _sizeY )
  {
    return;
  }

  assert( m_pCells[ x ][ y ] != nullptr );

  m_pCells[ x ][ y ].reset();

}

template< class T >
std::shared_ptr< T > CellHandler< T >::getCellPtr( uint32_t x, uint32_t y )
{
  return m_pCells[ x ][ y ];
}

template< class T >
std::shared_ptr< T > CellHandler< T >::getCellByCoords( float x, float y )
{
  return getCellPtr( getPosX( x ), getPosY( y ) );
}

template< class T >
uint32_t CellHandler< T >::getPosX( float x )
{
  assert( ( x >= _minX ) && ( x <= _maxX ) );
  return ( uint32_t ) ( ( _maxX - x ) / _cellSize );
}

template< class T >
uint32_t CellHandler< T >::getPosY( float y )
{
  assert( ( y >= _minY ) && ( y <= _maxY ) );
  return ( uint32_t ) ( ( _maxY - y ) / _cellSize );
}

}
#endif
