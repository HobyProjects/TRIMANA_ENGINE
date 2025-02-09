#include "core_pch.hpp"

namespace TE::Core
{
	static RENDERING_API s_API = RENDERER_API_OPENGL;

	void Renderer::Init()
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::Init();
				break;
			}
			case RENDERER_API_VULKAN:
			{
				TE_ASSERT(false, "Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				TE_ASSERT(false, "DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Renderer::Quit()
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::Quit();
				break;
			}
			case RENDERER_API_VULKAN:
			{
				TE_ASSERT(false, "Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				TE_ASSERT(false, "DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	RENDERING_API Renderer::API()
	{
		return s_API;
	}

	void Renderer::ChangeAPI(RENDERING_API api)
	{
		//[TODO]: Need to think about how to handle this
	}

	void Renderer::Clear()
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::Clear();
				break;
			}
			case RENDERER_API_VULKAN:
			{
				TE_ASSERT(false, "Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				TE_ASSERT(false, "DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Renderer::ClearColor(const glm::vec4& color)
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::ClearColor(color);
				break;
			}
			case RENDERER_API_VULKAN:
			{
				TE_ASSERT(false, "Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				TE_ASSERT(false, "DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Renderer::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::SetViewport(x, y, width, height);
				break;
			}
			case RENDERER_API_VULKAN:
			{
				TE_ASSERT(false, "Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				TE_ASSERT(false, "DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}

	void Renderer::Draw(uint32_t indicesCount)
	{
		switch( s_API )
		{
			case RENDERER_API_OPENGL:
			{
				OpenGL_Renderer::Draw(indicesCount);
				break;
			}
			case RENDERER_API_VULKAN:
			{
				TE_ASSERT(false, "Vulkan renderer is not implemented yet");
				break;
			}
			case RENDERER_API_DIRECTX:
			{
				TE_ASSERT(false, "DirectX renderer is not implemented yet");
				break;
			}
			default:
			{
				break;
			}
		};
	}


	////////////////////////////////////////////////////////////////////////////////////
	///							     BATCH RENDERER 2D                               ///
	////////////////////////////////////////////////////////////////////////////////////

	static const uint32_t MAX_QUADS						= 10000;
	static const uint32_t MAX_VERTICES					= MAX_QUADS * 4;
	static const uint32_t MAX_INDICES					= MAX_QUADS * 6;
	static const uint32_t MAX_TEXTURE_SLOTS				= 32;
	static const uint32_t MAX_QUAD_VERTEX_COUNT			= 4;
	static const glm::vec4 DEFAULT_COLOR				= { 1.0f, 1.0f, 1.0f, 1.0f };
	static const glm::vec2 DEFAULT_TEX_COORDS[]			= { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexIndex;
		float TilingFactor;
	};

	struct BatchData
	{
		std::shared_ptr<VertexArray> QuadVAO{ nullptr };
		std::shared_ptr<VertexBuffer> QuadVBO{ nullptr };
		std::shared_ptr<IndexBuffer> QuadIBO{ nullptr };

		std::shared_ptr<Texture2D> PlainTexture{ nullptr };
		uint32_t PlainTextureSlot{ 0 };
		uint32_t IndexCount{ 0 };

		Vertex* QuadBuffer{ nullptr };
		Vertex* QuadBufferPtr{ nullptr };

		std::shared_ptr<ShaderProgram> BatchShader{ nullptr };
		std::array<std::shared_ptr<Texture2D>, MAX_TEXTURE_SLOTS> TextureSlots;
		uint32_t TextureSlotIndex{ 1 };

		BatchRenderer2D::RendererStatus Status;
		glm::vec4 QuadVertexPositions [MAX_QUAD_VERTEX_COUNT];

	}; static BatchData s_BatchData;

	void BatchRenderer2D::Restart()
	{
		End();
		s_BatchData.QuadBufferPtr = s_BatchData.QuadBuffer;
		s_BatchData.IndexCount = 0;
		s_BatchData.TextureSlotIndex = 1;
	}

	void BatchRenderer2D::Init()
	{
		s_BatchData.QuadBuffer = new Vertex[MAX_QUADS];
		s_BatchData.QuadVBO = CreateVertexBuffer(MAX_VERTICES * sizeof(Vertex));
		s_BatchData.QuadVBO->SetLayout({
			{"a_Position", BUFFER_COMPO_XYZ, BUFFER_STRIDE_F3, false},
			{"a_Color", BUFFER_COMPO_RGBA, BUFFER_STRIDE_F4, false},
			{"a_Texcoord", BUFFER_COMPO_UV, BUFFER_STRIDE_F2, false},
			{"a_TexIndex", BUFFER_COMPO_X, BUFFER_STRIDE_F1, false},
			{"a_TilingFactor", BUFFER_COMPO_X, BUFFER_STRIDE_F1, false}
		});

		uint32_t indices [MAX_INDICES];
		uint32_t offset = 0;
		for( uint32_t i = 0; i < MAX_INDICES; i += 6 )
		{
			indices [i + 0] = offset + 0;
			indices [i + 1] = offset + 1;
			indices [i + 2] = offset + 2;

			indices [i + 3] = offset + 2;
			indices [i + 4] = offset + 3;
			indices [i + 5] = offset + 0;

			offset += 4;
		}

		s_BatchData.QuadIBO = CreateIndexBuffer(indices, MAX_INDICES);
		s_BatchData.QuadVAO = CreateVertexArray();

		s_BatchData.QuadVAO->EmplaceVtxBuffer(s_BatchData.QuadVBO);
		s_BatchData.QuadVAO->EmplaceIdxBuffer(s_BatchData.QuadIBO);

		for( uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++ )
			s_BatchData.TextureSlots [i] = nullptr;

		s_BatchData.PlainTexture = CreateTexture2D(1, 1);
		s_BatchData.TextureSlots [0] = s_BatchData.PlainTexture;

		s_BatchData.QuadVertexPositions [0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_BatchData.QuadVertexPositions [1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_BatchData.QuadVertexPositions [2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_BatchData.QuadVertexPositions [3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		s_BatchData.BatchShader = CreateShaderProgram("BatchRenderer2D", 
													  std::filesystem::path("res/shaders/Batch2DVertex.glsl"), 
													  std::filesystem::path("res/shaders/Batch2DFragment.glsl"));
	}

	void BatchRenderer2D::Quit()
	{
		delete[] s_BatchData.QuadBuffer;
	}

	void BatchRenderer2D::Begin(const Camera2D& camera)
	{
		s_BatchData.BatchShader->Bind();
		s_BatchData.BatchShader->SetUniform("u_MVP", camera.GetViewProjectionMatrix());
		uint32_t texture_location = s_BatchData.BatchShader->GetUniformLocation("u_Textures");
		int32_t samplers [MAX_TEXTURE_SLOTS];

		for( uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++ )
			samplers [i] = i;

		if(s_API == RENDERER_API_OPENGL)
			glUniform1iv(texture_location, MAX_TEXTURE_SLOTS, samplers);

		s_BatchData.QuadBufferPtr = s_BatchData.QuadBuffer;
	}

	void BatchRenderer2D::Begin(const Camera2D& camera, const glm::mat4& transform)
	{
		glm::mat4 MVP = camera.GetProjection() * glm::inverse(transform);
		s_BatchData.BatchShader->Bind();
		s_BatchData.BatchShader->SetUniform("u_MVP", MVP);

		uint32_t texture_location = s_BatchData.BatchShader->GetUniformLocation("u_Textures");
		int32_t samplers [MAX_TEXTURE_SLOTS];
		for( uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++ )
			samplers [i] = i;

		if(s_API == RENDERER_API_OPENGL)
			glUniform1iv(texture_location, MAX_TEXTURE_SLOTS, samplers);

		s_BatchData.QuadBufferPtr = s_BatchData.QuadBuffer;
	}

	void BatchRenderer2D::End()
	{
		GLsizeiptr size = (uint8_t*) s_BatchData.QuadBufferPtr - (uint8_t*) s_BatchData.QuadBuffer;
		s_BatchData.QuadVBO->Bind();
		s_BatchData.QuadVBO->SetData(s_BatchData.QuadBuffer, size);
		Flush();
	}

	void BatchRenderer2D::Flush()
	{
		for( uint32_t i = 0; i < s_BatchData.TextureSlotIndex; i++ )
		{
			s_BatchData.TextureSlots [i]->Bind(i);
		}

		s_BatchData.QuadVAO->Bind();
		Renderer::Draw(s_BatchData.IndexCount);

		s_BatchData.Status.DrawCount++;
		s_BatchData.IndexCount = 0;
		s_BatchData.TextureSlotIndex = 1;
	}

	void BatchRenderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(pos, size, color, s_BatchData.PlainTexture, 0.0f, 1.0f);
	}

	void BatchRenderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		DrawQuad(pos, size, color, s_BatchData.PlainTexture, rotation, 1.0f);
	}

	void BatchRenderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture2D> texture)
	{
		DrawQuad(pos, size, DEFAULT_COLOR, texture, 0.0f, 1.0f);
	}

	void BatchRenderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture2D> texture, float rotation)
	{
		DrawQuad(pos, size, DEFAULT_COLOR, texture, rotation, 1.0f);
	}

	void BatchRenderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture, float rotation)
	{
		DrawQuad(pos, size, color, texture, rotation, 1.0f);
	}

	void BatchRenderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, const std::shared_ptr<Texture2D> texture, float rotation, float tillingFactor)
	{
		if( s_BatchData.IndexCount >= MAX_INDICES || s_BatchData.TextureSlotIndex >= MAX_TEXTURE_SLOTS )
		{
			Restart();
		}

		float texture_index = 0.0f;
		for( uint32_t i = 1; i < s_BatchData.TextureSlotIndex; i++ )
		{
			if( s_BatchData.TextureSlots [i] == texture )
			{
				texture_index = static_cast<float>( i );
				break;
			}
		}

		if( texture_index == 0.0f )
		{
			texture_index = static_cast<float>( s_BatchData.TextureSlotIndex );
			s_BatchData.TextureSlots [s_BatchData.TextureSlotIndex] = texture;
			s_BatchData.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
			glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for( uint32_t i = 0; i < MAX_QUAD_VERTEX_COUNT; i++ )
		{
			s_BatchData.QuadBufferPtr->Position = transform * s_BatchData.QuadVertexPositions [i];
			s_BatchData.QuadBufferPtr->Color = color;
			s_BatchData.QuadBufferPtr->TexCoords = DEFAULT_TEX_COORDS [i];
			s_BatchData.QuadBufferPtr->TexIndex = texture_index;
			s_BatchData.QuadBufferPtr->TilingFactor = tillingFactor;
			s_BatchData.QuadBufferPtr++;
		}

		s_BatchData.IndexCount += 6;
		s_BatchData.Status.QuadCount++;
	}

	const BatchRenderer2D::RendererStatus& BatchRenderer2D::Status()
	{
		return s_BatchData.Status;
	}

	void BatchRenderer2D::StatusReset()
	{
		s_BatchData.Status.DrawCount = s_BatchData.Status.QuadCount = 0;
	}
}