#pragma once 

#include "StringId.h"
#include "../Containers/Array.h"

#define GetFuncName(FuncName) StringId(#FuncName)

template<typename... ParamTypes>
class IDelegate
{
public:
	StringId methodName;

	virtual void Call(ParamTypes... params) = 0;
};

template <class UserClass, typename... ParamTypes>
class Delegate : public IDelegate<ParamTypes...>
{
public:
	UserClass* object;
	void (UserClass::* methodPtr)(ParamTypes... params);

	virtual void Call(ParamTypes... params) override
	{
		(object->*methodPtr)(params...);
	}
};

template <typename... ParamTypes>
class Dispatcher
{
public:

	~Dispatcher()
	{
		Clear();
	}

	template <class UserClass>
	void _InternalAddEvent(UserClass* object, void (UserClass::* methodPtr)(ParamTypes... params), StringId methodName)
	{
		Delegate<UserClass, ParamTypes...>* delegate = new Delegate<UserClass, ParamTypes...>();
		delegate->object = object;
		delegate->methodPtr = methodPtr;
		delegate->methodName = methodName;
		mDelegates.Add(delegate);
	}

	template <class UserClass>
	void _InternalRemoveEvent(UserClass* object, StringId methodName)
	{
		int i = 0;
		for (i = 0; i < mDelegates.Size(); i++)
		{
			IDelegate<ParamTypes...>* delegate = mDelegates[i];
			if (delegate->methodName == methodName)
			{
				mDelegates.RemoveAt(i);
				return;
			}
		}
	}

	void Broadcast(ParamTypes... params)
	{
		for (auto delegate : mDelegates)
		{
			delegate->Call(params...);
		}
	}

	void Clear()
	{
		for (auto delegate : mDelegates)
		{
			delete delegate;
		}
		mDelegates.Clear();
	}

	int size()
	{
		return mDelegates.Length();
	}

private:
	Array<IDelegate<ParamTypes...>*> mDelegates;
};

#define AddEvent(object, methodPtr) _InternalAddEvent(object, methodPtr, GetFuncName(methodPtr))
#define RemoveEvent(object, methodPtr) _InternalRemoveEvent(object, GetFuncName(methodPtr))

#define EVENT_DISPATCHER(DisplayName, ...)	class HERO_API DisplayName : public Dispatcher <__VA_ARGS__>{};