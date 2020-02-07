#ifndef XIV_DAT_FILE_H
#define XIV_DAT_FILE_H

#include <vector>

#include <filesystem>
#include <stdint.h>
#include "bparse.h"


namespace xiv 
{
   namespace dat
   {
      enum class FileType : uint32_t
      {
         empty = 1, 
         standard = 2, 
         model = 3, 
         texture = 4,
      };
   }
};

namespace xiv
{
   namespace dat
   {

      class Dat;

      // Basic file from the dats
      class File
      {
         friend class Dat;
      public:
         File();
         ~File();

         FileType get_type() const;

         // Getters functions for the data in the file
         const std::vector<std::vector<char>>& get_data_sections() const;
         std::vector<std::vector<char>>& access_data_sections();

         void exportToFile( const std::filesystem::path& i_path ) const;

      protected:
         FileType _type;
         std::vector<std::vector<char>> _data_sections;
      };

   }
}

#endif // XIV_DAT_FILE_H
