// IMS project 2015 - 07 Menza
// authors: xmalin26 & xmasek15

#ifndef IMS_PROJECT_CUSTOMER_H
#define IMS_PROJECT_CUSTOMER_H

#include <iostream>
#include <vector>
#include <simlib.h>
#include "SkyResort_Data.h"


extern Facility cashier1;
extern Facility cashier2;
extern Facility cashierAutomat;
extern Facility cafeteria;
extern Store cafeteria_seats;
extern Queue skylift_queue;
extern Facility skylift;



class Visitor : public Process {
public:
    Visitor();
    /*Netusim co toto robi nasledujuce 3 veci */
    static int totalVisitors;
    static int totalVisitors2;
    static int VolanteerLeave;

    

    static int MidTicket;
    bool skipCashier = false;
    int groupSize = int(Random() * 4) + 1;
    void Behavior();

    

    inline void ProcessFacility(Facility &f, double w);
    inline void ActivateQueue(Queue &q);
    inline int Activate4Queue(Queue &q);
    void EnterQueueAndWait(Queue &queue, Facility &facility);
    void HandleGoingDownHill();
    void HandlePayment();
    void HandleCafeteria();  // encapsulates all proceses in thsi facility
    void HandleCafeteriaTable();
    void HandleActivity();  // is decision based process
    void HandleSkying();
    void HandleSkiLift();
    void HandleLeave();
};

class Lift : public Event {
public:
    void Behavior();
};

#endif  