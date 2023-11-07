/*
  name_table.cpp 
  Таблица имён интерпретатора.
  Модуль отвечает за хранение имён команд и переменных.
*/

#include "stdafx.h"
#include "name_table.h"

NameTable NT;

NameTable::~NameTable() {
	// Таблица имен "владеет" объектами команд
	for (std::map<std::string, Command*>::const_iterator it(commands.begin());
	     it != commands.end(); ++it) {
		delete (it->second);
	}
}

void NameTable::RegisterCommand(const std::string& name, Command* cmd) {
	commands[name] = cmd;
}

bool NameTable::ProcessCommand(Parser& parser) {
	for (std::map<std::string, Command*>::const_iterator it(commands.begin()); it != commands.end(); ++it) {
		if (it->second->Process(parser))
			return true;
	}

	return false;
}

void NameTable::SetVariable(const std::string& name, const float value) {
	variables[name] = value;
}

float NameTable::GetVariable(const std::string& name) {
	return variables[name];
}
