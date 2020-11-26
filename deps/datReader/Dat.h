#ifndef XIV_DAT_DAT_H
#define XIV_DAT_DAT_H

#include "SqPack.h"

#include <mutex>

#include <filesystem>

namespace xiv::dat
{

  class File;

  class Dat : public SqPack
  {
  public:
     // Full path to the dat file
     Dat( const std::filesystem::path& i_path, uint32_t i_nb );
     virtual ~Dat();

     // Retrieves a file given the offset in the dat file
     std::unique_ptr<File> getFile( uint32_t i_offset );

     // Appends to the vector the data of this block, it is assumed to be preallocated
     // Is it also assumed that the m_fileMutex is currently locked by this thread before the call
     void extractBlock( uint32_t i_offset, std::vector<char>& o_data );

     // Returns the dat number
     uint32_t getNum() const;

  protected:
     // File reading mutex to have only one thread reading the file at a time
     std::mutex m_fileMutex;

     // Dat nb
     uint32_t m_num;
  };

}

#endif // XIV_DAT_DAT_H
