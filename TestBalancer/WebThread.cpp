/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebThread.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 17 марта 2017 г., 13:49
 */

#include "WebThread.hpp"
#include "WebThreadManager.hpp"
#include "socket.hpp"
#include "WorkingServerApi.hpp"
#include <stdio.h>
using namespace lb;
WebThread::WebThread(WebThreadManager* mngr, SocketClient* serv) {
    this->mngr = mngr;
    this->serv = serv;
    SetDetachState();
    if (int ret = Create())
    {
        //LOG PANIC
    }
}

void WebThread::run()
{
    mngr->Add(this);
    const int WEB_BUF_SIZE=2000;
    char buf[WEB_BUF_SIZE]; //requests
    
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
        try{
            unsigned int size = client->Read(buf,WEB_BUF_SIZE);
            xml_document<> _doc;
            _doc.parse<parse_no_utf8>(buf);
            xml_node<> *root = _doc.first_node();
            if (root == NULL)
		throw true;
            if (strcmp(root->name(), "cmd"))
            {
                //L(LOG_ERROR, "[CT] Bad root name %s\n", root->name());
                throw std::exception();
            }
			/*Mysql sql;
			if (!VServerConfig::initDBConnect(sql))
			{
				L(LOG_ERROR, "Cannot connect to Mysql\n");
				throw std::exception();
			}*/ 
            for (xml_node<> *child = root->first_node(); child != NULL; child = child->next_sibling())
            {
                if (child->type() != node_element)
                    continue;	
                if (!strcmp(child->name(), "test"))
                {
                    WorkingServerApi api;
                    std::string ip("192.168.0.31");
                    api.BeginSession(ip);
                    uint32_t result = 0;
                    api.GetCalculations(result);
                    
                    printf("Result is %d\n", result);
                    delete client;
                    client = 0;
                }
        
            }
        }
        catch (...)
        {
            printf("Some exception\n");
            delete client;
            client = 0;
        }
    }
}