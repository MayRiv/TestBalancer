/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinProtocol.hpp
 * Author: i.maydanovskiy
 *
 * Created on 17 марта 2017 г., 16:41
 */

#ifndef BINPROTOCOL_HPP
#define BINPROTOCOL_HPP
#include "storage.hpp"
#include "socket.hpp"
#include <string>
const __uint32_t  BIN_OK_STATUS				= 1;
const __uint32_t  BIN_ERORR_STATUS			= 2;
const __uint32_t  BIN_TEMP_ERORR_STATUS		= 3;
const __uint32_t  SESSION_STORAGE_MEMMORY_USAGE = 100000;

const __uint32_t CMD_END_SESSION		= 1;
class CmdHandler
{
public:
    virtual int RunCmd(class lb::Storage &st) = 0;
    virtual ~CmdHandler() {};
};
class BinProtocol {
public:
    BinProtocol();
    BinProtocol(const BinProtocol& orig);
    virtual ~BinProtocol();
    lb::Storage& getStorage(){
        return st;
    }
    void BeginSession(){
        st.SetMaxMemmoryUsage(SESSION_STORAGE_MEMMORY_USAGE);
	st.Start();
    }
    
    int GetLastCmdTime() const {
        return secs;
    }
    
    int SendCmd(int cmdID, lb::SocketClient* client);
    int SendMsg(int cmdID, lb::SocketClient* client, int status=0);
    int ReadMsg(lb::SocketClient* client);
    
    struct CmdStruct{
        int cmdID;
        int status;
        int size;
    };
protected:
    lb::Storage st;
    CmdStruct cmd;
    int secs;
    long int _maxCmdWaitTime;
};

class BinAPI:public BinProtocol{
    
public:
    BinAPI(int port, std::string ip);
    
    int BeginSession(std::string bindIP);
    void EndSession()
	{
		if (client)
		{
			st.Start();
			SendMsg(CMD_END_SESSION, client, 0);
			delete client;
			client = NULL;
		}
	}
    ~BinAPI(){
        printf("Ended");
        EndSession();
    }
    
protected:
    std::string ip;
    int port;
    lb::SocketClient *client;
};


class BinSession:public BinProtocol{
public:
    ~BinSession()
    {
        for(auto it = cmdHandlerTable.begin(); it != cmdHandlerTable.end(); it++)
        {
            delete it->second;
        }
    }
    int GetCmd(lb::SocketClient *cl);
    void AddHandler(const int cmdID, CmdHandler* handler)
    {
        cmdHandlerTable.insert(std::pair<int,CmdHandler*>(cmdID,handler));
    }
    CmdHandler* FindHandler(const int cmdID)
    {
        for(auto it = cmdHandlerTable.begin(); it != cmdHandlerTable.end(); it++)
        {
            if (cmdID == it->first)
                return it->second;
        }
    }
    
protected:
    std::map<int, CmdHandler*> cmdHandlerTable;
    CmdHandler* currentHandler;
};


#endif /* BINPROTOCOL_HPP */

