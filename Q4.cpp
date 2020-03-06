//
//  Q4.cpp
//  Assignment 3
//
//  Created by Timothy Morvan on 06/03/2020.
//  Copyright © 2020 Timothy Morvan. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    
    const int arrsize = 100000, samplesize = 1000;
    long long delta = 0;
    long n = 0, min = 0, max = 0, input = 0;
    vector <int> sample (samplesize);
    srand (time(0));
    vector <int> vect(arrsize);
    
    // Randomly generating signed integers

    for (int i = 0; i < arrsize; i++){

        vect.at(i) = (rand() % (INT_MAX)) - rand()% (INT_MAX);
        
        cout << vect.at(i) << "\n";
    }
    
    cout << "\n\n";
    // Selecting samples
    
    for (int l = 0; l < samplesize; l++) {
    
    int slct = rand () % arrsize;
        sample.at(l) = vect.at(slct);
        
        cout << sample.at(l) << "\n";
    }
    
    // Sort the sample:
    
    sort(sample.begin(), sample.end());
    
    min = sample.at(0);
    max = sample.at(samplesize-1);
    
    // Dividing the array into N partitions
    
    cout << "Enter the number of partitions desired: ";
    cin >> n;
    
    delta = (max + abs(min)) / n;

    cout << "The partitions will have the size: " << delta << "\n";
    
    cout << "\n" << delta << "\n" << abs(min) << "\n" << n*delta + min << "\n" << max;
    
    
    // Creating n vectors with p size
    
    vector< vector<long> > vect1;
    vector<long> lastpartition;
    
    for (int row = 0; row < n; row++){
        
        vector<long> partition;

        for (int g =0; g < arrsize; g++){
            
            if (vect.at(g) >= (min+(row*delta)) && vect.at(g) <= ((min+(row+1)*delta)-1)){
                
                partition.push_back(vect.at(g));
                
            }
                
            else if (vect.at(g) < min || vect.at(g) > max) {
                
                if (row == 0){
                    
                lastpartition.push_back(vect.at(g));
                    
                }
            }
            
            // Storing max into the last partition because of float loss when calculating delta
            
            if (g == arrsize - 1 && row == n - 1) {
                partition.push_back(max);
            }
        }
        
        // Sorting partition
        sort(partition.begin(), partition.end());
        vect1.push_back(partition);
    }
    
    // Sorting the last partition
    sort(lastpartition.begin(), lastpartition.end());
    vect1.push_back(lastpartition);
    
    cout << "\n\nEnter any value in the integer data range to know if it's one of the randomly generate 100,000 integers: \n";
    cin >> input;
    
    for (int s = 0; s <= n; s++) {
        
        unsigned long sze = vect1.at(s).size();
        
        // Since there could be a partition with size 0 we need to make sure vect1 has at least one value stored inside of it
        if (sze > 0) {
            
        min = vect1.at(s).at(0);
                        
        max = vect1.at(s).at(sze-1);
        }
        
        if (input >= min && input <= max) {
            cout << "\nYour input is in the data range of partition: " << s << "\n";
            
            if (s == n) {
                cout << "So input is in the overflow partition, that is, it is not included in the sample data range\n";
            }
            cout << "\nNow we want to know if it's an actual value:\n";
            
            for (int h = 0; h < sze; h++) {
                
                if (input == vect1.at(s).at(h)){
                    cout << "We found it! Your input is at location " << h << " in that partition.\n";
                    return 0;
                }
            }
            vect1.at(s).push_back(input);
        }
    }
    cout << "Your input was not found in the partition, we will therefore implement it in this partition.";
    return 0;
}
