#include "mainframe.h"
#include "TicTacToeEngine.h"

#include <wx/wx.h>

using namespace std;


enum {

    ID_pick     = 2,
    ID_buttonX  = 111,
    ID_buttonO  = 999,

    ID_button11 = 11,
    ID_button12 = 12,
    ID_button13 = 13,
    ID_button21 = 21,
    ID_button22 = 22,
    ID_button23 = 23,
    ID_button31 = 31,
    ID_button32 = 32,
    ID_button33 = 33,

    ID_restart  = 69

};

int player = ID_buttonX;

bool isButtonBound[9] = {true,true,true,true,true,true,true,true,true};

Move bestMove;


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition,
                                                      wxDefaultSize, wxDEFAULT_FRAME_STYLE &
                                                      ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
    CreateControls();
    BindEventHandlers();

}



void MainFrame::CreateControls() {

     //MENU START
    menu = new wxMenu;
    menu->Append(wxID_ABOUT);

    menuBar = new wxMenuBar;
    menuBar->Append(menu, "About");

    SetMenuBar(menuBar);
    //MENU END

    wxIcon appIcon;
    appIcon.LoadFile("tictactoe.ico", wxBITMAP_TYPE_ICO);
    SetIcon(appIcon);



    panel = new wxPanel(this);

    restartButton = new wxButton(panel, ID_restart, "Play Again", wxPoint(0, 0), wxSize(402, 50));
    restartButton->SetForegroundColour(*wxRED);
    restartButton->Hide();



    pick = new wxStaticText(panel, ID_pick, "Pick ->", wxPoint(10, 2.5), wxDefaultSize);
    pick->SetForegroundColour(*wxRED);

    x_img.LoadFile("X.png", wxBITMAP_TYPE_PNG);
    o_img.LoadFile("O.png", wxBITMAP_TYPE_PNG);

    wxFont font(
        24,
        wxFONTFAMILY_SWISS,
        wxFONTSTYLE_ITALIC,
        wxFONTWEIGHT_BOLD,
        false,
        "Segoe UI"
    );
    pick->SetFont(font);

    buttonO = new wxButton(panel, ID_buttonO, "O", wxPoint(134, 0), wxSize(266, 50));
    buttonO->SetForegroundColour(*wxRED);

    button11 = new wxButton(panel, ID_button11, "", wxPoint(0, 50), wxSize(134, 134));
    button12 = new wxButton(panel, ID_button12, "", wxPoint(134, 50), wxSize(134, 134));
    button13 = new wxButton(panel, ID_button13, "", wxPoint(268, 50), wxSize(134, 134));

    button21 = new wxButton(panel, ID_button21, "", wxPoint(0, 184), wxSize(134, 134));
    button22 = new wxButton(panel, ID_button22, "", wxPoint(134, 184), wxSize(134, 134));
    button23 = new wxButton(panel, ID_button23, "", wxPoint(268, 184), wxSize(134, 134));

    button31 = new wxButton(panel, ID_button31, "", wxPoint(0, 318), wxSize(134, 134));
    button32 = new wxButton(panel, ID_button32, "", wxPoint(134, 318), wxSize(134, 134));
    button33 = new wxButton(panel, ID_button33, "", wxPoint(268, 318), wxSize(134, 134));

    buttonO->SetBackgroundColour(*wxBLACK);
    restartButton->SetBackgroundColour(*wxBLACK);

    button11->SetBackgroundColour(*wxBLACK);
    button12->SetBackgroundColour(*wxBLACK);
    button13->SetBackgroundColour(*wxBLACK);
    button21->SetBackgroundColour(*wxBLACK);
    button22->SetBackgroundColour(*wxBLACK);
    button23->SetBackgroundColour(*wxBLACK);
    button31->SetBackgroundColour(*wxBLACK);
    button32->SetBackgroundColour(*wxBLACK);
    button33->SetBackgroundColour(*wxBLACK);



    CreateStatusBar();
    SetStatusText("Hi");

}

void MainFrame::BindEventHandlers() {

    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);

    restartButton->Bind(wxEVT_BUTTON, &MainFrame::OnRestartButton, this);

    buttonO->Bind(wxEVT_BUTTON, &MainFrame::OnButtonO, this);

    button11->Bind(wxEVT_BUTTON, &MainFrame::OnButton11, this);
    button12->Bind(wxEVT_BUTTON, &MainFrame::OnButton12, this);
    button13->Bind(wxEVT_BUTTON, &MainFrame::OnButton13, this);
    button21->Bind(wxEVT_BUTTON, &MainFrame::OnButton21, this);
    button22->Bind(wxEVT_BUTTON, &MainFrame::OnButton22, this);
    button23->Bind(wxEVT_BUTTON, &MainFrame::OnButton23, this);
    button31->Bind(wxEVT_BUTTON, &MainFrame::OnButton31, this);
    button32->Bind(wxEVT_BUTTON, &MainFrame::OnButton32, this);
    button33->Bind(wxEVT_BUTTON, &MainFrame::OnButton33, this);

}


