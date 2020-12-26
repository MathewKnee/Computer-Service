#include "cAddUserFrame.h"

cAddUserFrame::cAddUserFrame(std::shared_ptr<Service> serv) : wxFrame(nullptr, wxID_ANY, "Add User", wxDefaultPosition, wxSize(265, 350), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN) {
	CentreOnScreen();
	service = serv;
	SetBackgroundColour(*wxWHITE);
	username_label = new wxStaticText(this, wxID_ANY, "Username", wxPoint(20, 10));
	username_txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 30), wxSize(230, 20));
	password_label = new wxStaticText(this, wxID_ANY, "Password", wxPoint(20, 60));
	password_txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 80), wxSize(230, 20));
	wxArrayString choices;
	choices.Add("Admin");
	choices.Add("Employee");
	choices.Add("Client");
	type = new wxRadioBox(this, wxID_ANY, "Select user type", wxPoint(10, 110), wxDefaultSize, choices, 3, wxRA_HORIZONTAL);
	name_label = new wxStaticText(this, wxID_ANY, "Name", wxPoint(20, 170));
	name_txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 190), wxSize(230, 20));
	surname_label = new wxStaticText(this, wxID_ANY, "Surname", wxPoint(20, 220));
	surname_txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 240), wxSize(230, 20));
	add = new wxButton(this, 1, "Add User", wxPoint(80, 270), wxSize(90, 25));
	add->SetBackgroundColour(wxColour(*wxWHITE));
	Connect(1, wxEVT_BUTTON, wxCommandEventHandler(cAddUserFrame::onAdd));
}
cAddUserFrame::~cAddUserFrame() {

}
void cAddUserFrame::onAdd(wxCommandEvent& WXUNUSED(event)) {
	std::string username = std::string(username_txt->GetValue());
	std::string password = std::string(password_txt->GetValue());
	int type_val = type->GetSelection();
	std::string name = std::string(name_txt->GetValue());
	std::string surname = std::string(surname_txt->GetValue());
	if (username.compare("")) {
		if (password.compare("")) {
			if (type_val!=wxNOT_FOUND) {
				if (name.compare("")) {
					if (surname.compare("")) {
						if (!service->addUser(username, password, type_val, name, surname)) {
							wxMessageDialog* err_msg = new wxMessageDialog(this, "Couldn't add user!", "Database Error");
							err_msg->ShowModal();
						}
					}
					else {
						wxMessageDialog* err_msg = new wxMessageDialog(this, "Enter surname!", "Input Error");
						err_msg->ShowModal();
					}
				}
				else {
					wxMessageDialog* err_msg = new wxMessageDialog(this, "Enter name!", "Input Error");
					err_msg->ShowModal();
				}
			}
			else {
				wxMessageDialog* err_msg = new wxMessageDialog(this, "Choose type!", "Input Error");
				err_msg->ShowModal();
			}
		}
		else {
			wxMessageDialog* err_msg = new wxMessageDialog(this, "Enter password!", "Input Error");
			err_msg->ShowModal();
		}
	}
	else {
		wxMessageDialog* err_msg = new wxMessageDialog(this, "Enter username!", "Input Error");
		err_msg->ShowModal();
	}
	

	this->Close();
}