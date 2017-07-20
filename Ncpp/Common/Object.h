#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>

#include <NovelCVLib\Ncpp\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\ObjRef.h>


#define FRM_Object(T) public Ncpp::Object<T>

namespace Ncpp
{
	template<class T>
	class Object
	{
	public:

		Object(void)
		{
			m_nRefCnt = 0;
		}

	private:
		void AddRef(void)
		{
			m_nRefCnt++;
		}

		static void ReleaseObject(T * a_pObj)
		{
			a_pObj->m_nRefCnt--;
			Ncpp_ASSERT(a_pObj->m_nRefCnt >= 0);

			if (0 == a_pObj->m_nRefCnt)
			{
				KillObj<T>(a_pObj);
			}
		}

	private:
		friend ObjRef<T>;

	private:
		int m_nRefCnt;
	};

}