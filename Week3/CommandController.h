#ifndef COMMAND_CONTROLLER_H
#define COMMAND_CONTROLLER_H

class Level;

#include "StandardIncludes.h"
#include "Command.h"

class CommandController : public Singleton<CommandController>
{
public:
	CommandController();
	virtual ~CommandController();
	void HandleInput(string _button, Level* _level);
	void Undo();
	void Redo();
	int GetUndo() { return m_undoCount; }
	int GetRedo() { return m_redoCount; }
private:
	vector<Command*> m_commands;
	vector<Command*> m_redoCommands;
	int m_redoCount;
	int m_undoCount;
};

#endif