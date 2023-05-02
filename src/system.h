#pragma once

#include <vector>
#include "../softrastCPP/softrast/softrast.h"

using namespace std;


#define WIDTH 500


struct Rule
{
    virtual vector<vector<float>> kernel() = 0;
    virtual float activation_fn(float x) = 0;
};

struct Rule1: public Rule
{
    vector<vector<float>> kernel()
    {
        return {
            { 0.100, -0.100,  0.100 },
            {-0.000,  1.000, -0.300 },
            {-0.500, -0.100,  0.200 }
        };
    };

    float activation_fn(float x)
    {
        return common::clamp(abs(x), 0.0f, 1.0f);
    };
};

struct Rule2: public Rule
{
    vector<vector<float>> kernel()
    {
        return {
            { 0.050, -0.250,  0.050 },
            {-0.250,  0.850, -0.250 },
            { 0.050, -0.250,  0.050 }
        };
    };

    float activation_fn(float x)
    {
        float fn = x*x;

        return common::clamp(fn, 0.0f, 1.0f);
    };
};

struct Mitosis: public Rule
{
    vector<vector<float>> kernel()
    {
        return {
            {-0.939,  0.880, -0.939 },
            { 0.880,  0.400,  0.880 },
            {-0.939,  0.880, -0.939 }
        };
    };

    float activation_fn(float x)
    {
        float fn = -1.0f/(0.9f*pow(x, 2.0f)+1.0f)+1.0f;
        return common::clamp(fn, 0.0f, 1.0f);
    };
};

struct Worms: public Rule
{
    vector<vector<float>> kernel()
    {
        return {
            { 0.680, -0.900,  0.680 },
            {-0.900, -0.660, -0.900 },
            { 0.680, -0.900,  0.680 }
        };
    };

    float activation_fn(float x)
    {
        float fn = -1.0f / pow(2.0f, (0.6f*pow(x, 2.0f))) + 1.0f;

        return common::clamp(fn, 0.0f, 1.0f);
    };
};

struct CGOL: public Rule
{
    vector<vector<float>> kernel()
    {
        return {
            { 1.000,  1.000,  1.000 },
            { 1.000,  9.000,  1.000 },
            { 1.000,  1.000,  1.000 }
        };
    };

    float activation_fn(float x)
    {
        if ((x > 2.9f && x < 3.1f) || (x > 10.9f && x < 11.1f) || (x > 11.9f && x < 12.1f))
            return 1.0f;
        return 0.0f;
    };
};

struct SlimeMold: public Rule
{
    vector<vector<float>> kernel()
    {
        return {
            { 0.800, -0.850,  0.800 },
            {-0.850, -0.200, -0.850 },
            { 0.800, -0.850,  0.800 }
        };
    };

    float activation_fn(float x)
    {
        return common::clamp(-1.0f / (0.89f*pow(x, 2.0f) + 1.0f) + 1.0f, 0.0f, 1.0f);
    };
};

struct Fabric: public Rule
{
    vector<vector<float>> kernel()
    {
        return {
            { 0.037,  0.430, -0.737 },
            { 0.406, -0.321, -0.319 },
            {-0.458,  0.416,  0.478 }
        };
    };

    float activation_fn(float x)
    {
        float fn = (exp(2.0f*x)-1.0f)/(exp(2.0f*x)+1.0f);
        return common::clamp(fn, 0.0f, 1.0f);
    };
};


class System
{
private:
    float **_data_back, **_data_front;
    float _apply_kernel(int r, int c, vector<vector<float>> kernel);

public:
    System();
    void tick(Rule *rule);
    void draw(Rule *rule, Renderer &renderer);

};


System::System()
{
    srand(clock());

    _data_back = new float *[WIDTH];
    _data_front = new float *[WIDTH];

    for (int i=0; i<WIDTH; i++)
    {
        _data_back[i]  = new float [WIDTH];
        _data_front[i] = new float [WIDTH];
    }


    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            _data_front[i][j] = 0.0f;
            _data_back[i][j] = 0.0f;
            
            if (rand()%1000 < 1000)
            {
                float f = (rand()%100) / 100.0f;

                _data_front[i][j] = f;
                _data_back[i][j] =  f;
            }
        }
    }
}



float System::_apply_kernel(int r, int c, vector<vector<float>> kernel)
{
    float sum = 0.0f;

    // ((val % 360) + 360) % 360

    int r0 = (((r-1) % WIDTH) + WIDTH) % WIDTH;
    int r1 = (((r+0) % WIDTH) + WIDTH) % WIDTH;
    int r2 = (((r+1) % WIDTH) + WIDTH) % WIDTH;

    int c0 = (((c-1) % WIDTH) + WIDTH) % WIDTH;
    int c1 = (((c+0) % WIDTH) + WIDTH) % WIDTH;
    int c2 = (((c+1) % WIDTH) + WIDTH) % WIDTH;

    sum += kernel[0][0] * _data_front[r0][c0];
    sum += kernel[0][1] * _data_front[r0][c1];
    sum += kernel[0][2] * _data_front[r0][c2];

    sum += kernel[1][0] * _data_front[r1][c0];
    sum += kernel[1][1] * _data_front[r1][c1];
    sum += kernel[1][2] * _data_front[r1][c2];

    sum += kernel[2][0] * _data_front[r2][c0];
    sum += kernel[2][1] * _data_front[r2][c1];
    sum += kernel[2][2] * _data_front[r2][c2];

    return sum;
}


void System::tick(Rule *rule)
{
    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            _data_back[i][j] = _apply_kernel(i, j, rule->kernel());
            _data_back[i][j] = rule->activation_fn(_data_back[i][j]);
        }
    }

    for (int i=0; i<WIDTH; i++)
        for (int j=0; j<WIDTH; j++)
        {
            _data_front[i][j] = 0.01f * _data_front[i][j] + 0.99f * _data_back[i][j];
        }
}


void System::draw(Rule *rule, Renderer &renderer)
{
    for (int i=0; i<WIDTH; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            float r = common::clamp(255.0f * _data_front[i][j], 0.0f, 255.0f);
            float g = r;
            float b = 1.0f / r;
            renderer.pixel(vec2(i, j), vec3(r, g, b));
        }
    }
}
