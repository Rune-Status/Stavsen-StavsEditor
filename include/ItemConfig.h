#pragma once

#include <string>

#include "RsUtil.h"
#include "RsConfig.h"

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
  int certTemplateID = -1;
  std::string actions[5];
  std::string groundActions[5];
  int certID = -1;
  bool isMembers = true;
  int lightModifier = 0;
  int shadowModifier = 0;
  int modelSizeX = 128;
  int modelSizeY = 128;
  int modelSizeZ = 128;
  bool stackable = false;
  int stackIDs[10];
  int stackAmounts[10];
  RsShort modelInvZoom = 2000;
  RsShort modelInvRotationX = 0;
  RsShort modelInvRotationY = 0;
  RsShort modelInvPosOffsetX = 0;
  RsShort modelInvPosOffsetY = 0;
  int team = 0;
  int diagonalRotation = 0;
  RsByte maleYOffset = 0;
  RsByte femaleYOffset = 0;
  RsShort maleWornModelID = -1;
  RsShort femaleWornModelID = -1;
  int femaleEmblem = -1;
  int maleEmblem = -1;
  RsShort femaleArmsID = -1;
  RsShort maleArmsID = -1;
  int maleDialog = -1;
  int femaleDialog = -1;
  int maleDialogHat = -1;
  int femaleDialogHat = -1;
  int lendID, lentItemID;
  int modifiedModelColors[256];
  int originalModelColors[256];
  RsShort dummy;
};
