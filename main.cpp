#include <string>
#include <iostream>

#include "src/Display/QDisplay.h"
#include "src/Display/FileInput.h"

#include "src/Handlers/DataEngine/DataEngine.h"

int main() {

	DataEngine dEngine;
	GLFWwindow* window = QDisplay::GetInstance().getWindow();

	while (!glfwWindowShouldClose(window)) {

		// Clear Frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. File loading
		QDisplay_LoadFile(&dEngine);

		// 2. Bot management

		// 3. Visualisation

		// Render and catch events
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

    return 0;
}