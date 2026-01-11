#pragma once

#include <array>
namespace eng {
	class InputManager {
	private:
		//we want to enforce that this class will only be created and owned by the engine itself so all constructors will be private
		InputManager() = default;
		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager& operator=(const InputManager&) = delete;
		InputManager& operator=(InputManager&&) = delete;

	public:
		void SetKeyPressed(int key, bool pressed);
		bool IsKeyPressed(int Key);

	private:
		//storing key states
		std::array<bool, 256> m_keys = { false };

		//only allow engine to manipulate input manager
		friend class Engine;
	};
}