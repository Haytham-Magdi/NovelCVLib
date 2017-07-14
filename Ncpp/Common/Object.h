#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>

#include <NovelCVLib\Ncpp\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\ObjRef.h>


#define FRM_Object(T) public virtual Ncpp::Object<T>

namespace Ncpp
{
	template<class T>
	class Object
	{
	public:
		
		Object(void)
		{
			m_nRefCnt = 0;
			m_nDel_RefCnt = 0;
			m_bAllowDelete = true;
		}

	private:
		void AddRef(void)
		{
			m_nRefCnt++;
		}

		void Release(void)
		{
			m_nRefCnt--;
			Ncpp_ASSERT(m_nRefCnt >= 0);

			if(0 == m_nRefCnt)
			{
				KillObj<T>((T*)this);
			}
		}

	protected:

	private:
		int m_nRefCnt;
		friend ObjectFriend;
	};

}