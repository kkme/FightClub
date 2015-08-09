namespace PWRD{
	inline void CloseSocket(Handle s)
	{
		close(s);
	}

	inline int GetLastError()
	{
		return errno;
	}
}
