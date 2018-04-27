#pragma once

#include "Decoder.h"
#include "Encoder.h"

#include "ItemOpHandler.h"

class ConfigManager
{
  private:
  public:
    ConfigManager()
    {
      ItemOpHandler Handler;

      std::vector<RsConfig> conf;
      conf.push_back(RsConfig{123});

      Handler.Read(conf);
    }
};

