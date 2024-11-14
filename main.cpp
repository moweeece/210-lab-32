// COMSC-210 | Mauricio Espinosa | Lab 32
// IDE Used: Visual Studio Code & Github

#include "Car.h"
#include <deque>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

// global constant declarations
const int INITIAL_NUM_CARS = 2;
const double CAR_PAY_PROBABILITY = 55;
const double CAR_JOIN_PROBABILITY = 45;


int main() {
    srand(time(0));    // seed time for random

    // Initialize a deque structure of Cars
    deque<Car> tollBoothLane;

    // Initialize the deque with the amount of initiaul number of cars
    for (int i = 0; i < INITIAL_NUM_CARS; i++)
    {
        tollBoothLane.push_back(Car());
    }

    cout << "Initial Queue:\n";
    for (auto& car : tollBoothLane)
    {
        cout << setw(5) << "";
        car.print();
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
