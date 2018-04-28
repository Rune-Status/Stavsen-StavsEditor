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

      std::vector<ItemConfig> items;
      items.push_back(ItemConfig{});

      Handler.Read(items);
    }
};

