#pragma once

#include "SqPack.h"

#include <unordered_map>

#include <filesystem>

namespace xiv::dat
{

  struct IndexBlockRecord;

  class Index :
    public SqPack
  {
  public:
    // Full path to the index file
    Index( const std::filesystem::path& i_path );

    virtual ~Index();

    // An entry in the hash table, representing a file in a given dat
    struct HashTableEntry
    {
      uint32_t datNum;
      uint32_t dirHash;
      uint32_t filenameHash;
      uint32_t datOffset;
    };

    // HashTable has dir hashes -> filename hashes -> HashTableEntry
    using DirHashTable = std::unordered_map< uint32_t, HashTableEntry >;
    using HashTable = std::unordered_map< uint32_t, DirHashTable >;

    // Get the number of dat files the index is linked to
    uint32_t getDatCount() const;

    bool doesFileExist( uint32_t dir_hash, uint32_t filename_hash ) const;

    bool doesDirExist( uint32_t dir_hash ) const;

    // Returns the whole HashTable
    const HashTable& getHashTable() const;

    // Returns the hash table for a specific dir
    const DirHashTable& getDirHashTable( uint32_t dir_hash ) const;

    // Returns the HashTableEntry for a given file given its hashes
    const HashTableEntry& getHashTableEntry( uint32_t dir_hash, uint32_t filename_hash ) const;

  protected:
    // Checks that the block is valid with regards to its hash
    void isIndexBlockValid( const IndexBlockRecord& i_index_block_record );

    uint32_t m_datCount;
    HashTable m_hashTable;
  };
    
}// namespace xiv::dat
