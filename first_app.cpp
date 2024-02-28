#include "first_app.hpp"

#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

namespace huhu
{
    FirstApp::FirstApp()
    {
        loadGameObjects();
    }

    FirstApp::~FirstApp() {}

    void FirstApp::run()
    {
        SimpleRenderSystem simpleRenderSystem{huhuDevice, huhuRenderer.getSwapChainRenderPass()};

        while (!huhuWindow.shouldClose())
        {
            glfwPollEvents();

            if (auto commandBuffer = huhuRenderer.beginFrame())
            {
                huhuRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
                huhuRenderer.endSwapChainRenderPass(commandBuffer);
                huhuRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(huhuDevice.device());
    }

    // temporary helper function, created 1x1x1 cube centered at offset
    std::unique_ptr<HuhuModel> createCubeModel(HuhuDevice &device, glm::vec3 offset)
    {
        std::vector<HuhuModel::Vertex> vertices
        {
            // left face (white)
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},

            // right face (yellow)
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},

            // top face (orange, remember y axis points down)
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},

            // bottom face (red)
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},

            // nose face (blue)
            {{-.5f, -.5f, .5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, .5f}, {.1f, .1f, .8f}},
            {{-.5f, .5f, .5f}, {.1f, .1f, .8f}},
            {{-.5f, -.5f, .5f}, {.1f, .1f, .8f}},
            {{.5f, -.5f, .5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, .5f}, {.1f, .1f, .8f}},

            // tail face (green)
            {{-.5f, -.5f, -.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f, -.5f}, {.1f, .8f, .1f}},
            {{-.5f, -.5f, -.5f}, {.1f, .8f, .1f}},
            {{.5f, -.5f, -.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -.5f}, {.1f, .8f, .1f}}
        };
        for(auto &v : vertices) { v.position += offset; }
        return std::make_unique<HuhuModel>(device, vertices);
    }

    void FirstApp::loadGameObjects()
    {
        std::shared_ptr<HuhuModel> huhuModel = createCubeModel(huhuDevice, {.0f, .0f, .0f});

        auto cube = HuhuGameObject::createGameObject();
        cube.model = huhuModel;
        cube.transform.translation = {.0f, .0f, .5f};
        cube.transform.scale = {.5f, .5f, .5f};

        gameObjects.push_back(std::move(cube));
    }
}