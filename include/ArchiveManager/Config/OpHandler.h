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
    virtual bool handle(RsUtil::RsByte, T&) = 0; 

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


      for(RsUtil::RsShort i = 0; i < r_configs.size();i++)
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
        {
          r_configs[i].Offset = (RsUtil::RsInt)r_configs[i-1].Offset + (RsUtil::RsInt)r_configs[i-1].Size;
        }
        else //First two bytes are the number of configs
          r_configs[i].Offset = RsUtil::RsInt(2); 

        //Move to offset in data stream
        this->p_dataIStream->seekg(r_configs[i].Offset);


        //Allocate opcode and set to non-zero
        RsUtil::RsByte opCode = 1;

        //loop over opcodes untill OP=0
        while(opCode != 0)
        {
          //Read opcode
          this->ReadSome<RsUtil::RsByte>(opCode, *(this->p_dataIStream));

          //Store opcode
          r_configs[i].Opcodes.push_back(opCode);

          
          //Handle opcode
          if(!this->handle(opCode, r_configs[i]))
          {
            std::cout << "Faulty item #" << std::dec << i << " [" 
                      << r_configs[i].name << "] at (0x" << std::hex
                      << this->p_dataIStream->tellg() << ")\n" << std::dec;

            //return false;
          }

        }

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
