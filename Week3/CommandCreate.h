#ifndef COMMAND_CREATE_H
#define COMMAND_CREATE_H
#include "Command.h"
#include "Level.h"
class CommandCreate : public Command
{
public:
	CommandCreate(Level* _level) {
		m_level = _level;
	}
	virtual void Execute() {
		cout << "Executing: CommandCreateImageBuffer" << endl;
		m_level->CreateImageBuffer();
	}
	virtual void Undo() {
		m_level->DeleteImageBuffer();
	}
	virtual bool IsRedoable() {
		return false;
	}
private:
	Level* m_level;
};

#endif COMMAND_CREATE_H