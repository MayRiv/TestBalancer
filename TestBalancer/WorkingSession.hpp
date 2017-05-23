/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorkingSession.hpp
 * Author: i.maydanovskiy
 *
 * Created on 20 марта 2017 г., 17:20
 */

#ifndef WORKINGSESSION_HPP
#define WORKINGSESSION_HPP
#include "BinProtocol.hpp"

class WorkingSession:public BinSession {
public:
    WorkingSession();
    virtual ~WorkingSession();
    int Cmd(lb::SocketClient* client);
private:

};

class CalculateHandler:public CmdHandler
{
    int RunCmd(class lb::Storage &st);
};
#endif /* WORKINGSESSION_HPP */

