/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinProtocol.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 17 марта 2017 г., 16:41
 */

#include "BinProtocol.hpp"
#include "storage.hpp"
#include "socket.hpp"
#include "time.hpp"
BinProtocol::BinProtocol():_maxCmdWaitTime(1000) {
}

BinProtocol::~BinProtocol() {
}

int BinProtocol::SendCmd(int cmdID, lb::SocketClient* client)
{
    secs = 0;
    lb::MicroTimer tm;
    if (!SendMsg(cmdID,client,0))
    {
        printf("SendMsg returned 0");
        return 0;
    }
       
    if (!ReadMsg(client))
        return 0;
    secs = tm.EndSec();
    if (cmd.cmdID != cmdID || cmd.status != BIN_OK_STATUS)
        return 0;
    return 1;
}

int BinProtocol::SendMsg(int cmdID, lb::SocketClient* client, int status)
{
    cmd.cmdID = cmdID;
    cmd.size = st.Size();
    cmd.status = status;
    if (client->Send((char*)&cmd, sizeof(CmdStruct), _maxCmdWaitTime) != sizeof(CmdStruct))
    {
		printf("Cannot send answer header \n");
        return 0;
    }
    if (cmd.size)
    {
        if (client->Send((char*)st.Data(), cmd.size, _maxCmdWaitTime) != cmd.size)
        {
		printf("Cannot send answer msg\n");
            return 0;
        }
    }
    return 1;
}
int BinProtocol::ReadMsg(lb::SocketClient* client)
{
    bzero(&cmd, sizeof(cmd));
    st.Start();
    
    
    if (client->ReadBin((char*)&cmd, sizeof(CmdStruct), _maxCmdWaitTime) != sizeof(CmdStruct))
    {
        return 0;
    }
    if (cmd.size > SESSION_STORAGE_MEMMORY_USAGE)
    {
        return 0;
    }
    if (cmd.size > 0)
    {
        __uint8_t *mem = st.AddAttach(cmd.size);
        if (client->ReadBin((char*)mem, cmd.size, _maxCmdWaitTime) != (int)cmd.size)
	{
            //L(LOG_ERROR, "Cannot read cmd data\n");
            return 0;
	}
        st.Begin();
    }
	
    return 1;
}


BinAPI::BinAPI(int port, std::string ip):BinProtocol()
{
    this->port = port;
    this->ip = ip;
    this->client = 0;
}
const int MAX_CONNECT_WAIT = 5;
int BinAPI::BeginSession(std::string bindIP)
{
    BinProtocol::BeginSession();
    if (!client)
	client = new lb::SocketClient();
    else
	client->Close();
    if (!client->BindOnIp(bindIP.c_str(), 0)) {
        delete client;
        client = NULL;
        return 0;
    }

	//if (!client->Connect(ip.c_str(), port))
    if (!client->Connect(lb::SocketClient::IpToLong(ip.c_str()), port, MAX_CONNECT_WAIT))
    {
		delete client;
		client = NULL;
		return 0;
    }
	//client->SetNoDelay(1);
    return 1;
}


int BinSession::GetCmd(lb::SocketClient *cl)
{
//	std::auto_ptr<AutoCounter> aC(new AutoCounter(_countReadMsg));
	//cl->SetNoDelay(1);

	if (!ReadMsg(cl))
            return 0;

	if (!cmd.cmdID)
	{
            return 0;
	}

	if (cmd.cmdID == CMD_END_SESSION)
	{
            return 0;
	}


	currentHandler = FindHandler(cmd.cmdID);
	if (!currentHandler)
	{
            return 0;
	}
	return 1;
}