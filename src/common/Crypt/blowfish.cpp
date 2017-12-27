// blowfish.cpp   C++ class implementation of the BLOWFISH encryption algorithm
// _THE BLOWFISH ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger

#include <cstdint>
#include "blowfish.h"
#include "blowfish.h2"	// holds the random digit tables

#define S(x,i) (SBoxes[i][x.w.byte##i])
#define bf_F(x) (((S(x,0) + S(x,1)) ^ S(x,2)) + S(x,3))
#define ROUND(a,b,n) (a.dword ^= bf_F(b) ^ PArray[n])


BlowFish::BlowFish ()
{
 	PArray = new DWORD [18] ;
 	SBoxes = new DWORD [4][256] ;
}

BlowFish::~BlowFish ()
{
	delete PArray ;
	delete [] SBoxes ;
}

	// the low level (private) encryption function
void BlowFish::Blowfish_encipher (DWORD *xl, DWORD *xr)
{
	union aword  Xl, Xr ;

	Xl.dword = *xl ;
	Xr.dword = *xr ;

	Xl.dword ^= PArray [0];
	ROUND (Xr, Xl, 1) ;  ROUND (Xl, Xr, 2) ;
	ROUND (Xr, Xl, 3) ;  ROUND (Xl, Xr, 4) ;
	ROUND (Xr, Xl, 5) ;  ROUND (Xl, Xr, 6) ;
	ROUND (Xr, Xl, 7) ;  ROUND (Xl, Xr, 8) ;
	ROUND (Xr, Xl, 9) ;  ROUND (Xl, Xr, 10) ;
	ROUND (Xr, Xl, 11) ; ROUND (Xl, Xr, 12) ;
	ROUND (Xr, Xl, 13) ; ROUND (Xl, Xr, 14) ;
	ROUND (Xr, Xl, 15) ; ROUND (Xl, Xr, 16) ;
	Xr.dword ^= PArray [17] ;

	*xr = Xl.dword ;
	*xl = Xr.dword ;
}

	// the low level (private) decryption function
void BlowFish::Blowfish_decipher (DWORD *xl, DWORD *xr)
{
   union aword  Xl ;
   union aword  Xr ;

   Xl.dword = *xl ;
   Xr.dword = *xr ;

   Xl.dword ^= PArray [17] ;
   ROUND (Xr, Xl, 16) ;  ROUND (Xl, Xr, 15) ;
   ROUND (Xr, Xl, 14) ;  ROUND (Xl, Xr, 13) ;
   ROUND (Xr, Xl, 12) ;  ROUND (Xl, Xr, 11) ;
   ROUND (Xr, Xl, 10) ;  ROUND (Xl, Xr, 9) ;
   ROUND (Xr, Xl, 8) ;   ROUND (Xl, Xr, 7) ;
   ROUND (Xr, Xl, 6) ;   ROUND (Xl, Xr, 5) ;
   ROUND (Xr, Xl, 4) ;   ROUND (Xl, Xr, 3) ;
   ROUND (Xr, Xl, 2) ;   ROUND (Xl, Xr, 1) ;
   Xr.dword ^= PArray[0];

   *xl = Xr.dword;
   *xr = Xl.dword;
}


	// constructs the enctryption sieve
void BlowFish::initialize (BYTE key[], int32_t keybytes)
{
	int  		i, j ;
	DWORD  		 datal, datar ;


	// first fill arrays from data tables
	for (i = 0 ; i < 18 ; i++)
		PArray [i] = bf_P [i] ;

	for (i = 0 ; i < 4 ; i++)
	{
	 	for (j = 0 ; j < 256 ; j++)
	 		SBoxes [i][j] = bf_S [i][j] ;
	}

  int32_t v12; // eax@6
  int32_t v13; // ecx@6
  int32_t v14; // eax@8
  int32_t v15; // edx@8
  int32_t v16; // edx@8
  int32_t v17; // eax@10
  int32_t v18; // ecx@10
  int32_t v19; // ecx@10
  int32_t v20; // edx@12
  int32_t v21; // edx@12



  int32_t v10 = keybytes;
  uintptr_t v9 = (uintptr_t)key;
  int32_t v8 = 0;
  int32_t v11 = 0;
  do {
    v13 = (char)(*(BYTE *)(v8 + v9));
    v12 = v8 + 1;
    if ( v12 >= v10 )
      v12 = 0;
    v16 = (char)*(BYTE *)(v12 + v9);
    v14 = v12 + 1;
    v15 = (v13 << 8) | v16;
    if ( v14 >= v10 )
      v14 = 0;
    v19 = (char)*(BYTE *)(v14 + v9);
    v17 = v14 + 1;
    v18 = (v15 << 8) | v19;
    if ( v17 >= v10 )
      v17 = 0;
    v21 = (char)*(BYTE *)(v17 + v9);
    v8 = v17 + 1;
    v20 = (v18 << 8) | v21;
    if ( v8 >= v10 )
      v8 = 0;
    *((DWORD *)PArray + v11++) ^= v20;
  } while ( v11 < 18 );



	datal = 0 ;
	datar = 0 ;

	for (i = 0 ; i < NPASS + 2 ; i += 2)
	{
		Blowfish_encipher (&datal, &datar) ;
		PArray [i] = datal ;
		PArray [i + 1] = datar ;
	}

	for (i = 0 ; i < 4 ; ++i)
	{
		for (j = 0 ; j < 256 ; j += 2)
		{
		  Blowfish_encipher (&datal, &datar) ;
		  SBoxes [i][j] = datal ;
		  SBoxes [i][j + 1] = datar ;
		}
	}
}

	// get output length, which must be even MOD 8
