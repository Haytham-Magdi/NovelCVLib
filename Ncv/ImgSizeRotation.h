#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>

#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_2D.h>

#include <NovelCVLib\Ncv\AngleRotation.h>


//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Channel.h>
//#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\Ncv\ImageLineItrProvider.h>
//#include <NovelCVLib\Ncv\ImageItrMgr.h>

//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


namespace Ncv
{


	class ImgSizeRotation : public Ncpp::Object
	{
		//typedef IntScale<int, float, 1000> SizeRotIntScale;
		//typedef IntScale<int, float, 1000> SRIntScale;
		
		//typedef IntScale<long long, float, 100000> SRRotIntScale;
		typedef IntScale<long long, double, 100000> SRRotIntScale;

	public:

		typedef IntScale<int, float, 100> SRResIntScale;

		ImgSizeRotation(Size_2D a_srcSiz, float a_angDig);

		//F32ImageRef GetSrcImg() { return m_srcImg; }

		//float GetAngleByDigree() { return m_angDig; }
		float GetAngleByDigree() { return m_angleRot.GetAngleByDigree(); }

		//float GetAngleByRad() { return m_angRad; }
		float GetAngleByRad() { return m_angleRot.GetAngleByRad(); }

		Size_2D GetSrcImgSiz() { return m_srcSiz; }

		Size_2D GetResImgSiz() { return m_resSiz; }

		ArrayHolder_2D_Ref<int> Get_ResToNearestSrcIndexMapImage() { return m_resToNearestSrcIndexMapImg; }

		ArrayHolder_2D_Ref<int> Get_SrcToNearestResIndexMapImage() { return m_srcToNearestResIndexMapImg; }
		


		template<class T>
		void RotateImage(const ActualArrayAccessor_2D<T> & a_destAcc, const ActualArrayAccessor_2D<T> & a_srcAcc)
		{
			RotateImage(a_destAcc.GetData(), a_destAcc.GetSize(), a_srcAcc.GetData(), a_srcAcc.GetSize());
		}


