#pragma once

#include "../../Manager/include.h"
#include "../../Data/include.h"
#include "../../Draw/include.h"

namespace FS {

	using MainFluidumScene = ::FS::FluidumScene <
		FD::GuiWrite,
		FD::GuiRead,
		FD::SceneRead,
		FD::WindowWrite,
		FD::WindowRead,
		FD::GuiTextRead,
		FD::StyleColorWrite,
		FD::StyleColorRead,
		FD::LayoutWrite,
		FD::LayoutRead,
		FD::ProjectWrite,
		FD::ProjectRead,
		FD::Coding::TabWrite,
		FD::Coding::TabRead,
		FD::ConsoleWrite,
		FD::FunctionWrite<FD::Calc::Language::Lua>,
		FD::FunctionRead<FD::Calc::Language::Lua>,
		FD::ImPlotWrite,
		FD::ImPlotRead,
		FD::TopBarWrite,
		FD::TopBarRead,
		FD::ImGuiWindowWrite,
		FD::ImGuiWindowRead
	> ;

	//各シーンでpublic継承する upcastするのでpublic
	using Scene = MainFluidumScene::SceneBaseType;

}
