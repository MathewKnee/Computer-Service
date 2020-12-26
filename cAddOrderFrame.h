#pragma once
#include "wx/wx.h"
#include "Service.h"
#include "Order.h"
class cAddOrderFrame : public wxFrame
{
public:
	cAddOrderFrame(std::shared_ptr<Service> serv);
	~cAddOrderFrame();
	void onAdd(wxCommandEvent& eve);
private:
	std::shared_ptr<Service> service;
	wxTextCtrl* device_txt;
	wxTextCtrl* desc_txt;
	wxButton* add;
	wxStaticText* device_label;
	wxStaticText* desc_label;
};

