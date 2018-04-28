#pragma once

#include <vector>
#include <iostream>

#include "RsUtil.h"
#include "Decoder.h"
#include "Encoder.h"

#define READ_MODE 1
#define WRITE_MODE 2

template <typename T>
class OpHandler : protected Decoder, protected Encoder
{
  private:
    RsUtil::RsByte mode = READ_MODE;

    std::istream* p_indexIStream;
    std::istream* p_dataIStream;

    std::ostream* p_indexOStream;
    std::ostream* p_dataOStream;

    bool validateStreams()
    {
      if(this->mode == READ_MODE)
        if(this->p_indexIStream == nullptr || this->p_dataIStream == nullptr)
          return false;

      if(this->mode == WRITE_MODE)
        if(this->p_indexOStream == nullptr || this->p_dataOStream == nullptr)
          return false;


      return true;
    }

  protected:
    virtual void handle(RsUtil::RsByte, T&) = 0; 

    template <typename D>
      void ReadWrite(D& data)
      {
        if(!this->validateStreams())
          return;

        if(this->mode == READ_MODE)
          this->ReadSome<D>(data, *(this->p_dataIStream));

        if(this->mode == WRITE_MODE)
          this->ReadSome<D>(data, *(this->p_dataIStream));
      }

    void ReadWriteString(std::string& str)
    {
        if(!this->validateStreams())
          return;

        if(this->mode == READ_MODE)
          this->ReadString(str,*(this->p_dataIStream));

        if(this->mode == WRITE_MODE)
          this->WriteString(str,*(this->p_dataOStream));
    }

  public:
    void SetInputStreams(std::istream& indexStream, std::istream& dataStream)
    {
      this->p_indexIStream = indexStream;
      this->p_dataIStream = dataStream;
    }

    void SetOutputStreams(std::ostream& indexStream, std::ostream& dataStream)
    {
      this->p_indexOStream = indexStream;
      this->p_dataOStream = dataStream;
    }

    void Read(std::vector<T>& r_elements)
    {
      this->handle(0, r_elements.front());
    }
    void Write(std::vector<T>& r_elements);
};
