#include "mysql_util.h"

long double strtold(const char *nptr, char **endptr)
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

long double strtonum( const std::string &str, int radix )
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