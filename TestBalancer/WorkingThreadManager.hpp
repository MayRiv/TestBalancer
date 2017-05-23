/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorkingThreadManager.hpp
 * Author: i.maydanovskiy
 *
 * Created on 20 марта 2017 г., 15:42
 */

#ifndef WORKINGTHREADMANAGER_HPP
#define WORKINGTHREADMANAGER_HPP
#include "WebThreadManager.hpp"
class WorkingThreadManager:public WebThreadManager {
public:
    void NewTask(class lb::SocketClient *client);
    
private:

};

#endif /* WORKINGTHREADMANAGER_HPP */

