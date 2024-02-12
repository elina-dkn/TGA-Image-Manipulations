#include "Level.h"


Level::Level() {
	AssetController::Instance().Initialize(10000000000000000000);
	FileChunk::Pool = new ObjectPool<FileChunk>();

	m_imageBuffer = nullptr;
	m_totalSize = 0;
	m_offset = 0;
	m_index = 0;


}
void Level::CreateImageBuffer() {
	unsigned int _totalSizeBytes = 0;
	for (int count = 0; count < 7; count++) {
		_totalSizeBytes += m_fileChunks[count]->GetChunk()->GetDataSize();
	}

	m_imageBuffer = new byte[_totalSizeBytes];
	m_totalSize = _totalSizeBytes;
	memset(m_imageBuffer, 0, _totalSizeBytes);
	WriteImage();
	
}
void Level::WriteImage() {
	cout << "Saving image NewImage.tga" << endl;
	ofstream writeStream("NewImage.tga", ios::out | ios::binary);
	for (int i = 0; i < m_totalSize; i++)
	{
		writeStream.write(reinterpret_cast<char*>(&m_imageBuffer[i]),sizeof(m_imageBuffer[i]) );
	}
	
	writeStream.close();
}

void Level::DeleteImageBuffer() {
	delete[] m_imageBuffer;
}

void Level::AddChunk() {
	if (m_index < m_fileChunks.size() && m_imageBuffer != nullptr) {
		byte* _chunkData = m_fileChunks[m_index]->GetChunk()->GetData();
		int size = m_fileChunks[m_index]->GetChunk()->GetDataSize();
		memcpy(m_imageBuffer + m_offset, _chunkData, size);
		m_offset += size;
		m_index++;
		WriteImage();
	}
	else {
		M_ASSERT(m_imageBuffer != nullptr, "Create buffer first! ");
	}
	
}

void Level::RemoveChunk() {
	

	if (m_index > 0 && m_imageBuffer != nullptr) {
		int size = m_offset - m_fileChunks[m_index - 1]->GetChunk()->GetDataSize();
		memset(m_imageBuffer + size, 0, m_fileChunks[m_index - 1]->GetChunk()->GetDataSize());
		m_offset -= m_fileChunks[m_index - 1]->GetChunk()->GetDataSize();
		m_index--;
		WriteImage();
	}
	else {
		M_ASSERT(m_imageBuffer != nullptr, "Add chunks first!");
	}
}


Level::~Level() {
	m_fileChunks.clear();
	delete[] m_imageBuffer;
	delete FileChunk::Pool;
	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues() {
	
	for (int count = 0; count < 7; count++) {
		FileChunk* unit = FileChunk::Pool->GetResource();
		unit->AssignNonDefaultValues();
		Asset* m_chunk = AssetController::Instance().GetAsset("chunk" + to_string(count) + ".bin");
		unit->SetChunk(m_chunk);
		m_fileChunks.push_back(unit);
	}
	
	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {
	int numOfUnits = m_fileChunks.size();
	_stream.write(reinterpret_cast<char*>(&numOfUnits), sizeof(numOfUnits));
	for (int count = 0; count < numOfUnits; count++) {
		SerializePointer(_stream, m_fileChunks[count]);
	}

	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	int numOfUnits = m_fileChunks.size();
	_stream.read(reinterpret_cast<char*>(&numOfUnits), sizeof(numOfUnits));
	for (int count = 0; count < numOfUnits; count++) {
		FileChunk* unit;
		DeserializePointer(_stream, unit);
		m_fileChunks.push_back(unit);
	}

	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "LEVEL" << endl;

	Resource::ToString();
}
