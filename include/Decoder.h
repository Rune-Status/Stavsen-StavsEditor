#pragma once

#include <istream>
#include <string>

#include "RsUtil.h"

class Decoder
{
  public:
    template <typename T>
      void Read(T& data, std::istream& r_istream)
      {
        r_istream.read(reinterpret_cast<char*>(data), sizeof(T));

        RsUtil::FixEndian(data);
      }

    void ReadString(std::string& str, std::istream& r_istream);
};