		template<class T>
		//void RotateImage(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(T) a_outAcc)
		void RotateImage(T * a_destBuf, Size_2D a_destSiz, T * a_srcBuf, Size_2D a_srcSiz)
		{
			////Ncpp_ASSERT(a_inpAcc->GetNofSteps_X() == m_srcSiz.GetX());
			////Ncpp_ASSERT(a_inpAcc->GetNofSteps_Y() == m_srcSiz.GetY());

			////Ncpp_ASSERT(a_outAcc->GetNofSteps_X() == m_resSiz.GetX());
			////Ncpp_ASSERT(a_outAcc->GetNofSteps_Y() == m_resSiz.GetY());

			//Ncpp_ASSERT(a_srcSiz.GetX() == m_srcSiz.GetX());
			//Ncpp_ASSERT(a_srcSiz.GetY() == m_srcSiz.GetY());

			//Ncpp_ASSERT(a_destSiz.GetX() == m_resSiz.GetX());
			//Ncpp_ASSERT(a_destSiz.GetY() == m_resSiz.GetY());

			//const int nScaled_SrcWidth = m_srcSiz.GetX() * SRIntScale::GetScaleVal();
			//const int nScaled_SrcHeight = m_srcSiz.GetY() * SRIntScale::GetScaleVal();

			////MemSimpleAccessor_2D<T> sac_Out = a_outAcc->GenSimpleAccessor();


			////F32ColorVal * srcBuf = (F32ColorVal *)m_srcImg->GetPixAt(0, 0);

			////F32ColorVal * resBuf = (F32ColorVal *)m_resImg->GetPixAt(0, 0);

			////int * resToSrcBuf = (int *)m_resToSrcMapImg->GetPixAt(0, 0);
			//int * resToSrcBuf = (int *)m_resToSrcMapImg->GetActualAccessor().GetData();

			//IndexCalc2D idxCalc_Src(m_srcSiz.GetX(), m_srcSiz.GetY());

			//IndexCalc2D idxCalc_Res(m_resSiz.GetX(), m_resSiz.GetY());



			//for (int y = 0; y < m_resSiz.GetY(); y++)
			//	//for (int y = 0; y < sac_Out.GetSize_Y(); y++)
			//{
			//	S32Point curPnt_Y;

			//	curPnt_Y.x = m_bgnPnt.x - y * m_nSin;
			//	curPnt_Y.y = m_bgnPnt.y + y * m_nCos;

			//	for (int x = 0; x < m_resSiz.GetX(); x++)
			//		//for (int x = 0; x < sac_Out.GetSize_X(); x++)
			//	{
			//		int nIdx_Res = idxCalc_Res.Calc(x, y);
			//		//int nIdx_Res = sac_Out->GetAt(x, y);

			//		T & rColor_Res = a_destBuf[nIdx_Res];

			//		S32Point curPnt_YX;
			//		//S32Point curPnt_YX = m_srcPntOfRes_Arr[nIdx_Res];

			//		curPnt_YX.x = curPnt_Y.x + x * m_nCos;
			//		curPnt_YX.y = curPnt_Y.y + x * m_nSin;

			//		//resToSrcBuf_X_Scaled[idxCalc_Res.Calc(x, y)] =

			//		//{
			//		int nX1, nX2, nY1, nY2;

			//		nY1 = SRIntScale::Floor(curPnt_YX.y);

			//		nX1 = SRIntScale::Floor(curPnt_YX.x);

			//		if (!(nY1 >= 0 && nY1 < nScaled_SrcHeight))
			//			//goto SrcToResEnd;
			//			goto SetResToUndefined;

			//		if (!(nX1 >= 0 && nX1 < nScaled_SrcWidth))
			//			//goto SrcToResEnd;
			//			goto SetResToUndefined;

			//		//srcPntArr.ResetSize();

			//		//srcPntArr.PushBack(cvPoint(nX1, nY1));

			//		nY2 = SRIntScale::Ceil(curPnt_YX.y);

			//		nX2 = SRIntScale::Ceil(curPnt_YX.x);

			//		//if (nY2 < 0 || nY2 >= nScaled_SrcHeight)
			//		//	nY2 = nY1;

			//		//if (nX2 < 0 || nX2 >= nScaled_SrcWidth)
			//		//	nX2 = nX1;

			//		if (!(nY2 >= 0 && nY2 < nScaled_SrcHeight))
			//			//goto SrcToResEnd;
			//			goto SetResToUndefined;

			//		if (!(nX2 >= 0 && nX2 < nScaled_SrcWidth))
			//			//goto SrcToResEnd;
			//			goto SetResToUndefined;


			//		//srcPntArr.PushBack(cvPoint(nX2, nY1));
			//		//srcPntArr.PushBack(cvPoint(nX2, nY2));
			//		//srcPntArr.PushBack(cvPoint(nX1, nY2));

			//	//SrcToResEnd:

			//		//	PrepareResImg
			//		//if (bInImg)
			//		{
			//			//T & rColor_Res = a_destBuf[nIdx_Res];

			//			int nIdx_Src = resToSrcBuf[nIdx_Res];


			//			if (nIdx_Src >= 0)
			//			{
			//				//Ncpp_ASSERT(nX1 >= 0);
			//				//Ncpp_ASSERT(nY1 >= 0);

			//				//Ncpp_ASSERT(nX2 >= 0);
			//				//Ncpp_ASSERT(nY2 >= 0);

			//				T & rColor_Src_X1_Y1 = a_srcBuf[idxCalc_Src.Calc(SRIntScale::IntDividByScale(nX1), SRIntScale::IntDividByScale(nY1))];
			//				T & rColor_Src_X1_Y2 = a_srcBuf[idxCalc_Src.Calc(SRIntScale::IntDividByScale(nX1), SRIntScale::IntDividByScale(nY2))];
			//				T & rColor_Src_X2_Y1 = a_srcBuf[idxCalc_Src.Calc(SRIntScale::IntDividByScale(nX2), SRIntScale::IntDividByScale(nY1))];
			//				T & rColor_Src_X2_Y2 = a_srcBuf[idxCalc_Src.Calc(SRIntScale::IntDividByScale(nX2), SRIntScale::IntDividByScale(nY2))];

			//				if (
			//					IsUndefined(rColor_Src_X1_Y1) ||
			//					IsUndefined(rColor_Src_X1_Y2) ||
			//					IsUndefined(rColor_Src_X2_Y1) ||
			//					IsUndefined(rColor_Src_X2_Y2)
			//					)
			//				{
			//					//SetToUndefined(&rColor_Res);
			//					goto SetResToUndefined;
			//				}


			//				//else
			//				{

			//					T color_Src_X_Y1;
			//					T color_Src_X_Y2;
			//					{
			//						//int nCur_X = (nX1 == nX2) ? nX1 : curPnt_YX.x;
			//						int nWt_X1 = (nX1 == nX2) ? SRIntScale::GetScaleVal() : abs(curPnt_YX.x - nX2);
			//						Ncpp_ASSERT(nWt_X1 <= SRIntScale::GetScaleVal());

			//						//T color_Src_X_Y1 = T::Add(
			//						//	rColor_Src_X1_Y1.MultBy(nWt_X1),
			//						//	rColor_Src_X2_Y1.MultBy(m_nScale - nWt_X1)
			//						//	).DividBy(m_nScale);



			//						//WaitedAdd_ByPtr(&rColor_Src_X1_Y1, (float)nWt_X1 / m_nScale,
			//						//	&rColor_Src_X2_Y1, (float)(m_nScale - nWt_X1) / m_nScale, &color_Src_X_Y1);

			//						//WaitedAdd_ByPtr(&rColor_Src_X1_Y2, (float)nWt_X1 / m_nScale,
			//						//	&rColor_Src_X2_Y2, (float)(m_nScale - nWt_X1) / m_nScale, &color_Src_X_Y2);

			//						WaitedAdd(rColor_Src_X1_Y1, SRIntScale::UnscaleToF(nWt_X1),
			//							rColor_Src_X2_Y1, 1 - SRIntScale::UnscaleToF(nWt_X1), &color_Src_X_Y1);

			//						WaitedAdd(rColor_Src_X1_Y2, SRIntScale::UnscaleToF(nWt_X1),
			//							rColor_Src_X2_Y2, 1 - SRIntScale::UnscaleToF(nWt_X1), &color_Src_X_Y2);



			//						//T color_Src_X_Y2 = T::Add(
			//						//	rColor_Src_X1_Y2.MultBy(nWt_X1),
			//						//	rColor_Src_X2_Y2.MultBy(m_nScale - nWt_X1)
			//						//	).DividBy(m_nScale);
			//					}

			//					{
			//						int nWt_Y1 = (nY1 == nY2) ? SRIntScale::GetScaleVal() : abs(curPnt_YX.y - nY2);
			//						Ncpp_ASSERT(nWt_Y1 <= SRIntScale::GetScaleVal());


			//						//WaitedAdd_ByPtr(&color_Src_X_Y1, (float)nWt_Y1 / m_nScale,
			//						//	&color_Src_X_Y2, (float)(m_nScale - nWt_Y1) / m_nScale, &rColor_Res);

			//						WaitedAdd(color_Src_X_Y1, SRIntScale::UnscaleToF(nWt_Y1),
			//							color_Src_X_Y2, 1 - SRIntScale::UnscaleToF(nWt_Y1), &rColor_Res);




			//						//rColor_Res = T::Add(
			//						//	color_Src_X_Y1.MultBy(nWt_Y1),
			//						//	color_Src_X_Y2.MultBy(m_nScale - nWt_Y1)
			//						//	).DividBy(m_nScale);
			//					}
			//				}
			//			}
			//			else
			//			{
			//			SetResToUndefined:
			//				////rColor_Res.AssignVal(0, 0, 0);
			//				//SetToZero(&rColor_Res);

			//				SetToUndefined(&rColor_Res);
			//			}
			//		}


			//	}

			//}



		}


