#pragma once

#include <memory>

namespace TE::Core
{
	struct FrameBufferSpecification
	{
		uint32_t Width{ 0 };
		uint32_t Height{ 0 };
		bool SwapChainTarget{ false };
	};

	class IFrameBuffer
	{
		public:
			IFrameBuffer() = default;
			virtual ~IFrameBuffer() = default;

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
			virtual void ResizeFrame(uint32_t width, uint32_t height) = 0;
			virtual uint32_t GetFrameBufferID() const = 0;
			virtual uint32_t GetColorAttachment() const = 0;
			virtual FrameBufferSpecification& GetFrameSpecification() = 0;

		protected:
			virtual void CreateFrame() = 0;
	};

	using FrameBuffer = IFrameBuffer;
	std::shared_ptr<FrameBuffer> CreateFrameBuffer(const FrameBufferSpecification& specification);
}