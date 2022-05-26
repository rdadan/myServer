#include "../../include/Cache/Cache.h"
#include <iostream>
#include <fstream>

namespace CACHE
{
    // ! 不要在头文件中定义，可能会出现重复定义的错误
    std::vector<MapCache> Cache::_sCacheList;
    string Cache::_filename;

    Cache::Cache(const int &threadNum, const string &filename)
    // : Cache::_filename(filename)
    {
        std::cout << "Cache()" << std::endl;
        _filename = filename;
        initCache();

        for (int idx = 0; idx < threadNum; idx++)
        {
            _sCacheList.push_back(_umapCache);
        }
    }

    void Cache::initCache()
    {
        std::ifstream ifs(Cache::_filename.c_str());
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
    void Cache::saveCacheToFile(MapCache allCache)
    {
        std::ofstream ofs(Cache::_filename.c_str());
        for (auto it = allCache.begin(); it != allCache.end(); it++)
        {
            ofs << it->first << "\t" << it->second << std::endl;
        }
    }

    void Cache::updataCacheFile()
    {
        std::cout << " >> updataCacheFile " << _sCacheList.size() << std::endl;
        // auto it1 = _sCacheList.begin();
        // auto it2 = ++it1;
        // // 将cache的都拷贝到第一个线程， 第一个拥有全部线程的cache
        // for (; it2 != _sCacheList.end(); ++it2)
        // {
        //     it1->insert(it2->begin(), it2->end());
        // }

        // it1 = _sCacheList.begin();
        // it2 = ++it1;
        // // 其他的线程再从第一个拷贝
        // for (; it2 != _sCacheList.end(); ++it2)
        // {
        //     it2->insert(it1->begin(), it1->end());
        // }
        for (int i = 1; i < _sCacheList.size(); i++)
        {
            _sCacheList[0].insert(_sCacheList[i].begin(), _sCacheList[i].end());
        }
        for (int i = 1; i < _sCacheList.size(); i++)
        {
            _sCacheList[i].insert(_sCacheList[0].begin(), _sCacheList[0].end());
        }
        // 保存到本地文件
        saveCacheToFile(_sCacheList[0]);
    }

} // CACHE
