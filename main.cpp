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

	while (!glfwWindowShouldClose(QDisplay::GetInstance().getWindow())) {

		QDisplay::clearFrame();

		// Display any captured errors as a modal popup over the top of the screen
        if (ErrorHandler::GetInstance().hasError()) {
            ErrorHandler::GetInstance().displayError();
        }

        // Main menu bar rendering & logic
        QDisplay_MainMenu(&dEngine);

		// Once CSV data has been loaded, additional gui items become available
        if (dEngine.isLoaded()) {

            // Bot Management GUI, attempt to load bots
            if (!bEngine.isLoaded() && bEngine.getValidJSON()) {
                bEngine.loadBots();
            }

			// On invalid JSON throw warning and allow user to edit / reload json file
			if (!bEngine.getValidJSON()) {
				{
					ImGui::Begin("Reload");

					if (ImGui::Button("Edit bots")) {
						// TODO: launch editor for bots.json
					}

					if (ImGui::Button("Reload")) {
						bEngine.setValidJSON(true);
					}
					ImGui::End();
				}
			// Success state, show Bot Management screen and allow for dataEngine to begin processing
			} else {
				{
					ImGui::Begin("Bot Management");
					ImGui::Text("Bots 'R Us!");

					// TODO: display bots to run

					if (ImGui::Button("Start Processing")) {
						dEngine.processData(bEngine);
					}
					ImGui::End();
				}
			}

            // 3. Visualisation
        }

		// Render and catch events
		QDisplay::processFrameAndEvents();
	}

    return 0;
}