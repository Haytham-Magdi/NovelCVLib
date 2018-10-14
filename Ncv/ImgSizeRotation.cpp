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

		//m_nCos = SRResIntScale::ScaleToI(cos(m_angRad));
		//m_nSin = SRResIntScale::ScaleToI(sin(m_angRad));

		//m_nCos = SRResIntScale::GoNearCeilByOne(m_nCos);
		//m_nSin = SRResIntScale::GoNearCeilByOne(m_nSin);

		//const int mag1 = Sqr(m_nCos) + Sqr(m_nSin);
		//Ncpp_ASSERT(mag1 >= Sqr(SRResIntScale::ScaleToI(1)));

		//m_angleRot

		Prepare();
	}

	void ImgSizeRotation::FindMinMaxXYForPointArr(const FixedVector<S64Point> & a_pointArr,
		int * a_pMin_X, int * a_pMin_Y, int * a_pMax_X, int * a_pMax_Y)
	{
		MinFinder<int> minFind_X;
		MinFinder<int> minFind_Y;
		MaxFinder<int> maxFind_X;
		MaxFinder<int> maxFind_Y;

		for (int i = 0; i < a_pointArr.GetSize(); i++)
		{
			S64Point & rPnt = a_pointArr[i];

			minFind_X.PushValue(rPnt.x);
			minFind_Y.PushValue(rPnt.y);
			maxFind_X.PushValue(rPnt.x);
			maxFind_Y.PushValue(rPnt.y);
		}
		*a_pMin_X = minFind_X.FindMin();
		*a_pMin_Y = minFind_Y.FindMin();
		*a_pMax_X = maxFind_X.FindMax();
		*a_pMax_Y = maxFind_Y.FindMax();
	}

	void ImgSizeRotation::Prepare()
	{
		const int nRotToResScaleRatio = SRRotIntScale::GetScaleVal() / SRResIntScale::GetScaleVal();

		const int nScaled_SrcWidth_Org = SRRotIntScale::ScaleToI(m_srcSiz.GetX());
		const int nScaled_SrcHeight_Org = SRRotIntScale::ScaleToI(m_srcSiz.GetY());

		S64Point addedToResMin;
		Size_2D resSize_Scaled;
		FixedVector<S64Point> resOfOrgSrcCornersArr(4);
		{
			FixedVector<S64Point> srcCornersArr(4);

			srcCornersArr.PushBack(S64Point(0, 0));
			srcCornersArr.PushBack(S64Point(0, nScaled_SrcHeight_Org));
			srcCornersArr.PushBack(S64Point(nScaled_SrcWidth_Org, 0));
			srcCornersArr.PushBack(S64Point(nScaled_SrcWidth_Org, nScaled_SrcHeight_Org));

			for (int i = 0; i < srcCornersArr.GetSize(); i++)
			{
				S64Point pnt1 = m_angleRot.RotateScaledPoint(srcCornersArr[i]);
				resOfOrgSrcCornersArr.PushBack(pnt1);

				//resOfOrgSrcCornersArr.PushBack(m_angleRot.RotateScaledPoint(srcCornersArr[i]));
			}

			int min_X, min_Y, max_X, max_Y;
			FindMinMaxXYForPointArr(resOfOrgSrcCornersArr, &min_X, &min_Y, &max_X, &max_Y);

			addedToResMin.x = 0 - min_X;
			addedToResMin.y = 0 - min_Y;

			for (int i = 0; i < resOfOrgSrcCornersArr.GetSize(); i++)
			{
				S64Point & rResPnt = resOfOrgSrcCornersArr[i];
				S64Point::Add(rResPnt, addedToResMin, &rResPnt);
				int a = 0;
			}

			resSize_Scaled.SetX(SRRotIntScale::Ceil(max_X + addedToResMin.x));
			resSize_Scaled.SetY(SRRotIntScale::Ceil(max_Y + addedToResMin.y));
		}


		m_resSiz.SetX(SRRotIntScale::IntDividByScale(resSize_Scaled.GetX()));
		m_resSiz.SetY(SRRotIntScale::IntDividByScale(resSize_Scaled.GetY()));




		/////////////////////////////////////////////


		m_resToScaledSrcMapImg = ArrayHolderUtil::CreateFrom<S32Point>(m_resSiz);




		Size_2D revSrcSize_Scaled;

		//int orgToRevRatio_X_Scaled, orgToRevRatio_Y_Scaled;
		long long orgToRevRatio_X_Scaled, orgToRevRatio_Y_Scaled;

		{
			FixedVector<S64Point> revSrcCornersArr(4);

			for (int i = 0; i < resOfOrgSrcCornersArr.GetSize(); i++)
			{
				S64Point resCornerPnt = resOfOrgSrcCornersArr[i];
				S64Point pnt1 = S64Point::Subtract(resCornerPnt, addedToResMin);
				S64Point pnt11 = m_angleRot.ReverseRotateScaledPoint(pnt1);
				//.DivideByNum((float)SRRotIntScale::GetScaleVal() / SRRotIntScale::GetScaleVal()).toS32Point();

				revSrcCornersArr.PushBack(pnt11);
				//revSrcCornersArr.PushBack(m_angleRot.ReverseRotateScaledPoint(
				//	//S64Point::Subtract(cornerPnt, addedToResMin)));
				//	pnt1));
			}


			int min_X, min_Y, max_X, max_Y;
			FindMinMaxXYForPointArr(revSrcCornersArr, &min_X, &min_Y, &max_X, &max_Y);

			Ncpp_ASSERT(0 == min_X);
			Ncpp_ASSERT(0 == min_Y);


			//{
			//	S64Point resCornerPnt = resOfOrgSrcCornersArr[i];
			//	S64Point pnt1 = S64Point::Subtract(resCornerPnt, addedToResMin);
			//	S64Point pnt11 = m_angleRot.ReverseRotateScaledPoint(pnt1);

			//	int a;
			//}


			revSrcSize_Scaled.SetX(max_X);
			revSrcSize_Scaled.SetY(max_Y);

			Size_2D orgSrcSize_Scaled;
			orgSrcSize_Scaled.SetX(SRRotIntScale::ScaleToI(this->m_srcSiz.GetX()));
			orgSrcSize_Scaled.SetY(SRRotIntScale::ScaleToI(this->m_srcSiz.GetY()));


			while (revSrcSize_Scaled.GetX() > orgSrcSize_Scaled.GetX())
			{
				orgToRevRatio_X_Scaled =
					(orgSrcSize_Scaled.GetX() * SRRotIntScale::GetScaleVal()) / revSrcSize_Scaled.GetX();

				revSrcSize_Scaled.SetX((revSrcSize_Scaled.GetX() * orgToRevRatio_X_Scaled) / SRRotIntScale::GetScaleVal());
			}

			while (revSrcSize_Scaled.GetY() > orgSrcSize_Scaled.GetY())
			{
				orgToRevRatio_Y_Scaled =
					(orgSrcSize_Scaled.GetY() * SRRotIntScale::GetScaleVal()) / revSrcSize_Scaled.GetY();

				revSrcSize_Scaled.SetY((revSrcSize_Scaled.GetY() * orgToRevRatio_Y_Scaled) / SRRotIntScale::GetScaleVal());
			}


			int a = 0;
		}










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

		//		nY1 = SRResIntScale::Floor(curSrcPnt_YX.y);

		//		nX1 = SRResIntScale::Floor(curSrcPnt_YX.x);

		//		if (!(nY1 >= 0 && nY1 < nScaled_SrcHeight_Org))
		//			//goto SrcToResEnd;
		//			goto SetResIdxToNegative;

		//		if (!(nX1 >= 0 && nX1 < nScaled_SrcWidth_Org))
		//			//goto SrcToResEnd;
		//			goto SetResIdxToNegative;

		//		srcPntArr.ResetSize();

		//		srcPntArr.PushBack(S32Point(nX1, nY1));

		//		nY2 = SRResIntScale::Ceil(curSrcPnt_YX.y);

		//		nX2 = SRResIntScale::Ceil(curSrcPnt_YX.x);

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
		//				//rSrcPnt.x / SRResIntScale::GetScaleVal(), rSrcPnt.y / SRResIntScale::GetScaleVal());
		//				SRResIntScale::IntDividByScale(rSrcPnt.x), SRResIntScale::IntDividByScale(rSrcPnt.y));

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

		//		int nX_Src = SRResIntScale::Round(curSrcPnt_YX.x);
		//		nX_Src /= SRResIntScale::GetScaleVal();

		//		if (!(nX_Src >= 0 && nX_Src < m_srcSiz.GetX()))
		//			bInImg = false;

		//		int nY_Src = SRResIntScale::Round(curSrcPnt_YX.y);
		//		nY_Src /= SRResIntScale::GetScaleVal();

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