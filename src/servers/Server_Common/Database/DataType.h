#ifndef SAPPHIRE_DATATYPE_H
#define SAPPHIRE_DATATYPE_H
namespace Core
{
namespace Db
{
   class DataType
   {
      DataType();

   public:
      enum
      {
         UNKNOWN = 0,
         BIT,
         TINYINT,
         SMALLINT,
         MEDIUMINT,
         INTEGER,
         BIGINT,
         REAL,
         DOUBLE,
         DECIMAL,
         NUMERIC,
         CHAR,
         BINARY,
         VARCHAR,
         VARBINARY,
         LONGVARCHAR,
         LONGVARBINARY,
         TIMESTAMP,
         DATE,
         TIME,
         YEAR,
         GEOMETRY,
         ENUM,
         SET,
         SQLNULL,
         JSON
      };
   };
}
}
#endif //SAPPHIRE_DATATYPE_H
