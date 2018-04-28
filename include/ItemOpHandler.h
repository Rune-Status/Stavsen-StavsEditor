#pragma once

#include "ItemConfig.h"
#include "OpHandler.h"

class ItemOpHandler : public OpHandler<ItemConfig> 
{
  protected:
    virtual void handle(RsUtil::RsByte op, ItemConfig& item) override {} //Test 
};
