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

	void CreateImageBuffer();
	void DeleteImageBuffer();
	void AddChunk(int i);
	void WriteImage();
private:
	vector<FileChunk*> m_fileChunks;
	vector<Unit*> m_units;
	byte* m_imageBuffer;
	int m_totalSize;
	int m_offset;
	

};

#endif