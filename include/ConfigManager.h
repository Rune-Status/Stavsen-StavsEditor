#pragma once

#include <type_traits>
#include <fstream>
#include <string>
#include <vector>

#include "RsUtil.h"
#include "Decoder.h"
#include "Encoder.h"
#include "RsConfig.h"
#include "OpHandler.h"

template <typename TOpHandler, typename TConfig>
class ConfigManager
{
  static_assert(std::is_base_of<OpHandler<TConfig>, TOpHandler>::value, 
      "TConfig IS NOT CHILD OF OpHandler<TConfig>!");

  static_assert(std::is_base_of<RsConfig, TConfig>::value, 
      "TConfig IS NOT CHILD OF RsConfig!");

  private:
  TOpHandler opHandler;

  std::vector<TConfig> configs;
  RsUtil::RsShort numConfigs;

  std::ifstream indexIFStream;
  std::ifstream dataIFStream;

  std::ofstream indexOFStream;
  std::ofstream dataOFStream;


  bool init()
  {
    //Read number of configs in file && make sure idx & dat match
    RsUtil::RsShort numConfigs_index;
    RsUtil::RsShort numConfigs_data;

    this->indexIFStream.read(reinterpret_cast<char*>(&numConfigs_index),2);
    this->dataIFStream.read(reinterpret_cast<char*>(&numConfigs_data),2);

    if(numConfigs_index == numConfigs_data)
    {
      RsUtil::FixEndian(numConfigs_index);
      this->numConfigs = numConfigs_index;
    }
    else
    {
      //TODO(Stavsen): Logger::Error
      return false;
    }

    //Resize vector
    this->configs.resize(this->numConfigs);

    return true;
  }

  public:
  ~ConfigManager()
  {
    if(this->indexIFStream.is_open())
      this->indexIFStream.close();

    if(this->dataIFStream.is_open())
      this->dataIFStream.close();

    if(this->indexOFStream.is_open())
      this->indexOFStream.close();

    if(this->dataOFStream.is_open())
      this->dataOFStream.close();
  }

  bool Open(std::string indexFilepath, std::string dataFilepath)
  {
    this->indexIFStream.open(indexFilepath);
    this->dataIFStream.open(dataFilepath);

    if(!this->indexIFStream.good() || !this->dataIFStream.good())
      return false;

    return this->init();
  }

  bool LoadConfigs()
  {
    if(!this->indexIFStream.good() || !this->dataIFStream.good())
      return false;

    this->opHandler.SetInputStreams(&(this->indexIFStream), &(this->dataIFStream));
    return this->opHandler.Read(this->configs);
  }

  bool Save(std::string indexOutputFile, std::string dataOutputFile)
  {
    this->indexOFStream.open(indexOutputFile);
    this->dataOFStream.open(dataOutputFile);

    if(!this->indexOFStream.good() || !this->dataOFStream.good())
      return false;

    this->opHandler.SetOutputStreams(&(this->indexOFStream), 
                                     &(this->dataOFStream));

    bool ret = this->opHandler.Write(this->configs);

    this->indexOFStream.close();
    this->dataOFStream.close();
    return ret;
  }
};

