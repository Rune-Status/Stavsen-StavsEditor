#include <iostream>

#include "ItemOpHandler.h"
#include "ItemConfig.h"
#include "ConfigManager.h"

int main()
{
  ConfigManager<ItemOpHandler, ItemConfig> ItemManager;

  ItemManager.Open("./bin/obj.idx","./bin/obj.dat");

  //ItemManager.LoadConfigs();


  return 0;
}
