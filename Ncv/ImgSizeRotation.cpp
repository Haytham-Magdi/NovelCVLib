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


	void ImgSizeRotation::GetScaledCornersOfSize2D(const Size_2D & a_size, FixedVector<S64Point> & a_outArr)
	{
		const int nScaled_Width = SRRotIntScale::ScaleToI(a_size.GetX());
		const int nScaled_Height = SRRotIntScale::ScaleToI(a_size.GetY());

		a_outArr.SetCapacity(4);

		a_outArr.PushBack(S64Point(0, 0));
		a_outArr.PushBack(S64Point(0, nScaled_Height));
		a_outArr.PushBack(S64Point(nScaled_Width, 0));
		a_outArr.PushBack(S64Point(nScaled_Width, nScaled_Height));
	}


	void ImgSizeRotation::GetVerticesPointsOfRectangle(
		long long a_x1, long long a_y1, long long a_x2, long long a_y2, FixedVector<S64Point> & a_outArr)
	{
		a_outArr.SetCapacity(4);

		a_outArr.PushBack(S64Point(a_x1, a_y1));
		a_outArr.PushBack(S64Point(a_x1, a_y2));
		a_outArr.PushBack(S64Point(a_x2, a_y1));
		a_outArr.PushBack(S64Point(a_x2, a_y2));
	}


	void ImgSizeRotation::InitResPointInfoArr(const ActualArrayAccessor_2D<ResPointInfo> & a_resPointInfoAcc, const Size_2D & a_resSize)
	{
		for (int resY = 0; resY < a_resSize.GetY(); resY++)
		{
			for (int resX = 0; resX < a_resSize.GetX(); resX++)
			{
				ResPointInfo & rResPntInfo = a_resPointInfoAcc.GetAt(resX, resY);
				rResPntInfo.WasVisited = false;
				rResPntInfo.PosInRes = S64Point(resX, resY);
				rResPntInfo.PosInRes_Scaled = rResPntInfo.PosInRes.MultiplyByIntNum(SRRotIntScale::GetScaleVal());
			}
		}
	}








	void ImgSizeRotation::Prepare_SrcToResPointMapImg_And_ResPointInfoImg(
		ArrayHolder_2D_Ref<S64Point> & a_srcToResPointMapImg, ArrayHolder_2D_Ref<ResPointInfo> & a_resPointInfoImg, const S64Point & a_addedToResMin)
	{
		Size_2D resSize_Scaled(
			(int)(m_resSiz.GetX() * SRRotIntScale::GetScaleVal()),
			(int)(m_resSiz.GetY() * SRRotIntScale::GetScaleVal())
			);

		a_resPointInfoImg = ArrayHolderUtil::CreateFrom<ResPointInfo>(m_resSiz);
		ActualArrayAccessor_2D<ResPointInfo> resPointInfoAcc = a_resPointInfoImg->GetActualAccessor();

		InitResPointInfoArr(resPointInfoAcc, m_resSiz);

		/////-------------------------------------------------------------


		a_srcToResPointMapImg = ArrayHolderUtil::CreateFrom<S64Point>(m_srcSiz);
		ActualArrayAccessor_2D<S64Point> srcToResPointMapAcc = a_srcToResPointMapImg->GetActualAccessor();

		for (int srcY = 0; srcY < m_srcSiz.GetY(); srcY++)
		{
			for (int srcX = 0; srcX < m_srcSiz.GetX(); srcX++)
			{
				S64Point srcPnt(srcX, srcY);
				S64Point srcPnt_Scaled = srcPnt.MultiplyByIntNum(SRRotIntScale::GetScaleVal());

				S64Point & rResPnt_Scaled = srcToResPointMapAcc.GetAt(srcX, srcY);
				m_angleRot.RotateScaledPoint(srcPnt_Scaled, &rResPnt_Scaled);

				rResPnt_Scaled.IncBy(a_addedToResMin);

				Ncpp_ASSERT(rResPnt_Scaled.GetX() >= 0);
				Ncpp_ASSERT(rResPnt_Scaled.GetY() >= 0);

				long long resX_NbrBef_Scaled = SRRotIntScale::Floor(rResPnt_Scaled.GetX());
				long long resY_NbrBef_Scaled = SRRotIntScale::Floor(rResPnt_Scaled.GetY());

				Ncpp_ASSERT(resX_NbrBef_Scaled >= 0);
				Ncpp_ASSERT(resY_NbrBef_Scaled >= 0);

				long long resX_NbrAft_Scaled = SRRotIntScale::Ceil(rResPnt_Scaled.GetX());
				long long resY_NbrAft_Scaled = SRRotIntScale::Ceil(rResPnt_Scaled.GetY());

				Ncpp_ASSERT(resX_NbrAft_Scaled <= resSize_Scaled.GetX() - SRRotIntScale::GetScaleVal());
				Ncpp_ASSERT(resY_NbrAft_Scaled <= resSize_Scaled.GetY() - SRRotIntScale::GetScaleVal());

				FixedVector<S64Point> nbrVerticiesInResArr;

				GetVerticesPointsOfRectangle(resX_NbrBef_Scaled, resY_NbrBef_Scaled,
					resX_NbrAft_Scaled, resY_NbrAft_Scaled, nbrVerticiesInResArr);

				for (int i = 0; i < nbrVerticiesInResArr.GetSize(); i++)
				{
					S64Point & rNbrInResVert_Scaled = nbrVerticiesInResArr[i];
					S64Point nbrInResVert = rNbrInResVert_Scaled.DivideByIntNum(SRRotIntScale::GetScaleVal());

					ResPointInfo & rNbrVertInfo = resPointInfoAcc.GetAt(nbrInResVert.GetX(), nbrInResVert.GetY());

					if (!rNbrVertInfo.WasVisited)
					{
						rNbrVertInfo.WasVisited = true;
					}

					Ncpp_ASSERT(S64Point::AreEqual(rNbrInResVert_Scaled, rNbrVertInfo.PosInRes_Scaled));

					double toNbrVertDistance = S64Point::CalcDistance(
						rNbrVertInfo.PosInRes_Scaled, rResPnt_Scaled);

					if (toNbrVertDistance >= rNbrVertInfo.NearestDistanceToSrcPosInRes)
					{
						continue;
					}

					rNbrVertInfo.NearestDistanceToSrcPosInRes = toNbrVertDistance;
					rNbrVertInfo.NearstSrcPosInRes_Scaled = rResPnt_Scaled;

					S64Point diffPnt = S64Point::Subtract(rNbrVertInfo.PosInRes_Scaled, rResPnt_Scaled);
					S64Point reverseRotatedDiffPnt;
					m_angleRot.ReverseRotateScaledPoint(diffPnt, &reverseRotatedDiffPnt);

					S64Point::Add(srcPnt_Scaled, reverseRotatedDiffPnt, &rNbrVertInfo.PosInSrc_Scaled);


					//if (
					//	rNbrVertInfo.PosInSrc_Scaled.GetX() < 0 ||
					//	rNbrVertInfo.PosInSrc_Scaled.GetY() < 0 ||

					//	(rNbrVertInfo.PosInSrc_Scaled.GetX() > srcSize_Scaled.GetX() - SRRotIntScale::GetScaleVal()) ||
					//	(rNbrVertInfo.PosInSrc_Scaled.GetY() > srcSize_Scaled.GetY() - SRRotIntScale::GetScaleVal())
					//	)
					//{
					//	rNbrVertInfo.HasDefinedSrc = false;
					//}
					//else
					//{
					//	rNbrVertInfo.HasDefinedSrc = true;
					//}



				}

			}
		}


	}
















	void ImgSizeRotation::Prepare()
	{
		const int nRotToResScaleRatio = SRRotIntScale::GetScaleVal() / SRResIntScale::GetScaleVal();

		//const int nScaled_SrcWidth_Org = SRRotIntScale::ScaleToI(m_srcSiz.GetX());
		//const int nScaled_SrcHeight_Org = SRRotIntScale::ScaleToI(m_srcSiz.GetY());

		S64Point addedToResMin;
		Size_2D resSize_Scaled;
		FixedVector<S64Point> resOfOrgSrcCornersArr(4);

		{
			FixedVector<S64Point> srcCornersArr;
			GetScaledCornersOfSize2D(m_srcSiz, srcCornersArr);

			for (int i = 0; i < srcCornersArr.GetSize(); i++)
			{
				resOfOrgSrcCornersArr.PushBack(m_angleRot.RotateScaledPoint(srcCornersArr[i]));
			}

			int min_X, min_Y, max_X, max_Y;
			FindMinMaxXYForPointArr(resOfOrgSrcCornersArr, &min_X, &min_Y, &max_X, &max_Y);

			addedToResMin.SetValue(-min_X, -min_Y);

			for (int i = 0; i < resOfOrgSrcCornersArr.GetSize(); i++)
			{
				S64Point & rResPnt = resOfOrgSrcCornersArr[i];
				//S64Point::Add(rResPnt, addedToResMin, &rResPnt);
				rResPnt.IncBy(addedToResMin);
			}

			resSize_Scaled.SetX(SRRotIntScale::Ceil(max_X + addedToResMin.x) + SRRotIntScale::GetScaleVal());
			resSize_Scaled.SetY(SRRotIntScale::Ceil(max_Y + addedToResMin.y) + SRRotIntScale::GetScaleVal());
		}


		m_resSiz.SetX(SRRotIntScale::IntDividByScale(resSize_Scaled.GetX()));
		m_resSiz.SetY(SRRotIntScale::IntDividByScale(resSize_Scaled.GetY()));



		/////-------------------------------------------------------------

		Size_2D srcSize_Scaled(m_srcSiz.GetX() * SRRotIntScale::GetScaleVal(), m_srcSiz.GetY() * SRRotIntScale::GetScaleVal());

		ArrayHolder_2D_Ref<ResPointInfo> resPointInfoImg;

		ArrayHolder_2D_Ref<S64Point> srcToResPointMapImg;

		Prepare_SrcToResPointMapImg_And_ResPointInfoImg(srcToResPointMapImg, resPointInfoImg, addedToResMin);
			



		///////////////////////////////////////////////



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





		/////////////////////////////////////////////


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