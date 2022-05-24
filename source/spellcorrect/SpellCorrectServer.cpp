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
	// class myTask : public THREADPOOL::Task
	// {
	// public:
	// 	myTask(reactor::spTcpConnPtr pConn) : _pConn(pConn) {}
	// 	void process() override
	// 	{
	// 		int i = 99999999999999999999999;
	// 		while (i--)
	// 		{
	// 		}
	// 		cout << "process thread: " << pthread_self() << endl;
	// 		_pConn->sendMsgToLoop("do process done\n");
	// 	}
	// 	reactor::spTcpConnPtr _pConn;
	// };

	SpellCorrectServer::SpellCorrectServer()
		: _threadPool(2, 2),
		  _tcpServer()
	{
		// 初始化字典
		string cnpath = "/mnt/d/MyProjects/linuxOS/myspellcorrection/file/dict_cn_test.dat";
		string enpath = "/mnt/d/MyProjects/linuxOS/myspellcorrection/file/dict_en_test.dat";
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