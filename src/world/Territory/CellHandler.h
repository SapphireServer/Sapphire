#ifndef _CELLHANDLER_H
#define _CELLHANDLER_H
#include <cassert>

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

class Zone;

template< class T >
class CellHandler
{
public:
  CellHandler();

  ~CellHandler();

  T* getCellPtr( uint32_t x, uint32_t y );

  T* getCellByCoords( float x, float y );

  T* create( uint32_t x, uint32_t y );

  T* createByCoords( float x, float y );

  void remove( uint32_t x, uint32_t y );

  bool allocated( uint32_t x, uint32_t y )
  {
    return m_pCells[ x ][ y ] != nullptr;
  }

  static uint32_t getPosX( float x );

  static uint32_t getPosY( float y );

protected:
  void _init();


  T*** m_pCells;

};

template< class T >
CellHandler< T >::CellHandler()
{

  _init();
}


template< class T >
void CellHandler< T >::_init()
{
  m_pCells = new T** [_sizeX];

  assert( m_pCells );
  for( uint32_t i = 0; i < _sizeX; i++ )
  {
    m_pCells[ i ] = nullptr;
  }

}

template< class T >
CellHandler< T >::~CellHandler()
{
  if( m_pCells )
  {
    for( uint32_t i = 0; i < _sizeX; i++ )
    {
      if( !m_pCells[ i ] )
      {
        continue;
      }

      for( uint32_t j = 0; j < _sizeY; j++ )
      {
        if( m_pCells[ i ][ j ] )
        {
          delete m_pCells[ i ][ j ];
        }
      }
      delete[] m_pCells[ i ];
    }
    delete[] m_pCells;
  }
}

template< class T >
T* CellHandler< T >::create( uint32_t x, uint32_t y )
{
  if( x >= _sizeX || y >= _sizeY )
  {
    return nullptr;
  }

  if( !m_pCells[ x ] )
  {
    m_pCells[ x ] = new T* [_sizeY];
    memset( m_pCells[ x ], 0, sizeof( T* ) * _sizeY );
  }

  assert( m_pCells[ x ][ y ] == nullptr );

  T* cls = new T;
  m_pCells[ x ][ y ] = cls;

  return cls;
}

template< class T >
T* CellHandler< T >::createByCoords( float x, float y )
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

  if( !m_pCells[ x ] )
  {
    return;
  }

  assert( m_pCells[ x ][ y ] != nullptr );

  T* cls = m_pCells[ x ][ y ];
  m_pCells[ x ][ y ] = nullptr;

  delete cls;
}

template< class T >
T* CellHandler< T >::getCellPtr( uint32_t x, uint32_t y )
{
  if( !m_pCells[ x ] )
  {
    return nullptr;
  }

  return m_pCells[ x ][ y ];
}

template< class T >
T* CellHandler< T >::getCellByCoords( float x, float y )
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
