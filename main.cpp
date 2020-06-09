#include <wx/wx.h>
#include <iostream>
#include <cmath>
#define BUTTON_BASE_ID 1
#define FIELDWIDTH 20
#define FIELDHEIGHT 20


using namespace std;
class MainWindow : public wxFrame
{
public:
// Constructor to create the Main Window for the application.
    MainWindow(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(900, 900))
	{
		Centre();
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        btn=new wxButton*[FIELDWIDTH*FIELDHEIGHT];
        grid =new wxGridSizer(20,20,30,30);
        for(int x=0;x<FIELDWIDTH;x++)
        {
            for(int y=0;y<FIELDHEIGHT;y++)
            {
                btn[y*FIELDWIDTH+x]=new wxButton(this, BUTTON_BASE_ID+(y*FIELDWIDTH+x));
                grid->Add(btn[y*FIELDWIDTH+x],1,wxEXPAND|wxALL);
                btn[y*FIELDWIDTH+x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&MainWindow::onButtonClicked,this);
            }
        }
        this->SetSizer(grid);
        grid->Layout();
	}
    void onButtonClicked(wxCommandEvent &evt)
    {
         const wxPoint pt1 = wxGetMousePosition();
         cout<<pt1.x - this->GetScreenPosition().x<<" "<<pt1.y - this->GetScreenPosition().y<<endl;
    }

    void onMouseClick(wxMouseEvent& event)
    {
            static int drag_=0;
            static int x=0;
            static int y=0;
            static wxPoint pt1_; 
            static const wxPoint pt2; 
            wxClientDC dc(this);
            wxPoint origin=dc.GetDeviceOrigin();
            dc.SetBackgroundMode(wxTRANSPARENT);
            dc.SetDeviceOrigin(origin.x,origin.y);

      
            if (event.Dragging())
            {
                if(drag_==0)
                {
                    // dc.Clear();
                    const wxPoint pt1 = wxGetMousePosition();
                    pt1_=pt1;
                    x = floor((pt1.x - this->GetScreenPosition().x)*(20.0/800.0));
                    y = floor((pt1.y-this->GetScreenPosition().y)*(20.0/800.0));
                    btn[x*FIELDWIDTH+y]->SetBackgroundColour(*wxBLUE);
                    cout<<x<<"  "<<y<<endl;
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
                btn[x*FIELDWIDTH+y]->SetBackgroundColour(wxColour(255,255,255));
                cout<<pt1_.x<<"  "<<pt1_.y<<endl;
                const wxPoint pt2 = wxGetMousePosition();
                cout<<pt2.x<<"  "<<pt2.y<<endl;
                int radius = sqrt(pow((pt1_.x-pt2.x),2)+pow((pt1_.y-pt2.y),2));
                
                int discreteX = round((pt1_.x - this->GetScreenPosition().x)*(20.0/800.0));
                int discreteY = round((pt1_.y-this->GetScreenPosition().y)*(20.0/800.0));
                 wxClientDC dc1(this);
                // dc1.SetBackgroundMode(wxTRANSPARENT);
               
                dc1.SetBrush(wxBrush( wxTransparentColour,wxTRANSPARENT));
                cout<<radius<<endl;
                 wxPen pen(*wxBLUE, 1); // red pen of width 1
                dc1.SetPen(pen);
             
                dc1.DrawCircle (discreteX*40+5,discreteY*40+30,radius);
                dc1.SetPen(wxNullPen);
                draw_circle(round(radius/40),x,y);

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
    
	        while(x < y)
	        {
                if(pk <= 0)
                {
                    pk = pk + (4*x) + 6;
                    drawCircle(++x,y,xc,yc);
                }
                else
                {
                    pk = pk + (4*(x-y)) + 10;
                    drawCircle(++x,--y,xc,yc);
                }
	        }
        }
        void drawCircle(int x, int y, int xc, int yc)
        {
            btn[(x+xc)*FIELDWIDTH+y+yc]->SetBackgroundColour(*wxBLUE);
            btn[(-x+xc)*FIELDWIDTH+y+yc]->SetBackgroundColour(*wxBLUE);
            btn[(x+xc)*FIELDWIDTH-y+yc]->SetBackgroundColour(*wxBLUE);
            btn[(-x+xc)*FIELDWIDTH-y+yc]->SetBackgroundColour(*wxBLUE);

            btn[(y+xc)*FIELDWIDTH+x+yc]->SetBackgroundColour(*wxBLUE);
            btn[(y+xc)*FIELDWIDTH-x+yc]->SetBackgroundColour(*wxBLUE);
            btn[(-y+xc)*FIELDWIDTH+x+yc]->SetBackgroundColour(*wxBLUE);
            btn[(-y+xc)*FIELDWIDTH-x+yc]->SetBackgroundColour(*wxBLUE);
            

        }
public:
    wxButton  **btn=nullptr;
    wxGridSizer *grid;
    wxDECLARE_EVENT_TABLE();
    int max_radius;
    int min_radius;


   

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