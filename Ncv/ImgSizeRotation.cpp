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


//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	using namespace Ncv::ImageOperations2;

	ImgSizeRotation::ImgSizeRotation(Size_2D a_srcSiz, float a_angDig)
	{
		Ncpp_ASSERT(a_angDig >= 0);
		Ncpp_ASSERT(a_angDig <= 90);

		m_srcSiz = a_srcSiz;

		//m_srcImg = a_srcImg;
		m_angDig = a_angDig;
		m_angRad = a_angDig * M_PI / 180;

		m_nCos = SRIntScale::Scale(cos(m_angRad));
		m_nSin = SRIntScale::Scale(sin(m_angRad));

		m_nCos++;
		m_nSin++;

		int mag1 = Sqr(m_nCos) + Sqr(m_nSin);
		Ncpp_ASSERT(mag1 >= Sqr(SRIntScale::Scale(1)));

		Prepare();
	}

	void ImgSizeRotation::Prepare()
	{
		const int nScaled_SrcWidth = SRIntScale::Scale(m_srcSiz.GetX());
		const int nScaled_SrcHeight = SRIntScale::Scale(m_srcSiz.GetY());

		//m_bgnPnt;

		int nSafeMarg = 0;
		//int nSafeMarg = 20;

		{
			//int nofLinesBef = SRIntScale::Round(
			int nofLinesBef = SRIntScale::Ceil(
				m_nSin * (m_srcSiz.GetX() + nSafeMarg));

			nofLinesBef /= SRIntScale::GetScaleVal();

			m_bgnPnt.x = nofLinesBef * m_nSin;
			m_bgnPnt.y = -nofLinesBef * m_nCos;

			int nofLinesAft = SRIntScale::Ceil(
				m_nCos * (m_srcSiz.GetY() + nSafeMarg));

			nofLinesAft /= SRIntScale::GetScaleVal();

			m_resSiz.SetY(nofLinesBef + nofLinesAft + 1);
		}

		{
			int nofLinesBef = m_nCos * (m_srcSiz.GetX() + nSafeMarg);
			nofLinesBef = SRIntScale::Ceil(nofLinesBef);

			nofLinesBef /= SRIntScale::GetScaleVal();

			int nofLinesAft = m_nSin * (m_srcSiz.GetY() + nSafeMarg);
			nofLinesAft = SRIntScale::Ceil(nofLinesAft);

			nofLinesAft /= SRIntScale::GetScaleVal();

			m_resSiz.SetX(nofLinesBef + nofLinesAft + 1);
		}

		m_resToSrcMapImg = ArrayHolderUtil::CreateFrom<int>(m_resSiz);
		int * resToSrcBuf = (int *)m_resToSrcMapImg->GetActualAccessor().GetData();

		m_srcToResMapImg = ArrayHolderUtil::CreateFrom<int>(m_srcSiz);
		int * srcToResBuf = (int *)m_srcToResMapImg->GetActualAccessor().GetData();


		ArrayHolder_2D_Ref<int> srcMinDistImg = ArrayHolderUtil::CreateFrom<int>(m_srcSiz);
		int *  srcMinDistBuf = (int *)srcMinDistImg->GetActualAccessor().GetData();

		const int nGreatDist = 10000000;
		FillImage(srcMinDistImg->GetVirtAccessor(), nGreatDist);

		int nMappedSrcCnt = 0;





		IndexCalc2D idxCalc_Src(m_srcSiz.GetX(), m_srcSiz.GetY());

		IndexCalc2D idxCalc_Res(m_resSiz.GetX(), m_resSiz.GetY());

		//S32Point curPnt = m_bgnPnt;

		FixedVector< S32Point > srcPntArr(100);

		for (int y = 0; y < m_resSiz.GetY(); y++)
		{
			S32Point curPnt_Y;

			curPnt_Y.x = m_bgnPnt.x - y * m_nSin;
			curPnt_Y.y = m_bgnPnt.y + y * m_nCos;

			for (int x = 0; x < m_resSiz.GetX(); x++)
			{
				int nIdx_Res = idxCalc_Res.Calc(x, y);

				S32Point curPnt_X;
				//S32Point curPnt_X = m_srcPntOfRes_Arr[nIdx_Res];



				curPnt_X.x = curPnt_Y.x + x * m_nCos;
				curPnt_X.y = curPnt_Y.y + x * m_nSin;

				//resToSrcBuf_X_Scaled[idxCalc_Res.Calc(x, y)] =

				//{
				int nX1, nX2, nY1, nY2;

				nY1 = SRIntScale::Floor(curPnt_X.y);

				nX1 = SRIntScale::Floor(curPnt_X.x);

				if (!(nY1 >= 0 && nY1 < nScaled_SrcHeight))
					goto SrcToResEnd;

				if (!(nX1 >= 0 && nX1 < nScaled_SrcWidth))
					goto SrcToResEnd;

				srcPntArr.ResetSize();

				srcPntArr.PushBack(S32Point(nX1, nY1));

				nY2 = SRIntScale::Ceil(curPnt_X.y);

				nX2 = SRIntScale::Ceil(curPnt_X.x);

				if (nY2 < 0 || nY2 >= nScaled_SrcHeight)
					nY2 = nY1;

				if (nX2 < 0 || nX2 >= nScaled_SrcWidth)
					nX2 = nX1;

				srcPntArr.PushBack(S32Point(nX2, nY1));
				srcPntArr.PushBack(S32Point(nX2, nY2));
				srcPntArr.PushBack(S32Point(nX1, nY2));

			SrcToResEnd:

				for (int i = 0; i < srcPntArr.GetSize(); i++)
				{
					S32Point & rSrcPnt = srcPntArr[i];

					int nIdx_Src = idxCalc_Src.Calc(
						rSrcPnt.x / SRIntScale::GetScaleVal(), rSrcPnt.y / SRIntScale::GetScaleVal());

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

				int nX_Src = SRIntScale::Round(curPnt_X.x);
				nX_Src /= SRIntScale::GetScaleVal();

				if (!(nX_Src >= 0 && nX_Src < m_srcSiz.GetX()))
					bInImg = false;

				int nY_Src = SRIntScale::Round(curPnt_X.y);
				nY_Src /= SRIntScale::GetScaleVal();

				if (!(nY_Src >= 0 && nY_Src < m_srcSiz.GetY()))
					bInImg = false;

				int nIdx_Src = -1;

				if (bInImg)
				{
					nIdx_Src = idxCalc_Src.Calc(nX_Src, nY_Src);
				}

				resToSrcBuf[nIdx_Res] = nIdx_Src;

			}
		}

		int nSrcSiz1D = m_srcSiz.GetX() * m_srcSiz.GetY();

		Ncpp_ASSERT(nMappedSrcCnt == nSrcSiz1D);

	}



}