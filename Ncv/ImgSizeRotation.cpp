#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderUtil.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\ImgSizeRotation.h>


#define M_PI 3.14159265358979323846
//#define M_PI 3.14159265358979323846f


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	using namespace Ncv::ImageOperations2;

	ImgSizeRotation::ImgSizeRotation(Size_2D a_srcSiz, float a_angDig) : m_angleRot(a_angDig)
	{
		//Ncpp_ASSERT(a_angDig >= 0);
		//Ncpp_ASSERT(a_angDig <= 90);

		m_srcSiz = a_srcSiz;

		//m_angDig = a_angDig;
		//m_angRad = (float)(a_angDig * M_PI / 180);

		//m_nCos = SRIntScale::ScaleToI(cos(m_angRad));
		//m_nSin = SRIntScale::ScaleToI(sin(m_angRad));

		//m_nCos = SRIntScale::GoNearCeilByOne(m_nCos);
		//m_nSin = SRIntScale::GoNearCeilByOne(m_nSin);

		//const int mag1 = Sqr(m_nCos) + Sqr(m_nSin);
		//Ncpp_ASSERT(mag1 >= Sqr(SRIntScale::ScaleToI(1)));

		//m_angleRot

		Prepare();
	}

	void ImgSizeRotation::Prepare()
	{
		const int nScaled_SrcWidth_Org = SRIntScale::ScaleToI(m_srcSiz.GetX());
		const int nScaled_SrcHeight_Org = SRIntScale::ScaleToI(m_srcSiz.GetY());

		S32Point addedToResMin;
		Size_2D resSize_Scaled;
		FixedVector<S32Point> resOfOrgSrcCornersArr(4);
		{
			FixedVector<S32Point> srcCornersArr(4);

			srcCornersArr.PushBack(S32Point(0, 0));
			srcCornersArr.PushBack(S32Point(0, nScaled_SrcHeight_Org));
			srcCornersArr.PushBack(S32Point(nScaled_SrcWidth_Org, 0));
			srcCornersArr.PushBack(S32Point(nScaled_SrcWidth_Org, nScaled_SrcHeight_Org));

			for (int i = 0; i < srcCornersArr.GetSize(); i++)
			{
				resOfOrgSrcCornersArr.PushBack(m_angleRot.RotateScaledPoint(srcCornersArr[i]));
			}

			MinFinder<int> minFind_X;
			MinFinder<int> minFind_Y;
			MaxFinder<int> maxFind_X;
			MaxFinder<int> maxFind_Y;

			for (int i = 0; i < resOfOrgSrcCornersArr.GetSize(); i++)
			{
				S32Point & rResPnt = resOfOrgSrcCornersArr[i];

				minFind_X.PushValue(rResPnt.x);
				minFind_Y.PushValue(rResPnt.y);
				maxFind_X.PushValue(rResPnt.x);
				maxFind_Y.PushValue(rResPnt.y);
			}
			int min_X = minFind_X.FindMin();
			int min_Y = minFind_Y.FindMin();
			int max_X = maxFind_X.FindMax();
			int max_Y = maxFind_Y.FindMax();

			addedToResMin.x = 0 - min_X;
			addedToResMin.y = 0 - min_Y;

			for (int i = 0; i < resOfOrgSrcCornersArr.GetSize(); i++)
			{
				S32Point & rResPnt = resOfOrgSrcCornersArr[i];
				S32Point::Add(rResPnt, addedToResMin, &rResPnt);
				int a = 0;
			}

			resSize_Scaled.SetX(SRIntScale::Ceil(max_X + addedToResMin.x));
			resSize_Scaled.SetY(SRIntScale::Ceil(max_Y + addedToResMin.y));
		}


		m_resSiz.SetX(SRIntScale::IntDividByScale(resSize_Scaled.GetX()));
		m_resSiz.SetY(SRIntScale::IntDividByScale(resSize_Scaled.GetY()));



		Size_2D revSrcSize_Scaled;

		int orgToRevRatio_X_Scaled, orgToRevRatio_Y_Scaled;

		{
			FixedVector<S32Point> revSrcCornersArr(4);

			for (int i = 0; i < resOfOrgSrcCornersArr.GetSize(); i++)
			{
				S32Point resCornerPnt = resOfOrgSrcCornersArr[i];
				S32Point pnt1 = S32Point::Subtract(resCornerPnt, addedToResMin);
				S32Point pnt11 = m_angleRot.ReverseRotateScaledPoint(pnt1);

				revSrcCornersArr.PushBack(pnt11);
				//revSrcCornersArr.PushBack(m_angleRot.ReverseRotateScaledPoint(
				//	//S32Point::Subtract(cornerPnt, addedToResMin)));
				//	pnt1));
			}

			MinFinder<int> minFind_X;
			MinFinder<int> minFind_Y;
			MaxFinder<int> maxFind_X;
			MaxFinder<int> maxFind_Y;

			for (int i = 0; i < revSrcCornersArr.GetSize(); i++)
			{
				S32Point & rRevSrcPnt = revSrcCornersArr[i];

				minFind_X.PushValue(rRevSrcPnt.x);
				minFind_Y.PushValue(rRevSrcPnt.y);
				maxFind_X.PushValue(rRevSrcPnt.x);
				maxFind_Y.PushValue(rRevSrcPnt.y);
			}
			int min_X = minFind_X.FindMin();
			int min_Y = minFind_Y.FindMin();
			int max_X = maxFind_X.FindMax();
			int max_Y = maxFind_Y.FindMax();

			Ncpp_ASSERT(0 == min_X);
			Ncpp_ASSERT(0 == min_Y);

			revSrcSize_Scaled.SetX(max_X);
			revSrcSize_Scaled.SetY(max_Y);

			Size_2D orgSrcSize_Scaled;
			orgSrcSize_Scaled.SetX(SRIntScale::ScaleToI(this->m_srcSiz.GetX()));
			orgSrcSize_Scaled.SetY(SRIntScale::ScaleToI(this->m_srcSiz.GetY()));


			while (revSrcSize_Scaled.GetX() > orgSrcSize_Scaled.GetX())
			{
				orgToRevRatio_X_Scaled =
					(orgSrcSize_Scaled.GetX() * SRIntScale::GetScaleVal()) / revSrcSize_Scaled.GetX();

				revSrcSize_Scaled.SetX((revSrcSize_Scaled.GetX() * orgToRevRatio_X_Scaled) / SRIntScale::GetScaleVal());
			}

			while (revSrcSize_Scaled.GetY() > orgSrcSize_Scaled.GetY())
			{
				orgToRevRatio_Y_Scaled =
					(orgSrcSize_Scaled.GetY() * SRIntScale::GetScaleVal()) / revSrcSize_Scaled.GetY();

				revSrcSize_Scaled.SetY((revSrcSize_Scaled.GetY() * orgToRevRatio_Y_Scaled) / SRIntScale::GetScaleVal());
			}


			int a = 0;
		}






		m_resToScaledSrcMapImg = ArrayHolderUtil::CreateFrom<S32Point>(m_resSiz);




//-----------------------------

		//m_resToSrcMapImg = ArrayHolderUtil::CreateFrom<int>(m_resSiz);
		//int * resToSrcBuf = (int *)m_resToSrcMapImg->GetActualAccessor().GetData();

		//m_srcToResMapImg = ArrayHolderUtil::CreateFrom<int>(m_srcSiz);
		//int * srcToResBuf = (int *)m_srcToResMapImg->GetActualAccessor().GetData();


		//ArrayHolder_2D_Ref<int> srcMinDistImg = ArrayHolderUtil::CreateFrom<int>(m_srcSiz);
		//int *  srcMinDistBuf = (int *)srcMinDistImg->GetActualAccessor().GetData();

		//const int nGreatDist = 10000000;
		//FillImage(srcMinDistImg->GetVirtAccessor(), nGreatDist);

		//int nMappedSrcCnt = 0;





		//IndexCalc2D idxCalc_Src(m_srcSiz.GetX(), m_srcSiz.GetY());

		//IndexCalc2D idxCalc_Res(m_resSiz.GetX(), m_resSiz.GetY());

		////S32Point curPnt = m_bgnPnt;

		//FixedVector< S32Point > srcPntArr(100);

		//for (int y = 0; y < m_resSiz.GetY(); y++)
		//{
		//	S32Point curSrcPnt_Y;

		//	curSrcPnt_Y.x = m_bgnPnt.x - y * m_nSin;
		//	curSrcPnt_Y.y = m_bgnPnt.y + y * m_nCos;

		//	for (int x = 0; x < m_resSiz.GetX(); x++)
		//	{
		//		int nIdx_Res = idxCalc_Res.Calc(x, y);

		//		S32Point curSrcPnt_YX;
		//		//S32Point curSrcPnt_YX = m_srcPntOfRes_Arr[nIdx_Res];



		//		curSrcPnt_YX.x = curSrcPnt_Y.x + x * m_nCos;
		//		curSrcPnt_YX.y = curSrcPnt_Y.y + x * m_nSin;

		//		//resToSrcBuf_X_Scaled[idxCalc_Res.Calc(x, y)] =

		//		//{
		//		int nX1, nX2, nY1, nY2;

		//		nY1 = SRIntScale::Floor(curSrcPnt_YX.y);

		//		nX1 = SRIntScale::Floor(curSrcPnt_YX.x);

		//		if (!(nY1 >= 0 && nY1 < nScaled_SrcHeight_Org))
		//			//goto SrcToResEnd;
		//			goto SetResIdxToNegative;

		//		if (!(nX1 >= 0 && nX1 < nScaled_SrcWidth_Org))
		//			//goto SrcToResEnd;
		//			goto SetResIdxToNegative;

		//		srcPntArr.ResetSize();

		//		srcPntArr.PushBack(S32Point(nX1, nY1));

		//		nY2 = SRIntScale::Ceil(curSrcPnt_YX.y);

		//		nX2 = SRIntScale::Ceil(curSrcPnt_YX.x);

		//		if (nY2 < 0 || nY2 >= nScaled_SrcHeight_Org)
		//			//nY2 = nY1;
		//			goto SetResIdxToNegative;

		//		if (nX2 < 0 || nX2 >= nScaled_SrcWidth_Org)
		//			//nX2 = nX1;
		//			goto SetResIdxToNegative;

		//		srcPntArr.PushBack(S32Point(nX2, nY1));
		//		srcPntArr.PushBack(S32Point(nX2, nY2));
		//		srcPntArr.PushBack(S32Point(nX1, nY2));


		//		goto SrcToResEnd;


		//	SetResIdxToNegative:
		//		resToSrcBuf[nIdx_Res] = -1;
		//		continue;


		//	SrcToResEnd:

		//		for (int i = 0; i < srcPntArr.GetSize(); i++)
		//		{
		//			S32Point & rSrcPnt = srcPntArr[i];

		//			int nIdx_Src = idxCalc_Src.Calc(
		//				//rSrcPnt.x / SRIntScale::GetScaleVal(), rSrcPnt.y / SRIntScale::GetScaleVal());
		//				SRIntScale::IntDividByScale(rSrcPnt.x), SRIntScale::IntDividByScale(rSrcPnt.y));

		//			int nOldDist = srcMinDistBuf[nIdx_Src];

		//			if (nGreatDist == nOldDist)
		//				nMappedSrcCnt++;

		//			int nNewDist = abs(curSrcPnt_YX.x - rSrcPnt.x) +
		//				abs(curSrcPnt_YX.y - rSrcPnt.y);

		//			if (nNewDist < nOldDist)
		//			{
		//				srcMinDistBuf[nIdx_Src] = nNewDist;
		//				srcToResBuf[nIdx_Src] = nIdx_Res;
		//			}

		//		}
		//		//}


		//		bool bInImg = true;

		//		int nX_Src = SRIntScale::Round(curSrcPnt_YX.x);
		//		nX_Src /= SRIntScale::GetScaleVal();

		//		if (!(nX_Src >= 0 && nX_Src < m_srcSiz.GetX()))
		//			bInImg = false;

		//		int nY_Src = SRIntScale::Round(curSrcPnt_YX.y);
		//		nY_Src /= SRIntScale::GetScaleVal();

		//		if (!(nY_Src >= 0 && nY_Src < m_srcSiz.GetY()))
		//			bInImg = false;

		//		int nIdx_Src = -1;

		//		if (bInImg)
		//		{
		//			nIdx_Src = idxCalc_Src.Calc(nX_Src, nY_Src);
		//		}

		//		resToSrcBuf[nIdx_Res] = nIdx_Src;

		//	}
		//}

		//int nSrcSiz1D = m_srcSiz.GetX() * m_srcSiz.GetY();

		//Ncpp_ASSERT(nMappedSrcCnt == nSrcSiz1D);

	}



}