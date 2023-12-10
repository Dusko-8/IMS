#include <simlib.h>
#include "visitor.h"
#include "visitor_generator.h"

Generator::Generator(ResortVariableData *data) {
    data_ = data;    
}
int Generator::MorningPeek = 0;
int Generator::MorningNormal= 0;
int Generator::MorningLow= 0;
 
int Generator::NightPeek= 0;
int Generator::NightLow= 0;

bool Generator::bus1= true;
bool Generator::bus2= true;

void Generator::Behavior() {
    Visitor* v = new Visitor();
    visitors.push_back(v);  // Store the pointer for later deletion
    v->Activate();
    int arraival_Time;

    if ( Time <=  5400)
    {
        arraival_Time = data_->customer_arraival_Time_peek; 
        MorningPeek++;
        this->Activate(Time + Exponential(arraival_Time));

        if(bus1){
            for (size_t i = 0; i < 10; i++)
            {
                Visitor* v = new Visitor();
                visitors.push_back(v);  // Store the pointer for later deletion
                v->Activate();
            }
            bus1 = false;
        }
        
    }else if (Time >  5400 && Time <=10800)
    {
        arraival_Time = data_->customer_arraival_Time_standard;
        MorningNormal++;
        this->Activate(Time + Exponential(arraival_Time));

    }else if (Time >  10800 && Time <=14400)
    {
        arraival_Time = data_->customer_arraival_Time_low;
        MorningLow++;
        this->Activate(Time + Exponential(arraival_Time));
        
    }
    
    else if (Time >  14400 && Time <=21600)
    {        arraival_Time = data_->customer_arraival_Time_none;
             this->Activate(Time + 7201);
    }else if (Time >  21600 && Time <=25200)
    {
        arraival_Time = data_->customer_arraival_Time_peek; 
        NightPeek++;
        this->Activate(Time + Exponential(arraival_Time));
        
        if(bus2){
            for (size_t i = 0; i < 10; i++)
            {
                Visitor* v = new Visitor();
                visitors.push_back(v);  // Store the pointer for later deletion
                v->Activate();
            }
            bus2 = false;
        }
        
    }
    else if (Time >  25200 && Time <=28000)
    {
        arraival_Time = data_->customer_arraival_Time_low; 
        NightLow++;
        this->Activate(Time + Exponential(arraival_Time));
    }else
    {
        arraival_Time = data_->customer_arraival_Time_none;
    }
    
    
}