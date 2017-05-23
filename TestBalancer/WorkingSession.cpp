/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorkingSession.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 20 марта 2017 г., 17:20
 */

#include "WorkingSession.hpp"
#include "cmds.hpp"
#include "socket.hpp"
#include "storage.hpp"
WorkingSession::WorkingSession() {
    this->AddHandler(ECmd::CMD_CALCULATE,new CalculateHandler());
}


WorkingSession::~WorkingSession() {
}

int WorkingSession::Cmd(lb::SocketClient* client)
{
    if (!GetCmd(client))
		return 0;
    
    int status = currentHandler->RunCmd(st);

    if (status != BIN_OK_STATUS)
    {
	st.Start();
    }
    return SendMsg(cmd.cmdID, client, status);
}

int CalculateHandler::RunCmd(lb::Storage &st){
    st.Start();
    
    uint32_t value = 32;
    st.Add(value);
    return BIN_OK_STATUS;
}