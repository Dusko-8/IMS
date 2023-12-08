#include "visitor.h"
#include <unistd.h>

Facility cashier1("Pokladna1");
Facility cashier2("Pokladna2");
Facility cashierAutomat("PokladnaAutomat");

Facility cafeteria("Cafeteria bar");
Store cafeteria_seats("Cafeteria sedacky", static_data.cafeteria_visitors_capacit);
Queue skylift_queue("Rada na lanovku");


int Visitor::totalVisitors = 0;
int Visitor::totalVisitors2 = 0;
int Visitor::VolanteerLeave = 0;
int Visitor::MidTicket = 0;

class ExitEvent : public Event {
    Visitor* visitor;
public:
    ExitEvent(Visitor* v) : visitor(v) {}

    void Behavior() override {
        visitor->HandleLeave();
        // If the visitor was dynamically allocated
    }

};

void Lift::Behavior() { 
        // Process up to 4 customers from the ski lift queue
        int processedCustomers = 0;
        while (!skylift_queue.Empty() && processedCustomers < 4) {
            Visitor *visitor = (Visitor *)skylift_queue.GetFirst(); // Get the first customer in the queue
            visitor->Activate();
            processedCustomers++;
        }
        if (Time >  10800 && Time < 10900){
            Activate(Time + 7200);
        }
        else
        {
            Activate(Time + 6);
        }
        
}

// Constructor
Visitor::Visitor() {
    
    if (Random() <= chances.half_day_ticket_chance) {
        /*if ((Time >  18000 && Time <=25200) || Time <=5400)
        {*/
            (new ExitEvent(this))->Activate(Time + 4 * 60 * 60);  // Assuming 60 time units = 1 hour
            MidTicket++;
        //}
    }
    totalVisitors2++;
    Activate();
}



// Main behavior of the customer
void Visitor::Behavior() {
    /*Mby add probability that he can leave*/ 
    HandlePayment();
}

void Visitor::HandlePayment() {

    if (!skipCashier) {
        if (cashier1.QueueLen() <= cashier2.QueueLen() && cashier1.QueueLen() <= cashierAutomat.QueueLen())
        {
            ProcessFacility(cashier1, static_data.cashier_selling_time);

        }else if(cashier2.QueueLen() <= cashier1.QueueLen() && cashier2.QueueLen() <= cashierAutomat.QueueLen()){
            ProcessFacility(cashier2, static_data.cashier_selling_time);
        }else{
            ProcessFacility(cashierAutomat, static_data.automat_selling_time);
        }

        totalVisitors += groupSize;
        for (int i = 0; i < groupSize-1; ++i) {
            Visitor* groupMember = new Visitor();
            groupMember->skipCashier = true;
            groupMember->Activate();
        }
    }

    HandleSkying();
}



void Visitor::HandleSkying() {
    // Check if the skylift is busy and enter the queue if necessary
    Into(skylift_queue);
    Passivate();
    HandleSkiLift();
}



void Visitor::HandleSkiLift() {
    Wait(Exponential(static_data.skylift_travle_time)); 
    HandleGoingDownHill();
}



void Visitor::HandleGoingDownHill() {
    
    Wait(RunData.customer_skying_Time);  //skiing down

    HandleActivity();
}

void Visitor::HandleActivity() {
    double next_step = Random();
    if(next_step <= chances.exit_chance){
        VolanteerLeave++;
        HandleLeave();
    }
    else if (next_step <= RunData.cafetria_visit_chance) {
        HandleCafeteria();

    }else
    {
        HandleSkying();
    }
    
}


void Visitor::HandleCafeteria() {

    ProcessFacility(cafeteria, static_data.cashier_selling_time);
    // let someone else from queue in
    HandleCafeteriaTable();
    
}

void Visitor::HandleCafeteriaTable() {
    if (cafeteria_seats.Free() > 0)
    {
        Enter(cafeteria_seats, 1);
        Wait(static_data.customer_cafetria_time_seted);
        Leave(cafeteria_seats, 1);
    }else
    {
        Wait(static_data.customer_cafetria_time_standing);
    }
    

    HandleSkying();
}

void Visitor::HandleLeave() {
    
}

// Process a facility with waiting time
void Visitor::ProcessFacility(Facility &f, double w) {
    f.Seize(this);
    Wait(Exponential(w));
    f.Release(this);
}

// Activate next customer in the queue
void Visitor::ActivateQueue(Queue &q) {
    if (!q.Empty()) {
        Visitor *v = (Visitor *)q.GetFirst();
        v->Activate();
    }
}

// Activate next 4 customers in the queue
int Visitor::Activate4Queue(Queue &q) {
    int i = 0;
    for(; i<4;i++){
        if (!q.Empty()) {
            Visitor *v = (Visitor *)q.GetFirst();
            v->Activate();
        }else
        {
            break;
        }
    }
    return i;
}
