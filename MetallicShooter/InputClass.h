#pragma once

class InputClass
{
private:
	InputClass();
public:
	InputClass(const InputClass&);
	~InputClass();

	static void CreateInputClass();
	static InputClass* GetInputObject();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);
	bool IsAnyKeyDown();

	bool IsKeyDownOnce(unsigned int);

private:
	bool m_keys[256];
	bool m_preKeys[256];
	static InputClass* m_input;
};
