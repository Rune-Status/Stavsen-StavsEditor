#pragma once

#include <cstddef>
#include <cstdint>

namespace RsUtil
{
  typedef std::uint8_t RsByte;
  typedef std::uint16_t RsShort;
  typedef std::uint32_t RsInt;
  typedef std::uint64_t RsLong;

  static constexpr RsByte StringTerminator = 0x0A;

  inline bool IsBigEndian()
  {
    static bool BigEndian{false};
    return BigEndian;
  }

  template <typename T>
    void SwapEndian(T& r_data)
    {
      union
      {
        T data;
        RsByte bytes[sizeof(T)];
      }input, output;

      input.data = r_data;

     for(size_t i = 0; i < sizeof(T); i++) 
       output.bytes[i] = input.bytes[sizeof(T) - i - 1];

      r_data = output.data;
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
