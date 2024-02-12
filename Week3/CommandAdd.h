#ifndef COMMAND_ADD_H
#define COMMAND_ADD_H
#include "Command.h"
#include "Level.h"
class CommandAdd : public Command
{
public:
	CommandAdd(Level* _level) {
		m_level = _level;
	}
	virtual void Execute() {
		cout << "Executing: CommandAddChunk" << endl;
		m_level->AddChunk();
	}
	virtual void Undo() {
		m_level->RemoveChunk();
	}
	virtual bool IsRedoable() {
		return true;
	}
private:
	Level* m_level;
};

#endif COMMAND_ADD_H