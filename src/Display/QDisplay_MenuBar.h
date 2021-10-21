#pragma once

#include <imgui.h>
#include <fstream>
#include <L2DFileDialog.h>
#include "../Handlers/DataEngine/DataEngine.h"

static std::string fileName;
static std::stringstream logFileBuffer;
bool fileDialogOpen = false;
bool logFileOpen = false;

/*
 * Popup for displaying log file output
 */
void QDisplay_LogFile() {
	if (logFileOpen) {

		ImGui::Begin("Log");

		// TODO: Text cuts long strings, TextUnformatted crashes, find workaround
		ImGui::Text("%s", logFileBuffer.str().c_str());

		if (ImGui::Button("Close")) {
			logFileOpen = false;
		}

		ImGui::End();
	}
}

/*
 * Popup for selecting CSV files for the data engine
 *
 * @param dEngine - reference to DataEngine
 */
void QDisplay_FileDialog(DataEngine* dEngine) {

	if (fileDialogOpen) {
		// Once selection has been made parse results
		if (FileDialog::fileDialogOpen) {
			FileDialog::ShowFileDialog(&fileDialogOpen, fileName);
		} else {
			if (!fileName.empty()) {
				dEngine->loadData(fileName, FileDialog::file_source_selection);
			}
			fileDialogOpen = false;
		}
	}
}

/*
 * Main Menu renderer, contains logic for showing additional display items
 *
 * @param dEngine - reference to DataEngine
 */
void QDisplay_MainMenu(DataEngine* dEngine) {

    if(ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            if(ImGui::MenuItem("Import CSV")) {
				fileDialogOpen = true;
				FileDialog::fileDialogOpen = true;
            }

			if (ImGui::MenuItem("Edit Bots")) {
				// TODO: open bots.json programmatically
			}

			if (ImGui::MenuItem("Open Log")) {
				// Set log flags and clear bugger
				logFileOpen = true;
				logFileBuffer.str(std::string());

				std::ifstream log;
				log.open("QLog.txt");
				logFileBuffer << log.rdbuf();
				log.close();
			}

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

	// These will only render if their corresponding flags are set
	QDisplay_LogFile();
	QDisplay_FileDialog(dEngine);
}