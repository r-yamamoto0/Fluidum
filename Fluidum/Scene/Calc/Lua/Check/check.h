#pragma once

#include "../type.h"
#include "../Utils/utils.h"
#include "../Log/log.h"

namespace FS::Lua::Internal {

	class Exception final {};

	class InternalError final {
	public:
		explicit InternalError(const char* const file) : file(file) {}
		const char* const file;
	};

	class Check {
	public:
		explicit Check(FD::ConsoleWrite* const consoleWrite) : consoleWrite(consoleWrite) {}

	public:
		template<FD::Calc::Lua::FunctionType Type>
		void numOfArgs(State L, const std::size_t correctSize, const std::size_t min, const std::size_t max) {
			assert(min != 0);
			assert(max != 0);

			const std::size_t size = getArgSize(L);

			if (size == correctSize)
				return;

			//関数{}の引数の数が少なすぎます．渡された引数の数:{}．正しい引数の数:{}．
			if (size < min) {
				Message message(LogType::NumOfArgs_Min);
				GLog.add<FD::Log::Type::None>(message, magic_enum::enum_name<Type>(), size, correctSize);
				//consoleWrite->add
				throw Exception();
			}


			//関数{}の引数の数が多すぎます．渡された引数の数:{}．正しい引数の数:{}．
			if (size < min) {
				Message message(LogType::NumOfArgs_Min);
				GLog.add<FD::Log::Type::None>(message, magic_enum::enum_name<Type>(), size, correctSize);
				throw Exception();
			}
		}

		template<FD::Calc::Lua::FunctionType Type>
		void numOfArgs_min(State L, const std::size_t correctSize) {
			const std::size_t size = getArgSize(L);

			if (size >= correctSize)
				return;

			Message message(LogType::NumOfArgs_Min);
			GLog.add<FD::Log::Type::None>(message, magic_enum::enum_name<Type>(), size, correctSize);
			throw Exception();
		}

		template<FD::Calc::Lua::FunctionType Type>
		void argType(State L, const std::vector<CoreType>& correctTypes) {
			assert(!correctTypes.empty());

			const auto types = getCoreTypes(L);

			//numOfArgs
			if (correctTypes.size() != types.size())
				throw std::runtime_error("Internal Error.");


			for (std::size_t i = 0, size = types.size(); i < size; i++) {
				bool same = (correctTypes[i] == types[i]);
				if (!same) {
					//関数{}の{}番目の引数の型に誤りがあります．渡された引数の型: {}．正しい引数の型: {}．
					Message message(LogType::Type);
					GLog.add<FD::Log::Type::None>(message, magic_enum::enum_name<Type>(), i + 1, getCoreTypeName(types[i]), getCoreTypeName(correctTypes[i]));
					throw Exception();
				}
			}

		}

		template<FD::Calc::Lua::FunctionType Type>
		void argType_intNum(State L, const std::vector<CoreType>& correctTypes) {
			assert(!correctTypes.empty());

			const auto types = getCoreTypes(L);

			//numOfArgs
			if (correctTypes.size() != types.size())
				throw std::runtime_error("Internal Error.");

			for (std::size_t i = 0, size = types.size(); i < size; i++) {
				bool same = (correctTypes[i] == types[i]);
				if (!same) {
					if (correctTypes[i] == CoreType::Number && types[i] == CoreType::Integer)
						;
					else {
						//関数{}の{}番目の引数の型に誤りがあります．渡された引数の型: {}．正しい引数の型: {}．
						Message message(LogType::Type);
						GLog.add<FD::Log::Type::None>(message, magic_enum::enum_name<Type>(), i + 1, getCoreTypeName(types[i]), getCoreTypeName(correctTypes[i]));
						throw Exception();
					}
				}
			}
		}


	private:
		FD::ConsoleWrite* const consoleWrite;
	};

}