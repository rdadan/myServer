#include "../../include/spellcorrect/QueryTask.h"
#include "../../include/spellcorrect/Dict.h"

namespace SPELLCORRECT
{
    QueryTask::QueryTask(string strQuery, spTcpConnPtr connPtr)
        : _strQuery(strQuery),
          _connPtr(connPtr)
    {
    }
    void QueryTask::process()
    {
        // 计算线程，对查询词进行匹配
        // 执行查询，查询索引表
        getRuesltFromIndexTable();
        sendRueslt(); // 3. 给客户端返回结果
    }

    void QueryTask::getRuesltFromIndexTable()
    {
        auto indexTable = Dict::getInstance()->getIndexTable();
        string ch;
        for (size_t idx = 0; idx < _strQuery.size(); idx++)
        {
            size_t bytes = ::getBytes(_strQuery[idx]);
            ch = _strQuery.substr(idx, bytes);
            cout << "ch: " << ch << " idx: " << idx << " _strQuery.size(): " << _strQuery.size() << endl;

            idx += bytes;
            if (indexTable.count(ch))
            {
                cout << "indexTable has character " << ch << endl;
                getQueRueslt(indexTable[ch]);
            }
        }
    }

    size_t QueryTask::getQueRueslt(set<int> &iset)
    {
        auto dict = Dict::getInstance()->getDict();
        auto iter = iset.begin();
        for (; iter != iset.end(); ++iter)
        {
            string rhsWord = dict[*iter].first;
            int idist = ::getMinEditDistance(_strQuery, rhsWord);
            //进行最小编辑距离的计算
            if (idist < 3)
            {
                MyResult res;
                res._word = rhsWord;
                res._iFreq = dict[*iter].second;
                res._iDist = idist;
                _queResult.push(res);
            }
        }
    }

    void QueryTask::sendRueslt()
    {
        if (_queResult.empty())
        {
            string result = "no answer!";
            _connPtr->sendMsgToLoop(result);
        }
        else
        {
            MyResult result = _queResult.top();
            _connPtr->sendMsgToLoop(result._word); //这里只返回了一个候选词

            // Cache &cache = CacheManager::getCache(wd::str2int(wd::current_thread::threadName));
            // cache.addElement(_queryWord, result._word); //在缓存中添加新的查询结果
            // cout << "> respone(): add Cache" << endl;
        }
        cout << "> reponse client" << endl;
    }

} // SPELLCORRECT
