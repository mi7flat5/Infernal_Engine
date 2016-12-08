#include "Engine.h"
#include "EventManagerImpl.h"


void EventManager::cleanUp()
{
	m_eventListeners.clear();

}
//---------------------------------------------------------------------------------------------------------------------
// EventManager::EventManager
//---------------------------------------------------------------------------------------------------------------------
EventManager::EventManager(const char* pName, bool setAsGlobal)
	: IEventManager(pName, setAsGlobal)
{
	
	m_activeQueue = 0;
}


//---------------------------------------------------------------------------------------------------------------------
// EventManager::~EventManager
//---------------------------------------------------------------------------------------------------------------------
EventManager::~EventManager()
{
	//m_eventListeners.clear();
}


//---------------------------------------------------------------------------------------------------------------------
// EventManager::VAddListener
//---------------------------------------------------------------------------------------------------------------------
bool EventManager::VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	//GCC_LOG("Events", "Attempting to add delegate function for event type: " + ToStr(type, 16));

	EventListenerList& eventListenerList = m_eventListeners[type];  // this will find or create the entry
	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	{
		if (eventDelegate == (*it))
		{
			std::cout<<"Attempting to double-register a delegate"<<'\n';//TODO
			return false;
		}
	}

	eventListenerList.push_back(eventDelegate);
	LOG_TO_FILE( std::string("Successfully added delegate for event type: " + ToStr(type, 16)).c_str());//TODO


	return true;
}


//---------------------------------------------------------------------------------------------------------------------
// EventManager::VRemoveListener
//---------------------------------------------------------------------------------------------------------------------
bool EventManager::VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	//GCC_LOG("Events", "Attempting to remove delegate function from event type: " + ToStr(type, 16));
	bool success = false;

	auto findIt = m_eventListeners.find(type);
	if (findIt != m_eventListeners.end())
	{
		EventListenerList& listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (eventDelegate == (*it))
			{
				listeners.erase(it);
				std::cout << "Successfully removed delegate function from event type: " + ToStr(type, 16)<<std::endl;//TODO
				success = true;
				break;  // we don't need to continue because it should be impossible for the same delegate function to be registered for the same event more than once
			}
		}
	}

	return success;
}


//---------------------------------------------------------------------------------------------------------------------
// EventManager::VTrigger
//---------------------------------------------------------------------------------------------------------------------
bool EventManager::VTriggerEvent(const IEventDataPtr& pEvent) const
{
	//GCC_LOG("Events", "Attempting to trigger event " + std::string(pEvent->GetName()));
	bool processed = false;

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		for (EventListenerList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerDelegate listener = (*it);
			
			listener(pEvent);  // call the delegate
			processed = true;
		}
	}

	return processed;
}


//---------------------------------------------------------------------------------------------------------------------
// EventManager::VQueueEvent
//---------------------------------------------------------------------------------------------------------------------
bool EventManager::VQueueEvent(const IEventDataPtr& pEvent)
{
	assert(m_activeQueue >= 0);
	assert(m_activeQueue < EVENTMANAGER_NUM_QUEUES);

	// make sure the event is valid
	if (!pEvent)
	{
		LOG_TO_FILE("Invalid event in VQueueEvent()");//TODO
		return false;
	}

		LOG_TO_FILE(std::string("Attempting to queue event: " + std::string(pEvent->GetName())).c_str());//TODO

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end())
	{
		m_queues[m_activeQueue].push_back(pEvent);
		LOG_TO_FILE(std::string("Succesfully queued event: " + std::string(pEvent->GetName())).c_str());//TODO
		return true;
	}
	else
	{
		LOG_TO_FILE(std::string("Skipping event since there are no delegates registered to receive it: " + std::string(pEvent->GetName())).c_str());
		return false;
	}
}


//---------------------------------------------------------------------------------------------------------------------
// EventManager::VThreadSafeQueueEvent
//---------------------------------------------------------------------------------------------------------------------
//bool EventManager::VThreadSafeQueueEvent(const IEventDataPtr& pEvent)
//{
//	m_realtimeEventQueue.push(pEvent);
//	return true;
//}


//---------------------------------------------------------------------------------------------------------------------
// EventManager::VAbortEvent
//---------------------------------------------------------------------------------------------------------------------
bool EventManager::VAbortEvent(const EventType& inType, bool allOfType)
{
	assert(m_activeQueue >= 0);
	assert(m_activeQueue < EVENTMANAGER_NUM_QUEUES);

	bool success = false;
	EventListenerMap::iterator findIt = m_eventListeners.find(inType);

	if (findIt != m_eventListeners.end())
	{
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto it = eventQueue.begin();
		while (it != eventQueue.end())
		{
			// Removing an item from the queue will invalidate the iterator, so have it point to the next member.  All
			// work inside this loop will be done using thisIt.
			auto thisIt = it;
			++it;

			if ((*thisIt)->VGetEventType() == inType)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!allOfType)
					break;
			}
		}
	}

	return success;
}


//---------------------------------------------------------------------------------------------------------------------
// EventManager::VTick
//---------------------------------------------------------------------------------------------------------------------
bool EventManager::VUpdate(unsigned long maxMillis)
{
	unsigned long currMs = GetTickCount();
	unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ? (IEventManager::kINFINITE) : (currMs + maxMillis));

	// This section added to handle events from other threads.  Check out Chapter 20.
	/*IEventDataPtr pRealtimeEvent;
	while (m_realtimeEventQueue.try_pop(pRealtimeEvent))
	{
		VQueueEvent(pRealtimeEvent);

		currMs = GetTickCount();
		if (maxMillis != IEventManager::kINFINITE)
		{
			if (currMs >= maxMs)
			{
				GCC_ERROR("A realtime process is spamming the event manager!");
			}
		}
	}*/

	// swap active queues and clear the new queue after the swap
	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	m_queues[m_activeQueue].clear();

	LOG_TO_FILE(std::string("Processing Event Queue " + ToStr(queueToProcess) + "; " + ToStr((unsigned long)m_queues[queueToProcess].size()) + " events to process").c_str());//TODO

	// Process the queue
	while (!m_queues[queueToProcess].empty())
	{
		// pop the front of the queue
		IEventDataPtr pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();
		std::cout<<"\t\tProcessing Event " + std::string(pEvent->GetName())<<'\n';

		const EventType& eventType = pEvent->VGetEventType();

		// find all the delegate functions registered for this event
		auto findIt = m_eventListeners.find(eventType);
		if (findIt != m_eventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;
			std::cout<<"\t\tFound " + ToStr((unsigned long)eventListeners.size()) + " delegates"<<'\n';

			// call each listener
			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
				EventListenerDelegate listener = (*it);
				std::cout << "\t\tSending event " + std::string(pEvent->GetName()) + " to delegate"<<'\n';
				listener(pEvent);
			}
		}

		// check to see if time ran out
		currMs = GetTickCount();
		if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs)
		{
			std::cout << "Aborting event processing; time ran out"<<'\n';
			break;
		}
	}

	// If we couldn't process all of the events, push the remaining events to the new active queue.
	// Note: To preserve sequencing, go back-to-front, inserting them at the head of the active queue
	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!queueFlushed)
	{
		while (!m_queues[queueToProcess].empty())
		{
			IEventDataPtr pEvent = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_activeQueue].push_front(pEvent);
		}
	}

	return queueFlushed;
}


