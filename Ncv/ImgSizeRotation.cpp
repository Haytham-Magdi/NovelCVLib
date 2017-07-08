#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>
#include <NovelCVLib\Ncv\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\ImgSizeRotation.h>


#define M_PI 3.14159265358979323846


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;


	ImgSizeRotation::ImgSizeRotation(CvSize a_srcSiz, float a_angDig)
	{
		Ncpp_ASSERT(a_angDig >= 0);
		Ncpp_ASSERT(a_angDig <= 90);

		m_srcSiz = a_srcSiz;

		//m_srcImg = a_srcImg;
		m_angDig = a_angDig;
		m_angRad = a_angDig * M_PI / 180;

		m_nScale = 1000;
		//m_nScale = 10000;
		m_nRound = 0.555555 * m_nScale;
		m_nRoundByMin = 0.999999 * m_nScale;

		m_nCos = cos(m_angRad) * m_nScale;
		m_nSin = sin(m_angRad) * m_nScale;

		m_nCos++;
		m_nSin++;

		int mag1 = Sqr(m_nCos) + Sqr(m_nSin);
		Ncpp_ASSERT(mag1 >= Sqr(m_nScale));

		Prepare();
	}

	int ImgSizeRotation::AddRound(int a_num)
	{
		int nRet;

		if (a_num > 0)
		{
			nRet = (int)(a_num + m_nRound);
		}
		else
		{
			nRet = (int)(a_num - m_nRound);
		}

		nRet /= m_nScale;
		nRet *= m_nScale;

		return nRet;
	}

	int ImgSizeRotation::AddRoundByMin(int a_num)
	{
		int nRet;

		if (a_num > 0)
		{
			nRet = (int)(a_num + m_nRoundByMin);
		}
		else
		{
			nRet = (int)(a_num - m_nRoundByMin);
		}

		nRet /= m_nScale;
		nRet *= m_nScale;

		return nRet;
	}

	void ImgSizeRotation::Prepare()
	{
		const int nScaled_SrcWidth = m_srcSiz.width * m_nScale;
		const int nScaled_SrcHeight = m_srcSiz.height * m_nScale;

		//m_bgnPnt;

		int nSafeMarg = 0;
		//int nSafeMarg = 20;

		{
			//int nofLinesBef = AddRound(
			int nofLinesBef = AddRoundByMin(
				m_nSin * (m_srcSiz.width + nSafeMarg));

			nofLinesBef /= m_nScale;

			m_bgnPnt.x = nofLinesBef * m_nSin;
			m_bgnPnt.y = -nofLinesBef * m_nCos;

			int nofLinesAft = AddRoundByMin(
				m_nCos * (m_srcSiz.height + nSafeMarg));

			nofLinesAft /= m_nScale;

			//m_resSiz.height = nofLinesBef + nofLinesAft;
			m_resSiz.height = nofLinesBef + nofLinesAft + 1;
		}

		{
			int nofLinesBef = m_nCos * (m_srcSiz.width + nSafeMarg);
			nofLinesBef = AddRoundByMin(nofLinesBef);

			nofLinesBef /= m_nScale;

			int nofLinesAft = m_nSin * (m_srcSiz.height + nSafeMarg);
			nofLinesAft = AddRoundByMin(nofLinesAft);

			nofLinesAft /= m_nScale;

			m_resSiz.width = nofLinesBef + nofLinesAft + 1;
		}

		//{
		//	int nofLinesBef = m_nCos * (m_srcSiz.width + nSafeMarg);

		//	int nofLinesAft = m_nSin * (m_srcSiz.height + nSafeMarg);

		//	//m_resSiz.width = AddRound(
		//	m_resSiz.width = AddRoundByMin(
		//		nofLinesBef + nofLinesAft );

		//	m_resSiz.width /= m_nScale;
		//}

		m_resToSrcMapImg = S32Image::Create(m_resSiz, 1);
		int * resToSrcBuf = (int *)m_resToSrcMapImg->GetPixAt(0, 0);

		//m_resToSrcMapImg_X_Scaled = S32Image::Create(m_resSiz, 1);
		//int * resToSrcBuf_X_Scaled = (int *)m_resToSrcMapImg_X_Scaled->GetPixAt(0, 0);

		//m_resToSrcMapImg_Y_Scaled = S32Image::Create(m_resSiz, 1);
		//int * resToSrcBuf_Y_Scaled = (int *)m_resToSrcMapImg_Y_Scaled->GetPixAt(0, 0);

		//m_srcPntOfRes_Arr.SetSize(m_resSiz.width * m_resSiz.height);

		m_srcToResMapImg = S32Image::Create(m_srcSiz, 1);
		int *  srcToResBuf = (int *)m_srcToResMapImg->GetPixAt(0, 0);

		S32ImageRef srcMinDistImg = S32Image::Create(m_srcSiz, 1);
		int *  srcMinDistBuf = (int *)srcMinDistImg->GetPixAt(0, 0);

		//m_resImg = F32Image::Create(m_resSiz, 3);
		//F32ColorVal * resBuf = (F32ColorVal *)m_resImg->GetPixAt(0, 0);

		//F32ColorVal * srcBuf = (F32ColorVal *)m_srcImg->GetPixAt(0, 0);

		const int nGreatDist = 10000000;
		srcMinDistImg->SetAll(nGreatDist);

		int nMappedSrcCnt = 0;





		IndexCalc2D idxCalc_Src(m_srcSiz.width, m_srcSiz.height);

		IndexCalc2D idxCalc_Res(m_resSiz.width, m_resSiz.height);

		//CvPoint curPnt = m_bgnPnt;

		FixedVector< CvPoint > srcPntArr(100);

		for (int y = 0; y < m_resSiz.height; y++)
		{
			CvPoint curPnt_Y;

			curPnt_Y.x = m_bgnPnt.x - y * m_nSin;
			curPnt_Y.y = m_bgnPnt.y + y * m_nCos;

			for (int x = 0; x < m_resSiz.width; x++)
			{
				int nIdx_Res = idxCalc_Res.Calc(x, y);

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

				srcPntArr.ResetSize();

				srcPntArr.PushBack(cvPoint(nX1, nY1));

				nY2 = AddRoundByMin(curPnt_X.y);

				nX2 = AddRoundByMin(curPnt_X.x);

				if (nY2 < 0 || nY2 >= nScaled_SrcHeight)
					nY2 = nY1;

				if (nX2 < 0 || nX2 >= nScaled_SrcWidth)
					nX2 = nX1;

				srcPntArr.PushBack(cvPoint(nX2, nY1));
				srcPntArr.PushBack(cvPoint(nX2, nY2));
				srcPntArr.PushBack(cvPoint(nX1, nY2));

			SrcToResEnd:

				for (int i = 0; i < srcPntArr.GetSize(); i++)
				{
					CvPoint & rSrcPnt = srcPntArr[i];

					int nIdx_Src = idxCalc_Src.Calc(
						rSrcPnt.x / m_nScale, rSrcPnt.y / m_nScale);

					int nOldDist = srcMinDistBuf[nIdx_Src];

					if (nGreatDist == nOldDist)
						nMappedSrcCnt++;

					int nNewDist = abs(curPnt_X.x - rSrcPnt.x) +
						abs(curPnt_X.y - rSrcPnt.y);

					if (nNewDist < nOldDist)
					{
						srcMinDistBuf[nIdx_Src] = nNewDist;
						srcToResBuf[nIdx_Src] = nIdx_Res;
					}

				}
				//}


				bool bInImg = true;

				int nX_Src = AddRound(curPnt_X.x);
				nX_Src /= m_nScale;

				if (!(nX_Src >= 0 && nX_Src < m_srcSiz.width))
					bInImg = false;

				int nY_Src = AddRound(curPnt_X.y);
				nY_Src /= m_nScale;

				if (!(nY_Src >= 0 && nY_Src < m_srcSiz.height))
					bInImg = false;

				int nIdx_Src = -1;

				if (bInImg)
				{
					nIdx_Src = idxCalc_Src.Calc(nX_Src, nY_Src);
				}

				resToSrcBuf[nIdx_Res] = nIdx_Src;

			}
		}

		int nSrcSiz1D = m_srcSiz.width * m_srcSiz.height;

		Ncpp_ASSERT(nMappedSrcCnt == nSrcSiz1D);



		//{
		//	m_lineLimit_H_Arr.SetSize(m_resSiz.height);
		//	m_lineLimit_V_Arr.SetSize(m_resSiz.width);

		//	for (int y = 0; y < m_resSiz.height; y++)
		//	{
		//		LineLimit & rLimit_H = m_lineLimit_H_Arr[y];

		//		//rLimit_H.nBgnIdx = 100000000;
		//		rLimit_H.nBgnIdx = nGreatDist;
		//		rLimit_H.nEndIdx = -nGreatDist;

		//		for (int x = 0; x < m_resSiz.width; x++)
		//		{
		//			int i = idxCalc_Res.Calc(x, y);

		//			int nSrcIdx = resToSrcBuf[i];

		//			if (nSrcIdx < 0)
		//				continue;

		//			if (rLimit_H.nEndIdx < 0)
		//			{
		//				rLimit_H.nBgnIdx = i;
		//			}

		//			rLimit_H.nEndIdx = i;
		//		}

		//		if (rLimit_H.nEndIdx < 0)
		//		{
		//			rLimit_H.nBgnIdx = m_resSiz.height / 2;
		//			rLimit_H.nEndIdx = rLimit_H.nBgnIdx - 1;
		//		}

		//	}


		//	for (int x = 0; x < m_resSiz.width; x++)
		//	{
		//		LineLimit & rLimit_V = m_lineLimit_V_Arr[x];

		//		//rLimit_H.nBgnIdx = 100000000;
		//		rLimit_V.nBgnIdx = nGreatDist;
		//		rLimit_V.nEndIdx = -nGreatDist;

		//		for (int y = 0; y < m_resSiz.height; y++)
		//		{
		//			int i = idxCalc_Res.Calc(x, y);

		//			int nSrcIdx = resToSrcBuf[i];

		//			if (nSrcIdx < 0)
		//				continue;

		//			if (rLimit_V.nEndIdx < 0)
		//			{
		//				rLimit_V.nBgnIdx = i;
		//			}

		//			rLimit_V.nEndIdx = i;
		//		}

		//		if (rLimit_V.nEndIdx < 0)
		//		{
		//			rLimit_V.nBgnIdx = m_resSiz.width / 2;
		//			rLimit_V.nEndIdx = rLimit_V.nBgnIdx - m_resSiz.width;
		//		}

		//	}


		//}

		//PrepareImageItrMgr();


		//PrepareResImg();

		//ShowImage( m_resImg, "m_resImg" );

	}


	//void ImgSizeRotation::PrepareProvArr()
	//void ImgSizeRotation::PrepareImageItrMgr()
	//{
	//	m_imageItrMgr = new ImageItrMgr(m_resSiz,
	//		m_lineLimit_H_Arr, m_lineLimit_V_Arr);
	//}



	//void ImgSizeRotation::PrepareResImg()
	//{
	//	//m_srcSiz = m_srcImg->GetSize();

	//	const int nScaled_SrcWidth = m_srcSiz.width * m_nScale;
	//	const int nScaled_SrcHeight = m_srcSiz.height * m_nScale;

	//	F32ColorVal * srcBuf = (F32ColorVal *)m_srcImg->GetPixAt(0, 0);

	//	F32ColorVal * resBuf = (F32ColorVal *)m_resImg->GetPixAt(0, 0);

	//	int * resToSrcBuf = (int *)m_resToSrcMapImg->GetPixAt(0, 0);

	//	IndexCalc2D idxCalc_Src(m_srcSiz.width, m_srcSiz.height);

	//	IndexCalc2D idxCalc_Res(m_resSiz.width, m_resSiz.height);

	//	for (int y = 0; y < m_resSiz.height; y++)
	//	{
	//		CvPoint curPnt_Y;

	//		curPnt_Y.x = m_bgnPnt.x - y * m_nSin;
	//		curPnt_Y.y = m_bgnPnt.y + y * m_nCos;

	//		for (int x = 0; x < m_resSiz.width; x++)
	//		{
	//			int nIdx_Res = idxCalc_Res.Calc(x, y);

	//			CvPoint curPnt_X;
	//			//CvPoint curPnt_X = m_srcPntOfRes_Arr[nIdx_Res];



	//			curPnt_X.x = curPnt_Y.x + x * m_nCos;
	//			curPnt_X.y = curPnt_Y.y + x * m_nSin;

	//			//resToSrcBuf_X_Scaled[idxCalc_Res.Calc(x, y)] =

	//			//{
	//			int nX1, nX2, nY1, nY2;

	//			nY1 = (curPnt_X.y / m_nScale) * m_nScale;

	//			nX1 = (curPnt_X.x / m_nScale) * m_nScale;

	//			if (!(nY1 >= 0 && nY1 < nScaled_SrcHeight))
	//				goto SrcToResEnd;

	//			if (!(nX1 >= 0 && nX1 < nScaled_SrcWidth))
	//				goto SrcToResEnd;

	//			//srcPntArr.ResetSize();

	//			//srcPntArr.PushBack(cvPoint(nX1, nY1));

	//			nY2 = AddRoundByMin(curPnt_X.y);

	//			nX2 = AddRoundByMin(curPnt_X.x);

	//			if (nY2 < 0 || nY2 >= nScaled_SrcHeight)
	//				nY2 = nY1;

	//			if (nX2 < 0 || nX2 >= nScaled_SrcWidth)
	//				nX2 = nX1;

	//			//srcPntArr.PushBack(cvPoint(nX2, nY1));
	//			//srcPntArr.PushBack(cvPoint(nX2, nY2));
	//			//srcPntArr.PushBack(cvPoint(nX1, nY2));

	//		SrcToResEnd:

	//			//	PrepareResImg
	//			//if (bInImg)
	//			{
	//				F32ColorVal & rColor_Res = resBuf[nIdx_Res];

	//				int nIdx_Src = resToSrcBuf[nIdx_Res];


	//				if (nIdx_Src >= 0)
	//				{
	//					//Ncpp_ASSERT(nX1 >= 0);
	//					//Ncpp_ASSERT(nY1 >= 0);

	//					//Ncpp_ASSERT(nX2 >= 0);
	//					//Ncpp_ASSERT(nY2 >= 0);

	//					F32ColorVal & rColor_Src_X1_Y1 = srcBuf[idxCalc_Src.Calc(nX1 / m_nScale, nY1 / m_nScale)];
	//					F32ColorVal & rColor_Src_X1_Y2 = srcBuf[idxCalc_Src.Calc(nX1 / m_nScale, nY2 / m_nScale)];
	//					F32ColorVal & rColor_Src_X2_Y1 = srcBuf[idxCalc_Src.Calc(nX2 / m_nScale, nY1 / m_nScale)];
	//					F32ColorVal & rColor_Src_X2_Y2 = srcBuf[idxCalc_Src.Calc(nX2 / m_nScale, nY2 / m_nScale)];

	//					//int nCur_X = (nX1 == nX2) ? nX1 : curPnt_X.x;
	//					int nWt_X1 = (nX1 == nX2) ? m_nScale : abs(curPnt_X.x - nX2);
	//					Ncpp_ASSERT(nWt_X1 <= m_nScale);

	//					F32ColorVal rColor_Src_X_Y1 = F32ColorVal::Add(
	//						rColor_Src_X1_Y1.MultBy(nWt_X1),
	//						rColor_Src_X2_Y1.MultBy(m_nScale - nWt_X1)
	//						).DividBy(m_nScale);

	//					F32ColorVal rColor_Src_X_Y2 = F32ColorVal::Add(
	//						rColor_Src_X1_Y2.MultBy(nWt_X1),
	//						rColor_Src_X2_Y2.MultBy(m_nScale - nWt_X1)
	//						).DividBy(m_nScale);

	//					int nWt_Y1 = (nY1 == nY2) ? m_nScale : abs(curPnt_X.y - nY2);
	//					Ncpp_ASSERT(nWt_Y1 <= m_nScale);

	//					rColor_Res = F32ColorVal::Add(
	//						rColor_Src_X_Y1.MultBy(nWt_Y1),
	//						rColor_Src_X_Y2.MultBy(m_nScale - nWt_Y1)
	//						).DividBy(m_nScale);
	//				}
	//				else
	//				{
	//					rColor_Res.AssignVal(0, 0, 0);
	//				}

	//			}


	//		}
	//	}


	//}



}