#include "cLoginFrame.h"
#include "string_utils.h"
#include "cMainFrame.h"
wxBEGIN_EVENT_TABLE(cLoginFrame, wxFrame)
EVT_BUTTON(1, OnButtonClicked)
wxEND_EVENT_TABLE()

cLoginFrame::cLoginFrame(std::shared_ptr<Service> service) : wxFrame(nullptr,wxID_ANY,"Login",wxPoint(30,30),wxSize(225,190),wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN) {
	CentreOnScreen();
	_service = service;
	SetBackgroundColour(*wxWHITE);
	_labelLogin = new wxStaticText(this, wxID_ANY,"Login",wxPoint(20,10));
	_txtLogin = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 30), wxSize(190, 20));
	_labelPassword = new wxStaticText(this, wxID_ANY, "Password", wxPoint(20, 60));
	_txtPassword = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 80), wxSize(190, 20),wxTE_PASSWORD);
	_buttonLogin = new wxButton(this, 1, "Login", wxPoint(60, 110), wxSize(90, 25));
	_buttonLogin->SetBackgroundColour(wxColour(*wxWHITE));
}
cLoginFrame::~cLoginFrame() {

}
void cLoginFrame::OnButtonClicked(wxCommandEvent &evt) {
	wxMessageDialog* err_msg;
	std::string login = std::string((_txtLogin->GetValue()).mb_str());
	std::string passwd = std::string((_txtPassword->GetValue()).mb_str());
	trim(login);
	trim(passwd);
	if (login.compare("")) {
		if (passwd.compare("")) {
			if (_service->login(login, passwd)) {
				
				cMainFrame* mainFrame = new cMainFrame(_service);
				mainFrame->Show();
				this->Close();
			}
			else {
				err_msg = new wxMessageDialog(this, "Failed to login, try again!", "Login error");
				err_msg->ShowModal();
			}
		}
		else {
			err_msg = new wxMessageDialog(this, "Enter password!", "Login error");
			err_msg->ShowModal();
		}
	}
	else {
		err_msg = new wxMessageDialog(this, "Enter login!", "Login error");
		err_msg->ShowModal();
	}
	evt.Skip();
}