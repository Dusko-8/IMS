#ifndef VISITOR_GENERATOR_H
#define VISITOR_GENERATOR_H

#include <vector>
#include <simlib.h>
#include "visitor.h"

/*class Generator : public Event {
    std::vector<Visitor *> visitor;
    ResortVariableData *data_;
public:
    Generator(ResortVariableData *data);
    void Behavior();
    
};*/
// In visitor_generator.h

class Generator : public Event {
    std::vector<Visitor *> visitors;  // Assuming this holds pointers to Visitor objects
    ResortVariableData *data_;
public:
    Generator(ResortVariableData *data);
    //~Generator();  // Destructor to clean up Visitor objects
    void Behavior();
    static int MorningPeek;
    static int MorningNormal;
    static int MorningLow;
    static int NightPeek;
    static int NightLow;

    static bool bus1;
    static bool bus2;
};

#endif 