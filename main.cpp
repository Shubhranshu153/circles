#include <wx/wx.h>
#include <iostream>
#include <cmath>
#define BUTTON_BASE_ID 1
#define FIELDWIDTH 19
#define FIELDHEIGHT 19


using namespace std;
class MainWindow : public wxFrame
{
public:
// Constructor to create the Main Window for the application.
    MainWindow(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(900, 900))
	{
		Centre();
       
       
   
	}
  
    void onMouseClick(wxMouseEvent& event)
    {
        static int first_exec=0;
        
        if(first_exec==0)
        {
            wxClientDC grid_init(this);
            wxPoint origin=grid_init.GetDeviceOrigin();
            grid_init.SetDeviceOrigin(origin.x,origin.y);
           
        

            for(int x=0;x<FIELDWIDTH;x++)
            {
                for(int y=0;y<FIELDHEIGHT;y++)
                {
                    grid_init.DrawRectangle(75+x*40,75+y*40,10,10);
                    
                
                }
            }
            cout<<"exec";
            first_exec=1;
        }

            static int drag_=0;
            static int x=0;
            static int y=0;
            static wxPoint pt1_; 
            static const wxPoint pt2; 
            wxClientDC dc(this);
            wxPoint origin=dc.GetDeviceOrigin();

            dc.SetDeviceOrigin(origin.x,origin.y);

      
            if (event.Dragging())
            {
                
                if(drag_==0)
                {
                    dc.Clear();
                     first_exec=0;
                    // dc.Clear();
                    const wxPoint pt1 = wxGetMousePosition();
                    pt1_=pt1;
                    x = floor((pt1.x - this->GetScreenPosition().x-80)/40);
                    y = floor((pt1.y - this->GetScreenPosition().y-80)/40);
                    wxPen pen(*wxBLUE, 1); // red pen of width 1
                    dc.SetPen(pen);
                    dc.SetBrush(wxBrush( *wxBLUE));
                    dc.DrawRectangle(75+x*40,75+y*40,10,10);
                    dc.SetPen(wxNullPen);
                    dc.SetBrush(wxNullBrush);
                    
                    cout<<"DRAG"<<x<<"  "<<y<<endl;
                }
                drag_++;
                
               
             
                wxPen pen(*wxRED, 1); // red pen of width 1
                dc.SetPen(pen);
                dc.DrawPoint(event.GetPosition());
                dc.SetPen(wxNullPen);
            }
            if (event.ButtonUp())
            {
            
                cout<<"hello"<<endl;
                dc.DrawRectangle(75+x*40,75+y*40,10,10);
             
                const wxPoint pt2 = wxGetMousePosition();
                cout<<pt2.x<<"  "<<pt2.y<<endl;
                int radius = sqrt(pow((pt1_.x-pt2.x),2)+pow((pt1_.y-pt2.y),2));
                
                int discreteX = floor((pt1_.x - this->GetScreenPosition().x-80)/(40.0));
                int discreteY = floor((pt1_.y-this->GetScreenPosition().y-80)/(40.0));
                 wxClientDC dc1(this);
                // dc1.SetBackgroundMode(wxTRANSPARENT);
               
                dc1.SetBrush(wxBrush( wxTransparentColour,wxTRANSPARENT));
                cout<<radius<<endl;
                wxPen pen(*wxBLUE, 1); // red pen of width 1
                dc1.SetPen(pen);
             
                
                draw_circle(round(radius/40.0),x,y);
                cout<<"radius"<<max_radius*40<<" "<<min_radius*40<<endl;
                dc1.DrawCircle (discreteX*40+80,discreteY*40+80,(max_radius+min_radius)*40/2+5);
                dc1.SetPen(wxNullPen);
           
               

                wxPen pen1(*wxRED, 1); // red pen of width 1
                dc1.SetPen(pen1);        
                dc1.DrawCircle (discreteX*40+80,discreteY*40+80,max_radius*40+10);
                dc1.DrawCircle (discreteX*40+80,discreteY*40+80,min_radius*40-10);
                dc1.SetPen(wxNullPen);


                 drag_=0;
                 x=0;
                 y=0;
                
          
                /* code */
            }
        
         }
        void draw_circle(int r,int xc,int yc)
        {
            int x,y;
            int pk = 3 - 2*r;
	        x=0; y = r;
	        drawCircle(x,y,xc,yc);
            min_radius=2*r;
            max_radius=-1;
	        while(x < y)
	        {
                if(sqrt(pow((x),2)+pow((y),2))>max_radius)
                    {
                        max_radius=sqrt(pow((x),2)+pow((y),2));
                    }
                    if(sqrt(pow((x),2)+pow((y),2))<min_radius)
                    {
                         min_radius=sqrt(pow((x),2)+pow((y),2));
                    }


                if(pk <= 0)
                {
                    pk = pk + (4*x) + 6;
                    drawCircle(++x,y,xc,yc);
                    if(sqrt(pow((x),2)+pow((y),2))>max_radius)
                    {
                        max_radius=sqrt(pow((x),2)+pow((y),2));
                    }
                    if(sqrt(pow((x),2)+pow((y),2))<min_radius)
                    {
                         min_radius=sqrt(pow((x),2)+pow((y),2));
                    }
                    
                }
                else
                {
                    pk = pk + (4*(x-y)) + 10;
                    drawCircle(++x,--y,xc,yc);
                      if(sqrt(pow((x),2)+pow((y),2))>max_radius)
                    {
                        max_radius=sqrt(pow((x),2)+pow((y),2));
                    }
                    if(sqrt(pow((x),2)+pow((y),2))<min_radius)
                    {
                         min_radius=sqrt(pow((x),2)+pow((y),2));
                    }
                    
                }
	        }
        }
        void drawCircle(int x, int y, int xc, int yc)
        {
            wxClientDC dc(this);
            wxPoint origin=dc.GetDeviceOrigin();

            dc.SetDeviceOrigin(origin.x,origin.y);
            wxPen pen(*wxBLUE, 1); // red pen of width 1
            dc.SetPen(pen);
            dc.SetBrush(wxBrush( *wxBLUE));

            dc.DrawRectangle(75+(x+xc)*40,75+(y+yc)*40,10,10);
            dc.DrawRectangle(75+(-x+xc)*40,75+(y+yc)*40,10,10);
            dc.DrawRectangle(75+(x+xc)*40,75+(-y+yc)*40,10,10);
            dc.DrawRectangle(75+(-x+xc)*40,75+(-y+yc)*40,10,10);

            dc.DrawRectangle(75+(y+xc)*40,75+(x+yc)*40,10,10);
            dc.DrawRectangle(75+(y+xc)*40,75+(-x+yc)*40,10,10);
            dc.DrawRectangle(75+(-y+xc)*40,75+(x+yc)*40,10,10);
            dc.DrawRectangle(75+(-y+xc)*40,75+(-x+yc)*40,10,10);
            dc.SetPen(wxNullPen);
            dc.SetBrush(wxNullBrush);
            

            

        }
public:
    wxButton  **btn=nullptr;
    wxGridSizer *grid;
    wxDECLARE_EVENT_TABLE();
    double max_radius;
    double min_radius;


   

};
wxBEGIN_EVENT_TABLE(MainWindow,wxFrame)
    EVT_MOUSE_EVENTS(MainWindow::onMouseClick)
wxEND_EVENT_TABLE()
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