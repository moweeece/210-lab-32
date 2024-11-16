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
    array<deque<Car>, NUM_LANES> tollBoothLanes;

    // Initialize the array with the amount of initial number of cars in each lane
    for(int i = 0; i < NUM_LANES; i++)
    {
        int initialCars = rand() % (INITIAL_NUM_CARS_MAX - INITIAL_NUM_CARS_MIN + 1) + INITIAL_NUM_CARS_MIN;
        for(int j = 0; j < initialCars; j++)
        {
            tollBoothLanes[i].push_back(Car());
        }   
    }

    // Print initial car queue
    cout << "Initial Queue:\n";
    for(int k = 0; k < NUM_LANES; k++)
    {
        cout << "Lane: " << (k + 1) << ":\n";
        for(auto& carInitial : tollBoothLanes[k])
        {
            cout << setw(5) << "";
            carInitial.print();
        }
    }
    
    
    // time intervals
    for(int time = 1; time <= NUM_SIMULATIONS; time++)
    {
        cout << "\nTime: " << time << endl;

        for (int lane = 0; lane < NUM_LANES; lane++)
        {
            double randProb = rand() % 100;

            // if the probably is higher than 55% (car pays) and the array is not empty
            if (randProb < CAR_PAY_PROBABILITY && !tollBoothLanes[lane].empty())
            {
                cout << "Lane: " << (lane + 1) << " Paid: ";
                // output the front car
                tollBoothLanes[lane].front().print();
                // remove the front car from the deque
                tollBoothLanes[lane].pop_front();
            }
            // new car joins
            else if (randProb < CAR_PAY_PROBABILITY + CAR_JOIN_PROBABILITY)
            {
                Car newCar;
                cout << "Lane: " << (lane + 1) << " Joined: ";
                newCar.print();
                // add the new car to the back of the line
                tollBoothLanes[lane].push_back(newCar);
            }
            // rear car switches
            else if (randProb < CAR_PAY_PROBABILITY + CAR_JOIN_PROBABILITY + CAR_SWITCH_PROBABILITY && !tollBoothLanes[lane].empty())
            {
                // variable to determine which lane to switch to
                int switchlane;
                do 
                {
                    switchlane = rand() % NUM_LANES;
                } while (switchlane == lane);  // this makes sure the car switches to a different lane

                cout << "Lane: " << (lane + 1) << " Switched to Lane " << (switchlane + 1) << ": ";
                tollBoothLanes[lane].back().print();

                // rear car switches and is removed from its current position
                tollBoothLanes[switchlane].push_back(tollBoothLanes[lane].back());
                tollBoothLanes[lane].pop_back();
            }
        }

        // display queue at the end of the time period
        for(int l = 0; l < NUM_LANES; l++)
        {
            cout << "Lane: " << (l + 1) << " Queue\n";
            // if the array is empty
            if (tollBoothLanes[l].empty())
            {
                cout << setw(5) << "";
                cout << "Empty" << endl;
            }
            else  // if the array is not empty
            {
                for (auto& carOutput : tollBoothLanes[l])
                {
                    cout << setw(5) << "";
                    carOutput.print();
                }
            }
        }
    }

    return 0;
}
