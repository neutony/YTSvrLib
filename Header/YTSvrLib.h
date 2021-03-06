/*MIT License

Copyright (c) 2016 Archer Xu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef _DIPAN_SERVER_H
#define _DIPAN_SERVER_H

//编译时显示代码中的TODO列表和ATTENTION列表
//#pragma INFO("your information")
//#pragma TODO("your todo sth.")
//#pragma ATTENTION("your attention sth.")
#define TOSTR(x)        #x
#define TOSTR2(x)       TOSTR(x)
#define INFO(x)         message(__FILE__ "(" TOSTR2(__LINE__) "): INFO " x)
#define TODO(x)         message(__FILE__ "(" TOSTR2(__LINE__) "): TODO " x)
#define ATTENTION(x)    message(__FILE__ "(" TOSTR2(__LINE__) "): ATTENTION " x)

extern "C" {
	const char* get_version_code();
}

#if defined(_WIN32) || defined(_WIN64)
#define LIB_WINDOWS
#else
#define LIB_LINUX
#endif

#define ASIO_STANDALONE 1

#ifdef LIB_WINDOWS

#pragma comment(lib, "openssl/lib/libeay32.lib")
#pragma comment(lib, "openssl/lib/ssleay32.lib")

#ifdef YTSVRLIB_USE_STATIC_LIB
#define YTSVRLIB_NO_DLL
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Winmm.lib" )
#pragma comment(lib, "crypt32.lib" )

#pragma comment(lib, "mysql/lib/static/mysqlpp.lib")
#pragma comment(lib, "mysql/lib/libmysql.lib")
#pragma comment(lib, "BugReport/BugslayerUtil.lib")
#pragma comment(lib, "iconv/lib/static/iconv.lib")
#pragma comment(lib, "jsoncpp/lib/static/jsoncpp.lib")
#pragma comment(lib, "libcurl/lib/static/libcurl.lib")
#pragma comment(lib, "zlib/lib/static/zlib.lib")
#pragma comment(lib, "lz4/lib/static/liblz4_static.lib")

#ifdef YTSVRLIB_WITH_REDIS
#pragma comment(lib, "redis/lib/s/cpp_redis.lib")
#pragma comment(lib, "redis/lib/s/tacopie.lib")
#endif // YTSVRLIB_WITH_REDIS

#pragma comment(lib, "protobuf/lib/static/libprotobuf.lib")
#ifdef DEBUG64
#pragma comment(lib, "YTSvrLibSD.lib" )
#else
#pragma comment(lib, "YTSvrLibS.lib" )
#endif

#elif defined(YTSVRLIB_USE_DLL_LIB)
#pragma comment(lib, "zlib/lib/dll/zlib.lib")
#pragma comment(lib, "mysql/lib/dll/mysqlpp.lib")
#pragma comment(lib, "libcurl/lib/dll/libcurl.lib")
#ifdef DEBUG64
#pragma comment(lib,"YTSvrLibD.lib")
#else
#pragma comment(lib,"YTSvrLib.lib")
#endif
#endif

#ifdef YTSVRLIB_MAKE_DLL
#define YTSVRLIB_EXPORT __declspec(dllexport)
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Winmm.lib" )
#pragma comment(lib, "crypt32.lib" )

#pragma comment(lib, "mysql/lib/dll/mysqlpp.lib")
#pragma comment(lib, "mysql/lib/libmysql.lib")
#pragma comment(lib, "BugReport/BugslayerUtil.lib")
#pragma comment(lib, "iconv/lib/dll/iconv.lib")
#pragma comment(lib, "jsoncpp/lib/dll/jsoncpp.lib")
#pragma comment(lib, "libcurl/lib/dll/libcurl.lib")
#pragma comment(lib, "zlib/lib/dll/zlib.lib")
#pragma comment(lib, "lz4/lib/dll/liblz4.lib")

#ifdef YTSVRLIB_WITH_REDIS
#pragma comment(lib, "redis/lib/dll/cpp_redis.lib")
#pragma comment(lib, "redis/lib/dll/tacopie.lib")
#endif // YTSVRLIB_WITH_REDIS

#pragma comment(lib, "protobuf/lib/dll/libprotobuf.lib")
#elif !defined(YTSVRLIB_NO_DLL)
#define YTSVRLIB_EXPORT __declspec(dllimport)
#else // MAKING STATIC LIB
#define YTSVRLIB_EXPORT
#define MYSQLPP_NO_DLL
#define CURL_STATICLIB
#endif

#else
#define YTSVRLIB_EXPORT
#endif

#ifdef LIB_WINDOWS
#include <winsock2.h>
#include <Mswsock.h>
#include <process.h>
#include "typedef.h"
#include "iconv/iconv.h"
#define DIRECTORY_SEPARATOR "\\"
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <signal.h>
#include <malloc.h>
#include <cassert>
#include <cstdio>
#include <cwchar>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <pthread.h>
#include <iconv.h>
#include <netdb.h>
#include "typedef.h"
#define DIRECTORY_SEPARATOR "/"
#endif // LIB_WINDOWS

#define X2		<< 1
#define X4		<< 2
#define X8		<< 3
#define X16		<< 4
#define X32		<< 5
#define X64		<< 6
#define X128	<< 7
#define X256	<< 8
#define X512	<< 9

//STL
#include <map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <istream>
using namespace std;
#ifdef LIB_WINDOWS
#include "BugReport/BugslayerUtil.h"
#endif // LIB_WINDOWS

#ifdef LIB_LINUX
#include <wchar.h>
#include <locale.h>
#endif // LIB_LINUX

#include "./Global/GlobalServer.h"
#include "./libcurl/curl.h"
#include "./zlib/zlib.h"
#include "./lz4/lz4.h"
#include "./lz4/lz4frame.h"
#include "./jsoncpp/json/json.h"
#include "./Global/Performance.h"
#include "./Single/Single.h"
#include "./lz4/lz4feasy.h"
#include "./Service/SyncObj.h"
#include "./dice/dice.h"
#include "./findpath/JPS.h"
#include "./Global/GlobalURLRequest.h"
#include "./Service/Pool.h"
#include "./Service/Utility.h"
#include "./Service/Log.h"
#include "./Service/Application.h"
#include "./Service/AutoCloseFile.h"
#include "./Service/YTThread.h"
#include "./urlwriter/urlwriter.h"
#include "./mysql/MYSQLManagerBase.h"
#include "./mysql/MYSQLDBSys.h"
#include "./Base64/Base64.h"
#include "./sha/sha1.h"
#include "./md5/md5.h"
#include "./Filter/Filter.h"
#include "./tinyxml/XMLDocument.h"
#include "./Socket/YTSocketThread.h"
#include "./Service/TimerThread.h"
#include "./Service/TimerHandler.h"
#include "./Socket/TCPSocket/TCPSocket.h"
#include "./Socket/RUDP/UDPSocket.h"
#include "./Socket/MessageMapping.h"

#ifdef YTSVRLIB_WITH_REDIS
#include "./redis/RedisConnector.h"
#endif // YTSVRLIB_WITH_REDIS

#ifdef YTSVRLIB_WITH_HTTP
#include "./Socket/HTTPSocket/HTTPSocket.hpp"
#endif // YTSVRLIB_WITH_HTTP

#ifdef YTLIB_WITH_WEBSOCKET
#include "./Socket/WebSocket/YTWSServer.h"
#include "./Socket/WebSocket/YTWSConnector.h"
#endif // WITH_WEBSOCKET

#endif