#pragma once

#include <imgui.h>
#include <L2DFileDialog.h>
#include "../Handlers/DataEngine/DataEngine.h"

static std::string fileName;
bool fileDialogOpen = false;

void QDisplay_MainMenu() {

    if(ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            if(ImGui::MenuItem("Import CSV")) {
				fileDialogOpen = true;
				FileDialog::fileDialogOpen = true;
            }

			if(ImGui::MenuItem("Open Log")) {
				//TODO: open txt file
			}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

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