#pragma once


namespace Ncpp
{
	
	template<class T>
		inline void KillObj(T * a_pObj)
	{
		delete a_pObj;
	}


}