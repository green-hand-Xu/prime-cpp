#include <iostream>


static inline uint8_t pack_left_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    // std::cout<<"value = "<<(int)value<<" shift = "<<(int)shift<<" mask = "<<(int)mask<<std::endl;
    return static_cast<uint8_t>(static_cast<uint8_t>(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u32(
    uint32_t value,
    uint8_t shift,
    uint8_t mask)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(value << shift) & mask);
}

static inline uint8_t pack_left_shift_u64(
    uint64_t value,
    uint8_t shift,
    uint8_t mask)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(value << shift) & mask);
}

static inline uint8_t pack_right_shift_u8(
    uint8_t value,
    uint8_t shift,
    uint8_t mask)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(value >> shift) & mask);
}

static inline uint8_t pack_right_shift_u16(
    uint16_t value,
    uint8_t shift,
    uint8_t mask)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(value >> shift) & mask);
}

static inline uint8_t pack_right_shift_u32(
    uint32_t value,
    uint8_t shift,
    uint8_t mask)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(value >> shift) & mask);
}

static inline uint8_t pack_right_shift_u64(
    uint64_t value,
    uint8_t shift,
    uint8_t mask)
{
    return static_cast<uint8_t>(static_cast<uint8_t>(value >> shift) & mask);
}
