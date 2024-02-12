#ifndef LEVEL_H
#define LEVEL_H

#include "Unit.h"
class Level : public Resource
{
public:
	Level();
	virtual ~Level();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

	int GetIndex() { return m_index; }
	void CreateImageBuffer();
	void DeleteImageBuffer();
	void AddChunk();
	void RemoveChunk();
private:
	void WriteImage();
	vector<FileChunk*> m_fileChunks;
	byte* m_imageBuffer;
	int m_totalSize;
	int m_offset;
	int m_index;
	
};

#endif