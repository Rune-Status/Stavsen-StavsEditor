#include <iostream>

#include <ArchiveManager/ArchiveManager.h>
#include <ArchiveManager/Config/ConfigManager.h>

int main()
{
  /*
     struct ArchiveFile
     {
     string name
     int size
     int offset
     int id
     headers....etc
     }

     ArchiveManager archive;
     archive.Open("main_file_cache.dat","main_file_cache.idx0");

     vector<ArchiveFile> archives = archive.ReadArchives();

     archive.SaveFile("./archives/"+archives[0].name, archives[0]);

*/

  std::cout << '\n' << '\n';

  ItemConfigManager ItemManager;
  std::cout << "-----------Reading Item Config-----------\n";

  if(ItemManager.Open("./bin/obj.idx","./bin/obj.dat"))
  {
    if(ItemManager.LoadConfigs())
    {
      std::cout << "Number of configs: " << ItemManager.GetConfigs().size() << std::endl;
      unsigned long int sizeTotal = 0;
      int faultyTotal = 0;

      for(ItemConfig item : ItemManager.GetConfigs())
      {
        sizeTotal += item.Size;

        if(item.Faulty)
          faultyTotal += 1;
      }

      std::cout << "Configs are taking up: " << sizeTotal+2 << " Bytes\n";
      std::cout << "Fault items found: " << faultyTotal << std::endl;
    }
  }

  return 0;
}
