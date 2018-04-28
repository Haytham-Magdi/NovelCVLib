#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Apps\Binarization2\ImgAngleDirMgr.h>


#define M_PI 3.14159265358979323846


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	using namespace Ncv::ImageOperations2;
	
	namespace Ns_Binarization
	{

		ImgAngleDirMgr::ImgAngleDirMgr(ImgAngleDirMgr_Context_Ref a_context, ImgAngleDirMgr_Context_Ref a_normalContext,
			AngleDirMgrColl_Context_Ref a_parentContext)
		{
			m_context = a_context;
			m_normalContext = a_normalContext;
			m_parentContext = a_parentContext;
		}

		ImgAngleDirMgr::Context::Context(int a_nIndex, ImgSizeRotationRef a_imgRot, F32ImageArrayHolder3C_Ref a_org_Img,
			F32ImageArrayHolder1C_Ref a_magSqr_Img, char a_hv)
		{
			m_nIndex = a_nIndex;
			m_imgRot = a_imgRot;

			m_org_Img = a_org_Img;
			m_magSqr_Img = a_magSqr_Img;

			Ncpp_ASSERT(a_hv == 'H' || a_hv == 'V');
			m_hv = a_hv;

			{
				char idStr_0[70];
				sprintf(idStr_0, "%.2f, %c: ", m_imgRot->GetAngleByDigree(), m_hv);
				m_idStr = idStr_0;
			}

		}

		void ImgAngleDirMgr::Proceed_1()
		{
			//return;

			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;


			//ShowImage(cx.m_org_Img->GetSrcImg(), cx.MakeStrWithId("org_Img->GetSrcImg()").c_str());

			cx.m_avgStandev_X_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetActualAccessor().GetSize());
			Cala_AvgStandevImage_X(cx.m_org_Img->GetVirtAccessor(), cx.m_magSqr_Img->GetVirtAccessor(),
				cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(-2, 2));

			//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-3, 3), Range<int>::New(-1, 1));
			//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-5, 5), Range<int>::New(-5, 5));

			//ShowImage(cx.m_avgStandev_X_Img->GetSrcImg(), cx.MakeStrWithId("m_avgStandev_X_Img->GetSrcImg()").c_str());

			//AffectCommonAvgStandev();

		}

		void ImgAngleDirMgr::Proceed_2()
		{
			//return;

			AffectCommonAvgStandev();

		}

		void ImgAngleDirMgr::Proceed_3()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			//Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			//Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);

			Window<int> avgWin = Window<int>::New(-1, 0, -2, 2);
			//Window<int> avgWin = Window<int>::New(0, 0, -2, 2);

			//Window<int> avgWin = Window<int>::New(-2, 2, -2, 2);
			//Window<int> avgWin = Window<int>::New(-2, 1, -2, 2);

			//cx.m_conflict_Img = new TempImageArrayHolder<ConflictInfo2>(cx.m_org_Img->GetActualAccessor().GetSize());
			cx.m_conflict_Img = ArrayHolderUtil::CreateFrom<ConflictInfo2>(cx.m_org_Img->GetActualAccessor().GetSize());

			F32ImageArrayHolder3C_Ref avg_Img = cx.m_org_Img->CloneEmpty();
			AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			F32ImageArrayHolder1C_Ref avg_MagSqr_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetSize());
			AvgImage(cx.m_magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);

			Range<int> confRange = Range<int>::New(
				-1 - avgWin.Get_X2(), 1 - avgWin.Get_X1());

			CalcConflictImage_X(avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
				cx.m_conflict_Img->GetVirtAccessor(), confRange);

			//if (0 == cx.m_nIndex)
			{
				//DisplayConflictImg();
			}

		}

		void ImgAngleDirMgr::Proceed_4()
		{
			//Context & cx = *m_context;
			//Context & ncx = *m_normalContext;
			//AngleDirMgrColl_Context & pcx = *m_parentContext;

			AffectCommonConflict();
		}

		void ImgAngleDirMgr::Proceed_5_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;


			F32ImageArrayHolder1C_Ref standev_InrWide_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetActualAccessor().GetSize());

			const int nInrRad = 5;
			//const int nInrRad = 5 * 2;
			//const int nInrRad = 8;
			F32ImageArrayHolder3C_Ref avg_InrWide_Img = new F32ImageArrayHolder3C(cx.m_org_Img->GetActualAccessor().GetSize());
			//F32VectorValImageArrayHolder_3C_Ref avg_InrWide_Img = new F32VectorValImageArrayHolder_3C(cx.m_org_Img->GetActualAccessor().GetSize());
			{
				Calc_Avg_And_Standev_Image(cx.m_org_Img->GetVirtAccessor(), avg_InrWide_Img->GetVirtAccessor(), standev_InrWide_Img->GetVirtAccessor(),
					Window<int>::New(-nInrRad, nInrRad, -nInrRad, nInrRad));

				MultiplyImageByNum(standev_InrWide_Img->GetVirtAccessor(), 2);
				//AssertValues_Image(avg_InrWide_Img->GetVirtAccessor());
			}

			if (0 == m_context->m_nIndex)
			{
				GlobalStuff::SetLinePathImg(GenTriChGrayImg(standev_InrWide_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
				ShowImage(standev_InrWide_Img->GetSrcImg(), "standev_InrWide_Img->GetSrcImg()");
			}

			//F32VectorValImageArrayHolder_4C_Ref cx.m_avgPStandev_InrWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetActualAccessor().GetSize());
			cx.m_avgPStandev_InrWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetActualAccessor().GetSize());
			{
				const int nSize_1D = avg_InrWide_Img->GetSize_1D();

				F32VectorVal<4> * dest_Ptr = (F32VectorVal<4> *)cx.m_avgPStandev_InrWide_Img->GetData();
				F32VectorVal<3> * src_Avg_Ptr = (F32VectorVal<3> *)avg_InrWide_Img->GetData();
				float * src_Standev_Ptr = standev_InrWide_Img->GetData();

				for (int i = 0; i < nSize_1D; i++)
				{
					*((F32VectorVal<3> *)&dest_Ptr[i]) = *(&src_Avg_Ptr[i]);
					dest_Ptr[i].Vals[3] = src_Standev_Ptr[i];
				}
			}

		}

		void ImgAngleDirMgr::Proceed_5_2()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			AffectCommonAvgPStandev_InrWide();
		}

		void ImgAngleDirMgr::Proceed_5_3()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			//const int nOutRad = 5;
			const int nOutRad = 8;
			//const int nOutRad = 8 * 2;
			{
				F32ImageArrayHolder1C_Ref standev_OutWide_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetActualAccessor().GetSize());
				F32VectorValImageArrayHolder_4C_Ref avg_OutWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetActualAccessor().GetSize());

				Calc_Avg_And_Standev_Image(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), avg_OutWide_Img->GetVirtAccessor(), standev_OutWide_Img->GetVirtAccessor(),
					//Window<int>::New(-nOutRad, nOutRad, -nOutRad, nOutRad));
					Window<int>::New(-nOutRad, nOutRad, 0, 0));

				cx.m_wideConflictDiff_Img = standev_OutWide_Img;

				//GlobalStuff::SetLinePathImg(GenTriChGrayImg(standev_OutWide_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
				//ShowImage(standev_OutWide_Img->GetSrcImg(), "standev_OutWide_Img->GetSrcImg()");
			}


			////------------

			//cx.m_wideConflictDiff_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetActualAccessor().GetSize());
			//{
			//	////Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			//	////Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);
			//	//Window<int> avgWin = Window<int>::New(-10, 10, -10, 10);
			//	////Window<int> avgWin = Window<int>::New(0, 0, -2, 2);
			//	Window<int> avgWin = Window<int>::New(-nOutRad, nOutRad, -nOutRad, nOutRad);

			//	F32VectorValImageArrayHolder_4C_Ref avg_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetActualAccessor().GetSize());
			//	AvgImage(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			//	F32ImageArrayHolder1C_Ref magSqr_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetActualAccessor().GetSize());
			//	CalcMagSqrImage(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), magSqr_Img->GetVirtAccessor());

			//	F32ImageArrayHolder1C_Ref avg_MagSqr_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetActualAccessor().GetSize());
			//	AvgImage(magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);

			//	Range<int> confRange = Range<int>::New(
			//		//-10 - avgWin.Get_X2(), 10 - avgWin.Get_X1());
			//		//-1 - avgWin.Get_X2(), 1 - avgWin.Get_X1());
			//		-1 - nOutRad - nInrRad, 1 + nOutRad + nInrRad);

			//	Calc_ConflictDiff_Image_X(avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
			//		cx.m_wideConflictDiff_Img->GetVirtAccessor(), confRange);

			//	//GlobalStuff::SetLinePathImg(GenTriChGrayImg(cx.m_wideConflictDiff_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//	//ShowImage(cx.m_wideConflictDiff_Img->GetSrcImg(), cx.MakeStrWithId("cx.m_wideConflictDiff_Img->GetSrcImg()").c_str());
			//}




		}

		void ImgAngleDirMgr::Proceed_6()
		{
			AffectCommonWideConflictDiff();
		}

		void ImgAngleDirMgr::AffectCommonAvgStandev()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			const int * orgToRotMap_Buf = orgToRotMap_Acc.GetData();
			
			PixelStandevInfo * commonImgBuf = (PixelStandevInfo *)m_parentContext->m_standevInfoImg->GetActualAccessor().GetData();

			float * localPtr = (float *)cx.m_avgStandev_X_Img->GetActualAccessor().GetData();
			float * localPtr_Norm = (float *)ncx.m_avgStandev_X_Img->GetActualAccessor().GetData();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffset_YX = nOffset_Y + x;

					PixelStandevInfo & rCommonPsi = commonImgBuf[nOffset_YX];

					int nOffset_Mapped = orgToRotMap_Buf[nOffset_YX];
					Ncpp_ASSERT(nOffset_Mapped >= 0);

					float standev_Local = localPtr[nOffset_Mapped];

					if (standev_Local < rCommonPsi.Val)
					{
						rCommonPsi.Val = standev_Local;
						rCommonPsi.NormVal = localPtr_Norm[nOffset_Mapped];
						rCommonPsi.Dir = cx.m_nIndex;
					}

				}
			}

		}

		void ImgAngleDirMgr::AffectCommonAvgPStandev_InrWide()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			const int * orgToRotMap_Buf = orgToRotMap_Acc.GetData();

			VectorVal<Float, 4> * commonImgBuf = (VectorVal<Float, 4> *)pcx.m_avgPStandev_InrWide_Img->GetActualAccessor().GetData();
			VectorVal<Float, 4> * localPtr = (VectorVal<Float, 4> *)cx.m_avgPStandev_InrWide_Img->GetActualAccessor().GetData();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffset_YX = nOffset_Y + x;

					VectorVal<Float, 4> & rCommonVal = commonImgBuf[nOffset_YX];

					int nOffset_Mapped = orgToRotMap_Buf[nOffset_YX];
					Ncpp_ASSERT(nOffset_Mapped >= 0);

					VectorVal<Float, 4> & val_Local = localPtr[nOffset_Mapped];
					Add(rCommonVal, val_Local, &rCommonVal);
				}
			}

		}
		
		void ImgAngleDirMgr::AffectCommonConflict()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			const int * orgToRotMap_Buf = orgToRotMap_Acc.GetData();

			int * rotToOrgMap_Buf = (int *)cx.m_rotToOrgMap_Img->GetActualAccessor().GetData();

			ConflictInfo2_Ex * commonImgBuf = (ConflictInfo2_Ex *)pcx.m_conflictInfoImg->GetActualAccessor().GetData();

			ConflictInfo2 * localPtr = (ConflictInfo2 *)cx.m_conflict_Img->GetActualAccessor().GetData();
			//ConflictInfo2 * localPtr_Norm = (ConflictInfo2 *)ncx.m_conflict_Img->GetActualAccessor().GetData();
			
			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffset_YX = nOffset_Y + x;

					ConflictInfo2_Ex & rCommonConf = commonImgBuf[nOffset_YX];

					int nOffset_Mapped = orgToRotMap_Buf[nOffset_YX];
					Ncpp_ASSERT(nOffset_Mapped >= 0);

					ConflictInfo2 & conf_Local = localPtr[nOffset_Mapped];

					if (conf_Local.Exists)
					{
						//*((ConflictInfo2 *)&rCommonConf) = conf_Local;

						int nOffset_Side_1_Mapped = rotToOrgMap_Buf[conf_Local.Offset_Side_1];
						if (nOffset_Side_1_Mapped < 0)
							continue;

						int nOffset_Side_2_Mapped = rotToOrgMap_Buf[conf_Local.Offset_Side_2];
						if (nOffset_Side_2_Mapped < 0)
							continue;

						rCommonConf.Exists = true;
						rCommonConf.Offset_Side_1 = nOffset_Side_1_Mapped;
						rCommonConf.Offset_Side_2 = nOffset_Side_2_Mapped;

						rCommonConf.Dir = cx.m_nIndex;
					}

				}
			}

		}

		void ImgAngleDirMgr::AffectCommonWideConflictDiff()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			const int * orgToRotMap_Buf = orgToRotMap_Acc.GetData();

			float * commonImgBuf = (float *)pcx.m_wideConflictDiff_Img->GetActualAccessor().GetData();

			float * localPtr = (float *)cx.m_wideConflictDiff_Img->GetActualAccessor().GetData();
			//float * localPtr_Norm = (float *)ncx.m_wideConflictDiff_Img->GetActualAccessor().GetData();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffset_YX = nOffset_Y + x;

					float & rCommonConf = commonImgBuf[nOffset_YX];

					int nOffset_Mapped = orgToRotMap_Buf[nOffset_YX];
					Ncpp_ASSERT(nOffset_Mapped >= 0);

					float & conf_Local = localPtr[nOffset_Mapped];

					if (conf_Local > rCommonConf)
					{
						rCommonConf = conf_Local;
					}

				}
			}


		}

		void ImgAngleDirMgr::DisplayConflictImg()
		{
			Context & cx = *m_context;

			const ActualArrayAccessor_2D<ConflictInfo2> & confAcc = cx.m_conflict_Img->GetActualAccessor();
			//F32ImageRef confDsp_Img = F32Image::Create(cvSize(confAcc->GetNofSteps_X_Org(), confAcc->GetNofSteps_Y_Org()), 3);
			F32ImageRef confDsp_Img = F32Image::Create(cvSize(confAcc.GetSize()), 3);

			confDsp_Img->SetAll(0);

			const int nSize_1D = confAcc.CalcSize_1D();

			F32ColorVal * destPtr = (F32ColorVal *)confDsp_Img->GetDataPtr();
			ConflictInfo2 * srcPtr = (ConflictInfo2 *)confAcc.GetData();

			float angle_Old = -1;
			for (int i = 0; i < nSize_1D; i++)
			{
				ConflictInfo2 & rSrc = srcPtr[i];
				F32ColorVal & rDest = destPtr[i];

				//rDest.val0 = 0;
				//rDest.val1 = 255;
				//rDest.val2 = 255;

				//continue;

				//Ncpp_ASSERT(-1 != rSrc.Dir);

				if (rSrc.Exists)
				{
					F32ColorVal & rDest_Side_1 = destPtr[rSrc.Offset_Side_1];
					F32ColorVal & rDest_Side_2 = destPtr[rSrc.Offset_Side_2];

					rDest.val0 = 0;
					rDest.val1 = 0;
					rDest.val2 = 255;

					rDest_Side_1.val0 = 0;
					rDest_Side_1.val1 = 255;
					rDest_Side_1.val2 = 0;

					rDest_Side_2.val0 = 0;
					rDest_Side_2.val1 = 255;
					rDest_Side_2.val2 = 0;
				}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}
			}

			ShowImage(confDsp_Img, cx.MakeStrWithId("confDsp_Img").c_str());
		}

	}
}

