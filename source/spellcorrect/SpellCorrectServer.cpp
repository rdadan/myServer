#include "../../include/spellcorrect/SpellCorrectServer.h"
// #include "../../include/tcp/TcpConnection.h"

#include <string>
#include <iostream>
#include <functional>
using std::bind;
using std::cout;
using std::endl;
namespace SPELLCORRECT
{
	class myTask : public THREADPOOL::Task
	{
	public:
		myTask(reactor::spTcpConnPtr pConn) : _pConn(pConn) {}
		void process() override
		{
			int i = 9999999999999999999999;
			while (i--)
			{
			}
			cout << "process thread: " << pthread_self() << endl;
			_pConn->sendMsgToLoop("do process done\n");
		}
		reactor::spTcpConnPtr _pConn;
	};

	SpellCorrectServer::SpellCorrectServer()
		: _threadPool(2, 2),
		  _tcpServer()
	{
	}
	void SpellCorrectServer::onConnection(spTcpConnPtr pConn)
	{
		cout << "\n> " << pConn->toString() << "has connected!" << endl;
		pConn->sendMsg(" > welcome to SpellCorrect Server!");
	}
	void SpellCorrectServer::onMessage(spTcpConnPtr pConn)
	{
		string msg = pConn->recvMsg();
		cout << "recv msg: " << msg << endl;
		// 去掉 '\n'
		int pos = msg.find('\n');
		if (pos != string::npos)
			msg = msg.substr(0, pos);

		myTask *ptask = new myTask(pConn);
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