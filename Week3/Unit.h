#ifndef UNIT_H
#define UNIT_H

#include "Resource.h"
#include "FileChunk.h"
class Unit : public Resource
{
public:
	Unit();
	virtual ~Unit();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

	static ObjectPool<Unit>* Pool;


private:
	FileChunk* m_fileChunk;

};

#endif


