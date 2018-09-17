#ifndef _BLOWFISH_H
#define _BLOWFISH_H
// blowfish.h     interface file for blowfish.cpp
// _THE BLOWFISH ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger

#define MAXKEYBYTES  56    // 448 bits max
#define NPASS           16    // SBox passes

#define DWORD    uint32_t
#define WORD      unsigned short
#define BYTE      uint8_t

class BlowFish
{
private:
  DWORD* PArray;
  DWORD    (* SBoxes)[256];

  void Blowfish_encipher( DWORD* xl, DWORD* xr );

  void Blowfish_decipher( DWORD* xl, DWORD* xr );

public:
  BlowFish();

  ~BlowFish();

  void initialize( BYTE key[], int32_t keybytes );

  DWORD GetOutputLength( DWORD lInputLong );

  DWORD Encode( BYTE* pInput, BYTE* pOutput, DWORD lSize );

  void Decode( BYTE* pInput, BYTE* pOutput, DWORD lSize );

};

// choose a byte order for your hardware
#define ORDER_DCBA  // chosing Intel in this case

#ifdef ORDER_DCBA    // DCBA - little endian - intel
union aword
{
  DWORD dword;
  BYTE byte[4];
  struct
  {
    uint32_t byte3:8;
    uint32_t byte2:8;
    uint32_t byte1:8;
    uint32_t byte0:8;
  } w;
};
#endif

#ifdef ORDER_ABCD    // ABCD - big endian - motorola
union aword {
  DWORD dword;
  BYTE byte [4];
  struct {
    uint32_t byte0:8;
    uint32_t byte1:8;
    uint32_t byte2:8;
    uint32_t byte3:8;
  } w;
};
#endif

#ifdef ORDER_BADC    // BADC - vax
union aword {
  DWORD dword;
  BYTE byte [4];
  struct {
    uint32_t byte1:8;
    uint32_t byte0:8;
    uint32_t byte3:8;
    uint32_t byte2:8;
  } w;
};
#endif
#endif