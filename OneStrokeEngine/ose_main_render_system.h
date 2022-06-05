#pragma once

#include "ose_device.h"
#include "ose_object_base.h"
#include "ose_pipeline.h"
#include "ose_camera.h"
#include <memory>
#include <vector>

namespace ose {
	class MainRenderSystem {
	public:
		MainRenderSystem(OseDevice& device, VkRenderPass renderPass);
		~MainRenderSystem();

		MainRenderSystem(const MainRenderSystem&) = delete;
		MainRenderSystem& operator=(const MainRenderSystem&) = delete;

		void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<OseGameObject>& gameObjects, const OseCamera &camera);

	private:
		void createPipelineLayout();
		void createPipeline(VkRenderPass renderPass);

		OseDevice& oseDevice;

		std::unique_ptr<OsePipeline> osePipeline;
		VkPipelineLayout pipelineLayout;
	};
}