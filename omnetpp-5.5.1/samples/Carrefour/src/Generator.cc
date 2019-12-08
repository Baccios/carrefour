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

#include "Generator.h"

Define_Module(Generator);

void Generator::initialize(){
    //read the distribution of items in a cart and interarrival times
    interArrivalDistribution_ = getParentModule()->par("interArrivalDistribution");
    itemsInCartDistribution_ = getParentModule()->par("itemsInCartDistribution");

    //read the mean values of items in a cart and interarrival times
    meanInterArrivalTime_ = getParentModule()->par("meanInterArrivalTime");
    meanItemsInACart_ = getParentModule()->par("meanItemsInACart");

    //create the feedback message
    beep_ = new cMessage("beep");

    //first customer comes as soon as the simulation starts
    scheduleAt(simTime(), beep_);

}

void Generator::handleMessage(cMessage *msg){
    Customer* cust = new Customer("newCustomer");

    //put some items in the cart of the customer
    if(itemsInCartDistribution_ == 0){
        //exponential distribution
        //NOTE: Using RNG #1 to generate the flow of service times
        cust->setServTime(exponential(meanItemsInACart_, 1));
    }else{
        EV << "This type of distribution for items in a cart is not supported yet!";
    }

    //throw this customer to the tills
    send(cust, "out");

    //wait some time before generating next customer
    if(interArrivalDistribution_ == 0){
        //exponential distribution
        //NOTE: Using RNG #0 to generate the flow of arrivals
        scheduleAt(simTime()+exponential(meanInterArrivalTime_, 0), beep_);
    }else{
        EV << "This type of distribution for interarrival times is not supported yet!";
    }
}

Generator::~Generator(){
    delete beep_;
}
