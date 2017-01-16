#pragma once

template <class Type>
std::shared_ptr<Type> MakeStrongPtr(std::weak_ptr<Type> pWeakPtr)
{
	if (!pWeakPtr.expired())
		return std::shared_ptr<Type>(pWeakPtr);
	else
		return std::hared_ptr<Type>();
}

template <class BaseType, class SubType>
BaseType* GenericObjectCreationFunction(void) { return new SubType; }

//actorcomponent,  component id
template <class BaseClass, class IdType>
class GenericObjectFactory
{
	typedef BaseClass* (*ObjectCreationFunction)(void);
	//will be a baseclass pointer pointing at a subclass


	std::map<IdType, ObjectCreationFunction> m_creationFunctions;

public:
	//specific component
	template <class SubClass>
	bool Register(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt == m_creationFunctions.end())
		{														//<actorcomponent, specific component> 
			m_creationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;  // insert() is giving me compiler errors
			return true;
		}

		return false;
	}

	BaseClass* Create(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt != m_creationFunctions.end())
		{
			ObjectCreationFunction pFunc = findIt->second;
			return pFunc();
		}

		return NULL;
	}
};