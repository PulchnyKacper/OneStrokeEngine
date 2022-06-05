#pragma once

#include "ose_device.h"
#include "ose_swap_chain.h"
#include "ose_window.h"
#include <cassert>
#include <memory>
#include <vector>

namespace ose {
    class OseRenderer {
    public:
        OseRenderer(OseWindow& window, OseDevice& device);
        ~OseRenderer();

        OseRenderer(const OseRenderer&) = delete;
        OseRenderer& operator=(const OseRenderer&) = delete;

        VkRenderPass getSwapChainRenderPass() const { return oseSwapChain->getRenderPass(); }
        float getAspectRatio() const { return oseSwapChain->extentAspectRatio(); }
        bool isFrameInProgress() const { return isFrameStarted; }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();
        void endFrame();
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();

        OseWindow& oseWindow;
        OseDevice& oseDevice;
        std::unique_ptr<OseSwapChain> oseSwapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex;
        bool isFrameStarted;
    };
}  // namespace ose