#pragma once

#include <string>

#include "RsConfig.h"

/*
   TODO(Stavsen): Change member types to their actual 
   types in the cache.
 */
struct ItemConfig : RsConfig
{
  std::string name = std::string("undefined");
  int modelID = 0;
  int value = 1;
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
  int modelInvZoom = 2000;
  int modelInvRotationX = 0;
  int modelInvRotationY = 0;
  int modelInvPosOffsetX = 0;
  int modelInvPosOffsetY = 0;
  int team = 0;
  int diagonalRotation = 0;
  std::uint8_t maleYOffset = 0;
  std::uint8_t femaleYOffset = 0;
  int maleWornModelID = -1;
  int femaleWornModelID = -1;
  int femaleEmblem = -1;
  int maleEmblem = -1;
  int femaleArmsID = -1;
  int maleArmsID = -1;
  int maleDialog = -1;
  int femaleDialog = -1;
  int maleDialogHat = -1;
  int femaleDialogHat = -1;
  int lendID, lentItemID;
  int modifiedModelColors[256];
  int originalModelColors[256];
};
