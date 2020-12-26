#pragma once
#include "wx/wx.h"
#include "Service.h"
class cAddUserFrame : public wxFrame
{
public:
	cAddUserFrame(std::shared_ptr<Service>);
	~cAddUserFrame();
	void onAdd(wxCommandEvent&);
private:
	std::shared_ptr<Service> service;
	wxStaticText* username_label;
	wxStaticText* password_label;
	wxStaticText* type_label;
	wxStaticText* name_label;
	wxStaticText* surname_label;

	wxTextCtrl* username_txt;
	wxTextCtrl* password_txt;
	wxRadioBox* type;
	wxTextCtrl* name_txt;
	wxTextCtrl* surname_txt;

	wxButton* add;
};

