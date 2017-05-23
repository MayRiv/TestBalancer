/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorkingThread.hpp
 * Author: i.maydanovskiy
 *
 * Created on 20 марта 2017 г., 15:39
 */

#ifndef WORKINGTHREAD_HPP
#define WORKINGTHREAD_HPP
#include "WebThread.hpp"
#include "socket.hpp"
class WorkingThread:public WebThread {
public:
    WorkingThread(class WebThreadManager* mngr, lb::SocketClient* client):WebThread(mngr, client){};
protected:
    virtual void run();
};

#endif /* WORKINGTHREAD_HPP */

