#pragma once

#include "OpHandler.h"

class ItemOpHandler : public OpHandler<RsConfig> //Test code: should be ItemConfig
{
  protected:
    virtual void handle(RsUtil::RsByte op, RsConfig item) override {} //Test code; Should be ItemConfig rather than RsConfig
};
