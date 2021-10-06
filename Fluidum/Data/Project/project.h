#pragma once

#include "../Common/common.h"

namespace FD::Project {
	struct CreateProjectInfo final {
		const char* projectName;
		const char* projectFolderPath;
	};

	enum class ExceptionType {
		NotFoundProjectFolder,
		AlreadyProjectFolderExist,
		FailedToOpenProjectFile,
		IllegalFile,
		BrokenFile
	};

	struct HistoryInfo final {
		std::string projectName{};
		std::string projectFilePath{};
		std::string ymd_h{};
	};

	enum class CodeType : uint8_t {
		Empty,      //mainコードが設定されていない
		Error,      //error 識別子が下記以外
		Python,
		Lua,
		AngelScript
	};
}

namespace FD {

	//現在のプロジェクト
	//起動時のプロジェクトは勝手に作るが保存しないと破棄
	class ProjectWrite final {
	public:
		//デフォルトで仮のプロジェクトを作成する
		explicit ProjectWrite(Internal::PassKey);
		~ProjectWrite() = default;
		FluidumUtils_Class_Delete_CopyMove(ProjectWrite)


	public:
		//現在のプロジェクトを保存せずに，新しいプロジェクトを作成する．
		void createNewProject(const Project::CreateProjectInfo& info) const;

		//現在のプロジェクトを保存せずに，既存のプロジェクトを読み込む．
		void loadExistProject(const char* path) const;

		//現在のプロジェクトを保存して，現在のプロジェクトを新しいパスへcopyする.
		void saveAs(const char* newName, const char* dstProjectFolderPath) const;

		//現在のプロジェクトを保存
		void save() const;

		//現在の情報を新たにバックアップをとる
		//アプリ終了時に最新のバックアップ以外は削除される
		void backup() const;

		void setMainCodePath(const char* path) const;
		void addIncludeCodePath(const char* path) const;
		void IncludeCodePath(const char* path) const;

	private:
		void write(const char* path) const;

		void makeBackupFolder() const;
		void makeCodeFolder() const;

		//ProjectFolderが消されたり移動したりしているか
		void checkIsProjectFolderExist() const;

		void updateHistory() const;

	private://read
		void readTabInfo(std::ifstream& ifs) const;

	};

	//現在のプロジェクト
	class ProjectRead final {
	public:
		explicit ProjectRead(Internal::PassKey) noexcept {};
		~ProjectRead() = default;
		FluidumUtils_Class_Delete_CopyMove(ProjectRead)

	public:
		_NODISCARD std::array<Project::HistoryInfo, 50> getProjectHistory() const;

		//保存されていない->true
		_NODISCARD bool isDataChanged() const;

		_NODISCARD std::vector<std::string> getIncludeCodeFilePathes() const;
		_NODISCARD std::string getMainCodeFilePath() const;

		_NODISCARD std::string getProjectFolderPath() const;
		_NODISCARD std::string getBackupFolderPath() const;
		_NODISCARD std::string getCodeFolderPath() const;
		_NODISCARD std::string getProjectName() const;

		_NODISCARD bool isDefaultProject() const;

		_NODISCARD Project::CodeType getCurrentMainCodeType() const;
	};

}