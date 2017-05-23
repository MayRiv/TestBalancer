/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WorkingServerApi.cpp
 * Author: i.maydanovskiy
 * 
 * Created on 20 марта 2017 г., 17:44
 */

#include "WorkingServerApi.hpp"
#include "cmds.hpp"
int WorkingServerApi::GetCalculations(uint32_t& result){
        st.Start();
	if (!SendCmd(ECmd::CMD_CALCULATE))
        {
                printf("cmd returned 0\n");
		return 0;
        }
        st.Get(&result);
	return 1;
}

int WorkingServerApi::SendCmd(int cmdID)
{
    return BinAPI::SendCmd(cmdID,client);
}