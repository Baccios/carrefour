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

package carrefour;

simple Till
{
    parameters:
        int position;
        //for P2 verification
        @signal[waitTime] (type=simtime_t);
        //OLD @statistic[stats_waitTime] (source="waitTime"; record=mean;);
        @statistic[stats_waitTime] (source="waitTime"; record=stats,vector;);
        @signal[responseTime] (type=simtime_t);
        //OLD @statistic[stats_responseTime] (source="responseTime"; record=mean;);
        @statistic[stats_responseTime] (source="responseTime"; record=stats,vector;);
        @signal[numCustomers] (type=long);
        @statistic[stats_numCustomers] (source="numCustomers"; record=timeavg;);
        @signal[numCustomersQueue] (type=long);
        @statistic[stats_numCustomersQueue] (source="numCustomersQueue"; record=timeavg;);
    gates:
        input in;
}












