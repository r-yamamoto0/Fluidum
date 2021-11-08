#pragma once

#include "../../Common/common.h"

namespace FS::Analysis {

	class Overview final : public Scene {
	public:
		template<FD::Calc::Language Lang>
		explicit Overview(
			const FD::FunctionRead<Lang>* const functionRead,
			FD::ImGuiWindowWrite* const imguiWindowWrite,
			FD::TopBarWrite* const topBarWrite
		) : imguiWindowWrite(imguiWindowWrite), topBarWrite(topBarWrite)
		{
			GLog.add<FD::Log::Type::None>("Construct AnalysisScene.");

			this->functionRead<Lang> = functionRead;

			topBarWrite->add(&Overview::topBar, this, "AnaOV");
		}

		void Constructor(FD::FunctionRead<FD::Calc::Language::Lua>, FD::ImGuiWindowWrite, FD::TopBarWrite);

		~Overview() noexcept;

		FluidumUtils_Class_Delete_CopyMove(Overview)

	public:
		virtual void call() override;

	private:
		template<FD::Calc::Language Lang>
		static inline const FD::FunctionRead<Lang>* functionRead = nullptr;

		FD::ImGuiWindowWrite* const imguiWindowWrite;
		FD::TopBarWrite* const topBarWrite;

		bool windowShouldClose = true;
	private:
		void closeWindow();

	private:

		void setWindowInfo();

		void function();

	private:
		void topBar();

	};
}