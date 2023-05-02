#pragma once

#include <vector>
#include "../softrastCPP/softrast/softrast.h"

using namespace std;

#define WIDTH 256


struct Rule
{
    virtual vector<vector<float>> kernel() = 0;
    virtual float activation_fn(float board[WIDTH][WIDTH]) = 0;
};


struct Rule1: public Rule
{
    vector<vector<float>> ksernel()
    {
        return {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f}
        };
    };

    float activation_fn(float board[WIDTH][WIDTH])
    {
        return 1.0f;
    };
};



class System
{
private:
    float _data_back[WIDTH][WIDTH], _data_front[WIDTH][WIDTH];

public:
    System() {  };
    void tick(Rule *rule);
    void draw(Renderer &renderer);

};


void System::tick(Rule *rule)
{
    
}


void System::draw(Renderer &renderer)
{
    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
        }
    }
}
