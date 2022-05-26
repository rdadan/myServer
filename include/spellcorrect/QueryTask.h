
#ifndef __QueryTask_H__
#define __QueryTask_H__
#include "../threadpool/ThreadPool.h"
#include "../tcp/TcpConnection.h"
#include "EditDistance.h"
#include "../../include/Cache/Cache.h"

#include <string>
#include <set>
using reactor::spTcpConnPtr;
// using namespace reactor;
using std::set;
using std::string;
namespace SPELLCORRECT
{

    class QueryTask : public THREADPOOL::Task
    {
    public:
        QueryTask(string strQuery, spTcpConnPtr connPtr);
        void process() override;

    private:
        string getRuesltFromIndexTable();
        void sendRueslt();
        size_t getQueRueslt(set<int> &iset);

    private:
        string _strQuery;  // 要查询的字符
        string _strResult; // 排序且拼接好的

        spTcpConnPtr _connPtr;
        using QueResult = priority_queue<MyResult, vector<MyResult>, MyCompare>;
        QueResult _queResult; // 排序的优先队列

        // static CACHE::Cache _sCache; // 所有线程共享一个cache
    };
    // CACHE::Cache _sCache;
} // space spellcorrct
#endif