#include "cMainFrame.h"
#include "admin.h"
#include "employee.h"
#include "client.h"
#include "wx/listbase.h"
#include "cAddOrderFrame.h"
#include "cAddUserFrame.h"

void loadInfo(wxListCtrl * list,std::vector<std::vector<std::string>> data,std::string text) {
    for (int i = 0; i < data[0].size(); i++) {
        wxListItem col;
        col.SetId(i);
        col.SetText(_(data[0][i]));
        list->InsertColumn(i, col);
    }
    for (int i = 0; i < data.size() - 1; i++) {
        wxListItem row;
        row.SetId(i);
        row.SetText(text);
        list->InsertItem(row);
        for (int j = 0; j < data[i].size(); j++) {
            list->SetItem(i, j, data[i + 1][j]);
        }
    }
}

cMainFrame::cMainFrame(std::shared_ptr<Service> service_) : wxFrame(nullptr, wxID_ANY, "Serwis", wxDefaultPosition, wxSize(1100,310), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN) {
    service = service_;
    wxPanel* mainPane = new wxPanel(this);
    if (service->curr_User->type == 0) {
        wxPanel* textPanel1 = new wxPanel(mainPane);
        wxPanel* textPanel2 = new wxPanel(mainPane);
        wxFlexGridSizer* sizer = new wxFlexGridSizer(2,10,10);
        
        wxStaticText* order_txt = new wxStaticText(textPanel1, wxID_ANY, "Orders",wxPoint(10,10));
        wxStaticText* users_txt = new wxStaticText(textPanel2, wxID_ANY, "Users", wxPoint(10,10));
        
        sizer->Add(textPanel1,1,wxEXPAND | wxALL);
        sizer->Add(textPanel2, 1, wxEXPAND | wxALL);
        
        orders = new wxListCtrl(mainPane, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
        loadInfo(orders, service->showOrders(),"Order");
        sizer->Add(orders, 1, wxEXPAND | wxALL, 10);
        
        users = new wxListCtrl(mainPane, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
        loadInfo(users, service->showUsers(),"User");
        sizer->Add(users, 1, wxEXPAND | wxALL, 10);

        wxPanel* order_buttons = new wxPanel(mainPane);
        wxFlexGridSizer * order_buttons_sizer = new wxFlexGridSizer(5, 10, 10);
        placeOrderButton = new wxButton(order_buttons, 1, "Place Order");
        removeOrderButton = new wxButton(order_buttons, 9, "Remove Order");
        assignOrderButton = new wxButton(order_buttons, 2, "Assign Order");
        showDelayedOrdersButton = new wxButton(order_buttons,3, "Show Delayed Orders");
        showAllOrdersButton = new wxButton(order_buttons,4, "Show All Orders");
        order_buttons_sizer->Add(placeOrderButton, 1, wxEXPAND | wxALL);
        order_buttons_sizer->Add(removeOrderButton, 1, wxEXPAND | wxALL);
        order_buttons_sizer->Add(assignOrderButton, 1, wxEXPAND | wxALL);
        order_buttons_sizer->Add(showDelayedOrdersButton, 1, wxEXPAND | wxALL);
        order_buttons_sizer->Add(showAllOrdersButton, 1, wxEXPAND | wxALL);

        order_buttons->SetSizer(order_buttons_sizer);
        
        sizer->Add(order_buttons,1,wxEXPAND|wxALL,10);

        wxPanel* user_buttons = new wxPanel(mainPane);
        wxFlexGridSizer* user_buttons_sizer = new wxFlexGridSizer(4, 10, 10);
        addUserButton = new wxButton(user_buttons, 5, "Add User");
        removeUserButton = new wxButton(user_buttons, 6, "Remove User");
        showUsersButton = new wxButton(user_buttons, 7, "Show Users");
        showPerfomanceRateButton = new wxButton(user_buttons, 8, "Show Performance");
        user_buttons_sizer->Add(addUserButton, 1, wxEXPAND | wxALL);
        user_buttons_sizer->Add(removeUserButton, 1, wxEXPAND | wxALL);
        user_buttons_sizer->Add(showUsersButton, 1, wxEXPAND | wxALL);
        user_buttons_sizer->Add(showPerfomanceRateButton, 1, wxEXPAND | wxALL);
        user_buttons->SetSizer(user_buttons_sizer);

        sizer->Add(user_buttons,1,wxEXPAND | wxALL, 10);
        mainPane->SetSizer(sizer);

        Connect(1, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onPlaceOrder));
        Connect(2, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onAssignOrder));
        Connect(4, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onShowAllOrders));
        Connect(3, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onShowDelayed));
        Connect(5, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onAddUser));
        Connect(6, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onRemoveUser));
        Connect(7, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onShowUsers));
        Connect(8, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onShowPerformance));
        Connect(9, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onRemoveOrder));
    }
    else if (service->curr_User->type == 1) {
        wxPanel* textPanel1 = new wxPanel(mainPane);
        wxPanel* textPanel2 = new wxPanel(mainPane);
        wxFlexGridSizer* sizer = new wxFlexGridSizer(2, 10, 10);

        wxStaticText* order_txt = new wxStaticText(textPanel1, wxID_ANY, "Orders", wxPoint(10, 10));
        wxStaticText* users_txt = new wxStaticText(textPanel2, wxID_ANY, "My Orders", wxPoint(10, 10));

        sizer->Add(textPanel1, 1, wxEXPAND | wxALL);
        sizer->Add(textPanel2, 1, wxEXPAND | wxALL);

        orders = new wxListCtrl(mainPane, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
        loadInfo(orders, service->showOrders(), "Order");
        sizer->Add(orders, 1, wxEXPAND | wxALL, 10);

        my_orders = new wxListCtrl(mainPane, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
        loadInfo(my_orders, service->takenOrders(), "Order");
        sizer->Add(my_orders, 1, wxEXPAND | wxALL, 10);

        wxPanel* order_buttons = new wxPanel(mainPane);
        wxFlexGridSizer* order_buttons_sizer = new wxFlexGridSizer(4, 10, 10);
        takeOrderButton = new wxButton(order_buttons, 1, "Take Order");
        markAsFinishedButton = new wxButton(order_buttons, 2, "Mark as Finished");
        order_buttons_sizer->Add(takeOrderButton, 1, wxEXPAND | wxALL);
        order_buttons_sizer->Add(markAsFinishedButton, 1, wxEXPAND | wxALL);

        order_buttons->SetSizer(order_buttons_sizer);

        sizer->Add(order_buttons, 1, wxEXPAND | wxALL, 10);
        mainPane->SetSizer(sizer);
        this->SetSize(wxSize(800,310));

        Connect(1, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onTakeOrder));
        Connect(2, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onMarkAsFinished));
    }
    else if (service->curr_User->type == 2) {
        wxPanel* textPanel1 = new wxPanel(mainPane);
        
        wxFlexGridSizer* sizer = new wxFlexGridSizer(1, 10, 10);

        wxStaticText* order_txt = new wxStaticText(textPanel1, wxID_ANY, "My Orders", wxPoint(10, 10));
        

        sizer->Add(textPanel1, 1, wxEXPAND | wxALL);
        

        orders = new wxListCtrl(mainPane, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
        loadInfo(orders, service->showOrders(), "Order");
        sizer->Add(orders, 1, wxEXPAND | wxALL, 10);

        

        wxPanel* order_buttons = new wxPanel(mainPane);
        wxFlexGridSizer* order_buttons_sizer = new wxFlexGridSizer(4, 10, 10);
        placeOrderButton = new wxButton(order_buttons, 1, "Place Order");
        showAllOrdersButton = new wxButton(order_buttons, 2, "Show My Orders");
        order_buttons_sizer->Add(placeOrderButton, 1, wxEXPAND | wxALL);
        order_buttons_sizer->Add(showAllOrdersButton, 1, wxEXPAND | wxALL);

        order_buttons->SetSizer(order_buttons_sizer);

        sizer->Add(order_buttons, 1, wxEXPAND | wxALL, 10);
        mainPane->SetSizer(sizer);
        this->SetSize(wxSize(360, 310));

        Connect(1, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onPlaceOrder));
        Connect(2, wxEVT_BUTTON, wxCommandEventHandler(cMainFrame::onShowAllOrders));
    }
    
}
cMainFrame::~cMainFrame() {

}

