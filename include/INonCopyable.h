#pragma once

class INonCopyable
{
  private:
    INonCopyable() = delete;
    INonCopyable& operator=(const INonCopyable&) = delete;
    INonCopyable operator=(INonCopyable&&) = delete;
};
