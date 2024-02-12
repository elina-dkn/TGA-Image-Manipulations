#include "CommandController.h"
#include "CommandCreate.h"
#include "CommandAdd.h"
#include "CommandDelete.h"
#include "CommandRemove.h"


CommandController::CommandController() {
	m_redoCount = 0;
	m_undoCount = 0;
}

CommandController::~CommandController() {

}

void CommandController::HandleInput(string _button, Level* _level) {
	Command* m_command = nullptr;
	if (_button == "C" || _button == "c") {
		m_command = new CommandCreate(_level);
	}
	else if (_button == "d" || _button == "D") {
		m_command = new CommandDelete(_level);
	}
	else if (_button == "a" || _button == "A") {
		m_command = new CommandAdd(_level);
	}
	else if (_button == "r" || _button == "R") {
		m_command = new CommandRemove(_level);
	}
	else if (_button == "z" || _button == "Z") {
		Undo();
	}
	else if (_button == "y" || _button == "Y") {
		Redo();
	}

	if (m_command != nullptr) {
		m_command->Execute();
		m_commands.push_back(m_command);
	}

}

void CommandController::Undo() {
	if (m_commands.empty()) return;
	Command* lastCommand = m_commands.back();
	if (lastCommand->IsRedoable()) {
		m_redoCommands.push_back(lastCommand);
	}
	lastCommand->Undo();
	m_commands.pop_back();
	m_undoCount++;
}

void CommandController::Redo() {
	if (m_redoCommands.empty()) return;
	Command* lastUndo = m_redoCommands.back();
	lastUndo->Execute();
	delete lastUndo;
	m_redoCommands.pop_back();
	m_redoCount++;
}
