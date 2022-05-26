#ifndef __CACHE_H__
#define __CACHE_H__
#include <unordered_map>
#include <string>
#include <vector>
using std::string;
using std::unordered_map;
namespace CACHE
{
    // key: strQuery val: strQueryResult
    using MapCache = std::unordered_map<string, string>;

    class Cache
    {
    public:
        // Cache();
        Cache(const int &threadNum, const string &filename);
        void initCache(); //初始化cache

        void setCacheResult(string strQuery, string strResult); // 查询结束后将查询结果添加到cache
        string getCacheResult(string strQuery);

        static string getCacheResult(string strQuery, int idx); // 根据strQuery从cache中查询结果
        static void setCacheResult(string strQuery, string strResult, int idx);
        static void saveCacheToFile(MapCache allCache);
        static void updataCacheFile();

        // static MapCache getCacheList() { return _sCacheList }
    private:
        MapCache _umapCache;
        static string _filename;
        static std::vector<MapCache> _sCacheList; // 一个线程一个cache
    };

} // end CACHE
#endif