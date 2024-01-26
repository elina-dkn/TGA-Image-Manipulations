#include "Resource.h"

ObjectPool<Resource>* Resource::Pool;

Resource::Resource() {
	m_val1 = 0;
	m_val2 = 0.0f;
	m_val3 = {};
	m_subResource = nullptr;
}

Resource::~Resource() {

}

void Resource::AssignNonDefaultValues() {
	m_val1 = 2;
	m_val2 = 2.0f;
	m_val3 = '2';
	m_subResource = Resource::Pool->GetResource();
	m_subResource->m_val1 = 3;
	m_subResource->m_val2 = 3.0f;
	m_subResource->m_val3 = '3';

}

void Resource::ToString() {
	cout << "m_val1 " << m_val1 << " ";
	cout << "m_val2 " << m_val2 << " ";
	cout << "m_val3 " << m_val3 << " " << endl;;
	if(m_subResource != nullptr) {
		m_subResource->ToString();
	}
}

void Resource::Serialize(std::ostream& _stream) {
	_stream.write(reinterpret_cast<char*>(&m_val1), sizeof(m_val1));
	_stream.write(reinterpret_cast<char*>(&m_val2), sizeof(m_val2));
	_stream.write(reinterpret_cast<char*>(&m_val3), sizeof(m_val3));

	byte exists = 1;
	if (m_subResource != nullptr) {
		_stream.write(reinterpret_cast<char*>(&exists), sizeof(byte));
		m_subResource->Serialize(_stream);
	}
	else {
		exists = 0;
		_stream.write(reinterpret_cast<char*>(&exists), sizeof(byte));
	}

}

void Resource::Deserialize(std::istream& _stream) {
	_stream.read(reinterpret_cast<char*>(&m_val1), sizeof(m_val1));
	_stream.read(reinterpret_cast<char*>(&m_val2), sizeof(m_val2));
	_stream.read(reinterpret_cast<char*>(&m_val3), sizeof(m_val3));

	byte exists = 0;
	_stream.read(reinterpret_cast<char*>(&exists), sizeof(exists));

	if (exists == 1) {
		m_subResource = Resource::Pool->GetResource();
		m_subResource->Deserialize(_stream);
	}

}