void MainFrame::OnAbout(wxCommandEvent& event) {

    wxMessageBox(
        "'Another Tic-Tac-Toe'\n"
        "----------------------\n"
        "Developed by M.H. Jim\n\n"
        "Built with C++ and wxWidgets.\n\n"
        ,"About this app",
        wxOK | wxICON_INFORMATION);

}

void MainFrame::OnButtonO(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    player = ID_buttonO;
    button22->SetBitmap(x_img);
    button22->Unbind(wxEVT_BUTTON, &MainFrame::OnButton22, this);
    isButtonBound[4] = false;

    board[1][1] = 'x';

}


void MainFrame::OnButton11(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[0]) {

        if(player == ID_buttonX) {

            button11->SetBitmap(x_img);
            board[0][0] = 'x';

        }
        else if(player == ID_buttonO) {

            button11->SetBitmap(o_img);
            board[0][0] = 'o';

        }

        button11->Unbind(wxEVT_BUTTON, &MainFrame::OnButton11, this);
        isButtonBound[0] = false;

        winOrdraw(0, 0, player);

        calculate();

    }

}

void MainFrame::OnButton12(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[1]) {

        if(player == ID_buttonX) {

            button12->SetBitmap(x_img);
            board[0][1] = 'x';

        }
        else if(player == ID_buttonO) {

            button12->SetBitmap(o_img);
            board[0][1] = 'o';

        }

        button12->Unbind(wxEVT_BUTTON, &MainFrame::OnButton11, this);
        isButtonBound[1] = false;

        winOrdraw(0, 1, player);

        calculate();

    }

}
void MainFrame::OnButton13(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[2]) {

        if(player == ID_buttonX) {

            button13->SetBitmap(x_img);
            board[0][2] = 'x';

        }
        else if(player == ID_buttonO) {

            button13->SetBitmap(o_img);
            board[0][2] = 'o';

        }

        button13->Unbind(wxEVT_BUTTON, &MainFrame::OnButton13, this);
        isButtonBound[2] = false;

        winOrdraw(0, 2, player);

        calculate();

    }

}
void MainFrame::OnButton21(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[3]) {

        if(player == ID_buttonX) {

            button21->SetBitmap(x_img);
            board[1][0] = 'x';

        }
        else if(player == ID_buttonO) {

            button21->SetBitmap(o_img);
            board[1][0] = 'o';

        }

        button21->Unbind(wxEVT_BUTTON, &MainFrame::OnButton21, this);
        isButtonBound[3] = false;

        winOrdraw(1, 0, player);

        calculate();

    }

}
void MainFrame::OnButton22(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[4]) {

        if(player == ID_buttonX) {

            button22->SetBitmap(x_img);
            board[1][1] = 'x';

        }
        else if(player == ID_buttonO) {

            button22->SetBitmap(o_img);
            board[1][1] = 'o';

        }

        button22->Unbind(wxEVT_BUTTON, &MainFrame::OnButton22, this);
        isButtonBound[4] = false;

        winOrdraw(1, 1, player);

        calculate();

    }

}
void MainFrame::OnButton23(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[5]) {

        if(player == ID_buttonX) {

            button23->SetBitmap(x_img);
            board[1][2] = 'x';

        }
        else if(player == ID_buttonO) {

            button23->SetBitmap(o_img);
            board[1][2] = 'o';

        }

        button23->Unbind(wxEVT_BUTTON, &MainFrame::OnButton23, this);
        isButtonBound[5] = false;

        winOrdraw(1, 2, player);

        calculate();

    }

}
void MainFrame::OnButton31(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[6]) {

        if(player == ID_buttonX) {

            button31->SetBitmap(x_img);
            board[2][0] = 'x';

        }
        else if(player == ID_buttonO) {

            button31->SetBitmap(o_img);
            board[2][0] = 'o';

        }

        button31->Unbind(wxEVT_BUTTON, &MainFrame::OnButton31, this);
        isButtonBound[6] = false;

        winOrdraw(2, 0, player);

        calculate();

    }

}
void MainFrame::OnButton32(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[7]) {

        if(player == ID_buttonX) {

            button32->SetBitmap(x_img);
            board[2][1] = 'x';

        }
        else if(player == ID_buttonO) {

            button32->SetBitmap(o_img);
            board[2][1] = 'o';

        }

        button32->Unbind(wxEVT_BUTTON, &MainFrame::OnButton32, this);
        isButtonBound[7] = false;

        winOrdraw(2, 1, player);

        calculate();

    }

}
void MainFrame::OnButton33(wxCommandEvent& event) {

    buttonO->Hide();
    pick->Hide();

    if(isButtonBound[8]) {

        if(player == ID_buttonX) {

            button33->SetBitmap(x_img);
            board[2][2] = 'x';

        }
        else if(player == ID_buttonO) {

            button33->SetBitmap(o_img);
            board[2][2] = 'o';

        }

        button33->Unbind(wxEVT_BUTTON, &MainFrame::OnButton33, this);
        isButtonBound[8] = false;

        winOrdraw(2, 2, player);

        calculate();

    }

}


