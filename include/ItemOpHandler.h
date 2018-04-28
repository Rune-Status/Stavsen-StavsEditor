#pragma once

#include "ItemConfig.h"
#include "OpHandler.h"

class ItemOpHandler : public OpHandler<ItemConfig> //Test code: should be ItemConfig
{
  protected:
    virtual void handle(RsUtil::RsByte op, ItemConfig item) override {} //Test code; Should be ItemConfig rather than RsConfig
};
