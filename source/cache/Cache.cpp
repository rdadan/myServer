#include "../../include/Cache/Cache.h"
#include <iostream>
#include <fstream>

namespace CACHE
{
    Cache::Cache() // const string _filename
    {
        initCache(_filename);
    }

    void Cache::initCache(const string _filename)
    {
        std::ifstream ifs(_filename.c_str());
        if (!ifs.good())
        {
            std::cout << "open cache file error!" << std::endl;
            return;
        }
        string key, value, tmp;
        ifs >> key;
        while (ifs >> tmp)
        {
            value += tmp + " ";
        }
        _umapCache.insert(std::make_pair(key, value));
    }

    void Cache::setCacheResult(string strQuery, string strResult)
    {
        _umapCache[strQuery] = strResult;
    }

    string Cache::getCacheResult(string strQuery)
    {
        return _umapCache[strQuery];
    }

    void Cache::saveCache()
    {

        std::ofstream ofs(_filename.c_str());

        for (auto it = _umapCache.begin(); it != _umapCache.end(); it++)
        {
            ofs << it->first << " " << it->second << std::endl;
        }
    }

} // CACHE
