#include "SkyResort_Data.h"

// Peak Season Data under Normal Weather Conditions
ResortVariableData seson_peak_weather_normal = {
    28800, // simulationLength in minutes (4 hours, considering peak times as busiest)
    60,     //customer_arraival_Time_standard
    30,     //customer_arraival_Time_peek
    120,    //customer_arraival_Time_low
    0,      //customer_arraival_Time_none
    240, // customer_skying_Time
    0.1,
};

ResortVariableData seson_peak_weather_raining = {
    28800, // simulationLength in minutes (4 hours, considering peak times as busiest)
    55,     //customer_arraival_Time_standard
    55,     //customer_arraival_Time_peek
    120,    //customer_arraival_Time_low
    0,      //customer_arraival_Time_none
    300, // customer_skying_Time
    0.15,
};


ResortVariableData season_normal_weather_normal = {
    28800, // simulationLength in minutes (4 hours, considering peak times as busiest)
    70,     //customer_arraival_Time_standard
    40,     //customer_arraival_Time_peek
    130,    //customer_arraival_Time_low
    0,      //customer_arraival_Time_none
    240, // customer_skying_Time
    0.09,
};

ResortVariableData season_normal_weather_raining = {
    28800, // simulationLength in minutes (4 hours, considering peak times as busiest)
    60,     //customer_arraival_Time_standard
    60,     //customer_arraival_Time_peek
    130,    //customer_arraival_Time_low
    0,      //customer_arraival_Time_none
    300, // customer_skying_Time
    0.14,
};

// Static data for the resort
ResortStaticData static_data = {
    1800,  //customer_cafetria_Time
    900,   //customer_cafetria_time_standing
    120,   //cafeteria_cashier_time
    30,    //cafeteria_visitors_capacit
    180,   //cashier_selling_time
    90,    //automat_selling_time
    504,   //skylift_travle_time
};

ResortVariableData RunData = season_normal_weather_raining;
// Chances of various events happening in the resort  
ResortChances chances = {
    0.005,
    0.35,
};
