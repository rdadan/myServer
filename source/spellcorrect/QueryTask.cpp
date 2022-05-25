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
        // 1. 先在cache中查询
        cout << "Process Thread: " << pthread_self() << endl;
        _strResult = "";
        _strResult = SPELLCORRECT::_sCache.getCacheResult(_strQuery);
        if (_strResult != "")
        {
            cout << " get result from cache " << endl;
        }
        else
        { // 2. cache中找不到，再查询询索引表
            cout << " get result from indexTable " << endl;
            getRuesltFromIndexTable();
        }
        sendRueslt();
    }

    string QueryTask::getRuesltFromIndexTable()
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
        _strResult = "";
        if (_queResult.empty())
        {
            _strResult = "no answer!";
        }
        else
        {
            _strResult = "\n";
            while (!_queResult.empty()) // 返回全部候选词
            {
                _strResult += _queResult.top()._word + " ";
                _queResult.pop();
            }
            SPELLCORRECT::_sCache.setCacheResult(_strQuery, _strResult);
        }
        return _strResult;
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
        cout << "> reponse client" << endl;
        _connPtr->sendMsgToLoop(_strResult);
    }

} // SPELLCORRECT
