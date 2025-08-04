#include "tic_tac_toe.h"
#include "mainframe.h"


wxIMPLEMENT_APP(TicTacToe);

bool TicTacToe::OnInit() {

    wxInitAllImageHandlers();

    MainFrame* mainFrame = new MainFrame("Another Tic-Tac-Toe");
    mainFrame->SetClientSize(402, 452);
    mainFrame->Center();
    mainFrame->SetBackgroundColour(*wxBLACK);
    mainFrame->Show(true);
    return true;

}
