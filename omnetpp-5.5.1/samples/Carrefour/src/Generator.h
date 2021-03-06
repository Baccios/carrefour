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

#ifndef __CARREFOUR_GENERATOR_H_
#define __CARREFOUR_GENERATOR_H_

#include <omnetpp.h>
#include"Customer_m.h"
#include"Departure_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Generator : public cSimpleModule
{
  private:
    double meanInterArrivalTime_;
    double meanItemsInACart_;
    double varianceOfItemsInACart_;
    int interArrivalDistribution_;
    int itemsInCartDistribution_;
    cMessage* beep_;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    ~Generator();
};

#endif
