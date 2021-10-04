#include "tab.h"

FS::Internal::Coding::Tab::Tab(const FD::ProjectRead* const projectRead)
	: projectRead(projectRead)
{
	GLog.add<FD::Log::Type::None>("Construct Coding::TabScene.");

}

FS::Internal::Coding::Tab::~Tab() noexcept {
	try {
		GLog.add<FD::Log::Type::None>("Destruct Coding::TabScene.");
	}
	catch (const std::exception& e) {
		try {
			std::cerr << e.what() << std::endl;
			abort();
		}
		catch (...) {
			abort();
		}
	}
	catch (...) {
		abort();
	}
}

void FS::Internal::Coding::Tab::call() {
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(ImGui::GetStyle().FramePadding.x, 0.0f));

	ImGui::Begin("CodingTab", &windowCloseFlag);
	
	ImGui::PushItemWidth(ImGui::GetWindowSize().x - (2.0f * ImGui::GetStyle().WindowPadding.x));


	ImGui::PopItemWidth();

	ImGui::End();

	ImGui::PopStyleVar();

	checkWindowShouldClose();
}

void FS::Internal::Coding::Tab::checkWindowShouldClose() {
	if (this->windowCloseFlag) {
		std::cout << "a";
	}
}




