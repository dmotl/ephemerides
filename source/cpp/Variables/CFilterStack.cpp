#include "CFilterStack.h"

//
// Copy constructor
//
CFilterStack::CFilterStack(const CFilterStack& other)
{
	if (!other.m_data.isEmpty()) {
		m_data.reserve(other.m_data.count());
		for (int i = 0; i < other.m_data.count(); i++) {
			assert(other.m_data[i] != nullptr);
			m_data.append(other.m_data[i]->makeCopy());
		}
	}
}


//
// Move constructor
//
CFilterStack::CFilterStack(CFilterStack&& other) noexcept
{
	m_data = other.m_data;
	other.m_data.clear();
}

//
// Copy assignment
//
CFilterStack& CFilterStack::operator=(const CFilterStack& other)
{
	if (&other != this) {
		qDeleteAll(m_data);
		m_data.clear();
		if (!other.m_data.isEmpty()) {
			m_data.reserve(other.m_data.count());
			for (int i = 0; i < other.m_data.count(); i++) {
				assert(other.m_data[i] != nullptr);
				m_data.append(other.m_data[i]->makeCopy());
			}
		}
	}
	return *this;
}


//
// Move assignment
//
CFilterStack& CFilterStack::operator=(CFilterStack&& other) noexcept
{
	if (&other != this) {
		m_data = other.m_data;
		other.m_data.clear();
	}
	return *this;
}


//
// Check filter
//
bool CFilterStack::check(const CCatalogObject* obj, const CJulianDate& jd) const
{
	for (int i = 0; i < m_data.count(); i++) {
		const CFilter* f = m_data[i];

		assert(f != nullptr);

		if (!(*f)(obj, jd))
			return false;
	}
	return true;
}
