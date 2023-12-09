#include "visitor.h"
#include <unistd.h>

Facility cashier1("Pokladna1");
Facility cashier2("Pokladna2");
Facility cashierAutomat2("PokladnaAutomat2");
Facility cashierAutomat("PokladnaAutomat");

Facility cafeteria("Cafeteria bar");
Store cafeteria_seats("Cafeteria sedacky", static_data.cafeteria_visitors_capacit);
Queue skylift_queue("Rada na lanovku");


int Visitor::totalVisitors = 0;
int Visitor::totalVisitors2 = 0;
int Visitor::VolanteerLeave = 0;
int Visitor::MidTicket = 0;
int Visitor::SkipedCashier = 0;
int Visitor::LeftInGap = 0;

int LeftInPause = 0;

class ExitEvent : public Event {
    Visitor* visitor;
public:
    ExitEvent(Visitor* v) : visitor(v) {}
    void Behavior() override {
        /*if(visitor->isInQueue()){
            printf("In quue and leaving");
        }*/
        Visitor::totalVisitors2++;
        visitor->HandleLeave();
    }

};

void Lift::Behavior() { 
        // Process up to 4 customers from the ski lift queue

        int processedCustomers = 0;

        /*if (Time >  21602 && Time <=21608){
            printf("queue size - %d",skylift_queue.size());
        }*/

        if (Time >  14400 && Time <=21600){
            printf("queue size - %d",skylift_queue.size());
            for (size_t i = 0; i < skylift_queue.size(); i++)
            {
                Visitor *visitor = (Visitor *)skylift_queue.GetFirst(); // Get the first customer in the queue
                visitor->Activate();
            }

            Activate(Time + 100);

        }
        else
        {
            while (!skylift_queue.Empty() && processedCustomers < 4) {
                Visitor *visitor = (Visitor *)skylift_queue.GetFirst(); // Get the first customer in the queue
                //skylift_queue.operator delete(visitor);
                //printf("queue size continuus - %d + %f\n",skylift_queue.size(),Time);
                visitor->Activate();
                processedCustomers++;
            }
            //printf("queue size - %d Time :%f \n",skylift_queue.size(),Time);
            
            Activate(Time + 6);
        }
        
}

// Constructor
Visitor::Visitor() {
    
    if (Random() <= chances.half_day_ticket_chance) {

        (new ExitEvent(this))->Activate(Time + 4 * 60 * 60); 
        MidTicket++;

    }
    //totalVisitors2++;
    Activate();
}



// Main behavior of the customer
void Visitor::Behavior() {
    HandlePayment();
}

void Visitor::HandlePayment() {

    if (!skipCashier) {

        if (cashier1.QueueLen() <= cashierAutomat2.QueueLen() && cashier1.QueueLen() <= cashierAutomat.QueueLen())
        {
            ProcessFacility(cashier1, static_data.cashier_selling_time);

        }else if(cashierAutomat2.QueueLen() <= cashier1.QueueLen() && cashierAutomat2.QueueLen() <= cashierAutomat.QueueLen()){
            ProcessFacility(cashierAutomat2, static_data.automat_selling_time);
        }else{
            ProcessFacility(cashierAutomat, static_data.automat_selling_time);
        }

        totalVisitors += groupSize;
        
        for (int i = 0; i < groupSize-1; ++i) {
            Visitor* groupMember = new Visitor();
            groupMember->skipCashier = true;
            groupMember->Activate();
        }

    }else
    {
        SkipedCashier++;
    }

    if (Time >  14400 && Time <=21600)
    {
        Wait(7201);
        HandleSkying();
    }
    
    HandleSkying();
}



void Visitor::HandleSkying() {
    // Check if the skylift is busy and enter the queue if necessary
    Into(skylift_queue);
    Passivate();

    if (Time >  14400 && Time <=21600){
        Visitor::LeftInGap++;
        HandleLeave();
        printf("Gong Home- %f \n",Time);
    }
    else{    
        HandleSkiLift();
        printf("Gong DownHill- %f \n",Time);
    }
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

    if ((Time >  14400 && Time <=21600) || Time > 28000){
        Visitor::LeftInGap++;
        HandleLeave();
    }else if(next_step <= chances.exit_chance){
        VolanteerLeave++;
        HandleLeave();
    }
    else if (next_step >= RunData.cafetria_visit_chance) {
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
