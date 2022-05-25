#ifndef __CACHE_H__
#define __CACHE_H__
#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;
namespace CACHE
{

    class Cache
    {
    public:
        Cache();
        void setCacheResult(string strQuery, string strResult); // 查询结束后将查询结果添加到cache
        string getCacheResult(string strQuery);          // 根据strQuery从cache中查询结果
        void initCache(const string cachefile);                 //初始化cache
        void saveCache();

    private:
        std::unordered_map<string, string> _umapCache; // key: strQuery val: strQueryResult
        string _filename = "/mnt/d/MyProjects/linuxOS/myspellcorrection/file/cache.dat";
    };
} // end CACHE
#endif