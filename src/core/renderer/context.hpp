#pragma once

#include <memory>

#include "renderer.hpp"

namespace trimana::core {

	class context {
	public:
		context() = default;
		virtual ~context() = default;

		virtual bool make_context() = 0;
		virtual void swap_buffers() = 0;
		virtual void change_swap_interval(uint32_t interval) = 0;

	public:
		class context_builder {
		private:
			context_builder() = default;
			~context_builder() = default;

		public:
			static std::shared_ptr<context> create(void* native_window, rendering_api api);
		};
	};
}