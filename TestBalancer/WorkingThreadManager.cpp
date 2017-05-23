/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorkingThreadManager.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 20 марта 2017 г., 15:42
 */

#include "WorkingThreadManager.hpp"
#include "WorkingThread.hpp"


void WorkingThreadManager::NewTask(class lb::SocketClient *client){
    new WorkingThread(this,client);
}