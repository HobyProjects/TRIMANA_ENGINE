#include "events_receiver.hpp"
#include "glfw_events_receiver.hpp"

namespace trimana::core {

	std::shared_ptr<events_receiver> events_receiver::events_receiver_builder::create(const std::shared_ptr<window>& window, const event_callback& callback){
		switch (window::window_builder::get_platform_service_api()->api()) {
		case platform_service_apis::glfw_api: 				return std::make_shared<glfw_events_receiver>(window, callback);
		default: 											return nullptr;
		}
	}
}