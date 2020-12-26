#include "Order.h"
Order::Order(std::string device_, std::string placed_, int client_id_, int state_, std::string description_) {
	device = device_;
	placed = placed_;
	client_id = client_id_;
	state = state_;
	description = description_;
}