#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncv
{
	using namespace Ncpp;

	template<class T_PixelRgnEx>
    class PixelRgn
    {
        public:

			PixelRgn() 
			{
				m_pRoot = (T_PixelRgnEx *)this;
			}

			T_PixelRgnEx * GetDirectRoot()
			{
				return m_pRoot;
			}

			T_PixelRgnEx * GetActRootAfterNecessaryUpdating()
			{
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

			static bool DoBothRgnsHaveTheSameRoot(T_PixelRgnEx & a_rgn1, T_PixelRgnEx & a_rgn2)
			{
				T_PixelRgnEx * pRoot1 = a_rgn1.GetActRootAfterNecessaryUpdating();
				T_PixelRgnEx * pRoot2 = a_rgn2.GetActRootAfterNecessaryUpdating();

				return pRoot1 == pRoot2;
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

			bool IsSelfRoot() const { return this == m_pRoot; }



	private:


		static void MergeRgnDataIntoAnother(T_PixelRgnEx & a_destRgn, const T_PixelRgnEx & a_srcRgn)
		{

		}

	private:

		T_PixelRgnEx * m_pRoot;

    };







}