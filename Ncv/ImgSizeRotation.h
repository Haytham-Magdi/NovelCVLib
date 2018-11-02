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
		typedef IntScale<long long, double, 100000> SRRotIntScale;

	public:

		typedef IntScale<int, float, 100> SRResIntScale;

		ImgSizeRotation(Size_2D a_srcSiz, float a_angDig);

		float GetAngleByDigree() { return m_angleRot.GetAngleByDigree(); }

		float GetAngleByRad() { return m_angleRot.GetAngleByRad(); }

		Size_2D GetSrcImgSiz() { return m_srcSiz; }

		Size_2D GetResImgSiz() { return m_resSiz; }

		ArrayHolder_2D_Ref<int> Get_ResToNearestSrcIndexMapImage() { return m_resToNearestSrcIndexMapImg; }

		ArrayHolder_2D_Ref<int> Get_SrcToNearestResIndexMapImage() { return m_srcToNearestResIndexMapImg; }



		template<class T>
		void RotateImage(const ActualArrayAccessor_2D<T> & a_destAcc, const ActualArrayAccessor_2D<T> & a_srcAcc)
		{
			Ncpp_ASSERT(Size_2D::AreEqual(a_srcAcc.GetSize(), m_srcSiz));
			Ncpp_ASSERT(Size_2D::AreEqual(a_destAcc.GetSize(), m_resSiz));

			const Size_2D srcSize_Scaled(m_srcSiz.GetX() * SRResIntScale::GetScaleVal(), m_srcSiz.GetY() * SRResIntScale::GetScaleVal());

			ActualArrayAccessor_2D<S32Point> resToScaledSrcPointMapAcc = m_resToScaledSrcPointMapImg->GetActualAccessor();
			Ncpp_ASSERT(Size_2D::AreEqual(resToScaledSrcPointMapAcc.GetSize(), m_resSiz));


			for (int y = 0; y < m_resSiz.GetY(); y++)
			{
				for (int x = 0; x < m_resSiz.GetX(); x++)
				{
					T & rDestVal = a_destAcc.GetAt(x, y);

					S32Point & rSrcPnt_Scaled = resToScaledSrcPointMapAcc.GetAt(x, y);
					if (rSrcPnt_Scaled.IsUndefined())
					{
						SetToUndefined(&rDestVal);
						continue;
					}

					const int nSrc_X1_Scaled = SRResIntScale::Floor(rSrcPnt_Scaled.GetX());
					const int nSrc_X2_Scaled = SRResIntScale::Ceil(rSrcPnt_Scaled.GetX());
					const int nSrc_Y1_Scaled = SRResIntScale::Floor(rSrcPnt_Scaled.GetY());
					const int nSrc_Y2_Scaled = SRResIntScale::Ceil(rSrcPnt_Scaled.GetY());

					S32Point srcPntX1Y1(
						SRResIntScale::IntDividByScale(nSrc_X1_Scaled),
						SRResIntScale::IntDividByScale(nSrc_Y1_Scaled)
						);
					Ncpp_ASSERT(srcPntX1Y1.IsInSize(m_srcSiz));
					T & rSrcValX1Y1 = a_srcAcc.GetAt(srcPntX1Y1.GetX(), srcPntX1Y1.GetY());
					AssertUndefinedOrValid(rSrcValX1Y1);

					S32Point srcPntX1Y2(
						SRResIntScale::IntDividByScale(nSrc_X1_Scaled),
						SRResIntScale::IntDividByScale(nSrc_Y2_Scaled)
						);
					Ncpp_ASSERT(srcPntX1Y2.IsInSize(m_srcSiz));
					T & rSrcValX1Y2 = a_srcAcc.GetAt(srcPntX1Y2.GetX(), srcPntX1Y2.GetY());
					AssertUndefinedOrValid(rSrcValX1Y2);

					S32Point srcPntX2Y1(
						SRResIntScale::IntDividByScale(nSrc_X2_Scaled),
						SRResIntScale::IntDividByScale(nSrc_Y1_Scaled)
						);
					Ncpp_ASSERT(srcPntX2Y1.IsInSize(m_srcSiz));
					T & rSrcValX2Y1 = a_srcAcc.GetAt(srcPntX2Y1.GetX(), srcPntX2Y1.GetY());
					AssertUndefinedOrValid(rSrcValX2Y1);

					S32Point srcPntX2Y2(
						SRResIntScale::IntDividByScale(nSrc_X2_Scaled),
						SRResIntScale::IntDividByScale(nSrc_Y2_Scaled)
						);
					Ncpp_ASSERT(srcPntX2Y2.IsInSize(m_srcSiz));
					T & rSrcValX2Y2 = a_srcAcc.GetAt(srcPntX2Y2.GetX(), srcPntX2Y2.GetY());
					AssertUndefinedOrValid(rSrcValX2Y2);


					if (
						IsUndefined(rSrcValX1Y1) ||
						IsUndefined(rSrcValX1Y2) ||
						IsUndefined(rSrcValX2Y1) ||
						IsUndefined(rSrcValX2Y2)
						)
					{
						SetToUndefined(&rDestVal);
						continue;
					}



					{
						T srcValXY1;
						T srcValXY2;
						{
							int nWt_SrcX1_Scaled = nSrc_X2_Scaled - rSrcPnt_Scaled.GetX();
							Ncpp_ASSERT(nWt_SrcX1_Scaled >= 0);
							Ncpp_ASSERT(nWt_SrcX1_Scaled < SRResIntScale::GetScaleVal());

							//int nWt_SrcX1_Scaled = (nSrc_X1_Scaled == nSrc_X2_Scaled) ? SRResIntScale::GetScaleVal() : abs(rSrcPnt_Scaled.GetX() - nSrc_X2_Scaled);
							//Ncpp_ASSERT(nWt_SrcX1_Scaled <= SRResIntScale::GetScaleVal());

							WaitedAdd(rSrcValX1Y1, SRResIntScale::UnscaleToF(nWt_SrcX1_Scaled),
								rSrcValX2Y1, 1 - SRResIntScale::UnscaleToF(nWt_SrcX1_Scaled), &srcValXY1);

							WaitedAdd(rSrcValX1Y2, SRResIntScale::UnscaleToF(nWt_SrcX1_Scaled),
								rSrcValX2Y2, 1 - SRResIntScale::UnscaleToF(nWt_SrcX1_Scaled), &srcValXY2);
						}

						{
							int nWt_SrcY1_Scaled = nSrc_Y2_Scaled - rSrcPnt_Scaled.GetY();
							Ncpp_ASSERT(nWt_SrcY1_Scaled >= 0);
							Ncpp_ASSERT(nWt_SrcY1_Scaled < SRResIntScale::GetScaleVal());

							//int nWt_SrcY1_Scaled = (nSrc_Y1_Scaled == nSrc_Y2_Scaled) ? SRResIntScale::GetScaleVal() : abs(rSrcPnt_Scaled.y - nSrc_Y2_Scaled);
							//Ncpp_ASSERT(nWt_SrcY1_Scaled <= SRResIntScale::GetScaleVal());

							WaitedAdd(srcValXY1, SRResIntScale::UnscaleToF(nWt_SrcY1_Scaled),
								srcValXY2, 1 - SRResIntScale::UnscaleToF(nWt_SrcY1_Scaled), &rDestVal);
						}
					}


				}	//	end for x
			}	//	end for y

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

		AngleRotation<SRRotIntScale> m_angleRot;

		Size_2D m_srcSiz;

		Size_2D m_resSiz;

		ArrayHolder_2D_Ref<S32Point> m_resToScaledSrcPointMapImg;
		ArrayHolder_2D_Ref<S32Point> m_srcToScaledResPointMapImg;

		ArrayHolder_2D_Ref<int> m_resToNearestSrcIndexMapImg;
		ArrayHolder_2D_Ref<int> m_srcToNearestResIndexMapImg;

	};


	typedef Ncpp::ObjRef< ImgSizeRotation > ImgSizeRotationRef;

}