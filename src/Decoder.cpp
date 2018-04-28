#include "Decoder.h"


void Decoder::ReadString(std::string& str, std::istream& r_istream)
{
  RsUtil::RsByte character = 0;

  while(character != RsUtil::StringTerminator)
  {
    this->ReadSome<RsUtil::RsByte>(character, r_istream);
    str.push_back(character);
  }

}

