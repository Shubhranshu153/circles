#ifndef __BRESHENHAM_H__
#define __BRESHENHAM_H__

#include <wx/wx.h>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
class breshenham_circle:public wxFrame
{
    public:
        breshenham_circle()
        {
        
        }
        
        ~breshenham_circle()
        {

        }
        // Function to compute the Breshenham circle drawing Algorithm
        vector <vector<int>> drawCircle(int r, int xc, int yc)
        {
            int x, y;
            int d = 3 - 2 * r;
            x = 0;
            y = r;

            drawCirclePlotter(x, y, xc, yc);
            
            min_radius = 2 * r;
            max_radius = -1;
            
            while (x < y)
            {
                if (sqrt(pow((x), 2) + pow((y), 2)) > max_radius)
                {
                    max_radius = sqrt(pow((x), 2) + pow((y), 2));
                }
                if (sqrt(pow((x), 2) + pow((y), 2)) < min_radius)
                {
                    min_radius = sqrt(pow((x), 2) + pow((y), 2));
                }

                if (d <= 0)
                {
                    d = d + (4 * x) + 6;
                    drawCirclePlotter(++x, y, xc, yc);
                    if (sqrt(pow((x), 2) + pow((y), 2)) > max_radius)
                    {
                        max_radius = sqrt(pow((x), 2) + pow((y), 2));
                    }
                    if (sqrt(pow((x), 2) + pow((y), 2)) < min_radius)
                    {
                        min_radius = sqrt(pow((x), 2) + pow((y), 2));
                    }
                }
                else
                {
                    d = d + (4 * (x - y)) + 10;
                    drawCirclePlotter(++x, --y, xc, yc);
                    if (sqrt(pow((x), 2) + pow((y), 2)) > max_radius)
                    {
                        max_radius = sqrt(pow((x), 2) + pow((y), 2));
                    }
                    if (sqrt(pow((x), 2) + pow((y), 2)) < min_radius)
                    {
                        min_radius = sqrt(pow((x), 2) + pow((y), 2));
                    }
                }
            }
            return points;
        }

        //Plotter Activates the required dots to construct the circle
        void drawCirclePlotter(int x, int y, int xc, int yc)
        {
            vector <int> point;
            point.push_back(x);
            point.push_back(y);
            points.push_back(point);
            
        }
    
    public:
        float min_radius;
        float max_radius;
        vector <vector <int>> points;
};

# endif