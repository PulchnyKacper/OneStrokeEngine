#pragma once

#include "ose_window.h"
#include "ose_model.h"
#include "ose_pipeline.h"
#include "ose_device.h"
#include "ose_renderer.h"
#include "ose_object_base.h"
#include <memory>
#include <vector>

namespace ose {
	class GameHandler {
	public:
		static constexpr int WIDTH = 1920;
		static constexpr int HEIGHT = 1280;

		GameHandler();
		~GameHandler();

		GameHandler(const GameHandler&) = delete;
		GameHandler& operator=(const GameHandler&) = delete;

		void run();

	private:
		void loadGameObjects();

		OseWindow oseWindow{ WIDTH, HEIGHT, "Vulkan Tutorial" };
		OseDevice oseDevice{ oseWindow };
		OseRenderer oseRenderer{ oseWindow, oseDevice };
		std::vector<OseGameObject> gameObjects;
	};
} 