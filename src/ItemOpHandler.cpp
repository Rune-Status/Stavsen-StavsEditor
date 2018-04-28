#include "ItemOpHandler.h"

void ItemOpHandler::handle(RsUtil::RsByte op, ItemConfig& item)
{
  std::cout << "handle\n";

  this->ReadWrite(
      []()
      {
        std::cout << "reading lambda\n";
      }, 

      []()
      {
        std::cout << "writing lambda\n";
      });
}

