#pragma once

#include <vector>

#include "RsUtil.h"

#define READ_MODE 1
#define WRITE_MODE 2

template <typename T>
class OpHandler 
{
  private:
    RsUtil::RsByte mode = READ_MODE;

  protected:
    /*
      TODO(Stavsen): Figure out whether to pass T as
                     reference, pointer or copy.

                     (references works but do we want to put everything on the stack? )

                     (pointers are problematic because then OpHandler wont be independant 
                      because we have to use the same kind of smartpointer as ConfigManager 
                      + im not sure if passing the vector by reference increases reference count )
    */
    virtual void handle(RsUtil::RsByte, T) = 0; 
  public:
    void Read(std::vector<T>& r_elements)
    {
      this->handle(3,r_elements.front());  //test code
    }

    void Write(std::vector<T>& r_elements);
};
