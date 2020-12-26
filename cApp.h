#pragma once
#include "wx/wx.h"
#include "cLoginFrame.h"
#include "cMainFrame.h"
#include "Service.h"
class cApp : public wxApp
{
public:
	cApp();
	~cApp();
	virtual bool OnInit();
	friend class cLoginFrame;
	friend class cMainFrame;
private:
	std::shared_ptr<Service> _service = nullptr;
	cLoginFrame * _loginFrame = nullptr;
	cMainFrame * _mainFrame = nullptr;
};

