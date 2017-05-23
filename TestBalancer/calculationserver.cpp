/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CalculationServer.cpp
 * Author: i.maydanovskiy
 *
 * Created on 20 марта 2017 г., 15:25
 */

#include <cstdlib>
#include <stdio.h>
#include "socket.hpp"
#include "WorkingThreadManager.hpp"
#include "WorkingServerApi.hpp"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    lb::SocketClient server;
    server.InitServer(API_PORT, "192.168.0.31");
    WorkingThreadManager manager;
    for (int i = 0; i < 10; i++)
    {
		manager.NewTask(&server);
                printf("Task launched\n");
    }
    printf("All tasks launched\n");
    while(1)
        sleep(1);
    return 0;
}

