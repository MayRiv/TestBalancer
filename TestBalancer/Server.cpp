/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 24 марта 2017 г., 11:33
 */

#include "Server.hpp"
#include <string>
#include <map>
std::map<int,Server*> Server::_servers;
Server::Server(int ID, std::string ip, int port)
{
    this->ID = ID;
    this->ip = ip;
    this->port = port;
    
}

int Server::LoadAll()
{
    _servers.insert(std::pair<int,Server*>(1,new Server(1,"192.168.0.31", 1100)));
    
    _servers.insert(std::pair<int,Server*>(2,new Server(2,"192.168.0.31", 1101)));    
}