//Event Handlers
void cMainFrame::onPlaceOrder(wxCommandEvent& WXUNUSED(event)) {
    cAddOrderFrame* ad = new cAddOrderFrame(service);
    ad->Show();
    orders->ClearAll();
    loadInfo(orders, service->showOrders(), "Order");
}
void cMainFrame::onAssignOrder(wxCommandEvent& WXUNUSED(event)) {
    int order_id, emp_id;
    long orderSelectedItem = orders->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (orderSelectedItem != -1) {
        wxListItem selectedItem;
        selectedItem.m_itemId = orderSelectedItem;
        selectedItem.m_col = 0;
        orders->GetItem(selectedItem);
        order_id = atoi(selectedItem.m_text);
        long userSelectedItem = users->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if (userSelectedItem != -1) {
            wxListItem selectedItem;
            selectedItem.m_itemId = userSelectedItem;
            selectedItem.m_col = 0;
            users->GetItem(selectedItem);
            emp_id = atoi(selectedItem.m_text);
            if (emp_id != service->curr_User->id) {
                if (!service->assignOrder(emp_id, order_id)) {
                    wxMessageDialog* err_msg = new wxMessageDialog(this, "Couldn't assign order!", "Error");
                    err_msg->ShowModal();
                }
            }
            else {
                wxMessageDialog* err_msg = new wxMessageDialog(this,"Can't assign order to yourself!", "Error");
                err_msg->ShowModal();
            }
        }
        else {
            wxMessageDialog* err_msg = new wxMessageDialog(this, "Select User!", "Error");
            err_msg->ShowModal();
        }
    }
    else {
        wxMessageDialog* test_msg = new wxMessageDialog(this, "Select Order!", "Error");
        test_msg->ShowModal();
    }

    orders->ClearAll();
    loadInfo(orders, service->showOrders(),"Order");
}
void cMainFrame::onShowAllOrders(wxCommandEvent& WXUNUSED(event)) {
    orders->ClearAll();
    loadInfo(orders, service->showOrders(),"Order");
}
void cMainFrame::onShowDelayed(wxCommandEvent& WXUNUSED(event)) {
    orders->ClearAll();
    loadInfo(orders, service->getDelayedOrders(), "Order");
}
void cMainFrame::onShowUsers(wxCommandEvent& WXUNUSED(event)) {
    users->ClearAll();
    loadInfo(users, service->showUsers(),"User");
}
void cMainFrame::onShowPerformance(wxCommandEvent& WXUNUSED(event)) {
    double rate = service->showPerformanceRate();
    
    if (rate > 8.0) {
        wxMessageBox(wxString::Format("Hire more employees!\nNumber of orders per one employee: %f", rate));
    }
    else {
        wxMessageBox(wxString::Format("Number of orders per one employee: %f", rate));
    }
}
void cMainFrame::onAddUser(wxCommandEvent& WXUNUSED(event)) {
    cAddUserFrame* add = new cAddUserFrame(service);
    add->Show();
}
void cMainFrame::onRemoveUser(wxCommandEvent& WXUNUSED(event)) {
    long userSelectedItem = users->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (userSelectedItem != -1) {
        wxListItem selectedItem;
        selectedItem.m_itemId = userSelectedItem;
        selectedItem.m_col = 0;
        users->GetItem(selectedItem);
        int emp_id = atoi(selectedItem.m_text);
        if (emp_id != service->curr_User->id) {
            service->removeUser(emp_id);
        }
        else {
            wxMessageDialog* err_msg = new wxMessageDialog(this, "Can't remove yourself!", "Error");
            err_msg->ShowModal();
        }
    }
    else {
        wxMessageDialog* err_msg = new wxMessageDialog(this, "Select User!", "Error");
        err_msg->ShowModal();
    }
    users->ClearAll();
    loadInfo(users, service->showUsers(), "User");
}

