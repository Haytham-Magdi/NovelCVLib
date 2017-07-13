#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>

#include <NovelCVLib\Ncpp\Common\Debug.h>

#define FRM_Object public virtual Ncpp::Object

namespace Ncpp
{
	class ObjectFriend;

	/*
	class IObject
	{
	public:

		IObject()
		{
			m_id = s_id++;
		}

		virtual ~IObject() {}

		static int s_id;

	protected:

		int m_id;

	private:

		virtual void AddRef(void) = 0;
		virtual void Release(void) = 0;

		friend ObjectFriend;
	};
	*/

	
	class Object
	{
	public:
		
		Object(void)
		{
			m_nRefCnt = 0;

			m_nDel_RefCnt = 0;

			m_bAllowDelete = true;
		}

		~Object(void)
		{
		}

	private:
		void AddRef(void)
		{
			m_nRefCnt++;
		}

		virtual void Release(void)
		{
			if( m_nRefCnt <= m_nDel_RefCnt )
				return;

			m_nRefCnt--;
			Ncpp_ASSERT(m_nRefCnt >= 0);

			//if( ! m_bAllowDelete )
			//	m_nRefCnt = m_nRefCnt;

			//if(0 == m_nRefCnt)
			if( m_nDel_RefCnt == m_nRefCnt &&
				m_bAllowDelete )				
			{
				delete this;
			}
		}

	protected:

		int m_nDel_RefCnt;

		bool m_bAllowDelete;

	private:
		int m_nRefCnt;

		friend ObjectFriend;
	};
	
	class ObjectFriend
	{
	public:

		ObjectFriend()
		{
			m_id = s_id++;
		}

		static int * m_testBuf;
		static int * m_testBuf_2;

		//static int s_nTestBuf_Cnt;
		static int s_nTestBuf_Siz;

	protected:

		int m_id;

		static int s_id;

	protected:
		void AddObjectRef(Object * a_pObj)
		{
			if (NULL != a_pObj)
			{
				a_pObj->AddRef();
			}
		}

		void ReleaseObject(Object * a_pObj)
		{
			if (NULL != a_pObj)
			{
				a_pObj->Release();
			}
		}
	};

}