#pragma once

#include <cstddef>

namespace RsUtil
{
  typedef uint8_t RsByte;
  typedef uint16_t RsShort;
  typedef uint32_t RsInt;
  typedef uint64_t RsLong;

  static constexpr RsByte StringTerminator = 0x0A;

  inline bool IsBigEndian()
  {
    static bool BigEndian{false};
    return BigEndian;
  }

  template <typename T>
    void SwapEndian(T& data)
    {

    }

  template <typename T>
    bool FixEndian(T& data)
    {
      if(!IsBigEndian() && sizeof(T) > 1)
      {
        SwapEndian<T>(data);
        return true;
      }

      return false;
    }
}
