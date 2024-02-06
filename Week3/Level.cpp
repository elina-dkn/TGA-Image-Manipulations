#include "Level.h"


Level::Level() {
	AssetController::Instance().Initialize(10000000000000000000);
	Unit::Pool = new ObjectPool<Unit>();
	SoundEffect::Pool = new ObjectPool<SoundEffect>();
	FileChunk::Pool = new ObjectPool<FileChunk>();

	m_imageBuffer = nullptr;
	m_totalSize = 0;
	m_offset = 0;


}
void Level::CreateImageBuffer() {
	unsigned int _totalSizeBytes = 0;
	for (int count = 0; count < 7; count++) {
		_totalSizeBytes += m_fileChunks[count]->GetChunk()->GetDataSize();
	}
	cout << "total: " << _totalSizeBytes << endl;
	cout << "Saving image NewImage.tga" << endl;
	m_imageBuffer = new byte[_totalSizeBytes];
	m_totalSize = _totalSizeBytes;
	memset(m_imageBuffer, 0, _totalSizeBytes);

	
}
void Level::WriteImage() {
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

void Level::AddChunk(int i) {
	byte* _chunkData = m_fileChunks[i]->GetChunk()->GetData();
	int size = m_fileChunks[i]->GetChunk()->GetDataSize();
	memcpy(m_imageBuffer +m_offset, _chunkData, size);
	m_offset += m_fileChunks[i]->GetChunk()->GetDataSize();

}


Level::~Level() {
	m_fileChunks.clear();
	m_units.clear();

	delete[] m_imageBuffer;
	delete SoundEffect::Pool;
	delete FileChunk::Pool;
	delete Unit::Pool;

	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues() {
	
	for (int count = 0; count < 7; count++) {
		FileChunk* unit = FileChunk::Pool->GetResource();
		unit->AssignNonDefaultValues();
		Asset* m_chunk = AssetController::Instance().GetAsset("chunk" + to_string(count) + ".bin");
		unit->SetChunk(m_chunk);
		m_fileChunks.push_back(unit);
		//Unit* unit = Unit::Pool->GetResource();
		//unit->AssignNonDefaultValues();
		//m_units.push_back(unit);
	}
	
	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {
	int numOfUnits = m_fileChunks.size();
	_stream.write(reinterpret_cast<char*>(&numOfUnits), sizeof(numOfUnits));
	for (int count = 0; count < numOfUnits; count++) {
		SerializePointer(_stream, m_fileChunks[count]);
	}


	/*int numOfUnits = m_units.size();
	_stream.write(reinterpret_cast<char*>(&numOfUnits), sizeof(numOfUnits));
	for (int count = 0; count < numOfUnits; count++) {
		SerializePointer(_stream, m_units[count]);
	}
	*/
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


	//int numOfUnits = m_units.size();
	//_stream.read(reinterpret_cast<char*>(&numOfUnits), sizeof(numOfUnits));
	//for (int count = 0; count < numOfUnits; count++) {
	//	Unit* unit;
	//	DeserializePointer(_stream, unit);
	//	m_units.push_back(unit);
	//}

	
	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "LEVEL" << endl;

	for (int count = 0; count < m_units.size(); count++) {
		m_units[count]->ToString();
	}
	Resource::ToString();
}
