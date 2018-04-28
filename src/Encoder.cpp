#include "Encoder.h"

void Encoder::WriteString(std::string& str, std::ostream& r_ostream)
{
  for(size_t i = 0; i < str.size(); i++)
    this->Write<RsUtil::RsByte>(str[i],r_ostream);

  this->Write<RsUtil::RsByte>(RsUtil::StringTerminator,r_ostream);
}

