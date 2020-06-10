#include <wx/wx.h>
#include <iostream>
#include <cmath>
#include "breshenham.h"

#define BUTTON_BASE_ID 1
#define FIELDWIDTH 20
#define FIELDHEIGHT 20
#define WINDOWSIZE 900
#define GRIDDOTSIZE 10
#define PIXTODOTS 40
#define STARTDOT 75
#define STARTDOTCENTER STARTDOT+GRIDDOTSIZE/2

using namespace std;

class MainWindow : public wxFrame
{
public:
    // Constructor to create the Main Window for the application.
    MainWindow(const wxString &title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(WINDOWSIZE, WINDOWSIZE))
    {
        Centre();
    }

    // Function to Draw the Grid
    void drawGridInit()
    {
        wxClientDC grid_init(this);
        wxPoint origin = grid_init.GetDeviceOrigin();
        grid_init.SetDeviceOrigin(origin.x, origin.y);

        for (int x = 0; x < FIELDWIDTH; x++)
        {
            for (int y = 0; y < FIELDHEIGHT; y++)
            {
                wxPen pen(*wxLIGHT_GREY, 1);
                grid_init.SetPen(pen);
                grid_init.SetBrush(wxBrush(*wxLIGHT_GREY));
                grid_init.DrawRectangle(STARTDOT + x * PIXTODOTS, STARTDOT + y * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
                grid_init.SetPen(wxNullPen);
                grid_init.SetBrush(wxNullBrush);
            }
        }
    }
    
    void onMouseClick(wxMouseEvent &event)
    {

        static bool draw_grid = 0;
        static bool refresh = 0;
        
        if (draw_grid == 0)
        {
            drawGridInit();
            draw_grid = 1;
        }

        //Create Object for Breshenham Class
        breshenham_circle *breshenhamCircle = new breshenham_circle();
       

        static bool drag_init = 0;

        static int x = 0;
        static int y = 0;

        static wxPoint ptCenter;
        
        wxClientDC circle(this);
        
        //Set Pen Colour
        wxPen penG(*wxLIGHT_GREY, 1);
        wxPen penR(*wxRED, 1);
        wxPen penB(*wxBLUE, 1); 

        wxPoint origin = circle.GetDeviceOrigin();
        circle.SetDeviceOrigin(origin.x, origin.y);

        if(event.ButtonUp() && refresh==0 )
        {
            //Regresh the Screen for next Drag
            circle.Clear();
            drawGridInit();
            refresh=1;
        }

        if (event.Dragging())
        {

            // At start of Drag show the Center of the circle on the grid
            if (drag_init == 0)
            {
                circle.Clear();
                drawGridInit();
                
                const wxPoint pt1 = wxGetMousePosition();
                ptCenter = pt1;
                x = floor((pt1.x - this->GetScreenPosition().x - STARTDOTCENTER) / PIXTODOTS);
                y = floor((pt1.y - this->GetScreenPosition().y - STARTDOTCENTER) / PIXTODOTS);
               
                circle.SetPen(penB);
                circle.SetBrush(wxBrush(*wxBLUE));
                circle.DrawRectangle(STARTDOT + x * PIXTODOTS, STARTDOT + y * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
                circle.SetPen(wxNullPen);
                circle.SetBrush(wxNullBrush);

                drag_init = 1;
            }

            
          
        }

        //Captures Event of Finish of Mouse Drag
        if (event.ButtonUp() && drag_init==1)
        { 

            refresh=0;
            
            // Reset the center point grid point
            circle.SetPen(penG);
            circle.SetBrush(wxBrush(*wxLIGHT_GREY));
            circle.DrawRectangle(STARTDOT + x * PIXTODOTS, STARTDOT + y * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
            circle.SetPen(wxNullPen);
            circle.SetBrush(wxNullBrush);

            const wxPoint ptRadius = wxGetMousePosition();
            int radius = sqrt(pow((ptCenter.x - ptRadius.x), 2) + pow((ptCenter.y - ptRadius.y), 2));

            //Convert Mouse Co-ordinates to Grid Points
            int discreteX = floor((ptCenter.x - this->GetScreenPosition().x - STARTDOTCENTER) /(float) (PIXTODOTS));
            int discreteY = floor((ptCenter.y - this->GetScreenPosition().y - STARTDOTCENTER) /(float) (PIXTODOTS));
        

            circle.SetBrush(wxBrush(wxTransparentColour, wxTRANSPARENT));
            circle.SetPen(penB);

            // Get Breshenham Circle Points 
            vector<vector<int>> points = breshenhamCircle->drawCircle(round(radius / (float)PIXTODOTS), x, y);
            drawCirclePlotter(points, x, y);
            min_radius = breshenhamCircle->min_radius;
            max_radius = breshenhamCircle->max_radius;

            // Draw Breshenham Circle
            circle.DrawCircle(discreteX * PIXTODOTS + STARTDOTCENTER, discreteY * PIXTODOTS + STARTDOTCENTER, (max_radius + min_radius) * PIXTODOTS / 2 + 5);
            circle.SetPen(wxNullPen);
  
            //Draw the max radius and min radius Circle
            circle.SetPen(penR);
            circle.DrawCircle(discreteX * PIXTODOTS + STARTDOTCENTER, discreteY * PIXTODOTS + STARTDOTCENTER, max_radius * PIXTODOTS + GRIDDOTSIZE);
            circle.DrawCircle(discreteX * PIXTODOTS + STARTDOTCENTER, discreteY * PIXTODOTS + STARTDOTCENTER, min_radius * PIXTODOTS - GRIDDOTSIZE);
            circle.SetPen(wxNullPen);

            //Reset the states for next operations
            drag_init = 0;
            x = 0;
            y = 0;

        }
    }

    // Function to plot the breshenham circle obtained
    void drawCirclePlotter(vector<vector<int>> points, int xc, int yc)
    {
        for (int i = 0; i < points.size(); i++)
        {
            wxClientDC dRect(this);
            int x = points[i][0];
            int y = points[i][1];
            wxPoint origin = dRect.GetDeviceOrigin();
            dRect.SetDeviceOrigin(origin.x, origin.y);

            wxPen pen(*wxBLUE, 1); // red pen of width 1
            dRect.SetPen(pen);
            dRect.SetBrush(wxBrush(*wxBLUE));

            dRect.DrawRectangle(STARTDOT + (x + xc) * PIXTODOTS, STARTDOT + (y + yc) * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
            dRect.DrawRectangle(STARTDOT + (-x + xc) * PIXTODOTS, STARTDOT + (y + yc) * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
            dRect.DrawRectangle(STARTDOT + (x + xc) * PIXTODOTS, STARTDOT + (-y + yc) * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
            dRect.DrawRectangle(STARTDOT + (-x + xc) * PIXTODOTS, STARTDOT + (-y + yc) * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);

            dRect.DrawRectangle(STARTDOT + (y + xc) * PIXTODOTS, STARTDOT + (x + yc) * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
            dRect.DrawRectangle(STARTDOT + (y + xc) * PIXTODOTS, STARTDOT + (-x + yc) * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
            dRect.DrawRectangle(STARTDOT + (-y + xc) * PIXTODOTS, STARTDOT + (x + yc) * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);
            dRect.DrawRectangle(STARTDOT + (-y + xc) * PIXTODOTS, STARTDOT + (-x + yc) * PIXTODOTS, GRIDDOTSIZE, GRIDDOTSIZE);

            dRect.SetPen(wxNullPen);
            dRect.SetBrush(wxNullBrush);
        }
    }

public:
    // Declare Event Table
    wxDECLARE_EVENT_TABLE();
    double max_radius;
    double min_radius;
};

//Event Table Initialize
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MOUSE_EVENTS(MainWindow::onMouseClick)
wxEND_EVENT_TABLE()

// App window initialize
class MyApp : public wxApp
{
public:
    bool OnInit()
    {
        MainWindow *Window = new MainWindow(wxT("Circle Drawer"));
        Window->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);