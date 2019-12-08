package carrefour.simulations;
import carrefour.*;

network Carrefour
{
    parameters:
        //the number of tills contained in the supermarket
        int tillsNumber;

        //avg speed of humans' walk is 1 m/s
        //avg interdistance between tills is 2 m.
        double delta @unit(s) = default(2s);

        //policy = 1 -> single queue, multiple servers
        //policy = 2 -> multiple queues, one for each server
        int policy;

        //this parameter represents the capacity of tills in the supermarket.
        //this value is expressed in number of processable items per second
        double capacity = default(0.3);
        
        //this parameter represents the mean interarrival time of the customers
        double meanInterArrivalTime @unit(s);
        
        //this parameter represents the mean number of items in a cart
        double meanItemsInACart;
        
        //0: exponential distribution of interarrival times
        int interArrivalDistribution;
        
        //0: exponential distribution of the number of items in a cart
        //1: lognormal distribution of the number of items in a cart
        int itemsInCartDistribution;
        
    submodules:
        generator: Generator;
        decider: Decider;
        tills[tillsNumber]: Till;
    connections:
        generator.out --> decider.customer_in;
        for j=0..(sizeof(tills)-1) {
            decider.out++ --> {  delay = delta*j; } --> tills[j].in;
        }
}