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

#ifndef __CARREFOUR_TILL_H_
#define __CARREFOUR_TILL_H_

#include <omnetpp.h>
#include"Customer_m.h"
#include"Departure_m.h"

using namespace std;
using namespace omnetpp;

class Till : public cSimpleModule
{
  private:
    cQueue* queue_;
    Customer* processing_;
    cMessage* beep_;
    double capacity_;
    void serveCustomer(Customer* msg);
    void serveNextCustomer();

    //attributes for P1 verification
    simsignal_t responseTime_;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void handleBeep(cMessage* msg);
    void handleCustomer(Customer* msg);
    ~Till();
};

#endif
