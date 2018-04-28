#include <iostream>

#include "ItemOpHandler.h"
#include "ItemConfig.h"
#include "ConfigManager.h"

int main()
{
  ConfigManager<ItemOpHandler, ItemConfig> ItemManager;

  if(ItemManager.Open("./bin/obj.idx","./bin/obj.dat"))
    if(ItemManager.LoadConfigs())
      if(ItemManager.Save("./bin/obj_out.idx","./bin/obj_out.dat"))
        std::cout << "Success\n";

  return 0;
}
