#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Apps\Binarization\ImgAngleDirMgr.h>


#define M_PI 3.14159265358979323846


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	namespace Ns_Binarization
	{

		ImgAngleDirMgr::ImgAngleDirMgr(F32ImageRef a_srcImg, float a_angDig)
		{
			Ncpp_ASSERT(a_angDig >= 0);
			Ncpp_ASSERT(a_angDig <= 90);

			m_srcImg = a_srcImg;
			m_angDig = a_angDig;
			m_angRad = a_angDig * M_PI / 180;

			m_nScale = 1000;
			//m_nScale = 10000;
			m_nRound = 0.555555 * m_nScale;
			m_nRoundByMin = 0.999999 * m_nScale;

			m_nCos = cos(m_angRad) * m_nScale;
			m_nSin = sin(m_angRad) * m_nScale;

			Prepare();
		}


		int ImgAngleDirMgr::AddRound(int a_num)
		{
			int nRet;

			if (a_num > 0)
				nRet = (int)(a_num + m_nRound);
			else
				nRet = (int)(a_num - m_nRound);

			nRet /= m_nScale;
			nRet *= m_nScale;

			return nRet;
		}


		int ImgAngleDirMgr::AddRoundByMin(int a_num)
		{
			int nRet;

			if (a_num > 0)
				nRet = (int)(a_num + m_nRoundByMin);
			else
				nRet = (int)(a_num - m_nRoundByMin);

			nRet /= m_nScale;
			nRet *= m_nScale;

			return nRet;
		}



		void ImgAngleDirMgr::Prepare()
		{
			CvSize srcSiz = m_srcImg->GetSize();

			const int nScaled_SrcWidth = srcSiz.width * m_nScale;
			const int nScaled_SrcHeight = srcSiz.height * m_nScale;

			CvPoint bgnPnt;

			//int nSafeMarg = 0;
			int nSafeMarg = 20;

			{
				//int nofLinesBef = AddRound(
				int nofLinesBef = AddRoundByMin(
					m_nSin * (srcSiz.width + nSafeMarg));

				nofLinesBef /= m_nScale;

				bgnPnt.x = nofLinesBef * m_nSin;
				bgnPnt.y = -nofLinesBef * m_nCos;

				//int nofLinesAft = AddRound(
				int nofLinesAft = AddRoundByMin(
					m_nCos * (srcSiz.height + nSafeMarg));

				nofLinesAft /= m_nScale;

				//m_resSiz.height = nofLinesBef + nofLinesAft;
				m_resSiz.height = nofLinesBef + nofLinesAft + 1;
			}

			{
				int nofLinesBef = m_nCos * (srcSiz.width + nSafeMarg);
				nofLinesBef = AddRoundByMin(nofLinesBef);

				nofLinesBef /= m_nScale;


				int nofLinesAft = m_nSin * (srcSiz.height + nSafeMarg);
				nofLinesAft = AddRoundByMin(nofLinesAft);

				nofLinesAft /= m_nScale;

				m_resSiz.width = nofLinesBef + nofLinesAft + 1;
			}

			//{
			//	int nofLinesBef = m_nCos * (srcSiz.width + nSafeMarg);

			//	int nofLinesAft = m_nSin * (srcSiz.height + nSafeMarg);

			//	//m_resSiz.width = AddRound(
			//	m_resSiz.width = AddRoundByMin(
			//		nofLinesBef + nofLinesAft );

			//	m_resSiz.width /= m_nScale;
			//}

			m_resToSrcMapImg = S32Image::Create(m_resSiz, 1);
			int * resToSrcBuf = (int *)m_resToSrcMapImg->GetPixAt(0, 0);

			m_srcToResMapImg = S32Image::Create(srcSiz, 1);
			int * srcToResBuf = (int *)m_srcToResMapImg->GetPixAt(0, 0);

			m_srcToResMapImg_Scaled = S32Image::Create(srcSiz, 1);
			int * srcToResBuf_Scaled = (int *)m_srcToResMapImg_Scaled->GetPixAt(0, 0);

			S32ImageRef srcMinDistImg = S32Image::Create(srcSiz, 1);
			int * srcMinDistBuf = (int *)srcMinDistImg->GetPixAt(0, 0);

			const int nGreatDist = 1000000000;
			srcMinDistImg->SetAll(nGreatDist);

			int nMappedSrcCnt = 0;





			IndexCalc2D idxCalc_Src(srcSiz.width, srcSiz.height);

			IndexCalc2D idxCalc_Res(m_resSiz.width, m_resSiz.height);

			//CvPoint curPnt = bgnPnt;

			FixedVector< CvPoint > srcPntArr(100);

			for (int y = 0; y < m_resSiz.height; y++)
			{
				CvPoint curPnt_Y;

				curPnt_Y.x = bgnPnt.x - y * m_nSin;
				curPnt_Y.y = bgnPnt.y + y * m_nCos;

				for (int x = 0; x < m_resSiz.width; x++)
				{
					int nIdx_Res = idxCalc_Res.Calc(x, y);

					CvPoint curPnt_X;

					curPnt_X.x = curPnt_Y.x + x * m_nCos;
					curPnt_X.y = curPnt_Y.y + x * m_nSin;


					{
						int nX1, nX2, nY1, nY2;

						nY1 = (curPnt_X.y / m_nScale) * m_nScale;

						if (!(nY1 >= 0 && nY1 < nScaled_SrcHeight))
							goto SrcToResEnd;

						nX1 = (curPnt_X.x / m_nScale) * m_nScale;

						if (!(nX1 >= 0 && nX1 < nScaled_SrcWidth))
							goto SrcToResEnd;

						srcPntArr.ResetSize();

						srcPntArr.PushBack(cvPoint(nX1, nY1));

						nY2 = AddRoundByMin(curPnt_X.y);

						nX2 = AddRoundByMin(curPnt_X.x);

						if ((nY2 >= 0 && nY2 < nScaled_SrcHeight) &&
							(nX2 >= 0 && nX2 < nScaled_SrcWidth))
						{
							srcPntArr.PushBack(cvPoint(nX2, nY1));
							srcPntArr.PushBack(cvPoint(nX2, nY2));
							srcPntArr.PushBack(cvPoint(nX1, nY2));
						}
						else if (nY2 >= 0 && nY2 < nScaled_SrcHeight)
						{
							srcPntArr.PushBack(cvPoint(nX1, nY2));
						}
						else if (nX2 >= 0 && nX2 < nScaled_SrcWidth)
						{
							srcPntArr.PushBack(cvPoint(nX2, nY1));
						}



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

					}



					bool bInImg = true;

					int nX_Src = AddRound(curPnt_X.x);
					nX_Src /= m_nScale;

					if (!(nX_Src >= 0 && nX_Src < srcSiz.width))
						bInImg = false;

					int nY_Src = AddRound(curPnt_X.y);
					nY_Src /= m_nScale;

					if (!(nY_Src >= 0 && nY_Src < srcSiz.height))
						bInImg = false;

					int nIdx_Src = -1;

					if (bInImg)
						nIdx_Src = idxCalc_Src.Calc(nX_Src, nY_Src);

					resToSrcBuf[nIdx_Res] = nIdx_Src;

					if (93339 == nIdx_Src)
						nIdx_Src = nIdx_Src;
				}
			}

			int nSrcSiz1D = srcSiz.width * srcSiz.height;

			Ncpp_ASSERT(nMappedSrcCnt == nSrcSiz1D);



			{
				m_lineLimit_H_Arr.SetSize(m_resSiz.height);
				m_lineLimit_V_Arr.SetSize(m_resSiz.width);

				for (int y = 0; y < m_resSiz.height; y++)
				{
					LineLimit & rLimit_H = m_lineLimit_H_Arr[y];

					//rLimit_H.nBgnIdx = 100000000;
					rLimit_H.nBgnIdx = nGreatDist;
					rLimit_H.nEndIdx = -nGreatDist;

					for (int x = 0; x < m_resSiz.width; x++)
					{
						int i = idxCalc_Res.Calc(x, y);

						int nSrcIdx = resToSrcBuf[i];

						if (nSrcIdx < 0)
							continue;

						if (rLimit_H.nEndIdx < 0)
						{
							rLimit_H.nBgnIdx = i;
						}

						rLimit_H.nEndIdx = i;
					}

					if (rLimit_H.nEndIdx < 0)
					{
						rLimit_H.nBgnIdx = m_resSiz.height / 2;
						rLimit_H.nEndIdx = rLimit_H.nBgnIdx - 1;
					}

				}


				for (int x = 0; x < m_resSiz.width; x++)
				{
					LineLimit & rLimit_V = m_lineLimit_V_Arr[x];

					//rLimit_H.nBgnIdx = 100000000;
					rLimit_V.nBgnIdx = nGreatDist;
					rLimit_V.nEndIdx = -nGreatDist;

					for (int y = 0; y < m_resSiz.height; y++)
					{
						int i = idxCalc_Res.Calc(x, y);

						int nSrcIdx = resToSrcBuf[i];

						if (nSrcIdx < 0)
							continue;

						if (rLimit_V.nEndIdx < 0)
						{
							rLimit_V.nBgnIdx = i;
						}

						rLimit_V.nEndIdx = i;
					}

					if (rLimit_V.nEndIdx < 0)
					{
						rLimit_V.nBgnIdx = m_resSiz.width / 2;
						rLimit_V.nEndIdx = rLimit_V.nBgnIdx - m_resSiz.width;
					}

				}


			}

			PrepareImageItrMgr();



			if (false)
			{
				F32ImageRef img1 = F32Image::Create(srcSiz, 3);

				img1->SetAll(0);

				F32ColorVal * img1_Buf =
					(F32ColorVal *)img1->GetPixAt(0, 0);

				//for( int i=0; i < nSrcSiz1D; i++ )

				int i = 0;
				for (int y = 0; y < srcSiz.height; y++)
				{
					for (int x = 0; x < srcSiz.width; x++, i++)
					{
						//F32ColorVal & rColor1 = img1_Buf[ i ];

						if (nGreatDist == srcMinDistBuf[i])
						{
							//rColor1.AssignVal( 0, 180, 0 );

							DrawCircle(img1, F32Point(x, y),
								//u8ColorVal( 0, 180, 0 ), 7 );
								u8ColorVal(0, 180, 0), 1);
						}


					}

				}

				ShowImage(img1, "img1");
			}





			PrepareResImg();

			//ShowImage( m_resImg, "m_resImg" );

		}


		//void ImgAngleDirMgr::PrepareProvArr()
		void ImgAngleDirMgr::PrepareImageItrMgr()
		{
			m_imageItrMgr = new ImageItrMgr(m_resSiz,
				m_lineLimit_H_Arr, m_lineLimit_V_Arr);
		}



		void ImgAngleDirMgr::PrepareResImg()
		{
			int * resToSrcBuf = (int *)m_resToSrcMapImg->GetPixAt(0, 0);

			m_resImg = F32Image::Create(m_resSiz, 3);

			F32ColorVal * resBuf =
				(F32ColorVal *)m_resImg->GetPixAt(0, 0);

			CvSize srcSiz = m_srcImg->GetSize();

			//int nSrcSiz1D = srcSiz.width * srcSiz.height;

			F32ColorVal * srcBuf =
				(F32ColorVal *)m_srcImg->GetPixAt(0, 0);

			int nResSiz1D = m_resSiz.width * m_resSiz.height;

			for (int i = 0; i < nResSiz1D; i++)
			{
				F32ColorVal & rColor_Res = resBuf[i];


				int nIdx_Src = resToSrcBuf[i];

				if (nIdx_Src >= 0)
				{
					F32ColorVal & rColor_Src = srcBuf[nIdx_Src];

					rColor_Res.AssignVal(rColor_Src);
				}
				else
				{
					//rColor_Res.AssignVal( 0, 120, 0 );
					rColor_Res.AssignVal(0, 0, 0);
				}
			}

			if (false)
			{
				IndexCalc2D idxCalc_Res(m_resSiz.width, m_resSiz.height);

				ImageLineItrProvider & rProv = m_imageItrMgr->GetItrProvAt(0);
				//ImageLineItrProvider & rProv = m_imageItrMgr->GetItrProvAt( 1 );
				//ImageLineItrProvider & rProv = m_imageItrMgr->GetItrProvAt( 3 );

				int nStartIdx = idxCalc_Res.Calc(
					m_resSiz.width / 3, m_resSiz.height / 3);

				ImageLineItr & rLineItr =
					rProv.GetItrForPixIdx(nStartIdx);

				//NumberIterator itr = rLineItr.GenBgnToEndItr();
				//itr.SetCurVal( nStartIdx );

				//NumberIterator itr;
				//itr.Init( rLineItr.GetFarBgn(),
				//	rLineItr.GetBgn() - rLineItr.GetIncVal(),
				//	rLineItr.GetIncVal() );

				NumberIterator itr;
				itr.Init(rLineItr.GetFarBgn(),
					rLineItr.GetAftBgn(-1), rLineItr.GetIncVal());

				//itr.GotoBgn();

				int i = 0;

				//while( itr.IsCurValid() )
				for (int j = itr.CalcCurStep();
					j < itr.GetLimStep(); j++, itr.MoveNext())
				{
					//int nCurIdx = rLineItr.GetCurIndex();
					int nCurIdx = itr.GetCurVal();

					//rLineItr.GoNext();
					//itr.MoveNext();

					F32ColorVal & rColor_Res = resBuf[nCurIdx];

					rColor_Res.AssignVal(0, i, i);
					i++;
				}
			}//	End of : Line draw try.


		}



	}
}

