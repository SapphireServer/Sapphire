#include "mysql_util.h"
#include "DataType.h"
#include <mysql.h>
#include <vector>
#include <stdexcept>

long double Util::strtold(const char *nptr, char **endptr)
{
   /*
  * Experienced odd compilation errors on one of windows build hosts -
  * cmake reported there is strold function. Since double and long double on windows
  * are of the same size - we are using strtod on those platforms regardless
  * to the HAVE_FUNCTION_STRTOLD value
  */
#ifdef _WIN32
   return ::strtod(nptr, endptr);
#else
   # ifndef HAVE_FUNCTION_STRTOLD
  return ::strtod(nptr, endptr);
# else
#  if defined(__hpux) && defined(_LONG_DOUBLE)
  union {
    long_double l_d;
    long double ld;
  } u;
  u.l_d = ::strtold( nptr, endptr);
  return u.ld;
#  else
  return ::strtold(nptr, endptr);
#  endif
# endif
#endif

}

long double Util::strtonum( const std::string &str, int radix )
{
   typedef std::istreambuf_iterator< char > iter_t;
   static std::locale c_locale( "C" );
   static const std::num_get< char > &cvt = std::use_facet< std::num_get< char > >( c_locale );

   std::istringstream inp( str );
   long double val = 0.0L;

   inp.imbue( c_locale );

   switch( radix )
   {
      case 10: inp.setf( std::ios_base::dec, std::ios_base::basefield ); break;
      case 16: inp.setf( std::ios_base::hex, std::ios_base::basefield ); break;
      case  8: inp.setf( std::ios_base::oct, std::ios_base::basefield ); break;
      default:
         inp.setf( std::ios_base::fmtflags( 0 ), std::ios_base::basefield );
         break;
   }

   iter_t beg( inp ), end;
   std::ios::iostate err = std::ios_base::goodbit;

   cvt.get( beg, end, inp, err, val );

   return val;
}

#define cppconn_mbcharlen_big5		NULL
#define check_mb_big5				NULL
#define cppconn_mbcharlen_ujis		NULL
#define check_mb_ujis				NULL
#define cppconn_mbcharlen_sjis		NULL
#define check_mb_sjis				NULL
#define cppconn_mbcharlen_euckr		NULL
#define check_mb_euckr				NULL
#define cppconn_mbcharlen_gb2312	NULL
#define check_mb_gb2312				NULL
#define cppconn_mbcharlen_gbk		NULL
#define check_mb_gbk				NULL
#define cppconn_mbcharlen_utf8		NULL
#define check_mb_utf8_valid			NULL
#define cppconn_mbcharlen_ucs2		NULL
#define check_mb_ucs2				NULL
#define cppconn_mbcharlen_cp932		NULL
#define check_mb_cp932				NULL
#define cppconn_mbcharlen_eucjpms	NULL
#define check_mb_eucjpms			NULL
#define cppconn_mbcharlen_utf8		NULL
#define check_mb_utf8_valid			NULL
#define cppconn_mbcharlen_utf8mb4	cppconn_mbcharlen_utf8
#define check_mb_utf8mb4_valid		check_mb_utf8_valid
#define cppconn_mbcharlen_utf16		NULL
#define check_mb_utf16_valid		NULL
#define cppconn_mbcharlen_utf32		NULL
#define check_mb_utf32_valid		NULL

