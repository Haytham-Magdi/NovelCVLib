#pragma once



//#include <NovelCVLib\Ncpp\Common\common.h>
#include <NovelCVLib\Ncpp\Common\object.h>
#include <NovelCVLib\Ncpp\Common\CommonKillers.h>
#include <NovelCVLib\Ncpp\Common\Object.h>


namespace Ncpp
{

	template<class T>
	class PtrObj : public Ncpp::Object
	{
	public:

		PtrObj(T * a_ptr)
		{
			m_ptr = a_ptr;
			m_nRefCnt = 0;
		}

		~PtrObj(void)
		{
			KillObj<T>(m_ptr);
		}

		T * GetPtr(void)
		{
			return m_ptr;
		}

	private:

		int m_nRefCnt;
		T * m_ptr;
	};

	template<class T>
	class PtrRef : public ObjectFriend
	{
	public:
		PtrRef()
		{
			m_pObj = nullptr;
		}

		PtrRef(T * a_ptr)
		{
			m_pObj = new PtrObj<T>(a_ptr);
			PtrRef<T>::AddObjectRef(m_pObj);
		}

		PtrRef(const PtrRef & a_ptrRef)
		{
			m_pObj = a_ptrRef.m_pObj;
			PtrRef<T>::AddObjectRef(m_pObj);
		}

		~PtrRef()
		{
			PtrRef<T>::ReleaseObject(m_pObj);
		}

		void operator = (const PtrRef<T> & a_ptrRef)
		{
			*this = a_ptrRef.m_pObj;
		}

		void operator = (PtrObj<T> * a_ptrObj)
		{
			PtrRef<T>::AddObjectRef(a_ptrObj);
			PtrRef<T>::ReleaseObject(m_pObj);
			m_pObj = a_ptrObj;
		}

		void operator = (T * a_ptr)
		{
			PtrRef<T>::ReleaseObject(m_pObj);
			m_pObj = new PtrObj<T>(a_ptr);
			PtrRef<T>::AddObjectRef(m_pObj);
		}

		T * operator -> (void)
		{
			return m_pObj->GetPtr();
		}

		operator T * (void)
		{
			return m_pObj->GetPtr();
		}

	protected:

		static void AddObjectRef(PtrObj<T> * a_pObj)
		{
			if (nullptr != a_pObj)
			{
				ObjectFriend::AddObjectRef(a_pObj);
			}
		}

		static void ReleaseObject(PtrObj<T> * a_pObj)
		{
			if (nullptr != a_pObj)
			{
				ObjectFriend::ReleaseObject(a_pObj);

				if (0 == ObjectFriend::GetObjectRefCount(a_pObj))
				{
					KillObj<PtrObj<T>>(a_pObj);
				}
			}
		}

	protected:
		PtrObj<T> * m_pObj;
	};


}


