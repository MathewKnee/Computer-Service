#pragma once
#include "wx/wx.h"
#include "Service.h"
#include "wx/listctrl.h"
class cMainFrame : public wxFrame
{
public:
	cMainFrame(std::shared_ptr<Service>);
	~cMainFrame();
protected:
	void onAddUser(wxCommandEvent& event);
	void onRemoveUser(wxCommandEvent& event);
	void onShowUsers(wxCommandEvent& event);
	void onShowPerformance(wxCommandEvent& event);
	void onShowDelayed(wxCommandEvent& event);
	void onPlaceOrder(wxCommandEvent& event);
	void onAssignOrder(wxCommandEvent& event);
	void onShowAllOrders(wxCommandEvent& event);
	void onRemoveOrder(wxCommandEvent& event);

	void onTakeOrder(wxCommandEvent& event);
	void onMarkAsFinished(wxCommandEvent& event);
private:
	std::shared_ptr<Service> service;

	wxListCtrl* orders;
	wxListCtrl* my_orders;
	wxListCtrl* users;
	
	wxButton* addUserButton;
	wxButton* removeUserButton;
	wxButton* showUsersButton;
	wxButton* removeOrderButton;

	wxButton* showPerfomanceRateButton;
	wxButton* showDelayedOrdersButton;
	wxButton* placeOrderButton;
	wxButton* assignOrderButton;
	wxButton* showAllOrdersButton;

	wxButton* takeOrderButton;
	wxButton* markAsFinishedButton;

};

