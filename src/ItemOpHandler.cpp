#include "ArchiveManager/Config/Item/ItemOpHandler.h"

using namespace RsUtil;

/*
 * TODO(Stavsen): Maybe document what each opcode indicates better.
 */
bool ItemOpHandler::handle(RsUtil::RsByte op, ItemConfig& item)
{
  switch(op)
  {
     case 0:
     {
       //Indicates end of item 
       break;
     }
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
     case 40:
     {
       auto read = [&]()
       {
         RsByte numColors;
         this->Read<RsByte>(numColors);

         item.originalModelColors.resize(numColors);
         item.modifiedModelColors.resize(numColors);

         for(RsByte i = 0; i < numColors; i++)
         {
           this->Read<RsShort>(item.originalModelColors[i]);
           this->Read<RsShort>(item.modifiedModelColors[i]);
         }

       };

       auto write = [&]()
       {
         RsByte numColors = item.originalModelColors.size();
         this->Write<RsByte>(numColors);

         for(RsByte i = 0; i < numColors; i++)
         {
           this->Write<RsShort>(item.originalModelColors[i]);
           this->Write<RsShort>(item.modifiedModelColors[i]);
         }

       };

       this->ReadWrite(read,write);
       break;
     }
     case 78:
     {
       this->ReadWrite<RsShort>(item.maleEmblem);
       break;
     }
     case 79:
     {
       this->ReadWrite<RsShort>(item.femaleEmblem);
       break;
     }
     case 90:
     {
       this->ReadWrite<RsShort>(item.maleDialog);
       break;
     }
     case 91:
     {
       this->ReadWrite<RsShort>(item.femaleDialog);
       break;
     }
     case 92:
     {
       this->ReadWrite<RsShort>(item.maleDialogHat);
       break;
     }
     case 93:
     {
       this->ReadWrite<RsShort>(item.femaleDialogHat);
       break;
     }
     case 95:
     {
       this->ReadWrite<RsShort>(item.diagonalRotation);
       break;
     }
     case 97:
     {
       this->ReadWrite<RsShort>(item.certID);
       break;
     }
     case 98:
     {
       this->ReadWrite<RsShort>(item.certTemplateID);
       break;
     }
     case 100:
     case 101:
     case 102:
     case 103:
     case 104:
     case 105:
     case 106:
     case 107:
     case 108:
     case 109:
     {
       this->ReadWrite<RsShort>(item.stackIDs[op-100]);
       this->ReadWrite<RsShort>(item.stackAmounts[op-100]);
       break;
     }
     case 110:
     {
       this->ReadWrite<RsShort>(item.modelSizeX);
       break;
     }
     case 111:
     {
       this->ReadWrite<RsShort>(item.modelSizeY);
       break;
     }
     case 112:
     {
       this->ReadWrite<RsShort>(item.modelSizeZ);
       break;
     }
     case 113:
     {
       //May be a signed byte, not sure
       this->ReadWrite<RsByte>(item.ambience);
       break;
     }
     case 114:
     {
       //This may also be incorrect
       this->ReadWrite<RsByte>(item.contrast);
       break;
     }
     case 115:
     {
       this->ReadWrite<RsByte>(item.team);
       break;
     }
     case 116:
     {
       this->ReadWrite<RsShort>(item.lendID);
       break;
     }
     case 117:
     {
       this->ReadWrite<RsShort>(item.lentItemID);
       break;
     }
     default:
     {
       std::cout << "UNKNOWN OPCODE: " << std::dec << unsigned(op) << '\n';
       item.Faulty = true;
       return false;
     }
  }
  return true;
}