void MainFrame::winOrdraw(int row, int col, int currentPlayer) {

    if(board[row][col] == checkWinner()) {

        unbindAll();

        if(currentPlayer == player) {
            wxLogStatus("You Won");
            restartButton->Show();
        }

        else {
            wxLogStatus("You Lose");
            restartButton->Show();
        }

    }

    else if(isDraw()) {
        wxLogStatus("Draw");
        restartButton->Show();
    }

}


void MainFrame::aiMove(int row, int col) {

    switch(row) {

        case 0:

            switch(col) {

                case 0:

                    if(player == ID_buttonX) {

                        button11->SetBitmap(o_img);
                        board[0][0] = 'o';

                    }
                    else if(player == ID_buttonO) {

                        button11->SetBitmap(x_img);
                        board[0][0] = 'x';

                    }

                    button11->Unbind(wxEVT_BUTTON, &MainFrame::OnButton11, this);
                    winOrdraw(0, 0, ID_buttonX ^ ID_buttonO ^ player);
                    break;

                case 1:

                    if (player == ID_buttonX) {
                        button12->SetBitmap(o_img);
                        board[0][1] = 'o';
                    }
                    else if (player == ID_buttonO) {
                        button12->SetBitmap(x_img);
                        board[0][1] = 'x';
                    }

                    button12->Unbind(wxEVT_BUTTON, &MainFrame::OnButton12, this);
                    winOrdraw(0, 1, ID_buttonX ^ ID_buttonO ^ player);
                    break;

                case 2:

                    if (player == ID_buttonX) {
                        button13->SetBitmap(o_img);
                        board[0][2] = 'o';
                    }
                    else if (player == ID_buttonO) {
                        button13->SetBitmap(x_img);
                        board[0][2] = 'x';
                    }

                    button13->Unbind(wxEVT_BUTTON, &MainFrame::OnButton13, this);
                    winOrdraw(0, 2, ID_buttonX ^ ID_buttonO ^ player);
                    break;

            }

            break;

        case 1:

            switch(col) {

                case 0:

                    if (player == ID_buttonX) {
                        button21->SetBitmap(o_img);
                        board[1][0] = 'o';
                    }
                    else if (player == ID_buttonO) {
                        button21->SetBitmap(x_img);
                        board[1][0] = 'x';
                    }

                    button21->Unbind(wxEVT_BUTTON, &MainFrame::OnButton21, this);
                    winOrdraw(1, 0, ID_buttonX ^ ID_buttonO ^ player);
                    break;

                case 1:

                    if (player == ID_buttonX) {
                        button22->SetBitmap(o_img);
                        board[1][1] = 'o';
                    }
                    else if (player == ID_buttonO) {
                        button22->SetBitmap(x_img);
                        board[1][1] = 'x';
                    }

                    button22->Unbind(wxEVT_BUTTON, &MainFrame::OnButton22, this);
                    winOrdraw(1, 1, ID_buttonX ^ ID_buttonO ^ player);
                    break;

                case 2:

                    if (player == ID_buttonX) {
                        button23->SetBitmap(o_img);
                        board[1][2] = 'o';
                    }
                    else if (player == ID_buttonO) {
                        button23->SetBitmap(x_img);
                        board[1][2] = 'x';
                    }

                    button23->Unbind(wxEVT_BUTTON, &MainFrame::OnButton23, this);
                    winOrdraw(1, 2, ID_buttonX ^ ID_buttonO ^ player);
                    break;

            }

            break;

        case 2:

            switch(col) {

               case 0:

                    if (player == ID_buttonX) {
                        button31->SetBitmap(o_img);
                        board[2][0] = 'o';
                    }
                    else if (player == ID_buttonO) {
                        button31->SetBitmap(x_img);
                        board[2][0] = 'x';
                    }

                    button31->Unbind(wxEVT_BUTTON, &MainFrame::OnButton31, this);
                    winOrdraw(2, 0, ID_buttonX ^ ID_buttonO ^ player);
                    break;

                case 1:

                    if (player == ID_buttonX) {
                        button32->SetBitmap(o_img);
                        board[2][1] = 'o';
                    }
                    else if (player == ID_buttonO) {
                        button32->SetBitmap(x_img);
                        board[2][1] = 'x';
                    }

                    button32->Unbind(wxEVT_BUTTON, &MainFrame::OnButton32, this);
                    winOrdraw(2, 1, ID_buttonX ^ ID_buttonO ^ player);
                    break;

                case 2:

                    if (player == ID_buttonX) {
                        button33->SetBitmap(o_img);
                        board[2][2] = 'o';
                    }
                    else if (player == ID_buttonO) {
                        button33->SetBitmap(x_img);
                        board[2][2] = 'x';
                    }

                    button33->Unbind(wxEVT_BUTTON, &MainFrame::OnButton33, this);
                    winOrdraw(2, 2, ID_buttonX ^ ID_buttonO ^ player);
                    break;

            }

            break;

    }

}


