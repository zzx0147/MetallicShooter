#include "stdafx.h"
#include "InputClass.h"

InputClass* InputClass::m_input = nullptr;

InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass & other)
{
}

InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	for (int i = 0; i < 256; ++i)
	{
		m_keys[i] = false;
		m_preKeys[i] = false;
	}
}

void InputClass::KeyDown(unsigned int input)
{
	m_keys[input] = true;
}

void InputClass::KeyUp(unsigned int input)
{
	m_keys[input] = false;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}

void InputClass::CreateInputClass()
{
	m_input = new InputClass();
	m_input->Initialize();
}

InputClass* InputClass::GetInputObject()
{
	return m_input;
}

bool InputClass::IsAnyKeyDown()
{
	for (int i = 0; i < 256; ++i)
	{
		if (m_keys[i])
		{
			m_preKeys[i] = m_keys[i];
			return true;
		}
	}


	return false;
}

bool InputClass::IsKeyDownOnce(unsigned int key)
{
	bool IsKeyDownOnce = false;
	if (m_keys[key] && (!m_preKeys[key]))
	{
		IsKeyDownOnce = true;
	}
	m_preKeys[key] = m_keys[key];

	return IsKeyDownOnce;
}