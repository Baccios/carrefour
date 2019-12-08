//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Decider.h"
#include <cstring>

Define_Module(Decider);

void Decider::initialize()
{
    //Note: the parent network is required to have a parameter named "tillsNumber" and "policy"
    policy_= getParentModule()->par("policy");
    tillsNumber_= getParentModule()->par("tillsNumber");
    tillCustomers_= new int [tillsNumber_];
    memset(tillCustomers_, 0x00, tillsNumber_);
    if(policy_==1)
        this->queue_ = new cQueue("line");//P2 doesn't need any queue in the decider

}

void Decider::handleMessage(cMessage *msg)
{
    switch ( policy_ )
          {
             case 1:
                handleMessageP1(msg);
                break;
             case 2:
                 handleMessageP2(msg);
                break;
             default:
                EV<<"Error! We need to abort the simulation!";
          }
}

void Decider::handleMessageP1(cMessage *msg){
    //An external arrival is happening
    if(strcmp(msg->getName(),"newCustomer") == 0)
        if(!queue_->isEmpty())
            queue_->insert(msg);    //Since all the tills are busy, otherwise no queue
        else{
            checkTillsAndPossiblySendCustomer(msg);
        }

    else {
        //It's an ack from a till
        Departure *dep = check_and_cast<Departure*>(msg);
        tillCustomers_[dep->getTillPosition()]--;
        if(!queue_->isEmpty())
            checkTillsAndPossiblySendCustomer(); //surely we'll send a msg because at least the till that has sent the ack is free (1^)
        delete dep;
    }
}

void Decider::checkTillsAndPossiblySendCustomer(cMessage *msg = NULL){
    if(!msg)
        msg = queue_->pop();
    int destTill;
    for(destTill = 0;destTill < tillsNumber_; destTill++){
        //(tillCustomers_[destTill] > 0) ? (continue) : (break);
        if(tillCustomers_[destTill] > 0)
            continue;
        else
            break;
    }
    if(destTill == tillsNumber_)
        queue_->insert(msg); //never insert again the msg that I have extracted (explained into 1^)
    else{
        tillCustomers_[destTill]++;
        send(msg, "out",destTill);
    }
}

void Decider::handleMessageP2(cMessage *msg){
    if(strcmp(msg->getName(),"newCustomer") == 0){
        int destTill=0;
        for(int i=0; i<tillsNumber_ ; i++)
            if(tillCustomers_[i] < tillCustomers_[destTill])
                destTill = i;
        tillCustomers_[destTill]++;
        send(msg, "out",destTill);
    }

    else {
        //It's an ack from a till
        Departure *dep = check_and_cast<Departure*>(msg);
        tillCustomers_[dep->getTillPosition()]--;
        delete dep;
    }
}

Decider::~Decider() {
    delete[] tillCustomers_;
    if(policy_==2)
        return; //no queue has been instantiated
    while(!queue_->isEmpty()) {
        Customer* tmp = check_and_cast<Customer*>(this->queue_->pop());
        delete tmp;
    }
}
