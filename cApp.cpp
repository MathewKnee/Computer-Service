#include "cApp.h"
wxIMPLEMENT_APP(cApp);
cApp::cApp() {

}
cApp::~cApp() {

}
bool cApp::OnInit() {
	_service = std::shared_ptr<Service>(new Service("tcp://127.0.0.1:3306","root",""));
	_loginFrame = new cLoginFrame(_service);
	_loginFrame->Show();
	return true;
}