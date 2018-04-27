#pragma once

#include <ostream>
#include <string>

#include "RsUtil.h"

class Encoder
{
  public:
    template <typename T>
      void Write(T data, std::ostream& r_ostream)
      {
        RsUtil::FixEndian(data);

        r_ostream.write(reinterpret_cast<char*>(data), sizeof(T));
      }

    void WriteString(std::string str, std::ostream& r_ostream);
};
