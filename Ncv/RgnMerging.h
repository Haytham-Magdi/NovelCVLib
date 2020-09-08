#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncv
{
	using namespace Ncpp;

	template<class T_RgnPix>
    class RgnMerging
    {
        public:

			PixelRgn() 
			{
				m_pRoot = (T_RgnPix *)this;

			}


			T_RgnPix * GetActRootAfterNecessaryUpdating()
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

			static bool DoBothRgnsHaveTheSameRoot(T_RgnPix & a_rgn1, T_RgnPix & a_rgn2)
			{
				T_RgnPix * pRoot1 = a_rgn1.GetActRootAfterNecessaryUpdating();
				T_RgnPix * pRoot2 = a_rgn2.GetActRootAfterNecessaryUpdating();

				return pRoot1 == pRoot2;
			}

			static void MergeRgns(T_RgnPix & a_rgn1, T_RgnPix & a_rgn2)
			{
				T_RgnPix * pRoot1 = a_rgn1.GetActRootAfterNecessaryUpdating();
				T_RgnPix * pRoot2 = a_rgn2.GetActRootAfterNecessaryUpdating();

				Ncpp_ASSERT(pRoot1 != pRoot2);

				T_RgnPix * pMinRoot = (pRoot1 <= pRoot2) ? pRoot1 : pRoot2;
				T_RgnPix * pMaxRoot = (pRoot1 > pRoot2) ? pRoot1 : pRoot2;

				pMaxRoot->m_pRoot = pMinRoot;
				T_RgnPix::MergeRgnDataIntoAnother(*pMinRoot, *pMaxRoot);
			}

			bool IsSelfRoot() const { return this == m_pRoot; }

	private:


		static void MergeRgnDataIntoAnother(T_RgnPix & a_destRgn, const T_RgnPix & a_srcRgn)
		{

		}

	private:

		T_RgnPix * m_pRoot;

    };







}