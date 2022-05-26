#include "../../include/spellcorrect/SpellCorrectServer.h"
#include "../../include/spellcorrect/QueryTask.h"
#include "../../include/spellcorrect/Dict.h"

#include <string>
#include <iostream>
#include <functional>
using std::bind;
using std::cout;
using std::endl;
namespace SPELLCORRECT
{

	SpellCorrectServer::SpellCorrectServer(const int &threadNum, const int &queSize, const string &cnpath, const string &enpath)
		: _threadPool(threadNum, queSize),
		  _tcpServer()
	{
		// 初始化字典
		Dict *pMyDict = Dict::getInstance();
		pMyDict->initDict(cnpath.c_str(), enpath.c_str());
	}
	void SpellCorrectServer::onConnection(spTcpConnPtr pConn)
	{
		cout << "\n> " << pConn->toString() << "has connected!" << endl;
		pConn->sendMsg(" > welcome to SpellCorrect Server!");
	}
	void SpellCorrectServer::onMessage(spTcpConnPtr pConn)
	{
		string strQuery = pConn->recvMsg();
		// 去掉 '\n'
		int pos = strQuery.find('\n');
		if (pos != string::npos)
		{
			strQuery.erase(pos, strQuery.size());
		}
		cout << "recv msg: " << strQuery << endl;
		QueryTask *ptask = new QueryTask(strQuery, pConn);
		_threadPool.setTask(ptask);
	}

	void SpellCorrectServer::onClose(spTcpConnPtr pConn)
	{
		cout << "\n> " << pConn->toString() << "has closs!" << endl;
	}
	void SpellCorrectServer::start()
	{

		_threadPool.start();
		using namespace std::placeholders;
		_tcpServer.setTcpConnCallBack(bind(&SpellCorrectServer::onConnection, this, _1));
		_tcpServer.setTcpMsgCallBack(bind(&SpellCorrectServer::onMessage, this, _1));
		_tcpServer.setTcpCloseCallBack(bind(&SpellCorrectServer::onClose, this, _1));
		_tcpServer.startTcpServer();
	}
} // space SPELLCORRECT