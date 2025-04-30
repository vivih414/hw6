#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0};
        int group = 4;
        for(int i = k.length(); group >= 0; group--)
        {
            unsigned long long sect = 0;
            unsigned long long base = 1;
            for(int j = 0; j < 6; j++)
            {
                if(i - 1 - j >= 0)
                {
                    sect += letterDigitToNumber(k[i-1-j]) * base;
                }
                base *= 36;
            }
            w[group] = sect;
            i -= 6;
        }
        unsigned long long hash = 0;
        for(int i = 0; i < 5; i++)
        {
            hash += rValues[i] * w[i];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = std::tolower(letter);
        if('a' <= letter && letter <= 'z')
        {
            return letter - 'a';
        }
        else if('0' <= letter && letter <= '9')
        {
            return letter - '0' + 26;
        }
        else
        {
            return 0;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
