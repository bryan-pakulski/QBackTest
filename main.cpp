#include <string>
#include <iostream>

#include "src/Display/QDisplay.h"
#include "src/Display/ErrorHandler.h"
#include "src/Display/QDisplay_MenuBar.h"
#include "src/Handlers/DataEngine/DataEngine.h"
#include "src/Handlers/BotEngine/BotEngine.h"

int main() {

	DataEngine dEngine;
    BotEngine bEngine;
	GLFWwindow* window = QDisplay::GetInstance().getWindow();

	while (!glfwWindowShouldClose(window)) {

		// Clear Frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        if (ErrorHandler::GetInstance().hasError()) {
            ErrorHandler::GetInstance().displayError();
        }

        // Menu Bar
        QDisplay_MainMenu();

		// File Handling
		QDisplay_FileDialog(&dEngine);

        if (dEngine.isLoaded()) {
            // 2. Bot management
            if (!bEngine.isLoaded()) {
                bEngine.loadBots();
            }
            {
                ImGui::Begin("Bot Management");
                ImGui::Text("Bots 'R Us!");

                // TODO: display bots to run

                if (ImGui::Button("Start Processing")) {
                    dEngine.processData();
                }
                ImGui::End();
            }

            // 3. Visualisation
        }

		// Render and catch events
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

    return 0;
}