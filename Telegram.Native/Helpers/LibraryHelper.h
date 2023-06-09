#pragma once
#include <Windows.h>

HMODULE GetKernelModule();
HMODULE GetModuleHandle2(_In_ LPCTSTR libFileName);
HMODULE LoadLibrary2(_In_ LPCTSTR lpFileName);
HMODULE LoadLibraryEx2(_In_ LPCTSTR lpFileName, _Reserved_ HANDLE hFile, _In_ DWORD flags);

struct LibraryInstance
{
public:
	LibraryInstance(LPCTSTR libFileName)
	{
		m_module = LoadLibrary2(libFileName);
	}

	LibraryInstance(LPCTSTR libFileName, DWORD flags)
	{
		m_module = LoadLibraryEx2(libFileName, NULL, flags);
	}

	~LibraryInstance()
	{
		FreeLibrary(m_module);
	}

	inline bool IsValid() const
	{
		return m_module != nullptr;
	}

	inline HMODULE GetHandle() const
	{
		return m_module;
	}

	template<typename T>
	T GetMethod(LPCSTR methodName) const
	{
		return reinterpret_cast<T>(GetProcAddress(m_module, methodName));
	}

	template<typename T>
	T GetMethod(DWORD offset) const
	{
		return reinterpret_cast<T>(m_module + offset);
	}

private:
	HMODULE m_module;
};