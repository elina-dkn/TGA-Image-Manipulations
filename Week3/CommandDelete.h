#ifndef COMMAND_DELETE_H
#define COMMAND_DELETE_H
#include "Command.h"
#include "Level.h"
class CommandDelete : public Command
{
public:
	CommandDelete(Level* _level) {
		m_level = _level;
	}
	virtual void Execute() {
		cout << "Executing: CommandDeleteImageBuffer" << endl;
		m_level->DeleteImageBuffer();
	}
	virtual void Undo() {
		m_level->CreateImageBuffer();
	}
	virtual bool IsRedoable() {
		return false;
	}
private:
	Level* m_level;
};

#endif COMMAND_DELETE_H