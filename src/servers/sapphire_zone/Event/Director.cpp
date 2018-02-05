#include "Director.h"

Core::Event::Director::Director( Core::Event::Director::DirectorType type, uint16_t contentId ) :
   m_contentId( contentId ),
   m_type( type ),
   m_directorId( ( static_cast< uint32_t >( type ) << 16 ) | contentId ),
   m_sequence( 0 ),
   m_branch( 0 )
{

}

uint32_t Core::Event::Director::getDirectorId() const
{
   return m_directorId;
}

uint16_t Core::Event::Director::getContentId() const
{
   return m_contentId;
}
