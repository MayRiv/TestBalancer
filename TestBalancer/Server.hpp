/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Server.hpp
 * Author: i.maydanovskiy
 *
 * Created on 24 марта 2017 г., 11:33
 */

#ifndef SERVER_HPP
#define SERVER_HPP
#include <string>
#include <map>
using namespace std;
class Server {
public:
    Server(int ID, std::string ip, int port);
    ~Server(){
        for(std::map<int,class Server*>::iterator it=_servers.begin(); it != _servers.end(); it++)
            delete it->second;
    }
    double Weight(){return 0;}
    double Reweight(int lastReqTime){
        averageReqTime = (averageReqTime * reqCount + lastReqTime) / (reqCount+1);
        reqCount++;
    }
    int LoadAll(); //future database load
private:
    std::string ip;
    int port, ID;
    double averageReqTime;
    long int reqCount;
    static std::map<int,class Server*> _servers;
};

#endif /* SERVER_HPP */

