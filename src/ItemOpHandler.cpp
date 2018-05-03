#include "ItemOpHandler.h"

using namespace RsUtil;

void ItemOpHandler::handle(RsUtil::RsByte op, ItemConfig& item)
{
  switch(op)
  {
     case 1:
     {
       this->ReadWrite<RsShort>(item.modelID);
       break;
     }
     case 2:
     {
       this->ReadWriteString(item.name);
       break;
     }
     case 3:
     {
       this->ReadWriteString(item.description);
       break;
     }
     case 4:
     {
       this->ReadWrite<RsShort>(item.modelInvZoom);
       break;
     }
     case 5:
     {
       this->ReadWrite<RsShort>(item.modelInvRotationY);
       break;
     }
     case 6:
     {
       this->ReadWrite<RsShort>(item.modelInvRotationX);
       break;
     }
     case 7:
     {
       auto read = [&]()
       {
         RsShort value;
         this->Read<RsShort>(value);

         if(value > 32767)
           value -= 65536;

         item.modelInvPosOffsetX = value;
       };

       auto write= [&]()
       {
         this->Write<RsShort>(item.modelInvPosOffsetX);
       };


       this->ReadWrite(read, write);
       break;
     }
     case 8:
     {
       auto read = [&]()
       {
         RsShort value;
         this->Read<RsShort>(value);

         if(value > 32767)
           value -= 65536;

         item.modelInvPosOffsetY = value;
       };

       auto write= [&]()
       {
         this->Write<RsShort>(item.modelInvPosOffsetY);
       };


       this->ReadWrite(read, write);
       break;
     }
     case 10:
     {
       this->ReadWrite<RsShort>(item.dummy);
       break;
     }
     case 11:
     {
       item.stackable = true;
       break;
     }
     case 12:
     {
       this->ReadWrite<RsInt>(item.value);
       break;
     }
     case 16:
     {
       item.membersObject = true;
       break;
     }
     case 23:
     {
       this->ReadWrite<RsShort>(item.maleWornModelID);
       this->ReadWrite<RsByte>(item.maleYOffset);
       break;
     }
     case 24:
     {
       this->ReadWrite<RsShort>(item.maleArmsID);
       break;
     }
     case 25:
     {
       this->ReadWrite<RsShort>(item.femaleWornModelID);
       this->ReadWrite<RsByte>(item.femaleYOffset);
       break;
     }
     case 26:
     {
       this->ReadWrite<RsShort>(item.femaleArmsID);
       break;
     }
     case 30:
     case 31:
     case 32:
     case 33:
     case 34:
     {
       this->ReadWriteString(item.groundActions[op-30]);
       break;
     }
     case 35:
     case 36:
     case 37:
     case 38:
     case 39:
     {
       this->ReadWriteString(item.actions[op-35]);
       break;
     }
     default:
     {
       std::cout << "[" << item.name << "] UNKNOWN OPCODE\n";
     }
  }
}