/* {{{ our_charsets60 */
const Util::OUR_CHARSET our_charsets60[] =
  {
    {   1, "big5","big5_chinese_ci", 1, 2, "", cppconn_mbcharlen_big5, check_mb_big5},
    {   3, "dec8", "dec8_swedisch_ci", 1, 1, "", NULL, NULL},
    {   4, "cp850", "cp850_general_ci", 1, 1, "", NULL, NULL},
    {   6, "hp8", "hp8_english_ci", 1, 1, "", NULL, NULL},
    {   7, "koi8r", "koi8r_general_ci", 1, 1, "", NULL, NULL},
    {   8, "latin1", "latin1_swedish_ci", 1, 1, "", NULL, NULL},
    {   9, "latin2", "latin2_general_ci", 1, 1, "", NULL, NULL},
    {  10, "swe7", "swe7_swedish_ci", 1, 1, "", NULL, NULL},
    {  11, "ascii", "ascii_general_ci", 1, 1, "", NULL, NULL},
    {  12, "ujis", "ujis_japanese_ci", 1, 3, "", cppconn_mbcharlen_ujis, check_mb_ujis},
    {  13, "sjis", "sjis_japanese_ci", 1, 2, "", cppconn_mbcharlen_sjis, check_mb_sjis},
    {  16, "hebrew", "hebrew_general_ci", 1, 1, "", NULL, NULL},
    {  18, "tis620", "tis620_thai_ci", 1, 1, "", NULL, NULL},
    {  19, "euckr", "euckr_korean_ci", 1, 2, "", cppconn_mbcharlen_euckr, check_mb_euckr},
    {  22, "koi8u", "koi8u_general_ci", 1, 1, "", NULL, NULL},
    {  24, "gb2312", "gb2312_chinese_ci", 1, 2, "", cppconn_mbcharlen_gb2312, check_mb_gb2312},
    {  25, "greek", "greek_general_ci", 1, 1, "", NULL, NULL},
    {  26, "cp1250", "cp1250_general_ci", 1, 1, "", NULL, NULL},
    {  28, "gbk", "gbk_chinese_ci", 1, 2, "", cppconn_mbcharlen_gbk, check_mb_gbk},
    {  30, "latin5", "latin5_turkish_ci", 1, 1, "", NULL, NULL},
    {  32, "armscii8", "armscii8_general_ci", 1, 1, "", NULL, NULL},
    {  33, "utf8", "utf8_general_ci", 1, 3, "UTF-8 Unicode", cppconn_mbcharlen_utf8,  check_mb_utf8_valid},
    {  35, "ucs2", "ucs2_general_ci", 2, 2, "UCS-2 Unicode", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    {  36, "cp866", "cp866_general_ci", 1, 1, "", NULL, NULL},
    {  37, "keybcs2", "keybcs2_general_ci", 1, 1, "", NULL, NULL},
    {  38, "macce", "macce_general_ci", 1, 1, "", NULL, NULL},
    {  39, "macroman", "macroman_general_ci", 1, 1, "", NULL, NULL},
    {  40, "cp852", "cp852_general_ci", 1, 1, "", NULL, NULL},
    {  41, "latin7", "latin7_general_ci", 1, 1, "", NULL, NULL},
    {  51, "cp1251", "cp1251_general_ci", 1, 1, "", NULL, NULL},
    {  57, "cp1256", "cp1256_general_ci", 1, 1, "", NULL, NULL},
    {  59, "cp1257", "cp1257_general_ci", 1, 1, "", NULL, NULL},
    {  63, "binary", "binary", 1, 1, "", NULL, NULL},
    {  92, "geostd8", "geostd8_general_ci", 1, 1, "", NULL, NULL},
    {  95, "cp932", "cp932_japanese_ci", 1, 2, "", cppconn_mbcharlen_cp932, check_mb_cp932},
    {  97, "eucjpms", "eucjpms_japanese_ci", 1, 3, "", cppconn_mbcharlen_eucjpms, check_mb_eucjpms},
    {   2, "latin2", "latin2_czech_cs", 1, 1, "", NULL, NULL},
    {   5, "latin1", "latin1_german_ci", 1, 1, "", NULL, NULL},
    {  14, "cp1251", "cp1251_bulgarian_ci", 1, 1, "", NULL, NULL},
    {  15, "latin1", "latin1_danish_ci", 1, 1, "", NULL, NULL},
    {  17, "filename", "filename", 1, 5, "", NULL, NULL},
    {  20, "latin7", "latin7_estonian_cs", 1, 1, "", NULL, NULL},
    {  21, "latin2", "latin2_hungarian_ci", 1, 1, "", NULL, NULL},
    {  23, "cp1251", "cp1251_ukrainian_ci", 1, 1, "", NULL, NULL},
    {  27, "latin2", "latin2_croatian_ci", 1, 1, "", NULL, NULL},
    {  29, "cp1257", "cp1257_lithunian_ci", 1, 1, "", NULL, NULL},
    {  31, "latin1", "latin1_german2_ci", 1, 1, "", NULL, NULL},
    {  34, "cp1250", "cp1250_czech_cs", 1, 1, "", NULL, NULL},
    {  42, "latin7", "latin7_general_cs", 1, 1, "", NULL, NULL},
    {  43, "macce", "macce_bin", 1, 1, "", NULL, NULL},
    {  44, "cp1250", "cp1250_croatian_ci", 1, 1, "", NULL, NULL},
    {  47, "latin1", "latin1_bin", 1, 1, "", NULL, NULL},
    {  48, "latin1", "latin1_general_ci", 1, 1, "", NULL, NULL},
    {  49, "latin1", "latin1_general_cs", 1, 1, "", NULL, NULL},
    {  50, "cp1251", "cp1251_bin", 1, 1, "", NULL, NULL},
    {  52, "cp1251", "cp1251_general_cs", 1, 1, "", NULL, NULL},
    {  53, "macroman", "macroman_bin", 1, 1, "", NULL, NULL},
    {  58, "cp1257", "cp1257_bin", 1, 1, "", NULL, NULL},
    {  60, "armascii8", "armascii8_bin", 1, 1, "", NULL, NULL},
    {  65, "ascii", "ascii_bin", 1, 1, "", NULL, NULL},
    {  66, "cp1250", "cp1250_bin", 1, 1, "", NULL, NULL},
    {  67, "cp1256", "cp1256_bin", 1, 1, "", NULL, NULL},
    {  68, "cp866", "cp866_bin", 1, 1, "", NULL, NULL},
    {  69, "dec8", "dec8_bin", 1, 1, "", NULL, NULL},
    {  70, "greek", "greek_bin", 1, 1, "", NULL, NULL},
    {  71, "hebrew", "hebrew_bin", 1, 1, "", NULL, NULL},
    {  72, "hp8", "hp8_bin", 1, 1, "", NULL, NULL},
    {  73, "keybcs2", "keybcs2_bin", 1, 1, "", NULL, NULL},
    {  74, "koi8r", "koi8r_bin", 1, 1, "", NULL, NULL},
    {  75, "koi8u", "koi8u_bin", 1, 1, "", NULL, NULL},
    {  77, "latin2", "latin2_bin", 1, 1, "", NULL, NULL},
    {  78, "latin5", "latin5_bin", 1, 1, "", NULL, NULL},
    {  79, "latin7", "latin7_bin", 1, 1, "", NULL, NULL},
    {  80, "cp850", "cp850_bin", 1, 1, "", NULL, NULL},
    {  81, "cp852", "cp852_bin", 1, 1, "", NULL, NULL},
    {  82, "swe7", "swe7_bin", 1, 1, "", NULL, NULL},
    {  93, "geostd8", "geostd8_bin", 1, 1, "", NULL, NULL},
    {  83, "utf8", "utf8_bin", 1, 3, "UTF-8 Unicode", cppconn_mbcharlen_utf8,  check_mb_utf8_valid},
    {  84, "big5", "big5_bin", 1, 2, "", cppconn_mbcharlen_big5, check_mb_big5},
    {  85, "euckr", "euckr_bin", 1, 2, "", cppconn_mbcharlen_euckr, check_mb_euckr},
    {  86, "gb2312", "gb2312_bin", 1, 2, "", cppconn_mbcharlen_gb2312, check_mb_gb2312},
    {  87, "gbk", "gbk_bin", 1, 2, "", cppconn_mbcharlen_gbk, check_mb_gbk},
    {  88, "sjis", "sjis_bin", 1, 2, "", cppconn_mbcharlen_sjis, check_mb_sjis},
    {  89, "tis620", "tis620_bin", 1, 1, "", NULL, NULL},
    {  90, "ucs2", "ucs2_bin", 2, 2, "UCS-2 Unicode", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    {  91, "ujis", "ujis_bin", 1, 3, "", cppconn_mbcharlen_ujis, check_mb_ujis},
    {  94, "latin1", "latin1_spanish_ci", 1, 1, "", NULL, NULL},
    {  96, "cp932", "cp932_bin", 1, 2, "", cppconn_mbcharlen_cp932, check_mb_cp932},
    {  99, "cp1250", "cp1250_polish_ci", 1, 1, "", NULL, NULL},
    {  98, "eucjpms", "eucjpms_bin", 1, 3, "", cppconn_mbcharlen_eucjpms, check_mb_eucjpms},
    { 128, "ucs2", "ucs2_unicode_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 129, "ucs2", "ucs2_icelandic_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 130, "ucs2", "ucs2_latvian_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 131, "ucs2", "ucs2_romanian_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 132, "ucs2", "ucs2_slovenian_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 133, "ucs2", "ucs2_polish_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 134, "ucs2", "ucs2_estonian_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 135, "ucs2", "ucs2_spanish_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 136, "ucs2", "ucs2_swedish_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 137, "ucs2", "ucs2_turkish_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 138, "ucs2", "ucs2_czech_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 139, "ucs2", "ucs2_danish_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 140, "ucs2", "ucs2_lithunian_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 141, "ucs2", "ucs2_slovak_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 142, "ucs2", "ucs2_spanish2_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 143, "ucs2", "ucs2_roman_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 144, "ucs2", "ucs2_persian_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 145, "ucs2", "ucs2_esperanto_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 146, "ucs2", "ucs2_hungarian_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 147, "ucs2", "ucs2_sinhala_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 148, "ucs2", "ucs2_german2_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 149, "ucs2", "ucs2_croatian_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 150, "ucs2", "ucs2_unicode_520_ci", 2, 2, "", cppconn_mbcharlen_ucs2, check_mb_ucs2},
    { 192, "utf8", "utf8_unicode_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 193, "utf8", "utf8_icelandic_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 194, "utf8", "utf8_latvian_ci", 1, 3, "", cppconn_mbcharlen_utf8,  check_mb_utf8_valid},
    { 195, "utf8", "utf8_romanian_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 196, "utf8", "utf8_slovenian_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 197, "utf8", "utf8_polish_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 198, "utf8", "utf8_estonian_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 199, "utf8", "utf8_spanish_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 200, "utf8", "utf8_swedish_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 201, "utf8", "utf8_turkish_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 202, "utf8", "utf8_czech_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 203, "utf8", "utf8_danish_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid },
    { 204, "utf8", "utf8_lithunian_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid },
    { 205, "utf8", "utf8_slovak_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 206, "utf8", "utf8_spanish2_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 207, "utf8", "utf8_roman_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 208, "utf8", "utf8_persian_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 209, "utf8", "utf8_esperanto_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 210, "utf8", "utf8_hungarian_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 211, "utf8", "utf8_sinhala_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 212, "utf8", "utf8_german2_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 213, "utf8", "utf8_croatian_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 214, "utf8", "utf8_unicode_520_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 215, "utf8", "utf8_vietnamese_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 223, "utf8", "utf8_general_mysql500_ci", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},
    { 45, "utf8mb4", "utf8mb4_general_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 46, "utf8mb4", "utf8mb4_bin", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 224, "utf8mb4", "utf8mb4_unicode_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 225, "utf8mb4", "utf8mb4_icelandic_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 226, "utf8mb4", "utf8mb4_latvian_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 227, "utf8mb4", "utf8mb4_romanian_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 228, "utf8mb4", "utf8mb4_slovenian_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 229, "utf8mb4", "utf8mb4_polish_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 230, "utf8mb4", "utf8mb4_estonian_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 231, "utf8mb4", "utf8mb4_spanish_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 232, "utf8mb4", "utf8mb4_swedish_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 233, "utf8mb4", "utf8mb4_turkish_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 234, "utf8mb4", "utf8mb4_czech_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 235, "utf8mb4", "utf8mb4_danish_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 236, "utf8mb4", "utf8mb4_lithuanian_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 237, "utf8mb4", "utf8mb4_slovak_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 238, "utf8mb4", "utf8mb4_spanish2_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 239, "utf8mb4", "utf8mb4_roman_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 240, "utf8mb4", "utf8mb4_persian_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 241, "utf8mb4", "utf8mb4_esperanto_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 242, "utf8mb4", "utf8mb4_hungarian_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 243, "utf8mb4", "utf8mb4_sinhala_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 244, "utf8mb4", "utf8mb4_german2_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 245, "utf8mb4", "utf8mb4_croatian_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 246, "utf8mb4", "utf8mb4_unicode_520_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},
    { 247, "utf8mb4", "utf8mb4_vietnamese_ci", 1, 4, "", cppconn_mbcharlen_utf8mb4, check_mb_utf8mb4_valid},

    /*Should not really happen, but adding them */
    { 254, "utf8", "utf8_general_cs", 1, 3, "", cppconn_mbcharlen_utf8, check_mb_utf8_valid},

    { 101, "utf16", "utf16_unicode_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 102, "utf16", "utf16_icelandic_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 103, "utf16", "utf16_latvian_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 104, "utf16", "utf16_romanian_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 105, "utf16", "utf16_slovenian_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 106, "utf16", "utf16_polish_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 107, "utf16", "utf16_estonian_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 108, "utf16", "utf16_spanish_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 109, "utf16", "utf16_swedish_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 110, "utf16", "utf16_turkish_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 111, "utf16", "utf16_czech_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 112, "utf16", "utf16_danish_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 113, "utf16", "utf16_lithuanian_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 114, "utf16", "utf16_slovak_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 115, "utf16", "utf16_spanish2_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 116, "utf16", "utf16_roman_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 117, "utf16", "utf16_persian_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 118, "utf16", "utf16_esperanto_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 119, "utf16", "utf16_hungarian_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 120, "utf16", "utf16_sinhala_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 121, "utf16", "utf16_german2_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 122, "utf16", "utf16_croatian_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 123, "utf16", "utf16_unicode_520_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},
    { 124, "utf16", "utf16_vietnamese_ci", 2, 4, "", cppconn_mbcharlen_utf16, check_mb_utf16_valid},

    { 160, "utf32", "utf32_unicode_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 161, "utf32", "utf32_icelandic_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 162, "utf32", "utf32_latvian_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 163, "utf32", "utf32_romanian_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 164, "utf32", "utf32_slovenian_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 165, "utf32", "utf32_polish_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 166, "utf32", "utf32_estonian_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 167, "utf32", "utf32_spanish_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 168, "utf32", "utf32_swedish_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 169, "utf32", "utf32_turkish_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 170, "utf32", "utf32_czech_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 171, "utf32", "utf32_danish_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 172, "utf32", "utf32_lithuanian_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 173, "utf32", "utf32_slovak_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 174, "utf32", "utf32_spanish2_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 175, "utf32", "utf32_roman_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 176, "utf32", "utf32_persian_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 177, "utf32", "utf32_esperanto_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 178, "utf32", "utf32_hungarian_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 179, "utf32", "utf32_sinhala_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 180, "utf32", "utf32_german2_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 181, "utf32", "utf32_croatian_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 182, "utf32", "utf32_unicode_520_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},
    { 183, "utf32", "utf32_vietnamese_ci", 4, 4, "", cppconn_mbcharlen_utf32, check_mb_utf32_valid},

    {   0, NULL, NULL, 0, 0, NULL, NULL, NULL}
};
#define MAGIC_BINARY_CHARSET_NR 63

const Util::OUR_CHARSET * Util::find_charset(unsigned int charsetnr)
{
   const OUR_CHARSET * c = our_charsets60;

   do {
      if (c->nr == charsetnr) {
         return c;
      }
      ++c;
   } while (c[0].nr != 0);
   return NULL;
}

int Util::mysql_type_to_datatype( const MYSQL_FIELD * const field )
{
   switch (field->type) {
      case MYSQL_TYPE_BIT:
         if (field->flags !=(BINARY_FLAG|UNSIGNED_FLAG))
            return Core::Db::DataType::BIT;
         return Core::Db::DataType::BINARY;
      case MYSQL_TYPE_DECIMAL:
      case MYSQL_TYPE_NEWDECIMAL:
         return Core::Db::DataType::DECIMAL;
      case MYSQL_TYPE_TINY:
         return Core::Db::DataType::TINYINT;
      case MYSQL_TYPE_SHORT:
         return Core::Db::DataType::SMALLINT;
      case MYSQL_TYPE_INT24:
         return Core::Db::DataType::MEDIUMINT;
      case MYSQL_TYPE_LONG:
         return Core::Db::DataType::INTEGER;
      case MYSQL_TYPE_LONGLONG:
         return Core::Db::DataType::BIGINT;
      case MYSQL_TYPE_FLOAT:
         return Core::Db::DataType::REAL;
      case MYSQL_TYPE_DOUBLE:
         return Core::Db::DataType::DOUBLE;
      case MYSQL_TYPE_NULL:
         return Core::Db::DataType::SQLNULL;
      case MYSQL_TYPE_TIMESTAMP:
         return Core::Db::DataType::TIMESTAMP;
      case MYSQL_TYPE_DATE:
         return Core::Db::DataType::DATE;
      case MYSQL_TYPE_TIME:
         return Core::Db::DataType::TIME;
      case MYSQL_TYPE_YEAR:
         return Core::Db::DataType::YEAR;
      case MYSQL_TYPE_DATETIME:
         return Core::Db::DataType::TIMESTAMP;
      case MYSQL_TYPE_TINY_BLOB:// should no appear over the wire
      {
         bool isBinary = (field->flags & BINARY_FLAG) &&
                         field->charsetnr == MAGIC_BINARY_CHARSET_NR;
         const Util::OUR_CHARSET * const cs =
                 Util::find_charset(field->charsetnr);
         if (!cs) {
            std::ostringstream msg("Server sent unknown charsetnr (");
            msg << field->charsetnr << ") . Please report";
            throw std::runtime_error( msg.str() );
         }
         return isBinary ? Core::Db::DataType::VARBINARY : Core::Db::DataType::VARCHAR;
      }
      case MYSQL_TYPE_MEDIUM_BLOB:// should no appear over the wire
      case MYSQL_TYPE_LONG_BLOB:// should no appear over the wire
      case MYSQL_TYPE_BLOB:
      {
         bool isBinary = (field->flags & BINARY_FLAG) &&
                         field->charsetnr == MAGIC_BINARY_CHARSET_NR;
         const Util::OUR_CHARSET * const cs =
                 Util::find_charset(field->charsetnr);
         if (!cs) {
            std::ostringstream msg("Server sent unknown charsetnr (");
            msg << field->charsetnr << ") . Please report";
            throw std::runtime_error( msg.str() );
         }
         return isBinary ? Core::Db::DataType::LONGVARBINARY : Core::Db::DataType::LONGVARCHAR;
      }
      case MYSQL_TYPE_VARCHAR:
      case MYSQL_TYPE_VAR_STRING:
         if (field->flags & SET_FLAG) {
            return Core::Db::DataType::SET;
         }
         if (field->flags & ENUM_FLAG) {
            return Core::Db::DataType::ENUM;
         }
         if ((field->flags & BINARY_FLAG) && field->charsetnr == MAGIC_BINARY_CHARSET_NR) {
            return Core::Db::DataType::VARBINARY;
         }
         return Core::Db::DataType::VARCHAR;
      case MYSQL_TYPE_STRING:
         if (field->flags & SET_FLAG) {
            return Core::Db::DataType::SET;
         }
         if (field->flags & ENUM_FLAG) {
            return Core::Db::DataType::ENUM;
         }
         if ((field->flags & BINARY_FLAG) && field->charsetnr == MAGIC_BINARY_CHARSET_NR) {
            return Core::Db::DataType::BINARY;
         }
         return Core::Db::DataType::CHAR;
      case MYSQL_TYPE_ENUM:
         /* This hould never happen - MYSQL_TYPE_ENUM is not sent over the wire, just used in the server */
         return Core::Db::DataType::ENUM;
      case MYSQL_TYPE_SET:
         /* This hould never happen - MYSQL_TYPE_SET is not sent over the wire, just used in the server */
         return Core::Db::DataType::SET;
      case MYSQL_TYPE_GEOMETRY:
         return Core::Db::DataType::GEOMETRY;
#if LIBMYSQL_VERSION_ID > 50700
      case MYSQL_TYPE_JSON:
      return Core::Db::DataType::JSON;
#endif //LIBMYSQL_VERSION_ID > 50700
      default:
         return Core::Db::DataType::UNKNOWN;
   }
}