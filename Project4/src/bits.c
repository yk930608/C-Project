#include "bits.h"
#include "cache.h"

int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  //
  int setBits = cache->set_bits;
  int blockBits = cache->block_bits;
  int LineBits = 32- setBits - blockBits;
  int toReturn= (address<<LineBits)>>(blockBits+LineBits);
  return toReturn;
}

int get_line(Cache *cache, address_type address) {
  // TODO:
  // Extract the tag bits from a 32-bit address.
  //
  int setBits = cache->set_bits;
  int blockBits = cache->block_bits;
  int LineBits = 32- setBits - blockBits;
  int toReturn= address>>(blockBits+setBits);
  return toReturn;
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  //
  int setBits = cache->set_bits;
  int blockBits = cache->block_bits;
  int LineBits = 32- setBits - blockBits;
  int toReturn= (address<<(LineBits+setBits))>>(LineBits+setBits);
  return toReturn;
}
