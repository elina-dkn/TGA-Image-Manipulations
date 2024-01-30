#include "Asset.h"

ObjectPool<Asset>* Asset::Pool;

Asset::Asset() {
	Reset();
}

void Asset::Reset() {
	m_GUID = "";
	m_dataSize = 0;
	m_data = nullptr;
}
