#pragma once

#include <memory>
#include <map>

#include <filesystem>

#include "bparse.h"
#include "Exd.h"


namespace xiv
{
   namespace dat
   {
      class GameData;
   }
   namespace exd
   {

      // Language in the exd files - note: chs/chinese is present in the languages array but not in the data files
      enum Language : uint16_t
      {
         none = 0,
         ja = 1,
         en = 2,
         de = 3,
         fr = 4,
         chs = 5,
      };

      class Exh;
      class Exd;

      // A category repesent a several data sheets in the dats all under the same category
      class Cat
      {
      public:
         // i_name: name of the category
         // i_game_data: used to fetch the files needed
         Cat( dat::GameData& i_game_data, const std::string& i_name );
         ~Cat();

         // Returns the name of the category
         const std::string& get_name() const;

         // Returns the header
         Exh& get_header();

         // Returns data for a specific language
         Exd& get_data_ln( Language i_language = Language::none );

         Exd& get_data( Language language = Language::none );
      protected:
         const std::string _name;

         // The header file of the category *.exh
         std::shared_ptr<Exh> _header;
         // The data files of the category, indexed by language *.exd
         // Note that if we have multiple files for different range of IDs, they are merged here
         std::map<Language, std::unique_ptr<Exd>> _data;
      };

   }
}
