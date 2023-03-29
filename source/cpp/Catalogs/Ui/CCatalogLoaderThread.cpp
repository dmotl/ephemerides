#include "CCatalogLoaderThread.h"

#include "CCatalogLoader.h"

//
// Work procedure
//
void CCatalogLoaderThread::run()
{
	assert(m_process != nullptr);

	m_process->m_retval = m_process->run();
}
