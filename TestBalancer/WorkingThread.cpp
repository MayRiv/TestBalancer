/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorkingThread.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 20 марта 2017 г., 15:39
 */

#include "WorkingThread.hpp"
#include "WebThreadManager.hpp"
#include "socket.hpp"
#include "WorkingSession.hpp"
using namespace lb;

void WorkingThread::run()
{
    mngr->Add(this);
    WorkingSession pr;
    while(1)
    {
        mngr->AddWaitThread();
        SocketClient* client = serv->GetConnection();
        mngr->RemWaitThread();
        if (!client)
        {
            delete client;
            continue;
        }
	//sessionID++;
		//L(LOG_WARNING, "Start session %s _%llx_%x_)\n", SocketClient::GetIPStr(client->GetIP()), tid, sessionID);
	pr.BeginSession();
	while (pr.Cmd(client)) // parse all cmd commands
			;
	//pr.ClearCurUser();
		//L(LOG_WARNING, "End session %s _%llx_%x_)\n", SocketClient::GetIPStr(client->GetIP()), tid, sessionID);
	delete client;
    }
}

