#pragma once

#include <imgui.h>
#include <L2DFileDialog.h>

void QDisplay_MainMenu(DataEngine* dEngine) {
    static std::string fileName;

    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Import CSV"))
            {
                FileDialog::fileDialogOpen = true;

                if (FileDialog::fileDialogOpen == true) {
                    FileDialog::ShowFileDialog(&FileDialog::fileDialogOpen, fileName);

                    dEngine->loadData(fileName);
                }
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}