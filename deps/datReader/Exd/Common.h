#pragma once
namespace Component::Excel
{

  struct ExcelDataRowHeader
  {
    uint32_t dataSize;
    uint16_t rowCount;
  };

  enum Language : int32_t
  {
    LANGUAGE_ALL = 0x0,
    LANGUAGE_JP = 0x1,
    LANGUAGE_EN = 0x2,
    LANGUAGE_DE = 0x3,
    LANGUAGE_FR = 0x4,
    LANGUAGE_CH = 0x5,
    LANGUAGE_MAX = 0x6,
  };

  struct StringOffset
  {
    uint32_t m_offset;
  };

  typedef int32_t LinkList[12];

/*  struct LinkList::Holder
  {
    Common::Component::Excel::LinkList m_begin;
    Common::Component::Excel::LinkList m_end;
    uint32_t m_size;
  };*/

  struct ExcelEntryKey
  {
    uint32_t m_mainkey;
    uint16_t m_hash;
    uint16_t m_subkey_info[3];
  };

  typedef int32_t StringPOD[4];

  union ExcelCell
  {
    bool b;
    int8_t s8;
    uint8_t u8;
    int16_t s16;
    uint16_t u16;
    int32_t s32;
    uint32_t u32;
    int64_t s64;
    uint64_t u64;
    float f;
    StringPOD str_pod;
    StringPOD str_old;
    StringOffset str_new;
    StringPOD str;
    StringOffset str_ofs;
    int8_t *bin;
    uint8_t boolean0;
    uint8_t boolean1;
    uint8_t boolean2;
    uint8_t boolean3;
    uint8_t boolean4;
    uint8_t boolean5;
    uint8_t boolean6;
    uint8_t boolean7;
  };

  using ExdCell = ExcelCell;

  enum CELL_TYPE : uint32_t
  {
    TYPE_NONE = 0xFFFFFFFF,
    TYPE_STR = 0x0,
    TYPE_BOOL = 0x1,
    TYPE_S8 = 0x2,
    TYPE_U8 = 0x3,
    TYPE_S16 = 0x4,
    TYPE_U16 = 0x5,
    TYPE_S32 = 0x6,
    TYPE_U32 = 0x7,
    TYPE_F16 = 0x8,
    TYPE_FLOAT = 0x9,
    TYPE_S64 = 0xA,
    TYPE_U64 = 0xB,
    TYPE_BIN = 0xC,
    TYPE_BOOLEAN0 = 0x19,
    TYPE_BOOLEAN1 = 0x1A,
    TYPE_BOOLEAN2 = 0x1B,
    TYPE_BOOLEAN3 = 0x1C,
    TYPE_BOOLEAN4 = 0x1D,
    TYPE_BOOLEAN5 = 0x1E,
    TYPE_BOOLEAN6 = 0x1F,
    TYPE_BOOLEAN7 = 0x20,
    TYPE_MAX_4 = 0x21,
  };


}
