#pragma once

#include <type_traits>

#include "RsUtil.h"
#include "Decoder.h"
#include "Encoder.h"
#include "RsConfig.h"
#include "OpHandler.h"

template <typename TOpHandler, typename TConfig>
class ConfigManager
{
  static_assert(std::is_base_of<OpHandler<TConfig>, TOpHandler>::value, 
      "TConfig IS NOT CHILD OF RsConfig!");
  
  static_assert(std::is_base_of<RsConfig, TConfig>::value, 
      "TConfig IS NOT CHILD OF RsConfig!");

  private:
    RsUtil::RsShort NumElements;

  public:
    ConfigManager()
    {
      TOpHandler Handler;


      std::vector<TConfig> items;
      items.push_back(TConfig{});

      Handler.Read(items);
    }
};

