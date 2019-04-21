#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
//#include <NovelCVLib\Ncpp\Common\ListQue.h>
#include <NovelCVLib\Ncpp\Common\FixedVector.h>

#include <NovelCVLib\Ncpp\Common\FixedDeque.h>
#include <NovelCVLib\Ncpp\Common\MultiAllocProvider.h>



namespace Ncpp
{
	template<class T>
	class ExtendableMultiAllocPtrPool : public Ncpp::Object
	{
	private:

	public:

		ExtendableMultiAllocPtrPool(const int a_singleAllocCapacity, const int a_higherOrderCapacity = 2000)
		{ 
			m_singleAllocCapacity = a_singleAllocCapacity;
			m_nofElmsInQues = 0;
			
			m_provider = new MultiAllocProvider<T>(a_singleAllocCapacity, a_singleAllocCapacity, a_higherOrderCapacity);
			m_providerOfQues = new MultiAllocProvider< FixedDeque<T *> >(a_higherOrderCapacity, a_higherOrderCapacity, 1);

			m_queOfWorkingQues.SetCapacity(a_higherOrderCapacity);
			m_queOfReserveQues.SetCapacity(a_higherOrderCapacity);

			m_pBackWorkingQue = m_pFrontWorkingQue = m_providerOfQues->ProvideNewElementPtr();
			m_pBackWorkingQue->SetCapacity(a_singleAllocCapacity);
			m_queOfWorkingQues.PushBack(m_pBackWorkingQue);
		}


		void TakePtrBack( T * a_ptr )
		{
			//if (GetBackWorkingQuePtr()->HasFreeCapacity())
			//{
				GetBackWorkingQuePtr()->PushBack(a_ptr);

				PostMangeBackWorkingQue();
			//}

		}

		T * ProvidePtr( )
		{
			if (GetFrontWorkingQuePtr()->GetSize() > 0)
			{
				T * ptr = GetFrontWorkingQuePtr()->GetFront();
				GetFrontWorkingQuePtr()->PopFront();

				PostManageFrontWorkingQue();

				return ptr;
			}
			else
			{
				T * ptr = m_provider->ProvideNewElementPtr();
				return ptr;
			}

		}


	private:


		FixedDeque< T *> * GetBackWorkingQuePtr()
		{
			return m_pBackWorkingQue;
		}

		FixedDeque< T *> * GetFrontWorkingQuePtr()
		{
			return m_pFrontWorkingQue;
		}

		void PostMangeBackWorkingQue()
		{
			if (GetBackWorkingQuePtr()->HasFreeCapacity())
			{
				return;
			}

			FixedDeque< T *> * pTmpQue;

			if (m_queOfReserveQues.GetSize() > 0)
			{
				pTmpQue = m_queOfReserveQues.GetFront();
				m_queOfReserveQues.PopFront();
			}
			else
			{
				pTmpQue = m_providerOfQues->ProvideNewElementPtr();
			}

			m_queOfWorkingQues.PushBack(pTmpQue);
			m_pBackWorkingQue = pTmpQue;

			return;
		}

		void PostManageFrontWorkingQue()
		{
			if (GetFrontWorkingQuePtr()->GetSize() > 0)
			{
				return;
			}
			Ncpp_ASSERT(0 == GetFrontWorkingQuePtr()->GetSize());

			if (1 == m_queOfWorkingQues.GetSize())
			{
				return;
			}
			
			Ncpp_ASSERT(m_queOfWorkingQues.GetSize() > 1);

			m_queOfReserveQues.PushBack(GetFrontWorkingQuePtr());
			m_queOfWorkingQues.PopFront();
			m_pFrontWorkingQue = m_queOfWorkingQues.GetFront();
		}

	private:

		int m_singleAllocCapacity;
		int m_nofElmsInQues;

		MultiAllocProviderRef<T> m_provider;
		MultiAllocProviderRef< FixedDeque<T *> > m_providerOfQues;
		
		FixedDeque< FixedDeque< T *> * > m_queOfWorkingQues;
		FixedDeque< FixedDeque< T *> * > m_queOfReserveQues;
		
		FixedDeque< T *> * m_pBackWorkingQue;
		FixedDeque< T *> * m_pFrontWorkingQue;
	};

	template<class T>
	using ExtendableMultiAllocPtrPoolRef = ObjRef< ExtendableMultiAllocPtrPool< T >>;

}