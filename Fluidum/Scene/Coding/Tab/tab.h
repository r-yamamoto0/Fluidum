#pragma once

#include "../../Common/common.h"

namespace FS::Coding {

	class Tab final : public Scene {
	public:
		explicit Tab(
			FD::Coding::TabWrite* const tabWrite,
			const FD::Coding::TabRead* const tabRead,
			const FD::ProjectRead* const projectRead
		);
		void Constructor(FD::Coding::TabWrite, FD::Coding::TabRead, FD::ProjectRead);

		~Tab() noexcept;

	public:
		virtual void call() override;

	private://data
		FD::Coding::TabWrite* const tabWrite;
		const FD::Coding::TabRead* const tabRead;
		const FD::ProjectRead* const projectRead;

		FD::Text::CodingTab text{};


		bool windowCloseFlag = false;

		struct {
			ImVec2 topBarSize{};
		}style;

		struct {
			ImVec2 center{};
		}pos;

		struct {
			std::vector<std::string> pathes;//full

			// "C:/test/text.lua" -> "text.lua"
			std::vector<std::string> fileNames;

			std::size_t currentIndex = 0;
		}files;

	private:
		void checkWindowShouldClose();

		void topBar();

		void include();
		void create();
		void sync();
		void code();
		void save();

	private:
		void update();

	private:
		void fileList();
	};
}