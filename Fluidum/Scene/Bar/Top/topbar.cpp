#include "topbar.h"
#include "../../Calc/Lua/lua.h"

using namespace FU::ImGui::Operators;

FS::TopBar::TopBar(
	const FD::ProjectRead* const projectRead,
	const FD::GuiRead* const guiRead,
	FD::GuiWrite* const guiWrite,
	const FD::SceneRead* const sceneRead
)
	: projectRead(projectRead), guiRead(guiRead), guiWrite(guiWrite), sceneRead(sceneRead)
{
	GLog.add<FD::Log::Type::None>("Construct TopBarScene.");

	style.windowPos = ImVec2(0.0f, guiRead->menuBarHeight());
	const float windowHeight = guiRead->menuBarHeight();
	style.windowSize = ImVec2(guiRead->windowSize().x, windowHeight);

	if (windowHeight <= ImGui::GetStyle().WindowMinSize.y)
		guiWrite->topBarHeight(ImGui::GetStyle().WindowMinSize.y);
	else
		guiWrite->topBarHeight(windowHeight);


	style.packageWindowPos = { guiRead->windowSize().x * 0.3f,0.0f };
	style.packageWindowSize = { guiRead->windowSize().x * 0.6f,guiRead->menuBarHeight() };

}

FS::TopBar::~TopBar() noexcept {
	try {
		GLog.add<FD::Log::Type::None>("Destruct TopBarScene.");
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

namespace FS::Internal::Bar {
	constexpr auto commonWindowFlag =
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar;
}

void FS::TopBar::call() {

	ImGui::SetNextWindowPos(style.windowPos);
	ImGui::SetNextWindowSize(style.windowSize);

	//�p���Ƃ�
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	//border���ׂ�
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGui::Begin("TopBar", nullptr, Internal::Bar::commonWindowFlag | ImGuiWindowFlags_NoBringToFrontOnFocus);

	ImGui::End();


	this->rightGui();
	this->calc();
	this->file();


	ImGui::PopStyleVar(2);

	////////////////////////////////////////////////////////////////////////////////////////////


	ImGui::SetNextWindowPos(style.packageWindowPos);
	ImGui::SetNextWindowSize(style.packageWindowSize);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());

	ImGui::Begin("TopBar2", nullptr, Internal::Bar::commonWindowFlag | ImGuiWindowFlags_NoBackground);

	ImGui::Dummy(ImGui::GetStyle().FramePadding * 1.17f);

	this->packageGui(); ImGui::SameLine(); ImGui::Dummy(ImVec2(guiRead->windowSize().x * 0.02f, 0.0f)); ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.05f, 0.05f, 0.05f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.03f, 0.03f, 0.03f, 1.0f));
	ImGui::PushItemWidth(guiRead->windowSize().x / 13.0f);

	this->layoutGui(); ImGui::SameLine(); ImGui::Dummy(ImVec2(guiRead->windowSize().x * 0.02f, 0.0f)); ImGui::SameLine();
	this->templateGui(); ImGui::SameLine(); ImGui::Dummy(ImVec2(guiRead->windowSize().x * 0.1f, 0.0f)); ImGui::SameLine();
	ImGui::PopItemWidth();

	this->projectNameGui();

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();

	ImGui::End();
}

void FS::TopBar::packageGui() {
	ImGui::AlignTextToFramePadding();
	ImGui::Text(text.package); ImGui::SameLine();

	ImGui::Button(ICON_MD_ARCHIVE);
}

void FS::TopBar::layoutGui() {
	ImGui::AlignTextToFramePadding();
	ImGui::Text("Layout"); ImGui::SameLine();

	int32_t layoutIndex = 0;
	const char* layoutTemplateNames[4] = { ICON_MD_DASHBOARD " Standard",ICON_MD_SCHEDULE " Animation",ICON_MD_SHARE " Node" ,ICON_MD_VISIBILITY " View" };
	ImGui::Combo("##Layout", &layoutIndex, layoutTemplateNames, IM_ARRAYSIZE(layoutTemplateNames));
}

void FS::TopBar::templateGui() {
	ImGui::AlignTextToFramePadding();
	ImGui::Text("Template"); ImGui::SameLine();

	int32_t layoutIndex = 0;
	const char* layoutTemplateNames[4] = { ICON_MD_DASHBOARD " Standard",ICON_MD_SCHEDULE " Animation",ICON_MD_SHARE " Node" ,ICON_MD_VISIBILITY " View" };
	ImGui::Combo("##Template", &layoutIndex, layoutTemplateNames, IM_ARRAYSIZE(layoutTemplateNames));
}

void FS::TopBar::projectNameGui() {
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

	if (projectRead->isDefaultProject())
		ImGui::Button(text.tempProject);
	else
		ImGui::Button(projectRead->getProjectName().c_str());

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(2);
}

