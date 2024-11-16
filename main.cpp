// COMSC-210 | Mauricio Espinosa | Lab 32
// IDE Used: Visual Studio Code & Github

#include "Car.h"
#include <deque>
#include <ctime>
#include <array>
#include <cstdlib>
#include <iostream>

using namespace std;

// global constant declarations
const double CAR_PAY_PROBABILITY = 46.0;
const double CAR_JOIN_PROBABILITY = 39.0;
const double CAR_SWITCH_PROBABILITY = 15.0;
const int INITIAL_NUM_CARS_MIN = 1;
const int INITIAL_NUM_CARS_MAX = 3;
const int NUM_LANES = 4;
const int NUM_SIMULATIONS = 20;


int main() {
    srand(time(0));    // seed time for random

    // Initialize a deque structure of Cars
    array<deque<Car>, NUM_LANES> tollBoothLane;

    // Initialize the array with the amount of initial number of cars in each lane
    for(int i = 0; i < NUM_LANES; i++)
    {
        int initialCars = rand() % (INITIAL_NUM_CARS_MAX - INITIAL_NUM_CARS_MIN + 1) + INITIAL_NUM_CARS_MIN;
        for(int j = 0; j < initialCars; j++)
        {
            tollBoothLane[i].push_back(Car());
        }   
    }

    // Print initial car queue
    cout << "Initial Queue:\n";
    for(int k = 0; k < NUM_LANES; k++)
    {
        cout << "Lane " << (k + 1) << ":\n";
        for(auto& carInitial : tollBoothLane[k])
        {
            cout << setw(5) << "";
            carInitial.print();
        }
    }
    
    
    // time intervals
    int time = 1;

    // run while the deque is not empty
    while (!tollBoothLane.empty())
    {
        double randProb = rand() % 100;

        cout << "Time: " << time << " Operation: ";

        // if the probably is higher than 55% (car pays) and the deque is not empty
        if (randProb < CAR_PAY_PROBABILITY && !tollBoothLane.empty())
        {
            cout << "Car Paid: ";
            // output the front car
            tollBoothLane.front().print();
            // remove the front car from the deque
            tollBoothLane.pop_front();
        }
        else // new car joins the line
        {
            Car newCar;
            cout << "Joined lane: ";
            newCar.print();
            // add the new car to the back of the line
            tollBoothLane.push_back(newCar);
        }

        cout << "Queue:" << endl;
        // if the deque is empty
        if (tollBoothLane.empty())
        {
            cout << setw(5) << "";
            cout << "Empty" << endl;
        }
        else  // if the deuque is not empty
        {
            for (auto& carOutput : tollBoothLane)
            {
                cout << setw(5) << "";
                carOutput.print();
            }
        }

        time++;
    }

    return 0;
}
