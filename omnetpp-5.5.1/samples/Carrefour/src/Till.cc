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

#include "Till.h"
#include <cstring>

Define_Module(Till);

void Till::initialize()
{
    this->beep_ = new cMessage("beep");
    this->queue_ = new cQueue("line");
    this->processing_ = NULL;

    //Note: the parent network is required to have a parameter named "capacity"
    this->capacity_= getParentModule()->par("capacity");
}

void Till::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
        handleBeep(msg);
    else {
        handleCustomer(check_and_cast<Customer*>(msg));
    }
    //nothing else to do: these are the only two cases of message
}

void Till::handleCustomer(Customer *msg) {

    //if the till is empty the customer gets served
    if(this->processing_ == NULL && this->queue_->isEmpty()) {
        serveCustomer(msg);
    }
    //otherwise it gets enqueued
    else {
        this->queue_->insert(msg);
    }
}

void Till::handleBeep(cMessage *msg){
    Departure *dep = new Departure("departure");
    dep->setTillPosition(par("position"));
    //Note: the parent network is required to call the Decider instance "decider"
    cModule *targetModule = getParentModule()->getSubmodule("decider");
    this->sendDirect(dep, targetModule, "ack_in");
    serveNextCustomer();
}

void Till::serveCustomer(Customer *msg) {
    double procTime = msg->getCartLength()/this->capacity_;//cartLength/capacity;
    this->processing_ = msg;
    this->scheduleAt(simTime() + procTime, this->beep_);
}

void Till::serveNextCustomer() {
    Customer* old = this->processing_;
    if(!this->queue_->isEmpty()) {
        Customer* nextProc = check_and_cast<Customer*>(this->queue_->pop());
        serveCustomer(nextProc);
    }
    else {
        this->processing_ = NULL;
    }

    delete old;
}

Till::~Till() {
    cancelAndDelete(this->beep_);
    while(!this->queue_->isEmpty()) {
        Customer* tmp = check_and_cast<Customer*>(this->queue_->pop());
        delete tmp;
    }
    if(processing_) {
        delete processing_;
    }
}
