#pragma once
#define GLM_FORCE_RADNIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include "ose_device.h"
#include <vector>
#include <stdexcept>


namespace ose {

	class OseModel
	{
	public:

		struct Vertex {
			glm::vec3 position{};
			glm::vec3 color{};


			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
		};
		struct Builder {
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indices{};

		};
		OseModel(OseDevice &device, const OseModel::Builder &builder);
		~OseModel();

		OseModel(const OseModel&) = delete;
		OseModel& operator=(const OseModel&) = delete;

		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);
		void createTextureImage();

	private:

		void createVertexBuffers(const std::vector<Vertex> &vertices);
		void createIndexBuffers(const std::vector<uint32_t>	&indicse);


		bool hasIndexBuffer = false;
		OseDevice& oseDevice;
		VkBuffer vertexBuffer, indexBuffer;
		VkDeviceMemory vertexBufferMemory, indexBufferMemory;
		uint32_t vertexCount, indexCount;

	};

}


