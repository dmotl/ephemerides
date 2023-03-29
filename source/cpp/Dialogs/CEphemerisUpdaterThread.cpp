#include "CEphemerisUpdaterThread.h"

#include "CEphemerisUpdater.h"

//
// Work procedure
//
void CEphemerisUpdaterThread::run()
{
	assert(m_process != nullptr);

	m_process->m_retval = m_process->run();
}
