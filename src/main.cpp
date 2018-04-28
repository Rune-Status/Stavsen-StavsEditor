#include <iostream>

#include "ItemOpHandler.h"
#include "ItemConfig.h"
#include "ConfigManager.h"

int main()
{
  ConfigManager<ItemOpHandler, ItemConfig> c;

  return 0;
}