void cMainFrame::onTakeOrder(wxCommandEvent& WXUNUSED(event)) {
    long orderSelectedItem = orders->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (orderSelectedItem != -1) {
        wxListItem selectedItem;
        selectedItem.m_itemId = orderSelectedItem;
        selectedItem.m_col = 0;
        orders->GetItem(selectedItem);
        int ord_id = atoi(selectedItem.m_text);

        if (!service->assignOrder(service->curr_User->id, ord_id)) {
            wxMessageDialog* err_msg = new wxMessageDialog(this, "Couldn't assign order!", "Error");
            err_msg->ShowModal();
        }
    }
    else {
        wxMessageDialog* err_msg = new wxMessageDialog(this, "Select Order!", "Error");
        err_msg->ShowModal();
    }
    orders->ClearAll();
    my_orders->ClearAll();
    loadInfo(orders, service->showOrders(), "Order");
    loadInfo(my_orders, service->takenOrders(), "Order");
}

void cMainFrame::onMarkAsFinished(wxCommandEvent& WXUNUSED(event)) {
    long orderSelectedItem = my_orders->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (orderSelectedItem != -1) {
        wxListItem selectedItem;
        selectedItem.m_itemId = orderSelectedItem;
        selectedItem.m_col = 0;
        my_orders->GetItem(selectedItem);
        int ord_id = atoi(selectedItem.m_text);

        if (!service->markAsFinished(ord_id)) {
            wxMessageDialog* err_msg = new wxMessageDialog(this, "Couldn't mark order as finished!", "Error");
            err_msg->ShowModal();
        }
    }
    else {
        wxMessageDialog* err_msg = new wxMessageDialog(this, "Select Order!", "Error");
        err_msg->ShowModal();
    }
    orders->ClearAll();
    my_orders->ClearAll();
    loadInfo(orders, service->showOrders(), "Order");
    loadInfo(my_orders, service->takenOrders(), "Order");
}

