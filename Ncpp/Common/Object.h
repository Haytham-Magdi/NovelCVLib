#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>

#include <NovelCVLib\Ncpp\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\ObjRef.h>



namespace Ncpp
{
	class ObjectFriend;

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

		void Release()
		{
			m_nRefCnt--;
			Ncpp_ASSERT(m_nRefCnt >= 0);
		}

		int GetRefCount()
		{
			return m_nRefCnt;
		}

	private:
		friend ObjectFriend;

	private:
		int m_nRefCnt;
	};


	class ObjectFriend
	{
	protected:

		static void AddObjectRef(Object * a_pObj)
		{
			a_pObj->AddRef();
		}

		static void ReleaseObject(Object * a_pObj)
		{
			a_pObj->Release();
		}

		static int GetObjectRefCount(Object * a_pObj)
		{
			return a_pObj->GetRefCount();
		}

	};
}