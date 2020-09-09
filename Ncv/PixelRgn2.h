#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncv
{
	using namespace Ncpp;

	template<class T_PixelRgnEx>
    class PixelRgn2
    {
        public:

			void SetRootToSelf() { m_pRoot = (T_PixelRgnEx *)this; }

			void SetRootToNull() { m_pRoot = nullptr; }

			T_PixelRgnEx * GetDirectRoot() { return m_pRoot; }

			void SetDirectRoot(T_PixelRgnEx * a_pRoot) { m_pRoot = a_pRoot; }

			bool HasRoot() { return nullptr != m_pRoot;	}

			bool IsSelfRoot() const { return this == m_pRoot; }

			//	todo: faster implementation (not recursive).
			T_PixelRgnEx * GetActRootAfterNecessaryUpdating()
			{
				Ncpp_ASSERT(HasRoot());

				if (m_pRoot->IsSelfRoot())
				{
					return m_pRoot;
				}
				else
				{
					m_pRoot = m_pRoot->GetActRootAfterNecessaryUpdating();
					return m_pRoot;
				}
			}

			static bool DoBothRgnsHaveTheSameActRoot(T_PixelRgnEx & a_rgn1, T_PixelRgnEx & a_rgn2)
			{
				T_PixelRgnEx * pRoot1 = a_rgn1.GetActRootAfterNecessaryUpdating();
				T_PixelRgnEx * pRoot2 = a_rgn2.GetActRootAfterNecessaryUpdating();

				return pRoot1 == pRoot2;
			}

			static void MergeRgns_Direct(T_PixelRgnEx * a_pActRgn1, T_PixelRgnEx * a_pActRgn2)
			{
				Ncpp_ASSERT(a_actRgn1 != a_actRgn2);

				T_PixelRgnEx * pMinRgn, * pMaxRgn;
				AssignForCondition(a_pActRgn1 < a_pActRgn2, a_pActRgn1, a_pActRgn2, pMinRgn, pMaxRgn);
	
				pMaxRoot->m_pRoot = pMinRoot;
			}


			static void MergeRgns(T_PixelRgnEx & a_rgn1, T_PixelRgnEx & a_rgn2)
			{
				T_PixelRgnEx * pRoot1 = a_rgn1.GetActRootAfterNecessaryUpdating();
				T_PixelRgnEx * pRoot2 = a_rgn2.GetActRootAfterNecessaryUpdating();

				Ncpp_ASSERT(pRoot1 != pRoot2);

				T_PixelRgnEx * pMinRoot = (pRoot1 <= pRoot2) ? pRoot1 : pRoot2;
				T_PixelRgnEx * pMaxRoot = (pRoot1 > pRoot2) ? pRoot1 : pRoot2;

				T_PixelRgnEx::MergeRgnDataIntoAnother(*pMinRoot, *pMaxRoot);
				pMaxRoot->m_pRoot = pMinRoot;
			}




	private:


		static void MergeRgnDataIntoAnother(T_PixelRgnEx & a_destRgn, const T_PixelRgnEx & a_srcRgn)
		{

		}

	private:

		T_PixelRgnEx * m_pRoot;

    };







}