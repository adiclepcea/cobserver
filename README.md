# cobserver
Simple implementation of the obeserver pattern in C

## Observer pattern

The observer pattern is the pattern used in the reactive programming concept.

You have one publisher and several subscribers (like with a magazine). 
Each time a magazine has a new issue, the subscribers receive it. 
The same conccept applies to the observer pattern. 
Each time you call the _publish"_ method of the _publisher_, each of the 
_subscribers_ get the info passed in to the _publisher_.

## Where to use it

This is useful in many places. It is used in actions in gui frameworks sometimes.
Let's think at another example.

You could have a sistem that reads or receives some data and you want it analysed.
But in the same time you want a graph of the data and also a log of the times the data has arrived.
You could have three subscribers:

* one will analyse the data
* one will generate and show the graph
* one will generate a log 

If later you also want to generate an spredsheet or transform the data in something else, 
you could just create another _subscriber_ and subscribe it to the same _publisher_.

## What can I find here

You have a simple implementation of the pattern in the *C programming language*.
In the main.c file you have a very simple example that shows you how to use it.
