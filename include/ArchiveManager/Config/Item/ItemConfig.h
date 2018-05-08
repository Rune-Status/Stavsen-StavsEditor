#pragma once

#include <string>
#include <vector>

#include "../RsUtil.h"
#include "../RsConfig.h"

/*
   TODO(Stavsen): Change member types to their actual 
   types in the cache.
 */
using namespace RsUtil;
struct ItemConfig : public RsConfig
{
  std::string name = std::string("undefined");
  RsShort modelID = 0;
  RsInt value = 1;
  std::string description;
  bool membersObject = false;
  RsShort certTemplateID = -1;
  std::string actions[5];
  std::string groundActions[5];
  RsShort certID = -1;
  bool isMembers = true;
  RsByte ambience = 0;
  RsByte contrast = 0;
  RsShort modelSizeX = 128;
  RsShort modelSizeY = 128;
  RsShort modelSizeZ = 128;
  bool stackable = false;
  RsShort stackIDs[10];
  RsShort stackAmounts[10];
  RsShort modelInvZoom = 2000;
  RsShort modelInvRotationX = 0;
  RsShort modelInvRotationY = 0;
  RsShort modelInvPosOffsetX = 0;
  RsShort modelInvPosOffsetY = 0;
  RsByte team = 0;
  RsShort diagonalRotation = 0;
  RsByte maleYOffset = 0;
  RsByte femaleYOffset = 0;
  RsShort maleWornModelID = -1;
  RsShort femaleWornModelID = -1;
  RsShort femaleEmblem = -1;
  RsShort maleEmblem = -1;
  RsShort femaleArmsID = -1;
  RsShort maleArmsID = -1;
  RsShort maleDialog = -1;
  RsShort femaleDialog = -1;
  RsShort maleDialogHat = -1;
  RsShort femaleDialogHat = -1;
  RsShort lendID, lentItemID;
  std::vector<RsShort> modifiedModelColors;
  std::vector<RsShort> originalModelColors;
  RsShort dummy;
};
