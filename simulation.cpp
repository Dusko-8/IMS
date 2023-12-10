#include <iostream>
#include <simlib.h>

#include "visitor.h"
#include "visitor_generator.h"


using namespace std;


int main() {
    Init(0, RunData.simulationLength);
    RandomSeed(time(nullptr));
    //fflush(stdout);
    
    //Generator *gen = new Generator(&RunData);
    (new Generator(&RunData))->Activate();
    (new Lift())->Activate();
    Run();

    cashier1.Output();
    cashier2.Output();
    cashierAutomat.Output();
    cashierAutomat2.Output();
    cafeteria.Output();
    cafeteria_seats.Output();
    skylift_queue.Output();
    printf("Total of visitors -> %d\n",Visitor::totalVisitors);
    printf("Total of visitors Leve on 4H dedline-> %d\n",Visitor::totalVisitors2);
    printf("Volantere leave of visitors -> %d\n",Visitor::VolanteerLeave);
    printf("4 H tickets -> %d\n",Visitor::MidTicket);
    printf("skiped -> %d\n",Visitor::SkipedCashier);
    printf("MorningPeek -> %d\n",Generator::MorningPeek);
    printf("MorningNormal -> %d\n",Generator::MorningNormal);
    printf("MorningLow -> %d\n",Generator::MorningLow);
    printf("NightPeek -> %d\n",Generator::NightPeek);
    printf("NightLow -> %d\n",Generator::NightLow);
    //printf("Left IN gap -> %d\n",Visitor::LeftInGap);
    


    return 0;
}