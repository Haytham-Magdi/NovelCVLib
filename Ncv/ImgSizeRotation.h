#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>

#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_2D.h>


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
	public:

		ImgSizeRotation(Size_2D a_srcSiz, float a_angDig);

		//F32ImageRef GetSrcImg() { return m_srcImg; }

		float GetAngleByDigree() { return m_angDig; }

		float GetAngleByRad() { return m_angRad; }

		Size_2D GetSrcImgSiz() { return m_srcSiz; }

		Size_2D GetResImgSiz() { return m_resSiz; }

		S32ImageRef Get_ResToSrcMapImage() { return m_resToSrcMapImg; }

		//F32ImageRef GetResImg() { return m_resImg; }

		S32ImageRef Get_SrcToResMapImage() { return m_srcToResMapImg; }

		//ImageItrMgrRef GetImageItrMgr() { return m_imageItrMgr; }

		CvPoint & GetBgnPnt() { return m_bgnPnt; }


		template<class T>
		void RotateImage(const ActualArrayAccessor_2D<T> & a_destAcc, const ActualArrayAccessor_2D<T> & a_srcAcc)
		{
			RotateImage(a_destAcc.GetData(), a_destAcc.GetSize(), a_srcAcc.GetData(), a_srcAcc.GetSize());
		}


		template<class T>
		//void RotateImage(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(T) a_outAcc)
		void RotateImage(T * a_destBuf, Size_2D a_destSiz, T * a_srcBuf, Size_2D a_srcSiz)
		{
			//Ncpp_ASSERT(a_inpAcc->GetNofSteps_X() == m_srcSiz.GetX());
			//Ncpp_ASSERT(a_inpAcc->GetNofSteps_Y() == m_srcSiz.GetY());

			//Ncpp_ASSERT(a_outAcc->GetNofSteps_X() == m_resSiz.GetX());
			//Ncpp_ASSERT(a_outAcc->GetNofSteps_Y() == m_resSiz.GetY());

			Ncpp_ASSERT(a_srcSiz.GetX() == m_srcSiz.GetX());
			Ncpp_ASSERT(a_srcSiz.GetY() == m_srcSiz.GetY());

			Ncpp_ASSERT(a_destSiz.GetX() == m_resSiz.GetX());
			Ncpp_ASSERT(a_destSiz.GetY() == m_resSiz.GetY());

			const int nScaled_SrcWidth = m_srcSiz.GetX() * m_nScale;
			const int nScaled_SrcHeight = m_srcSiz.GetY() * m_nScale;

			//MemSimpleAccessor_2D<T> sac_Out = a_outAcc->GenSimpleAccessor();


			//F32ColorVal * srcBuf = (F32ColorVal *)m_srcImg->GetPixAt(0, 0);

			//F32ColorVal * resBuf = (F32ColorVal *)m_resImg->GetPixAt(0, 0);

			int * resToSrcBuf = (int *)m_resToSrcMapImg->GetPixAt(0, 0);

			IndexCalc2D idxCalc_Src(m_srcSiz.GetX(), m_srcSiz.GetY());

			IndexCalc2D idxCalc_Res(m_resSiz.GetX(), m_resSiz.GetY());



			for (int y = 0; y < m_resSiz.GetY(); y++)
				//for (int y = 0; y < sac_Out.GetSize_Y(); y++)
			{
				CvPoint curPnt_Y;

				curPnt_Y.x = m_bgnPnt.x - y * m_nSin;
				curPnt_Y.y = m_bgnPnt.y + y * m_nCos;

				for (int x = 0; x < m_resSiz.GetX(); x++)
					//for (int x = 0; x < sac_Out.GetSize_X(); x++)
				{
					int nIdx_Res = idxCalc_Res.Calc(x, y);
					//int nIdx_Res = sac_Out->GetAt(x, y);

					CvPoint curPnt_X;
					//CvPoint curPnt_X = m_srcPntOfRes_Arr[nIdx_Res];

					curPnt_X.x = curPnt_Y.x + x * m_nCos;
					curPnt_X.y = curPnt_Y.y + x * m_nSin;

					//resToSrcBuf_X_Scaled[idxCalc_Res.Calc(x, y)] =

					//{
					int nX1, nX2, nY1, nY2;

					nY1 = (curPnt_X.y / m_nScale) * m_nScale;

					nX1 = (curPnt_X.x / m_nScale) * m_nScale;

					if (!(nY1 >= 0 && nY1 < nScaled_SrcHeight))
						goto SrcToResEnd;

					if (!(nX1 >= 0 && nX1 < nScaled_SrcWidth))
						goto SrcToResEnd;

					//srcPntArr.ResetSize();

					//srcPntArr.PushBack(cvPoint(nX1, nY1));

					nY2 = AddRoundByMin(curPnt_X.y);

					nX2 = AddRoundByMin(curPnt_X.x);

					if (nY2 < 0 || nY2 >= nScaled_SrcHeight)
						nY2 = nY1;

					if (nX2 < 0 || nX2 >= nScaled_SrcWidth)
						nX2 = nX1;

					//srcPntArr.PushBack(cvPoint(nX2, nY1));
					//srcPntArr.PushBack(cvPoint(nX2, nY2));
					//srcPntArr.PushBack(cvPoint(nX1, nY2));

				SrcToResEnd:

					//	PrepareResImg
					//if (bInImg)
					{
						T & rColor_Res = a_destBuf[nIdx_Res];

						int nIdx_Src = resToSrcBuf[nIdx_Res];


						if (nIdx_Src >= 0)
						{
							//Ncpp_ASSERT(nX1 >= 0);
							//Ncpp_ASSERT(nY1 >= 0);

							//Ncpp_ASSERT(nX2 >= 0);
							//Ncpp_ASSERT(nY2 >= 0);

							T & rColor_Src_X1_Y1 = a_srcBuf[idxCalc_Src.Calc(nX1 / m_nScale, nY1 / m_nScale)];
							T & rColor_Src_X1_Y2 = a_srcBuf[idxCalc_Src.Calc(nX1 / m_nScale, nY2 / m_nScale)];
							T & rColor_Src_X2_Y1 = a_srcBuf[idxCalc_Src.Calc(nX2 / m_nScale, nY1 / m_nScale)];
							T & rColor_Src_X2_Y2 = a_srcBuf[idxCalc_Src.Calc(nX2 / m_nScale, nY2 / m_nScale)];


							T color_Src_X_Y1;
							T color_Src_X_Y2;
							{
								//int nCur_X = (nX1 == nX2) ? nX1 : curPnt_X.x;
								int nWt_X1 = (nX1 == nX2) ? m_nScale : abs(curPnt_X.x - nX2);
								Ncpp_ASSERT(nWt_X1 <= m_nScale);

								//T color_Src_X_Y1 = T::Add(
								//	rColor_Src_X1_Y1.MultBy(nWt_X1),
								//	rColor_Src_X2_Y1.MultBy(m_nScale - nWt_X1)
								//	).DividBy(m_nScale);



								//WaitedAdd_ByPtr(&rColor_Src_X1_Y1, (float)nWt_X1 / m_nScale,
								//	&rColor_Src_X2_Y1, (float)(m_nScale - nWt_X1) / m_nScale, &color_Src_X_Y1);

								//WaitedAdd_ByPtr(&rColor_Src_X1_Y2, (float)nWt_X1 / m_nScale,
								//	&rColor_Src_X2_Y2, (float)(m_nScale - nWt_X1) / m_nScale, &color_Src_X_Y2);

								WaitedAdd(rColor_Src_X1_Y1, (float)nWt_X1 / m_nScale,
									rColor_Src_X2_Y1, (float)(m_nScale - nWt_X1) / m_nScale, &color_Src_X_Y1);

								WaitedAdd(rColor_Src_X1_Y2, (float)nWt_X1 / m_nScale,
									rColor_Src_X2_Y2, (float)(m_nScale - nWt_X1) / m_nScale, &color_Src_X_Y2);



								//T color_Src_X_Y2 = T::Add(
								//	rColor_Src_X1_Y2.MultBy(nWt_X1),
								//	rColor_Src_X2_Y2.MultBy(m_nScale - nWt_X1)
								//	).DividBy(m_nScale);
							}

							{
								int nWt_Y1 = (nY1 == nY2) ? m_nScale : abs(curPnt_X.y - nY2);
								Ncpp_ASSERT(nWt_Y1 <= m_nScale);


								//WaitedAdd_ByPtr(&color_Src_X_Y1, (float)nWt_Y1 / m_nScale,
								//	&color_Src_X_Y2, (float)(m_nScale - nWt_Y1) / m_nScale, &rColor_Res);

								WaitedAdd(color_Src_X_Y1, (float)nWt_Y1 / m_nScale,
									color_Src_X_Y2, (float)(m_nScale - nWt_Y1) / m_nScale, &rColor_Res);




								//rColor_Res = T::Add(
								//	color_Src_X_Y1.MultBy(nWt_Y1),
								//	color_Src_X_Y2.MultBy(m_nScale - nWt_Y1)
								//	).DividBy(m_nScale);
							}
						}
						else
						{
							//rColor_Res.AssignVal(0, 0, 0);
							SetToZero(&rColor_Res);
						}
					}


				}

			}



		}


	protected:

		void Prepare();

		//void PrepareResImg();

		int AddRound(int a_num);

		int AddRoundByMin(int a_num);

		//void PrepareImageItrMgr();



	protected:

		//F32ImageRef m_srcImg;
		float m_angDig;
		float m_angRad;

		int m_nScale;
		int m_nRound;
		int m_nRoundByMin;
		int m_nCos;
		int m_nSin;

		CvPoint m_bgnPnt;

		Size_2D m_srcSiz;

		Size_2D m_resSiz;
		S32ImageRef m_resToSrcMapImg;
		//F32ImageRef m_resImg;
		S32ImageRef m_srcToResMapImg;

		//FixedVector< LineLimit > m_lineLimit_X_Arr;
		//FixedVector< LineLimit > m_lineLimit_V_Arr;

		//ImageItrMgrRef m_imageItrMgr;

	};


	typedef Ncpp::ObjRef< ImgSizeRotation > ImgSizeRotationRef;

}