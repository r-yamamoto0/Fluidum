#pragma once

#include "../../../Libraries/ImGuiColorTextEdit/TextEditor.h"

namespace FTE {

	//Fluidumに特化した構文強調
	::TextEditor::LanguageDefinition getLuaLanguageDefinition();

	class TextEditor final : public ::TextEditor {



	};

}