	protected:

		class ResPointInfo
		{
		public:
			ResPointInfo()
			{
				WasVisited = false;
				//HasDefinedSrc = false;
				NearestDistanceToSrcPosInRes = 1000000000000;
			}


		public:
			bool WasVisited;
			//bool HasDefinedSrc;
			S64Point PosInRes;
			S64Point PosInRes_Scaled;
			S64Point NearstSrcPosInRes_Scaled;
			S64Point PosInSrc_Scaled;

			double NearestDistanceToSrcPosInRes;

		};



	protected:
		
		void FindMinMaxXYForPointArr(const FixedVector<S64Point> & a_pointArr,
			int * a_pMin_X, int * a_pMin_Y, int * a_pMax_X, int * a_pMax_Y);

		void GetScaledCornersOfSize2D(const Size_2D & a_size, FixedVector<S64Point> & a_outArr);

		void ImgSizeRotation::GetVerticesPointsOfRectangle(
			long long a_x1, long long a_y1, long long a_x2, long long a_y2, FixedVector<S64Point> & a_outArr);

		void InitResPointInfoArr(const ActualArrayAccessor_2D<ResPointInfo> & a_resPointInfoAcc, const Size_2D & a_resSize);

		static void ValidateRotScaledPointMapImg_CoreCycle(
			const S64Point & a_rPnt, const Size_2D & a_mappedSize_Scaled, const int a_scaleVal,
			bool & a_bLastPntDefined, bool & a_bTurnedToDefined, bool & a_bTurnedToUndefinedAgain,
			const bool a_canHaveUndefined
			);

