#ifndef __CACHE_H__
#define __CACHE_H__
#include <unordered_map>
#include <string>
#include <vector>
using std::string;
using std::unordered_map;
namespace CACHE
{
    using MapCache = std::unordered_map<string, string>;

    class Cache
    {
    public:
        // Cache();
        Cache(const int &threadNum, const string &filename);
        void setCacheResult(string strQuery, string strResult); // 查询结束后将查询结果添加到cache
        string getCacheResult(string strQuery);
        static string getCacheResult(string strQuery, int idx); // 根据strQuery从cache中查询结果
        static void setCacheResult(string strQuery, string strResult, int idx);

        void initCache(); //初始化cache
        void saveCache();
        // static MapCache getCacheList() { return _sCacheList }

    private:
        MapCache _umapCache; // key: strQuery val: strQueryResult
        string _filename;
        static std::vector<MapCache> _sCacheList; // 一个线程一个cache
    };
} // end CACHE
#endif