// #include "./include/socket/SockFd.h"
// #include "./include/socket/SockAddress.h"
// #include "./include/socket/SockIO.h"
// #include "./include/socket/SockAcceptor.h"
// #include "./include/socket/SockConnection.h"
// #include "./include/epoll/Epoll.h"
// #include "./include/epoll/EpollPoller.h"
#ifndef __SPELLCORRECTSERVER_H__
#define __SPELLCORRECTSERVER_H__
#include "../tcp/TcpServer.h"
#include "../threadpool/ThreadPool.h"
namespace SPELLCORRECT
{
	using reactor::spTcpConnPtr;
	class SpellCorrectServer
	{
	public:
		SpellCorrectServer(const int &threadNum, const int &queSize, const string &cnpath, const string &enpath);
		void start();
		void onConnection(spTcpConnPtr pConn);
		void onMessage(spTcpConnPtr pConn);
		void onClose(spTcpConnPtr pConn);

	private:
		THREADPOOL::ThreadPool _threadPool;
		reactor::TcpServer _tcpServer;
	};

} // space spellcorrct
#endif