#ifndef COMMAND_REMOVE_H
#define COMMAND_REMOVE_H
#include "Command.h"
#include "Level.h"
class CommandRemove: public Command
{
public:
	CommandRemove(Level* _level) {
		m_level = _level;
	}
	virtual void Execute() {
		cout << "Executing: CommandRemoveChunk" << endl;
		m_level->RemoveChunk();
	}
	virtual void Undo() {
		m_level->AddChunk();
	}
	virtual bool IsRedoable() {
		return true;
	}
private:
	Level* m_level;
};

#endif COMMAND_REMOVE_H