#pragma once
#include "wx/wx.h"
#include "Service.h"

class cLoginFrame : public wxFrame
{
public:
	cLoginFrame(std::shared_ptr<Service>);
	~cLoginFrame();
	std::shared_ptr<Service> _service;
	wxButton* _buttonLogin = nullptr;
	wxStaticText* _labelLogin = nullptr;
	wxStaticText* _labelPassword = nullptr;
	wxTextCtrl* _txtLogin = nullptr;
	wxTextCtrl* _txtPassword = nullptr;
	void OnButtonClicked(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

