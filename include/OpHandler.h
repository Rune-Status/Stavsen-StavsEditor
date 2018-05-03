#pragma once

#include <vector>
#include <iostream>
#include <functional>

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

    std::istream* p_indexIStream = nullptr;
    std::istream* p_dataIStream = nullptr;

    std::ostream* p_indexOStream = nullptr;
    std::ostream* p_dataOStream = nullptr;

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
      void Read(D& data)
      {
        this->ReadSome<D>(data, *(this->p_dataIStream));
      }

    template <typename D>
      void Write(D& data)
      {
        this->WriteSome<D>(data, *(this->p_dataOStream));
      }

    template <typename D>
      void ReadWrite(D& data)
      {
        if(this->mode == READ_MODE)
          this->ReadSome<D>(data, *(this->p_dataIStream));

        if(this->mode == WRITE_MODE)
          this->WriteSome<D>(data, *(this->p_dataOStream));
      }

    void ReadWrite(std::function<void()> read, std::function<void()> write)
    {
      if(this->mode == READ_MODE)
        read();

      if(this->mode == WRITE_MODE)
        write();
    }

    void ReadWriteString(std::string& str)
    {
      if(this->mode == READ_MODE)
        this->ReadString(str,*(this->p_dataIStream));

      if(this->mode == WRITE_MODE)
        this->WriteString(str,*(this->p_dataOStream));
    }

  public:
    void SetInputStreams(std::istream& indexStream, std::istream& dataStream)
    {
      this->p_indexIStream = &indexStream;
      this->p_dataIStream = &dataStream;
    }

    void SetOutputStreams(std::ostream& indexStream, std::ostream& dataStream)
    {
      this->p_indexOStream = &indexStream;
      this->p_dataOStream = &dataStream;
    }

    bool Read(std::vector<T>& r_configs)
    {
      this->mode = READ_MODE;

      if(!this->validateStreams())
        return false;


      for(RsUtil::RsShort i = 0; i < 10;i++)
      {
        //Set ID
        r_configs[i].ID = i;

        //Read Size from index stream
        this->ReadSome<RsUtil::RsShort>(r_configs[i].Size, *(this->p_indexIStream));

        /*
           New Offset = last offset + last size
           if i = 0 there is no last config
         */
        if(i != 0)
          r_configs[i].Offset = r_configs[i-1].Offset + r_configs[i-1].Size;
        else
          r_configs[i].Offset = 2; //First two bytes are the number of configs


        //Move to offset
        this->p_dataIStream->seekg(r_configs[i].Offset);


        //Read first opcode
        RsUtil::RsByte opCode;
        this->ReadSome<RsUtil::RsByte>(opCode, *(this->p_dataIStream));

        //handle opcode then read another untill opcode 0
        while(opCode != 0)
        {
          this->handle(opCode, r_configs[i]);
          this->ReadSome<RsUtil::RsByte>(opCode, *(this->p_dataIStream));
        }

        std::cout << r_configs[i].name << '\n';

      }

      return true;
    }
    bool Write(std::vector<T>& r_configs, bool sort=false)
    {
      this->mode = WRITE_MODE;

      if(!this->validateStreams())
        return false;

      return true;
    }
};
