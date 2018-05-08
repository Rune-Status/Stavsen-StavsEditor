#include "ArchiveManager/Config/Decoder.h"


void Decoder::ReadString(std::string& str, std::istream& r_istream)
{
  RsUtil::RsByte character = 0;

  str.clear();

  this->ReadSome<RsUtil::RsByte>(character, r_istream);

  while(character != RsUtil::StringTerminator)
  {
    str.push_back(character);
    this->ReadSome<RsUtil::RsByte>(character, r_istream);
  }

}

