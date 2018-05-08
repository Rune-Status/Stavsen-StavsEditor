#pragma once

#include <vector>

#include "RsUtil.h"

struct RsConfig
{
  RsUtil::RsShort ID;
  RsUtil::RsInt Offset;
  RsUtil::RsShort Size;
  std::vector<RsUtil::RsByte> Opcodes;

  //set to true if an unknown opcode is discovered
  bool Faulty = false; 
};

