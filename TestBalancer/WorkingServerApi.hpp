/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorkingServerApi.hpp
 * Author: i.maydanovskiy
 *
 * Created on 20 марта 2017 г., 17:44
 */

#ifndef WORKINGSERVERAPI_HPP
#define WORKINGSERVERAPI_HPP
#include "BinProtocol.hpp"
const int API_PORT = 1100;
class WorkingServerApi:public BinAPI {
public:
    WorkingServerApi():BinAPI(API_PORT,"192.168.0.31"){};
    int GetCalculations(uint32_t& result);
protected:
    int SendCmd(int cmdID);
};

#endif /* WORKINGSERVERAPI_HPP */

