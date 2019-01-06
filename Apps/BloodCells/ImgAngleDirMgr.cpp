#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Apps\BloodCells\ImgAngleDirMgr.h>


//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	using namespace Ncv::ImageOperations2;
	
	namespace Ns_BloodCells
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

		void ImgAngleDirMgr::Proceed_1_1()
		{
			Context & cx = *m_context;

			//ShowImage(cx.m_org_Img->GetSrcImg(), cx.MakeStrWithId("org_Img->GetSrcImg()").c_str());

			cx.m_avgStandev_X_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			Calc_AvgStandevImage_X(cx.m_org_Img->GetVirtAccessor(), cx.m_magSqr_Img->GetVirtAccessor(),
				cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(-2, 2));
				//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(0, 1));
			//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(0, 0));
			//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-6, 6), Range<int>::New(-6, 6));
			//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-6, 6), Range<int>::New(-2, 2));
			//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-36, 36), Range<int>::New(-36, 36));
			//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-6, 6), Range<int>::New(-36, 36));
			//cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-36, 36), Range<int>::New(-6, 6));

			//if (1 == cx.m_nIndex)
			if (0 == cx.m_nIndex)
			{
				//float & elm1 = cx.m_avgStandev_X_Img->GetActualAccessor().GetAt(45, 77);
				// float & elm1 = cx.m_avgStandev_X_Img->GetActualAccessor().GetAt(215, 40);
				//elm1 = 255;

				//ShowImage(cx.m_avgStandev_X_Img->GetSrcImg(), cx.MakeStrWithId("m_avgStandev_X_Img->GetSrcImg()").c_str());
				ShowImage(GenTriChGrayImg(cx.m_avgStandev_X_Img->GetSrcImg()), cx.MakeStrWithId("m_avgStandev_X_Img->GetSrcImg()").c_str());
			}
			
		}

		void ImgAngleDirMgr::Proceed_1_2()
		{
			AffectCommonAvgStandev();
		}

		void ImgAngleDirMgr::Proceed_2_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			//Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			//Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);

			//Window<int> avgWin = Window<int>::New(-1, 0, -2, 2);
			////Window<int> avgWin = Window<int>::New(0, 0, -2, 2);
			Window<int> avgWin = Window<int>::New(-1, 0, -1, 1);

			//Window<int> avgWin = Window<int>::New(-2, 2, -2, 2);
			//Window<int> avgWin = Window<int>::New(-2, 1, -2, 2);

			cx.m_conflict_Img = ArrayHolderUtil::CreateEmptyFrom<ConflictInfo2>(cx.m_org_Img->AsHolderRef());

			F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			F32ImageArrayHolder1C_Ref avg_MagSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			AvgImage(cx.m_magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);

			Range<int> confRange = Range<int>::New(-1 - avgWin.GetX2(), 1 - avgWin.GetX1());

			CalcConflictImage_X(avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
				cx.m_conflict_Img->GetVirtAccessor(), confRange);

			if (0 == cx.m_nIndex)
			{
				DisplayConflictImg();
			}

		}

		void ImgAngleDirMgr::Proceed_2_2()
		{
			//Context & cx = *m_context;
			//Context & ncx = *m_normalContext;
			//AngleDirMgrColl_Context & pcx = *m_parentContext;

			AffectCommonConflict();
		}

		void ImgAngleDirMgr::Proceed_2b_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			//Window<int> avgWin = Window<int>::New(-1, 0, -1, 1);
			Window<int> avgWin = Window<int>::New(0, 0, 0, 0);

			//F32ImageArrayHolder3C_Ref diff_Img_1;
			//diff_Img_1 = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			
			cx.m_diff_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			cx.m_diff_2_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);

			//cx.m_bidiffInfo_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			cx.m_bidiffInfo_Img = ArrayHolderUtil::CreateEmptyFrom<BidiffInfo>(cx.m_org_Img->AsHolderRef());

			
			const int posDiff = 1;

			//F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			//Range<int> diffRange = Range<int>::New(-10 - avgWin.GetX2(), 10 - avgWin.GetX1());
			//Range<int> diffRange = Range<int>::New(-1 - avgWin.GetX2(), 1 - avgWin.GetX1());
			
			//Range<int> diffRange = Range<int>::New(-1 - avgWin.GetX2(), 0 - avgWin.GetX1());
			Range<int> diffRange = Range<int>::New(-posDiff - avgWin.GetX2(), 0 - avgWin.GetX1());
			

			//Range<int> diffRange = Range<int>::New(0 - avgWin.GetX2(), 1 - avgWin.GetX1());
			//Range<int> diffRange = Range<int>::New(0 - avgWin.GetX2(), -1 - avgWin.GetX1());

			CalcDiffImageX(cx.m_org_Img->GetVirtAccessor(), cx.m_diff_Img->GetVirtAccessor(), diffRange);
			CalcDiffImageX(cx.m_diff_Img->GetVirtAccessor(), cx.m_diff_2_Img->GetVirtAccessor(), diffRange);

			PrepareBidiffInfoImageFromDiffImages(cx.m_diff_Img->GetVirtAccessor(), cx.m_bidiffInfo_Img->GetVirtAccessor(), posDiff);

			if (0 == cx.m_nIndex)
			{
				DisplayDiffImages();
			}

		}

		
		void ImgAngleDirMgr::Proceed_2b_2()
		{
				//Context & cx = *m_context;
				//Context & ncx = *m_normalContext;
				//AngleDirMgrColl_Context & pcx = *m_parentContext;

				AffectCommonBidiffInfo();
		}


		void ImgAngleDirMgr::Proceed_3_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;


			//F32ImageArrayHolder1C_Ref standev_InrWide_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref standev_InrWide_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);

			const int nInrRad = 5;
			//const int nInrRad = 5 * 2;
			//const int nInrRad = 8;
			//F32ImageArrayHolder3C_Ref avg_InrWide_Img = new F32ImageArrayHolder3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder3C_Ref avg_InrWide_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			////F32VectorValImageArrayHolder_3C_Ref avg_InrWide_Img = new F32VectorValImageArrayHolder_3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//F32VectorValImageArrayHolder_3C_Ref avg_InrWide_Img = F32VectorValImageArrayHolder_3C::CreateEmptyFrom(cx.m_org_Img);
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

			////F32VectorValImageArrayHolder_4C_Ref cx.m_avgPStandev_InrWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//F32VectorValImageArrayHolder_4C_Ref cx.m_avgPStandev_InrWide_Img = F32VectorValImageArrayHolder_4C::CreateEmptyFrom(cx.m_org_Img);
			//cx.m_avgPStandev_InrWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetVirtAccessor().GetSize());
			cx.m_avgPStandev_InrWide_Img = F32VectorValImageArrayHolder_4C::CreateEmptyFrom(cx.m_org_Img);
			{
				const int nSize_1D = avg_InrWide_Img->GetActualAccessor().CalcSize_1D();

				F32VectorVal<4> * dest_Ptr = (F32VectorVal<4> *)cx.m_avgPStandev_InrWide_Img->GetActualAccessor().GetData();
				F32VectorVal<3> * src_Avg_Ptr = (F32VectorVal<3> *)avg_InrWide_Img->GetActualAccessor().GetData();
				float * src_Standev_Ptr = (float *)standev_InrWide_Img->GetActualAccessor().GetData();

				for (int i = 0; i < nSize_1D; i++)
				{
					AssertUndefinedOrValid(*(&src_Avg_Ptr[i]));
					AssertUndefinedOrValid(src_Standev_Ptr[i]);

					*((F32VectorVal<3> *)&dest_Ptr[i]) = *(&src_Avg_Ptr[i]);
					dest_Ptr[i].Vals[3] = src_Standev_Ptr[i];
				}
			}

		}

		void ImgAngleDirMgr::Proceed_3_2()
		{
			//Context & cx = *m_context;
			//Context & ncx = *m_normalContext;
			//AngleDirMgrColl_Context & pcx = *m_parentContext;

			AffectCommonAvgPStandev_InrWide();
		}

		void ImgAngleDirMgr::Proceed_4_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			//const int nOutRad = 5;
			const int nOutRad = 8;
			//const int nOutRad = 8 * 2;
			{
				//F32ImageArrayHolder1C_Ref standev_OutWide_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
				F32ImageArrayHolder1C_Ref standev_OutWide_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
				//F32VectorValImageArrayHolder_4C_Ref avg_OutWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetVirtAccessor().GetSize());
				F32VectorValImageArrayHolder_4C_Ref avg_OutWide_Img = F32VectorValImageArrayHolder_4C::CreateEmptyFrom(cx.m_org_Img);

				Calc_Avg_And_Standev_Image(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), avg_OutWide_Img->GetVirtAccessor(), standev_OutWide_Img->GetVirtAccessor(),
					//Window<int>::New(-nOutRad, nOutRad, -nOutRad, nOutRad));
					Window<int>::New(-nOutRad, nOutRad, 0, 0));

				cx.m_wideConflictDiff_Img = standev_OutWide_Img;

				//GlobalStuff::SetLinePathImg(GenTriChGrayImg(standev_OutWide_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
				//ShowImage(standev_OutWide_Img->GetSrcImg(), "standev_OutWide_Img->GetSrcImg()");
			}


			////------------

			////cx.m_wideConflictDiff_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//cx.m_wideConflictDiff_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//{
			//	////Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			//	////Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);
			//	//Window<int> avgWin = Window<int>::New(-10, 10, -10, 10);
			//	////Window<int> avgWin = Window<int>::New(0, 0, -2, 2);
			//	Window<int> avgWin = Window<int>::New(-nOutRad, nOutRad, -nOutRad, nOutRad);

			////	F32VectorValImageArrayHolder_4C_Ref avg_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//	F32VectorValImageArrayHolder_4C_Ref avg_Img = F32VectorValImageArrayHolder_4C::CreateEmptyFrom(cx.m_org_Img);
			//	AvgImage(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			////	F32ImageArrayHolder1C_Ref magSqr_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//	F32ImageArrayHolder1C_Ref magSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//	CalcMagSqrImage(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), magSqr_Img->GetVirtAccessor());

			////	F32ImageArrayHolder1C_Ref avg_MagSqr_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//	F32ImageArrayHolder1C_Ref avg_MagSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//	AvgImage(magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);

			//	Range<int> confRange = Range<int>::New(
			//		//-10 - avgWin.GetX2(), 10 - avgWin.GetX1());
			//		//-1 - avgWin.GetX2(), 1 - avgWin.GetX1());
			//		-1 - nOutRad - nInrRad, 1 + nOutRad + nInrRad);

			//	Calc_ConflictDiff_Image_X(avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
			//		cx.m_wideConflictDiff_Img->GetVirtAccessor(), confRange);

			//	//GlobalStuff::SetLinePathImg(GenTriChGrayImg(cx.m_wideConflictDiff_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//	//ShowImage(cx.m_wideConflictDiff_Img->GetSrcImg(), cx.MakeStrWithId("cx.m_wideConflictDiff_Img->GetSrcImg()").c_str());
			//}




		}

		void ImgAngleDirMgr::Proceed_4_2()
		{
			AffectCommonWideConflictDiff();
		}

		void ImgAngleDirMgr::AffectCommonAvgStandev()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();
			
			// const ActualArrayAccessor_2D<int> & rotToOrgMap_Acc = cx.m_rotToOrgMap_Img->GetActualAccessor();

			ActualArrayAccessor_2D<PixelStandevInfo> commonAcc = m_parentContext->m_standevInfoImg->GetActualAccessor();
			Ncpp_ASSERT(Size_2D::AreEqual(orgToRotMap_Acc.GetSize(), commonAcc.GetSize()));

			ActualArrayAccessor_1D<PixelStandevInfo> commonAcc_1D = commonAcc.GenAcc_1D();



			//float * localAcc_1D = (float *)cx.m_avgStandev_X_Img->GetActualAccessor().GetData();
			ActualArrayAccessor_1D<float> localAcc_1D = cx.m_avgStandev_X_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<float> localAcc_1D_Norm = ncx.m_avgStandev_X_Img->GetActualAccessor().GenAcc_1D();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					PixelStandevInfo & rCommonPsi = commonAcc_1D[nOffsetInOrg_1D];

					int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];

					// S32Point pntInRot = rotToOrgMap_Acc.CalcPointFromIndex_1D(nOffsetInRot_1D);

					const float standev_Local = localAcc_1D[nOffsetInRot_1D];
					const float standev_Norm = localAcc_1D_Norm[nOffsetInRot_1D];

					//rCommonPsi.allVals[cx.m_nIndex] = standev_Local;

					if (IsUndefined(standev_Local) || IsUndefined(standev_Norm))
					{
						continue;
					}
					
					//Ncpp_ASSERT(standev_Local >= 0.0f || standev_Local > -5000.0f);
					AssertValue(standev_Local);
					Ncpp_ASSERT(standev_Local >= -0.001);

					//if (standev_Local < rCommonPsi.Val)
					////if (1 == cx.m_nIndex)
					//{
					//	Assign(&rCommonPsi.Val, standev_Local);
					//	Assign(&rCommonPsi.NormLeastVal, standev_Norm);
					//	
					//	Assign(&rCommonPsi.Dir, cx.m_nIndex);
					//}


					if (IsUndefined(rCommonPsi))
					{
						Assign(&rCommonPsi.LeastVal, standev_Local);
						Assign(&rCommonPsi.NormLeastVal, standev_Norm);

						Assign(&rCommonPsi.LeastValDir, cx.m_nIndex);

						Assign(&rCommonPsi.SecondLeastVal, standev_Local);
						Assign(&rCommonPsi.NormSecondLeastVal, standev_Norm);

						Assign(&rCommonPsi.SecondLeastValDir, cx.m_nIndex);

						continue;
					}

					AssertValue(rCommonPsi);

					if (standev_Local < rCommonPsi.LeastVal)
					{
						Assign(&rCommonPsi.SecondLeastVal, rCommonPsi.LeastVal);
						Assign(&rCommonPsi.NormSecondLeastVal, rCommonPsi.NormLeastVal);

						Assign(&rCommonPsi.SecondLeastValDir, rCommonPsi.LeastValDir);

						Assign(&rCommonPsi.LeastVal, standev_Local);
						Assign(&rCommonPsi.NormLeastVal, standev_Norm);

						Assign(&rCommonPsi.LeastValDir, cx.m_nIndex);
					}
					else if (standev_Local < rCommonPsi.SecondLeastVal)
					{
						Assign(&rCommonPsi.SecondLeastVal, standev_Local);
						Assign(&rCommonPsi.NormSecondLeastVal, standev_Norm);

						Assign(&rCommonPsi.SecondLeastValDir, cx.m_nIndex);
					}

					AssertValue(rCommonPsi);

					////else if (standev_Local > rCommonPsi.MaxVal)
					//if (standev_Local > rCommonPsi.MaxVal)
					//{
					//	Assign(&rCommonPsi.MaxVal, standev_Local);
					//	Assign(&rCommonPsi.MaxValDir, cx.m_nIndex);
					//}

				}
			}

		}

		void ImgAngleDirMgr::AffectCommonAvgPStandev_InrWide()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();

			ActualArrayAccessor_1D<VectorVal<Float, 4>> commonAcc_1D = pcx.m_avgPStandev_InrWide_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<VectorVal<Float, 4>> localAcc_1D = cx.m_avgPStandev_InrWide_Img->GetActualAccessor().GenAcc_1D();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					VectorVal<Float, 4> * pCommonVal = &commonAcc_1D[nOffsetInOrg_1D];
					if (IsUndefined(*pCommonVal))
						continue;

					AssertValue(*pCommonVal);

					int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];
					Ncpp_ASSERT(nOffsetInRot_1D >= 0);

					VectorVal<Float, 4> & val_Local = localAcc_1D[nOffsetInRot_1D];
					AssertUndefinedOrValid(val_Local);
					if (IsUndefined(val_Local))
					{
						//SetToUndefined(pCommonVal);
						continue;
					}
					
					IncBy(*pCommonVal, val_Local);
				}
			}

		}
		

		void ImgAngleDirMgr::AffectCommonConflict()
		{
			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = m_context->m_orgToRotMap_Img->GetActualAccessor();

			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();
			ActualArrayAccessor_1D<int> rotToOrgMap_Acc_1D = m_context->m_rotToOrgMap_Img->GetActualAccessor().GenAcc_1D();

			ActualArrayAccessor_1D<ConflictInfo2_Ex> commonImgAcc_1D = m_parentContext->m_conflictInfoImg->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<ConflictInfo2> localAcc_1D = m_context->m_conflict_Img->GetActualAccessor().GenAcc_1D();
			
			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					ConflictInfo2_Ex & rCommonConf = commonImgAcc_1D[nOffsetInOrg_1D];
					
					AssertValue(rCommonConf);

					const int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];

					ConflictInfo2 & conf_Local = localAcc_1D[nOffsetInRot_1D];

					if (IsUndefined(conf_Local))
						continue;


					if (conf_Local.Exists)
					{
						Ncpp_ASSERT(conf_Local.Offset_Side_1 >= 0);
						int nOffset_Side_1_Mapped = rotToOrgMap_Acc_1D[conf_Local.Offset_Side_1];
						if (nOffset_Side_1_Mapped < 0)
							continue;

						Ncpp_ASSERT(conf_Local.Offset_Side_2 >= 0);
						int nOffset_Side_2_Mapped = rotToOrgMap_Acc_1D[conf_Local.Offset_Side_2];
						if (nOffset_Side_2_Mapped < 0)
							continue;

						rCommonConf.Exists = true;
						rCommonConf.Offset_Side_1 = nOffset_Side_1_Mapped;
						rCommonConf.Offset_Side_2 = nOffset_Side_2_Mapped;

						rCommonConf.Dir = m_context->m_nIndex;
					}

				}
			}

		}


		
		void ImgAngleDirMgr::AffectCommonBidiffInfo()
		{

			Context & cx = *m_context;
			Context & ncx = *m_normalContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();

			const ActualArrayAccessor_2D<int> & rotToOrgMap_Acc = cx.m_rotToOrgMap_Img->GetActualAccessor();

			ActualArrayAccessor_2D<BidiffInfoCommon> commonAcc = m_parentContext->m_bidiffInfoCommonImg->GetActualAccessor();
			Ncpp_ASSERT(Size_2D::AreEqual(orgToRotMap_Acc.GetSize(), commonAcc.GetSize()));

			ActualArrayAccessor_1D<BidiffInfoCommon> commonAcc_1D = commonAcc.GenAcc_1D();



			//float * localAcc_1D = (float *)cx.m_avgStandev_X_Img->GetActualAccessor().GetData();
			ActualArrayAccessor_1D<BidiffInfo> localAcc_1D = cx.m_bidiffInfo_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<BidiffInfo> localAcc_1D_Norm = ncx.m_bidiffInfo_Img->GetActualAccessor().GenAcc_1D();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					BidiffInfoCommon & rCommonBdc = commonAcc_1D[nOffsetInOrg_1D];

					int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];

					 S32Point pntInRot = rotToOrgMap_Acc.CalcPointFromIndex_1D(nOffsetInRot_1D);

					const BidiffInfo & rBidiffInfo_Local = localAcc_1D[nOffsetInRot_1D];
					const BidiffInfo & rBidiffInfo_Norm = localAcc_1D_Norm[nOffsetInRot_1D];

					//rCommonBdc.allVals[cx.m_nIndex] = bidiffInfo_Local;

					if ((IsUndefined(rBidiffInfo_Local.Diff1_BkwdMag) && IsUndefined(rBidiffInfo_Local.Diff1_FwdMag)) ||
						(IsUndefined(rBidiffInfo_Norm.Diff1_BkwdMag) && IsUndefined(rBidiffInfo_Norm.Diff1_FwdMag)) )
					{
						continue;
					}

					float bidiffInfoMin_Local, bidiffInfoMax_Local;
					{
						MaxFinder<float> maxFinder;
						MinFinder<float> minFinder;
						
						if (!IsUndefined(rBidiffInfo_Local.Diff1_BkwdMag))
						{
							maxFinder.PushValue(rBidiffInfo_Local.Diff1_BkwdMag);
							minFinder.PushValue(rBidiffInfo_Local.Diff1_BkwdMag);
						}

						if (!IsUndefined(rBidiffInfo_Local.Diff1_FwdMag))
						{
							maxFinder.PushValue(rBidiffInfo_Local.Diff1_FwdMag);
							minFinder.PushValue(rBidiffInfo_Local.Diff1_FwdMag);
						}

						bidiffInfoMax_Local = maxFinder.FindMax();
						AssertValue(bidiffInfoMax_Local);
						Ncpp_ASSERT(bidiffInfoMax_Local >= -0.001);

						bidiffInfoMin_Local = minFinder.FindMin();
						AssertValue(bidiffInfoMin_Local);
						Ncpp_ASSERT(bidiffInfoMin_Local >= -0.001);
					}

					float bidiffInfoMin_Norm, bidiffInfoMax_Norm;
					{
						MaxFinder<float> maxFinder;
						MinFinder<float> minFinder;

						if (!IsUndefined(rBidiffInfo_Norm.Diff1_BkwdMag))
						{
							maxFinder.PushValue(rBidiffInfo_Norm.Diff1_BkwdMag);
							minFinder.PushValue(rBidiffInfo_Norm.Diff1_BkwdMag);
						}

						if (!IsUndefined(rBidiffInfo_Norm.Diff1_FwdMag))
						{
							maxFinder.PushValue(rBidiffInfo_Norm.Diff1_FwdMag);
							minFinder.PushValue(rBidiffInfo_Norm.Diff1_FwdMag);
						}

						bidiffInfoMax_Norm = maxFinder.FindMax();
						AssertValue(bidiffInfoMax_Norm);
						Ncpp_ASSERT(bidiffInfoMax_Norm >= -0.001);

						bidiffInfoMin_Norm = minFinder.FindMin();
						AssertValue(bidiffInfoMin_Norm);
						Ncpp_ASSERT(bidiffInfoMin_Norm >= -0.001);
					}



					//if (standev_Local < rCommonBdc.Val)
					////if (1 == cx.m_nIndex)
					//{
					//	Assign(&rCommonBdc.Val, standev_Local);
					//	Assign(&rCommonBdc.NormLeastVal, standev_Norm);
					//	
					//	Assign(&rCommonBdc.Dir, cx.m_nIndex);
					//}



					//if (4 == cx.m_nIndex)
					//if (bidiffInfoMax_Norm > 300 && 4 == cx.m_nIndex && 158 == y)
					if ((0 == cx.m_nIndex || 4 == cx.m_nIndex ) && 129 == x && 158 == y)
					{
						x = x;
					}

					if (IsUndefined(rCommonBdc))
					{
						//if (bidiffInfoMax_Norm > 0)
						if (bidiffInfoMax_Norm > 300 && 4 == cx.m_nIndex && 158 == y)
						{
							x = x;
						}

						Assign(&rCommonBdc.LeastVal, bidiffInfoMax_Local);
						//Assign(&rCommonBdc.LeastVal, bidiffInfoMin_Local);
						Assign(&rCommonBdc.NormLeastVal, bidiffInfoMax_Norm);

						Assign(&rCommonBdc.LeastValDir, cx.m_nIndex);

						Assign(&rCommonBdc.SecondLeastVal, bidiffInfoMax_Local);
						//Assign(&rCommonBdc.SecondLeastVal, bidiffInfoMin_Local);
						Assign(&rCommonBdc.NormSecondLeastVal, bidiffInfoMax_Norm);

						Assign(&rCommonBdc.SecondLeastValDir, cx.m_nIndex);

						continue;
					}

					AssertValue(rCommonBdc);

					if (bidiffInfoMax_Local < rCommonBdc.LeastVal)
					//if (bidiffInfoMin_Local < rCommonBdc.LeastVal)
					{
						if (0 != cx.m_nIndex)
						{
							x = x;
						}

						Assign(&rCommonBdc.SecondLeastVal, rCommonBdc.LeastVal);
						Assign(&rCommonBdc.NormSecondLeastVal, rCommonBdc.NormLeastVal);

						Assign(&rCommonBdc.SecondLeastValDir, rCommonBdc.LeastValDir);

						Assign(&rCommonBdc.LeastVal, bidiffInfoMax_Local);
						//Assign(&rCommonBdc.LeastVal, bidiffInfoMin_Local);
						Assign(&rCommonBdc.NormLeastVal, bidiffInfoMax_Norm);

						Assign(&rCommonBdc.LeastValDir, cx.m_nIndex);
					}
					else if (bidiffInfoMax_Local < rCommonBdc.SecondLeastVal)
					//else if (bidiffInfoMin_Local < rCommonBdc.SecondLeastVal)
					{
						Assign(&rCommonBdc.SecondLeastVal, bidiffInfoMax_Local);
						//Assign(&rCommonBdc.SecondLeastVal, bidiffInfoMin_Local);
						Assign(&rCommonBdc.NormSecondLeastVal, bidiffInfoMax_Norm);

						Assign(&rCommonBdc.SecondLeastValDir, cx.m_nIndex);
					}

					AssertValue(rCommonBdc);

					////else if (bidiffInfoMax_Local > rCommonBdc.MaxVal)
					//if (bidiffInfoMax_Local > rCommonBdc.MaxVal)
					//{
					//	Assign(&rCommonBdc.MaxVal, bidiffInfoMax_Local);
					//	Assign(&rCommonBdc.MaxValDir, cx.m_nIndex);
					//}

				}	//	x for end.
			}	//	y	for end.


		}

		void ImgAngleDirMgr::AffectCommonWideConflictDiff()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();

			ActualArrayAccessor_1D<float> commonAcc_1D = pcx.m_wideConflictDiff_Img->GetActualAccessor().GenAcc_1D();

			float * localAcc_1D = (float *)cx.m_wideConflictDiff_Img->GetActualAccessor().GetData();
			//float * localAcc_1D_Norm = (float *)ncx.m_wideConflictDiff_Img->GetActualAccessor().GetData();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					float & rCommonConf = commonAcc_1D[nOffsetInOrg_1D];
					AssertValue(rCommonConf);

					int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];
					Ncpp_ASSERT(nOffsetInRot_1D >= 0);

					float & conf_Local = localAcc_1D[nOffsetInRot_1D];
					if (IsUndefined(conf_Local))
					{
						continue;
					}

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
			F32ImageRef confDsp_Img = F32Image::Create(toCvSize(confAcc.GetSize()), 3);

			confDsp_Img->SetAll(0);

			ActualArrayAccessor_1D<F32ColorVal> dispAcc_1D((F32ColorVal *)confDsp_Img->GetDataPtr(), confDsp_Img->GetSize1D());


			const ActualArrayAccessor_1D<ConflictInfo2> & confAcc_1D = confAcc.GenAcc_1D();

			//float angle_Old = -1;
			for (int i = 0; i < confAcc_1D.GetSize(); i++)
			{
				ConflictInfo2 & rSrc = confAcc_1D[i];
				if (IsUndefined(rSrc))
				{
					continue;
				}

				AssertValue(rSrc);

				F32ColorVal & rDest = dispAcc_1D[i];

				//rDest.val0 = 0;
				//rDest.val1 = 255;
				//rDest.val2 = 255;

				//continue;

				//Ncpp_ASSERT(-1 != rSrc.Dir);

				if (rSrc.Exists)
				{
					F32ColorVal & rDest_Side_1 = dispAcc_1D[rSrc.Offset_Side_1];
					F32ColorVal & rDest_Side_2 = dispAcc_1D[rSrc.Offset_Side_2];

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

		void ImgAngleDirMgr::DisplayDiffImages()
		{
			Context & cx = *m_context;


			F32ImageArrayHolder3C_Ref diff_Img_disp = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_diff_Img);
			CopyImage(diff_Img_disp->GetVirtAccessor(), cx.m_diff_Img->GetVirtAccessor());
			//CopyImageWithShift(diff_Img_disp->GetVirtAccessor(), cx.m_diff_Img->GetVirtAccessor(), S32Point(70, 70));
			SetUndefinedInImageToZero(diff_Img_disp->GetVirtAccessor());
			AddValueToImage(diff_Img_disp->GetVirtAccessor(), F32ColorVal::FromNum(130));

			F32ImageArrayHolder3C_Ref diff_2_Img_disp = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_diff_2_Img);
			CopyImage(diff_2_Img_disp->GetVirtAccessor(), cx.m_diff_2_Img->GetVirtAccessor());
			SetUndefinedInImageToZero(diff_2_Img_disp->GetVirtAccessor());
			AddValueToImage(diff_2_Img_disp->GetVirtAccessor(), F32ColorVal::FromNum(130));

			////--

			const ActualArrayAccessor_2D<BidiffInfo> & bidiffInfoAcc = cx.m_bidiffInfo_Img->GetActualAccessor();

			F32ImageRef bidiffInfoDsp_Img = F32Image::Create(toCvSize(bidiffInfoAcc.GetSize()), 3);


			bidiffInfoDsp_Img->SetAll(0);

			ActualArrayAccessor_1D<F32ColorVal> dispAcc_1D((F32ColorVal *)bidiffInfoDsp_Img->GetDataPtr(), bidiffInfoDsp_Img->GetSize1D());

			const ActualArrayAccessor_1D<BidiffInfo> & bidiffInfoAcc_1D = bidiffInfoAcc.GenAcc_1D();

			for (int i = 0; i < bidiffInfoAcc_1D.GetSize(); i++)
			{
				BidiffInfo & rSrc = bidiffInfoAcc_1D[i];

				F32ColorVal & rDest = dispAcc_1D[i];

				//rDest.val0 = 0;

				if (!IsUndefined(rSrc.Diff1_BkwdMag))
				{
					//if (rSrc.Diff1_BkwdMag > 50)
					//{
					//	i = i;
					//}

					AssertValue(rSrc.Diff1_BkwdMag);
					rDest.val1 = rSrc.Diff1_BkwdMag;
				}

				if (!IsUndefined(rSrc.Diff1_FwdMag))
				{
					//if (rSrc.Diff1_FwdMag > 50)
					//{
					//	i = i;
					//}

					AssertValue(rSrc.Diff1_FwdMag);
					rDest.val2 = rSrc.Diff1_FwdMag;
				}

			}

			ShowImage(bidiffInfoDsp_Img, cx.MakeStrWithId("bidiffInfoDsp_Img").c_str());





			ShowImage(diff_Img_disp->GetSrcImg(), cx.MakeStrWithId("diffDsp_Img").c_str());
			ShowImage(diff_2_Img_disp->GetSrcImg(), cx.MakeStrWithId("diff_2_Dsp_Img").c_str());
			
			//GlobalStuff::SetLinePathImg(diff_Img_disp->GetSrcImg());
			//GlobalStuff::SetLinePathImg(diff_2_Img_disp->GetSrcImg());
			GlobalStuff::SetLinePathImg(bidiffInfoDsp_Img);
			GlobalStuff::ShowLinePathImg();

		}

	}
}

