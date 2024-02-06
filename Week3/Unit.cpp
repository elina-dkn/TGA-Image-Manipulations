#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit() {
	m_soundEffect = nullptr;
	m_fileChunk = nullptr;
}

Unit::~Unit(){}

void Unit::AssignNonDefaultValues() {
	m_fileChunk = FileChunk::Pool->GetResource();
	m_fileChunk->AssignNonDefaultValues();

	m_soundEffect = SoundEffect::Pool->GetResource();
	m_soundEffect->AssignNonDefaultValues();

	Resource::AssignNonDefaultValues();
}

void Unit::Serialize(std::ostream& _stream) {
	SerializePointer(_stream, m_fileChunk);

	SerializePointer(_stream, m_soundEffect);
	Resource::Serialize(_stream);
}

void Unit::Deserialize(std::istream& _stream) {
	DeserializePointer(_stream, m_fileChunk);

	DeserializePointer(_stream, m_soundEffect);
	Resource::Deserialize(_stream);
}

void Unit::ToString() {
	cout << "UNIT" << endl;
	m_fileChunk->ToString();
	m_soundEffect->ToString();
	Resource::ToString();
}