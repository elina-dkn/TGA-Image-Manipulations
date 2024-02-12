#include "Unit.h"

ObjectPool<Unit>* Unit::Pool = nullptr;

Unit::Unit() {
	m_fileChunk = nullptr;
}

Unit::~Unit(){}

void Unit::AssignNonDefaultValues() {
	m_fileChunk = FileChunk::Pool->GetResource();
	m_fileChunk->AssignNonDefaultValues();
	Resource::AssignNonDefaultValues();
}

void Unit::Serialize(std::ostream& _stream) {
	SerializePointer(_stream, m_fileChunk);

	Resource::Serialize(_stream);
}

void Unit::Deserialize(std::istream& _stream) {
	DeserializePointer(_stream, m_fileChunk);
	Resource::Deserialize(_stream);
}

void Unit::ToString() {
	cout << "UNIT" << endl;
	m_fileChunk->ToString();
	Resource::ToString();
}