		static void ValidateRotScaledPointMapImg(ArrayHolder_2D_Ref<S64Point> a_rotPointMapImg, 
			const Size_2D & a_mappeSize_Scaled, const int a_scaleVal, const bool a_canHaveUndefined);

		void PrepareFirst_SrcToScaledResPointMapImg_And_ResToScaledSrcPointMapImg(
			ArrayHolder_2D_Ref<S64Point> & a_srcToResPointMapImg, ArrayHolder_2D_Ref<S64Point> & a_resToSrcPointMapImg, 
			const S64Point & a_srcToResShift_Scaled);

		static void PrepareAFinalScaledPointMapImgFromAFirstOne(
			ArrayHolder_2D_Ref<S64Point> a_firstPointMapImg, ArrayHolder_2D_Ref<S32Point> & a_finalPointMapImg);

		static void PrepareNearestIndexMapImgFromScaledPointMapImg(
			ArrayHolder_2D_Ref<S32Point> a_scaledPointMapImg, ArrayHolder_2D_Ref<int> & a_nearestIndexMapImg);

		void Prepare();


	protected:

		//float m_angDig;
		//float m_angRad;

		//int m_nCos;
		//int m_nSin;

		AngleRotation<SRRotIntScale> m_angleRot;

		//S32Point m_bgnPnt;

		Size_2D m_srcSiz;

		Size_2D m_resSiz;

		//S32ImageRef m_resToSrcMapImg;
		ArrayHolder_2D_Ref<S32Point> m_resToScaledSrcPointMapImg;
		ArrayHolder_2D_Ref<S32Point> m_srcToScaledResPointMapImg;

		//ArrayHolder_2D_Ref<int> m_resToSrcMapImg;
		ArrayHolder_2D_Ref<int> m_resToNearestSrcIndexMapImg;
		ArrayHolder_2D_Ref<int> m_srcToNearestResIndexMapImg;


		//FixedVector< LineLimit > m_lineLimit_X_Arr;
		//FixedVector< LineLimit > m_lineLimit_V_Arr;

		//ImageItrMgrRef m_imageItrMgr;

	};


	typedef Ncpp::ObjRef< ImgSizeRotation > ImgSizeRotationRef;

}