#pragma once

#include <imgui_stdlib.h>
#include "../Handlers/DataEngine/DataEngine.h"

void QDisplay_LoadFile(DataEngine* dEngine) {
	static std::string fileName;

	ImGui::Begin("Load File");

	ImGui::Text("Input a CSV data file to parse");
	ImGui::InputText("File Path", &fileName);

	if (ImGui::Button("Load file")) {
		dEngine->loadData(fileName);
	}

	ImGui::End();
}