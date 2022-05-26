#include "../../include/Cache/Cache.h"
#include <iostream>
#include <fstream>

namespace CACHE
{
    std::vector<MapCache> Cache::_sCacheList;
    Cache::Cache(const int &threadNum, const string &filename)
        : _filename(filename)
    {
        std::cout << "Cache()" << std::endl;
        initCache();

        for (int idx = 0; idx < threadNum; idx++)
        {
            _sCacheList.push_back(_umapCache);
        }
    }

    void Cache::initCache()
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
    void Cache::setCacheResult(string strQuery, string strResult, int idx)
    {
        _sCacheList[idx][strQuery] = strResult;
    }

    string Cache::getCacheResult(string strQuery, int idx)
    {
        return _sCacheList[idx][strQuery];
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