DWORD BlowFish::GetOutputLength (DWORD lInputLong)
{
	DWORD 	lVal ;

	lVal = lInputLong % 8 ;	// find out if uneven number of bytes at the end
	if (lVal != 0)
		return lInputLong + 8 - lVal ;
	else
		return lInputLong ;
}

	// Encode pIntput into pOutput.  Input length in lSize.  Returned value
	// is length of output which will be even MOD 8 bytes.  Input buffer and
	// output buffer can be the same, but be sure buffer length is even MOD 8.
DWORD BlowFish::Encode (BYTE * pInput, BYTE * pOutput, DWORD lSize)
{
	DWORD 	lCount, lOutSize, lGoodBytes ;
	BYTE	*pi, *po ;
	int		i, j ;
	int		SameDest = (pInput == pOutput ? 1 : 0) ;

	lOutSize = GetOutputLength (lSize) ;
	for (lCount = 0 ; lCount < lOutSize ; lCount += 8)
	{
		if (SameDest)	// if encoded data is being written into input buffer
		{
		 	if (lCount < lSize - 7)	// if not dealing with uneven bytes at end
		 	{
		 	 	Blowfish_encipher ((DWORD *) pInput,
		 	 		(DWORD *) (pInput + 4)) ;
		 	}
		 	else		// pad end of data with null bytes to complete encryption
		 	{
				po = pInput + lSize ;	// point at byte past the end of actual data
				j = (int) (lOutSize - lSize) ;	// number of bytes to set to null
				for (i = 0 ; i < j ; i++)
					*po++ = 0 ;
		 	 	Blowfish_encipher ((DWORD *) pInput,
		 	 		(DWORD *) (pInput + 4)) ;
		 	}
		 	pInput += 8 ;
		}
		else 			// output buffer not equal to input buffer, so must copy
		{               // input to output buffer prior to encrypting
		 	if (lCount < lSize - 7)	// if not dealing with uneven bytes at end
		 	{
		 		pi = pInput ;
		 		po = pOutput ;
		 		for (i = 0 ; i < 8 ; i++)
// copy bytes to output
		 			*po++ = *pi++ ;
		 	 	Blowfish_encipher ((DWORD *) pOutput,	// now encrypt them
		 	 		(DWORD *) (pOutput + 4)) ;
		 	}
		 	else		// pad end of data with null bytes to complete encryption
		 	{
		 		lGoodBytes = lSize - lCount ;	// number of remaining data bytes
		 		po = pOutput ;
		 		for (i = 0 ; i < (int) lGoodBytes ; i++)
		 			*po++ = *pInput++ ;
		 		for (j = i ; j < 8 ; j++)
		 			*po++ = 0 ;
		 	 	Blowfish_encipher ((DWORD *) pOutput,
		 	 		(DWORD *) (pOutput + 4)) ;
		 	}
		 	pInput += 8 ;
		 	pOutput += 8 ;
		}
	}
	return lOutSize ;
 }

	// Decode pIntput into pOutput.  Input length in lSize.  Input buffer and
	// output buffer can be the same, but be sure buffer length is even MOD 8.
void BlowFish::Decode (BYTE * pInput, BYTE * pOutput, DWORD lSize)
{
	DWORD 	lCount ;
	BYTE	*pi, *po ;
	int		i ;
	int		SameDest = (pInput == pOutput ? 1 : 0) ;

	for (lCount = 0 ; lCount < lSize ; lCount += 8)
	{
		if (SameDest)	// if encoded data is being written into input buffer
		{
	 	 	Blowfish_decipher ((DWORD *) pInput,
	 	 		(DWORD *) (pInput + 4)) ;
		 	pInput += 8 ;
		}
		else 			// output buffer not equal to input buffer
		{               // so copy input to output before decoding
	 		pi = pInput ;
	 		po = pOutput ;
	 		for (i = 0 ; i < 8 ; i++)
	 			*po++ = *pi++ ;
	 	 	Blowfish_decipher ((DWORD *) pOutput,
	 	 		(DWORD *) (pOutput + 4)) ;
		 	pInput += 8 ;
		 	pOutput += 8 ;
		}
	}
}

