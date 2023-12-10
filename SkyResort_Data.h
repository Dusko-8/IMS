#ifndef SKYRESORT_DATA_H
#define SKYRESORT_DATA_H

typedef struct {
    unsigned int customer_cafetria_time_seted,
                 customer_cafetria_time_standing,
                 cafeteria_cashier_time,
                 cafeteria_visitors_capacit,
                 cashier_selling_time,
                 automat_selling_time,
                 skylift_travle_time;
} ResortStaticData;


typedef struct {

    double  exit_chance,
            half_day_ticket_chance;
            
} ResortChances;

typedef struct {
    unsigned int simulationLength;
    double customer_arraival_Time_standard,
           customer_arraival_Time_peek,
           customer_arraival_Time_low,
           customer_arraival_Time_none,
           customer_skying_Time,
           cafetria_visit_chance;
} ResortVariableData;

// Experiment data represent different times of visitors 
extern ResortVariableData seson_peak_weather_normal;  
extern ResortVariableData seson_peak_weather_raining;  
extern ResortVariableData season_normal_weather_normal; 
extern ResortVariableData season_normal_weather_raining; 

// actual experiment data that are used
extern ResortVariableData RunData; // always is assigned to one of the experiment representation data
extern ResortChances chances; // data used to represent chances and probability of decisions of visitors
extern ResortStaticData static_data;

#endif //IMS_PROJECT_DATA_H