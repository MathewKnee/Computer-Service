#include "cAddOrderFrame.h"

cAddOrderFrame::cAddOrderFrame(std::shared_ptr<Service> serv) : wxFrame(nullptr, wxID_ANY, "Add User", wxDefaultPosition, wxSize(225, 190), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN) {
	CentreOnScreen();
	service = serv;
	SetBackgroundColour(*wxWHITE);
	device_label = new wxStaticText(this, wxID_ANY, "Device", wxPoint(20, 10));
	device_txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 30), wxSize(190, 20));
	desc_label = new wxStaticText(this, wxID_ANY, "Description", wxPoint(20, 60));
	desc_txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 80), wxSize(190, 20));
	add = new wxButton(this, 1, "Add Order", wxPoint(60, 110), wxSize(90, 25));
	add->SetBackgroundColour(wxColour(*wxWHITE));
	double performance = service->showPerformanceRate();
	if (performance > 8.0) {
		wxMessageDialog* err_msg = new wxMessageDialog(this, "Order might take more time to complete!", "Overload");
		err_msg->ShowModal();
	}
	Connect(1, wxEVT_BUTTON, wxCommandEventHandler(cAddOrderFrame::onAdd));
}
cAddOrderFrame::~cAddOrderFrame() {

}
void cAddOrderFrame::onAdd(wxCommandEvent& WXUNUSED(event)) {
	std::string device = std::string(device_txt->GetValue().mb_str());
	std::string desc = std::string(desc_txt->GetValue().mb_str());
	
	if (device.compare("")) {
		if (desc.compare("")) {
			std::shared_ptr<Order> new_order = std::shared_ptr<Order>(new Order(device, "", service->curr_User->id, 0, desc));
			(*service) += new_order;
			this->Close();
		}
		else {
			wxMessageDialog* err_msg = new wxMessageDialog(this, "Enter description!", "Input Error");
			err_msg->ShowModal();
		}
	}
	else {
		wxMessageDialog* err_msg = new wxMessageDialog(this, "Enter device!", "Input Error");
		err_msg->ShowModal();
	}
}