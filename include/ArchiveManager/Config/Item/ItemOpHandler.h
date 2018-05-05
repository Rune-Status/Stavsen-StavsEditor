#pragma once

#include <cstdlib>

#include "ItemConfig.h"
#include "../OpHandler.h"

class ItemOpHandler : public OpHandler<ItemConfig> 
{
  protected:
    virtual bool handle(RsUtil::RsByte op, ItemConfig& item) override;
};
