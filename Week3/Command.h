#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
    virtual ~Command() { }
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual bool IsRedoable() = 0;
    
};

#endif