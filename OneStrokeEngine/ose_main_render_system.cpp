#include "ose_main_render_system.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <array>
#include <cassert>
#include <stdexcept>

namespace ose {

    struct SimplePushConstantData {
        glm::mat4 transform{ 1.f };
        alignas(16) glm::vec3 color{};
    };

    MainRenderSystem::MainRenderSystem(OseDevice& device, VkRenderPass renderPass): oseDevice{ device } {
        createPipelineLayout();
        createPipeline(renderPass);
    }

    MainRenderSystem::~MainRenderSystem() {
        vkDestroyPipelineLayout(oseDevice.device(), pipelineLayout, nullptr);
    }

    void MainRenderSystem::createPipelineLayout() {
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(SimplePushConstantData);

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
        if (vkCreatePipelineLayout(oseDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void MainRenderSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        PipelineConfigInfo pipelineConfig{};
        OsePipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        osePipeline = std::make_unique<OsePipeline>(oseDevice, "Shaders/vert.spv","Shaders/frag.spv", pipelineConfig);
    }

    void MainRenderSystem::renderGameObjects(VkCommandBuffer commandBuffer, std::vector<OseGameObject>& gameObjects, const OseCamera& camera) {
        osePipeline->bind(commandBuffer);

        auto projectionView = camera.getProjection() * camera.getView();

        for (auto& obj : gameObjects) {

            SimplePushConstantData push{};
            push.color = obj.color;
            push.transform = projectionView * obj.transform.mat4();

            vkCmdPushConstants( commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(SimplePushConstantData), &push);
            obj.model->bind(commandBuffer);
            obj.model->draw(commandBuffer);
        }
    }

}