void MainFrame::calculate() {

    if(player == ID_buttonX) {

        bestMove = findBestMove('o');
        aiMove(bestMove.row, bestMove.col);

    }
    else {

        bestMove = findBestMove('x');
        aiMove(bestMove.row, bestMove.col);

    }

}

void MainFrame::unbindAll() {

    button11->Unbind(wxEVT_BUTTON, &MainFrame::OnButton11, this);
    button12->Unbind(wxEVT_BUTTON, &MainFrame::OnButton12, this);
    button13->Unbind(wxEVT_BUTTON, &MainFrame::OnButton13, this);
    button21->Unbind(wxEVT_BUTTON, &MainFrame::OnButton21, this);
    button22->Unbind(wxEVT_BUTTON, &MainFrame::OnButton22, this);
    button23->Unbind(wxEVT_BUTTON, &MainFrame::OnButton23, this);
    button31->Unbind(wxEVT_BUTTON, &MainFrame::OnButton31, this);
    button32->Unbind(wxEVT_BUTTON, &MainFrame::OnButton32, this);
    button33->Unbind(wxEVT_BUTTON, &MainFrame::OnButton33, this);

}


void MainFrame::bindAll() {

    button11->Bind(wxEVT_BUTTON, &MainFrame::OnButton11, this);
    button12->Bind(wxEVT_BUTTON, &MainFrame::OnButton12, this);
    button13->Bind(wxEVT_BUTTON, &MainFrame::OnButton13, this);
    button21->Bind(wxEVT_BUTTON, &MainFrame::OnButton21, this);
    button22->Bind(wxEVT_BUTTON, &MainFrame::OnButton22, this);
    button23->Bind(wxEVT_BUTTON, &MainFrame::OnButton23, this);
    button31->Bind(wxEVT_BUTTON, &MainFrame::OnButton31, this);
    button32->Bind(wxEVT_BUTTON, &MainFrame::OnButton32, this);
    button33->Bind(wxEVT_BUTTON, &MainFrame::OnButton33, this);

}

void MainFrame::resetImg() {

    button11->SetBitmap(wxNullBitmap);
    button12->SetBitmap(wxNullBitmap);
    button13->SetBitmap(wxNullBitmap);
    button21->SetBitmap(wxNullBitmap);
    button22->SetBitmap(wxNullBitmap);
    button23->SetBitmap(wxNullBitmap);
    button31->SetBitmap(wxNullBitmap);
    button32->SetBitmap(wxNullBitmap);
    button33->SetBitmap(wxNullBitmap);

    button11->Refresh();
    button11->Update();

    button12->Refresh();
    button12->Update();

    button13->Refresh();
    button13->Update();

    button21->Refresh();
    button21->Update();

    button22->Refresh();
    button22->Update();

    button23->Refresh();
    button23->Update();

    button31->Refresh();
    button31->Update();

    button32->Refresh();
    button32->Update();

    button33->Refresh();
    button33->Update();

}

void MainFrame::OnRestartButton(wxCommandEvent& event) {

    initializeBoard();
    bindAll();
    restartButton->Hide();
    pick->Show();
    buttonO->Show();
    resetImg();

    for(int i = 0; i < 9; i++) isButtonBound[i] = true;

    player = ID_buttonX;

    SetStatusText("The more you try the more you draw... Or lose");

}