void FS::TopBar::rightGui() {
	ImGui::SetNextWindowPos(ImVec2(style.windowSize.x * 0.6f, style.windowPos.y));
	ImGui::SetNextWindowSize(ImVec2(style.windowSize.x * 0.4f, style.windowSize.y));

	ImGui::Begin("Right", nullptr, Internal::Bar::commonWindowFlag | ImGuiWindowFlags_NoBackground);

	this->backColorGui();
	ImGui::SameLine(); ImGui::Spacing(); ImGui::SameLine();
	this->areaGui();

	ImGui::End();
}

void FS::TopBar::backColorGui() {
	ImGui::SetNextItemWidth(style.windowSize.x * 0.1f);
	static float col[3] = {};
	if (ImGui::ColorEdit3("##Back", col)) {
		//auto ind = commands->getIndices(FVK::CommandType::BEGIN_RENDERPASS);
		//for (auto& x : ind) {
		//	FVK::BeginRenderPassCommand command = commands->at<FVK::CommandType::BEGIN_RENDERPASS>(x);

		//	command->setBackColor(std::array<float, 4>{col[0], col[1], col[2], 1.0f});
		//}

	}

}

void FS::TopBar::areaGui() {
	//static bool temp = false;
	//ImGui::Button(ICON_MD_BRANDING_WATERMARK);
}

void FS::TopBar::calc() {
	ImGui::SetNextWindowPos(ImVec2(style.windowSize.x * 0.3f, style.windowPos.y));
	ImGui::SetNextWindowSize(ImVec2(style.windowSize.x * 0.3f, style.windowSize.y));

	ImGui::Begin("Calc", nullptr, Internal::Bar::commonWindowFlag | ImGuiWindowFlags_NoBackground);

	bool isRunning = sceneRead->isExist<LuaCalc>();

	//�O�̃X�e�b�v�܂Ŗ߂�
	//�ꎞ��~���ȊO�͑I��s��
	if (isRunning) {
		ImGui::Button(ICON_MD_SKIP_PREVIOUS);
	}
	else {
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.1f);
		ImGui::Button(ICON_MD_SKIP_PREVIOUS);
		ImGui::PopStyleVar();
	}

	ImGui::SameLine();

	//���s��
	if (isRunning) {

		//�ꎞ��~��v��
		bool pause = ImGui::Button(ICON_MD_STOP);

		ImGui::SameLine();
	}
	else {

		bool run = ImGui::Button(ICON_MD_PLAY_ARROW);
		if (run)
			this->run();
	}

	ImGui::SameLine();

	//���̃X�e�b�v�܂Ői��
	if (isRunning) {
		ImGui::Button(ICON_MD_SKIP_NEXT);

	}
	else {
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.1f);

		//��~��v��
		bool stop = ImGui::Button(ICON_MD_PAUSE);
		ImGui::SameLine();

		//���̃X�e�b�v
		ImGui::Button(ICON_MD_SKIP_NEXT);

		ImGui::PopStyleVar();
	}


	ImGui::End();

	this->playCheck();
}

void FS::TopBar::run() {
	const FD::Project::CodeType type = projectRead->getCurrentMainCodeType();
	using enum FD::Project::CodeType;

	if (type == Empty) {

	}
	else if (type == Error) {

	}
	else if (type == Lua) {
		GLog.add<FD::Log::Type::None>("Request add LuaCalcScene.");
		Scene::addAsyncScene<LuaCalc>();
	}
	else if (type == Python) {

	}
	else if (type == AngelScript) {

	}
}

void FS::TopBar::playCheck() {
	//if (!wait.isPlayButtonClicked || !loadingParam.finishFlag.load())
	//	return;



	////�v�Z���J�n���閽�߂����ł���

	////�ۑ��������I����Ă��Ă��ҋ@
	//const auto currentTime = std::chrono::system_clock::now();
	//if (currentTime > wait.time) {
	//	std::cout << "a\n\n\n\n";
	//	wait.reset();
	//	//Scene::addAsyncScene<FS::Lua>();
	//}



}

void FS::TopBar::file() {
	ImGui::SetNextWindowPos(ImVec2(style.windowSize.x * 0.05f, style.windowPos.y));
	ImGui::SetNextWindowSize(ImVec2(style.windowSize.x * 0.1f, style.windowSize.y));

	ImGui::Begin("File", nullptr, Internal::Bar::commonWindowFlag | ImGuiWindowFlags_NoBackground);

	ImGui::Button(ICON_MD_ADD_BOX); 
	//FU::ImGui::exclamationMarker();
	ImGui::SameLine();
	ImGui::Button(ICON_MD_NOTE_ADD); ImGui::SameLine();
	ImGui::Button(ICON_MD_SAVE);

	ImGui::End();
}