
#ifndef __QueryTask_H__
#define __QueryTask_H__
#include "../threadpool/ThreadPool.h"
#include "../tcp/TcpConnection.h"
#include "EditDistance.h"

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
        void getRuesltFromIndexTable();
        void sendRueslt();
        size_t getQueRueslt(set<int> &iset);

    private:
        string _strQuery;
        spTcpConnPtr _connPtr;
        using QueResult = priority_queue<MyResult, vector<MyResult>, MyCompare>;
        QueResult _queResult;
    };

} // space spellcorrct
#endif