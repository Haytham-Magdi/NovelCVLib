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


			T_PixelRgnEx * GetRootAfterNecessaryUpdating()
			{
				if (m_pRoot->IsSelfRoot())
				{
					return m_pRoot;
				}
				else
				{
					m_pRoot = m_pRoot->GetRootAfterUpdating();
					return m_pRoot;
				}
			}

			static bool DoBothRgnsHaveTheSameRoot(T_PixelRgnEx & a_rgn1, T_PixelRgnEx & a_rgn2)
			{
				T_PixelRgnEx * pRoot1 = a_rgn1.GetRootAfterNecessaryUpdating();
				T_PixelRgnEx * pRoot2 = a_rgn2.GetRootAfterNecessaryUpdating();

				return pRoot1 == pRoot2;
			}

			static void MergeRgns(T_PixelRgnEx & a_rgn1, T_PixelRgnEx & a_rgn2)
			{
				T_PixelRgnEx * pRoot1 = a_rgn1.GetRootAfterNecessaryUpdating();
				T_PixelRgnEx * pRoot2 = a_rgn2.GetRootAfterNecessaryUpdating();

				Ncpp_ASSERT(pRoot1 != pRoot2);

				T_PixelRgnEx * pMinRoot = (pRoot1 <= pRoot2) ? pRoot1 : pRoot2;
				T_PixelRgnEx * pMaxRoot = (pRoot1 > pRoot2) ? pRoot1 : pRoot2;

				pMaxRoot->m_pRoot = pMinRoot;
				T_PixelRgnEx::MergeRgnDataIntoAnother(*pMinRoot, *pMaxRoot);
			}

	private:

		bool IsSelfRoot() { return this == m_pRoot; }

		static void MergeRgnDataIntoAnother(T_PixelRgnEx & a_destRgn, const T_PixelRgnEx & a_srcRgn)
		{

		}

	private:

		T_PixelRgnEx * m_pRoot;

    };







}