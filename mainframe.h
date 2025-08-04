#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame {

    public:

        MainFrame(const wxString& title);

    private:

        void OnAbout(wxCommandEvent& event);
        void CreateControls();
        void BindEventHandlers();

        wxMenu *menu;
        wxMenuBar *menuBar;



        void aiMove(int row, int col);
        void calculate();
        void unbindAll();
        void bindAll();
        void winOrdraw(int row, int col, int currentPlayer);
        void resetImg();

        wxPanel* panel;

        wxStaticText* pick;
        wxButton* buttonO;

        wxBitmap x_img;
        wxBitmap o_img;

        wxButton* button11;
        wxButton* button12;
        wxButton* button13;
        wxButton* button21;
        wxButton* button22;
        wxButton* button23;
        wxButton* button31;
        wxButton* button32;
        wxButton* button33;
        wxButton* restartButton;

        void OnButtonO(wxCommandEvent& event);

        void OnButton11(wxCommandEvent& event);
        void OnButton12(wxCommandEvent& event);
        void OnButton13(wxCommandEvent& event);
        void OnButton21(wxCommandEvent& event);
        void OnButton22(wxCommandEvent& event);
        void OnButton23(wxCommandEvent& event);
        void OnButton31(wxCommandEvent& event);
        void OnButton32(wxCommandEvent& event);
        void OnButton33(wxCommandEvent& event);

        void OnRestartButton(wxCommandEvent& event);

};
