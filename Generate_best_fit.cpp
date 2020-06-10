#include <wx/wx.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "Eigen/Dense"
#include "Eigen/StdVector"
#define BUTTON_BASE_ID 1
#define FIELDWIDTH 20
#define FIELDHEIGHT 20

using namespace std;
class MainWindow : public wxFrame
{
public:
    // Constructor to create the Main Window for the application.
    MainWindow(const wxString &title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(900, 900))
    {
        Centre();
       wxPanel *panel = new wxPanel(this, wxID_ANY);
      

        generate = new wxButton(this, 10000, "Generate", wxPoint(10, 10), wxSize(100, 50));

        for (int x = 0; x < FIELDWIDTH; x++)
        {
            for (int y = 0; y < FIELDHEIGHT; y++)
            {

                state_btn[x * FIELDWIDTH + y] = 0;
            }
        }
        
    }
    void onGenerate(wxCommandEvent &evt)
    {
        for (int x = 0; x < FIELDWIDTH; x++)
        {
            for (int y = 0; y < FIELDHEIGHT; y++)
            {
                if (state_btn[x * FIELDWIDTH + y] == 1)
                {
                    samplePoints.push_back(Eigen::Vector2d(round(x * 40 + 80), round(y * 40 + 80)));
                    state_btn[x * FIELDWIDTH + y] = 0;
                }
            }
        }

        float xc, yc;
        double radius;
        solveMinCircle(samplePoints, xc, yc, radius);
        wxClientDC dc_(this);
        wxPoint origin = dc_.GetDeviceOrigin();
        dc_.SetDeviceOrigin(origin.x, origin.y);
        dc_.SetBrush(wxBrush(wxTransparentColour, wxTRANSPARENT));
        wxPen pen(*wxBLUE, 1); // red pen of width 1
        dc_.SetPen(pen);
        dc_.DrawCircle(xc, yc, radius);
        dc_.SetPen(wxNullPen);

        cout << xc << " " << yc << " " << radius << endl;
        first_exec = 1;
        generate_state = 1;
        samplePoints.clear();
        evt.Skip();
    }

    void onMouseClick(wxMouseEvent &event)
    {
        int x, y;
        const wxPoint pt1 = wxGetMousePosition();
        wxClientDC dc(this);
        wxPoint origin = dc.GetDeviceOrigin();
        dc.SetDeviceOrigin(origin.x, origin.y);

        if (first_exec == 0)
        {
            wxClientDC grid_init(this);
            wxPoint origin = grid_init.GetDeviceOrigin();
            grid_init.SetDeviceOrigin(origin.x, origin.y);

            for (int x = 0; x < FIELDWIDTH; x++)
            {
                for (int y = 0; y < FIELDHEIGHT; y++)
                {
                    grid_init.DrawRectangle(75 + x * 40, 75 + y * 40, 10, 10);
                }
            }
            cout << "exec";
            first_exec = 1;
        }

        if (event.ButtonUp())
        {

            if (generate_state == 1)
            {
                
                Refresh();
                generate_state = 0;
                first_exec = 0;

                wxClientDC grid_init(this);
                wxPoint origin = grid_init.GetDeviceOrigin();
                grid_init.SetDeviceOrigin(origin.x, origin.y);

                for (int x = 0; x < FIELDWIDTH; x++)
                {
                    for (int y = 0; y < FIELDHEIGHT; y++)
                    {
                        grid_init.DrawRectangle(75 + x * 40, 75 + y * 40, 10, 10);
                    }
                }
                cout << "here" << endl;
            }

            else
            {

                x = floor((pt1.x - this->GetScreenPosition().x - 80) / (40.0));
                y = floor((pt1.y - this->GetScreenPosition().y - 80) / (40.0));
                if (state_btn[x * FIELDWIDTH + y] == 0)
                {

                    wxPen pen(*wxBLUE, 1); // red pen of width 1
                    dc.SetPen(pen);
                    dc.SetBrush(wxBrush(*wxBLUE));
                    dc.DrawRectangle(75 + x * 40, 75 + y * 40, 10, 10);
                    dc.SetPen(wxNullPen);
                    dc.SetBrush(wxNullBrush);
                    state_btn[x * FIELDWIDTH + y] = 1;
                    cout << "1  " << endl;
                }
                else
                {
                    wxPen pen(*wxBLUE, 1); // red pen of width 1
                    dc.SetPen(pen);
                    dc.SetBrush(wxBrush(wxColour(192, 192, 192)));
                    dc.DrawRectangle(75 + x * 40, 75 + y * 40, 10, 10);
                    dc.SetPen(wxNullPen);
                    dc.SetBrush(wxNullBrush);
                    state_btn[x * FIELDWIDTH + y] = 0;
                    cout << "2  " << endl;
                }
            }
        }
        // btn[x*FIELDWIDTH+y]->SetBackgroundColour(*wxBLUE);
    }

    bool solveMinCircle(const std::vector<Eigen::Vector2d> &points, float &midpointX, float &midpointY, double &radius)
    {
        int length = points.size();
        double x1;
        double x2;
        double x3;
        Eigen::MatrixXd AFill(3, length);
        Eigen::MatrixXd A(length, 3);
        Eigen::VectorXd AFirst(length);
        Eigen::VectorXd ASec(length);
        Eigen::VectorXd AFirstSquared(length);
        Eigen::VectorXd ASecSquared(length);
        Eigen::VectorXd ASquaredRes(length);
        Eigen::VectorXd b(length);
        Eigen::VectorXd c(3);
        bool ok = true;

        if (length > 1)
        {
            for (int i = 0; i < length; i++)
            {
                AFill(0, i) = points[i](0);
                AFill(1, i) = points[i](1);
                AFill(2, i) = 1;
            }

            A = AFill.transpose();

            for (int i = 0; i < length; i++)
            {
                AFirst(i) = A(i, 0);
                ASec(i) = A(i, 1);
            }

            for (int i = 0; i < length; i++)
            {
                AFirstSquared(i) = AFirst(i) * AFirst(i);
                ASecSquared(i) = ASec(i) * ASec(i);
            }

            b = AFirstSquared + ASecSquared;

            c = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);

            x1 = c(0);

            midpointX = x1 * 0.5;
            x2 = c(1);
            midpointY = x2 * 0.5;
            x3 = c(2);
            cout << x1 << " " << x2 << " " << x3 << endl;
            radius = sqrt((x1 * x1 + x2 * x2) / 4 + x3);
        }
        else
        {
            ok = false;
        }

        return ok;
    }

public:
    wxButton **btn = nullptr;
    wxButton *generate = nullptr;
    bool state_btn[FIELDHEIGHT * FIELDWIDTH];
    wxGridSizer *grid;
    wxDECLARE_EVENT_TABLE();
    int x_sum;
    int y_sum;
    int counter;
    bool first_exec = 0;
    bool generate_state = 0;
    std::vector<Eigen::Vector2d> samplePoints;
};
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MOUSE_EVENTS(MainWindow::onMouseClick)
        EVT_BUTTON(10000, MainWindow::onGenerate)
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