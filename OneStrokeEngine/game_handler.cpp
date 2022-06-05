#define GLM_FORCE_RADNIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "ose_main_render_system.h"
#include "ose_user_input.h"
#include "game_handler.h"
#include "ose_camera.h"
#include <array>
#include <chrono>
#include <cassert>
#include <stdexcept>

namespace ose {

    GameHandler::GameHandler() {
        loadGameObjects();
    }

    GameHandler::~GameHandler() {}

    void GameHandler::run() {
        MainRenderSystem mainRenderSystem{ oseDevice, oseRenderer.getSwapChainRenderPass() };
        OseCamera camera{};


        auto viewerObject = OseGameObject::createGameObject();
        OseUserInput cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();
        

        while (!oseWindow.shouldClose()) {
            glfwPollEvents();


            auto newTime = std::chrono::high_resolution_clock::now();
            float aspect = oseRenderer.getAspectRatio();
            float frameTime = std::chrono::duration<float, ::std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.move(oseWindow.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 200.f);

            if (auto commandBuffer = oseRenderer.beginFrame()) {
                oseRenderer.beginSwapChainRenderPass(commandBuffer);
                mainRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                oseRenderer.endSwapChainRenderPass(commandBuffer);
                oseRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(oseDevice.device());
    }

    std::unique_ptr<OseModel> createModel(OseDevice& device, glm::vec3 offset) {

        OseModel::Builder modelBuilder{};
        modelBuilder.vertices = {
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        };
        for (auto& v : modelBuilder.vertices) {
            v.position += offset;
        }

        modelBuilder.indices = { 0,  1,  2,  0,  3,  1,  4};

        return std::make_unique<OseModel>(device, modelBuilder);
    }

    void GameHandler::loadGameObjects() {

        std::shared_ptr<OseModel> oseModel = createModel(oseDevice, { .0f, .0f, .0f });
        auto cube = OseGameObject::createGameObject();
        cube.model = oseModel;
        cube.transform.translation = { .0f, .0f, 3.5f };
        cube.transform.scale = { .5f, .5f, .5f };
        gameObjects.push_back(std::move(cube));


    }
}