void cMainFrame::onRemoveOrder(wxCommandEvent& WXUNUSED(event)) {
    std::string device, placed, description;
    int client_id, state;
    long orderSelectedItem = orders->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (orderSelectedItem != -1) {
        wxListItem selectedItem;
        selectedItem.m_itemId = orderSelectedItem;
        selectedItem.m_col = 1;
        orders->GetItem(selectedItem);
        device = selectedItem.m_text;
        selectedItem.m_col = 3;
        orders->GetItem(selectedItem);
        placed = selectedItem.m_text;
        selectedItem.m_col = 2;
        orders->GetItem(selectedItem);
        client_id = std::atoi(selectedItem.m_text);
        selectedItem.m_col = 4;
        orders->GetItem(selectedItem);
        std::string state_txt = std::string(selectedItem.m_text);
        if (!state_txt.compare("waiting")) {
            state = 0;
        }
        else if (!state_txt.compare("taken")) {
            state = 1;
        }
        else if (!state_txt.compare("finished")) {
            state = 2;
        }
        else {
            state = -1;
        }
        selectedItem.m_col = 5;
        orders->GetItem(selectedItem);
        description = selectedItem.m_text;

        std::shared_ptr<Order> order = std::shared_ptr<Order>(new Order(device, placed, client_id, state, description));

        (*service) -= order;
    }
    else {
        wxMessageDialog* test_msg = new wxMessageDialog(this, "Select Order!", "Error");
        test_msg->ShowModal();
    }
    orders->ClearAll();
    loadInfo(orders, service->showOrders(), "Order");
}