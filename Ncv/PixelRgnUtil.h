#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncv
{
	namespace PixelRgnUtil
	{

		using namespace Ncpp;


		template <class T_PixelRgn>
		void PrepareRandomColorRepForRgns(ActualArrayAccessor_2D<T_PixelRgn> a_inpAcc, ActualArrayAccessor_2D<F32ColorVal> a_outAcc)
		{
			Ncpp_ASSERT(Size_2D::AreEqual(a_inpAcc.GetSize(), a_outAcc.GetSize()));
			PrepareRandomColorRepForRgns(a_inpAcc.GenAcc_1D(), a_outAcc.GenAcc_1D());
		}

		template <class T_PixelRgn>
		void PrepareRandomColorRepForRgns(ActualArrayAccessor_1D<T_PixelRgn> a_inpAcc_1D, ActualArrayAccessor_1D<F32ColorVal> a_outAcc_1D)
		{
			Ncpp_ASSERT(a_inpAcc_1D.GetSize() == a_outAcc_1D.GetSize());

			//ArrayHolder_1D<bool> isColorDoneHolder = ArrayHolderUtil::CreateFrom()
			FixedVector<bool> isColorDoneVect;
			isColorDoneVect.InitSize(a_inpAcc_1D.GetSize());
			isColorDoneVect.SetAllToVal(false);

			T_PixelRgn * pixelRgnHeadPtr = a_inpAcc_1D.GetData();
			for (int i = 0; i < a_inpAcc_1D.GetSize(); i++)
			{
				T_PixelRgn & rRgn = a_inpAcc_1D[i];
				const T_PixelRgn * pRootRgn = (T_PixelRgn *)rRgn.GetActRootAfterNecessaryUpdating();

				const int rootIndex = pRootRgn - pixelRgnHeadPtr;

				bool & rIsRootColorDone = isColorDoneVect[rootIndex];

				F32ColorVal & rRootColor = a_outAcc_1D[rootIndex];
				if (!rIsRootColorDone)
				{
					rRootColor.val0 = (float)(rand() % 255);
					rRootColor.val1 = (float)(rand() % 255);
					rRootColor.val2 = (float)(rand() % 255);

					rIsRootColorDone = true;
				}

				//	if rRgn is the root by itself.
				if (rRgn.IsSelfRoot())
				{
					continue;
				}

				F32ColorVal & rRgnColor = a_outAcc_1D[i];

				Assign(&rRgnColor, rRootColor);
			
			}	//	end i for.

		}


	}
}