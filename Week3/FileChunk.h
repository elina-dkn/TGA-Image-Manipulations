#ifndef FILECHUNK_H
#define FILECHUNK_H

#include "Resource.h"

class FileChunk : public Resource
{

public:
	FileChunk();
	virtual ~FileChunk();

	Asset* GetChunk() { return m_chunk; }
	void SetChunk(Asset* _part) { m_chunk = _part; }

	virtual void Serialize(std::ostream& _stream);
	virtual void Deserialize(std::istream& _stream);
	virtual void AssignNonDefaultValues();
	virtual void ToString();

	static ObjectPool<FileChunk>* Pool;

private:
	Asset* m_chunk;
};

#endif