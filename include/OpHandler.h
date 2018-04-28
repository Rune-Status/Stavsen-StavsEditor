#pragma once

#include <vector>
#include <iostream>

#include "RsUtil.h"

#define READ_MODE 1
#define WRITE_MODE 2

template <typename T>
class OpHandler 
{
  private:
    RsUtil::RsByte mode = READ_MODE;

    std::istream* p_indexIStream;
    std::istream* p_dataIStream;

    std::ostream* p_indexOStream;
    std::ostream* p_dataOStream;

  protected:
    virtual void handle(RsUtil::RsByte, T&) = 0; 

  public:
    void SetInputStream(std::istream& indexStream, std::istream& dataStream)
    {
      this->p_indexIStream = indexStream;
      this->p_dataIStream = dataStream;
    }

    void SetOutputStream(std::ostream& indexStream, std::ostream& dataStream)
    {
      this->p_indexOStream = indexStream;
      this->p_dataOStream = dataStream;
    }

    void Read(std::vector<T>& r_elements);
    void Write(std::vector<T>& r_elements);
};
