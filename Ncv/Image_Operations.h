#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\Element_Operations\Element_Operations.h>
#include <NovelCVLib\Ncv\Line_Operations.h>
#include <NovelCVLib\Ncv\TempImageAccessor.h>



namespace Ncv
{
	using namespace Ncpp;
	using namespace Line_Operations;
	using namespace Element_Operations;

	namespace Image_Operations
	{
		template<class T>
		void FillImage_Stripes_H(MemAccessor_2D_REF(T) a_memAcc, T & a_val1, T & a_val2, int a_stripWidth)
		{
			T * valArr[2];
			valArr[0] = &a_val1;
			valArr[1] = &a_val2;

			int valIdx = 1;

			MemAccessor_1D_REF(T) acc_Y = a_memAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_X = a_memAcc->GenAccessor_1D_X();

			PtrIterator<T> ptrItr_Y = acc_Y->GenPtrIterator();

			for (int i = 0; !ptrItr_Y.IsDone(); ptrItr_Y.Next(), i++)
			{
				T * ptr_Y = ptrItr_Y.GetCurrent();

				if (0 == i % a_stripWidth)
				{
					valIdx = 1 - valIdx;
				}

				acc_X->SetDataPtr(ptr_Y);
				FillLine<T>(acc_X, *valArr[valIdx]);
			}
		}

		template<class T>
		void FillImage(MemAccessor_2D_REF(T) a_memAcc, T & a_val)
		{
			MemAccessor_1D_REF(T) acc_Y = a_memAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_X = a_memAcc->GenAccessor_1D_X();

			PtrIterator<T> ptrItr_Y = acc_Y->GenPtrIterator();

			//for (int i = 0; !ptrItr_Y.IsDone(); ptrItr_Y.Next(), i++)
			for (; !ptrItr_Y.IsDone(); ptrItr_Y.Next())
			{
				T * ptr_Y = ptrItr_Y.GetCurrent();

				acc_X->SetDataPtr(ptr_Y);
				FillLine<T>(acc_X, a_val);
			}
		}

		template<class T>
		void DivideImageByNum(MemAccessor_2D_REF(T) a_memAcc, float a_num)
		{
			MemAccessor_1D_REF(T) acc_Y = a_memAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_X = a_memAcc->GenAccessor_1D_X();

			PtrIterator<T> ptrItr_Y = acc_Y->GenPtrIterator();

			for (int i = 0; !ptrItr_Y.IsDone(); ptrItr_Y.Next(), i++)
			{
				T * ptr_Y = ptrItr_Y.GetCurrent();

				acc_X->SetDataPtr(ptr_Y);
				DivideLineByNum<T>(acc_X, a_num);
			}
		}

		template<class T>
		void MultiplyImageByNum(MemAccessor_2D_REF(T) a_memAcc, float a_num)
		{
			MemAccessor_1D_REF(T) acc_Y = a_memAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_X = a_memAcc->GenAccessor_1D_X();

			PtrIterator<T> ptrItr_Y = acc_Y->GenPtrIterator();

			for (int i = 0; !ptrItr_Y.IsDone(); ptrItr_Y.Next(), i++)
			{
				T * ptr_Y = ptrItr_Y.GetCurrent();

				acc_X->SetDataPtr(ptr_Y);
				MultiplyLineByNum<T>(acc_X, a_num);
			}
		}

		template<class T>
		void CopyImage(MemAccessor_2D_REF(T) a_destAcc, MemAccessor_2D_REF(T) a_srcAcc)
		{
			MemAccessor_1D_REF(T) acc_Src_Y = a_srcAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Src_X = a_srcAcc->GenAccessor_1D_X();

			MemAccessor_1D_REF(T) acc_Dest_Y = a_destAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Dest_X = a_destAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Src_Y->GetNofElms() == acc_Dest_Y->GetNofElms());

			PtrIterator<T> ptrItr_Src_Y = acc_Src_Y->GenPtrIterator();
			PtrIterator<T> ptrItr_Dest_Y = acc_Dest_Y->GenPtrIterator();

			for (; !ptrItr_Src_Y.IsDone(); ptrItr_Src_Y.Next(), ptrItr_Dest_Y.Next())
			{
				T * ptr_Src_Y = ptrItr_Src_Y.GetCurrent();
				T * ptr_Dest_Y = ptrItr_Dest_Y.GetCurrent();

				acc_Src_X->SetDataPtr(ptr_Src_Y);
				acc_Dest_X->SetDataPtr(ptr_Dest_Y);

				CopyLine<T>(acc_Dest_X, acc_Src_X);
			}
		}

		template<class T>
		void CalcMagImage(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(float) a_outAcc)
		{
			MemAccessor_1D_REF(T) acc_Inp_Y = a_inpAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Inp_X = a_inpAcc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Out_Y = a_outAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Out_X = a_outAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Inp_Y->GetNofElms() ==
				acc_Out_Y->GetNofElms());

			PtrIterator<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; !ptrItr_Inp_Y.IsDone(); ptrItr_Inp_Y.Next(), ptrItr_Out_Y.Next())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetCurrent();
				float * ptr_Out_Y = ptrItr_Out_Y.GetCurrent();

				acc_Inp_X->SetDataPtr(ptr_Inp_Y);
				acc_Out_X->SetDataPtr(ptr_Out_Y);

				CalcMagLine<T>(acc_Inp_X, acc_Out_X);
			}
		}

		template<class T>
		void CalcMagSqrImage(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(float) a_outAcc)
		{
			MemAccessor_1D_REF(T) acc_Inp_Y = a_inpAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Inp_X = a_inpAcc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Out_Y = a_outAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Out_X = a_outAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Inp_Y->GetNofElms() == acc_Out_Y->GetNofElms());

			PtrIterator<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; !ptrItr_Inp_Y.IsDone(); ptrItr_Inp_Y.Next(), ptrItr_Out_Y.Next())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetCurrent();
				float * ptr_Out_Y = ptrItr_Out_Y.GetCurrent();

				acc_Inp_X->SetDataPtr(ptr_Inp_Y);
				acc_Out_X->SetDataPtr(ptr_Out_Y);

				CalcMagSqrLine<T>(acc_Inp_X, acc_Out_X);
			}
		}

		template<class T>
		void AssertValues_Image(MemAccessor_2D_REF(T) a_inpAcc)
		{
			MemAccessor_1D_REF(T) acc_Inp_Y = a_inpAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Inp_X = a_inpAcc->GenAccessor_1D_X();

			PtrIterator<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();

			for (; !ptrItr_Inp_Y.IsDone(); ptrItr_Inp_Y.Next())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetCurrent();

				acc_Inp_X->SetDataPtr(ptr_Inp_Y);
				AssertValues_Line<T>(acc_Inp_X);
			}
		}

		template<class T>
		void AvgImage_H(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(T) a_outAcc, Range<int> & a_range_X)
		{
			MemAccessor_1D_REF(T) acc_Inp_Y = a_inpAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Inp_X = a_inpAcc->GenAccessor_1D_X();

			MemAccessor_1D_REF(T) acc_Out_Y = a_outAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Out_X = a_outAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Inp_Y->GetNofElms() ==
				acc_Out_Y->GetNofElms());

			PtrIterator<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator<T> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; !ptrItr_Inp_Y.IsDone(); ptrItr_Inp_Y.Next(), ptrItr_Out_Y.Next())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetCurrent();
				T * ptr_Out_Y = ptrItr_Out_Y.GetCurrent();

				acc_Inp_X->SetDataPtr(ptr_Inp_Y);
				acc_Out_X->SetDataPtr(ptr_Out_Y);

				AvgLine(acc_Inp_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void AvgImage(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(T) a_outAcc, Window<int> & a_window)
		{
			TempImageAccessor_REF(T) tmpImgAcc = new TempImageAccessor<T>(a_outAcc->GetOffsetCalc());

			AvgImage_H<T>(a_inpAcc, tmpImgAcc->GetMemAccessor(), a_window.GetRange_X());
			//AvgImage_H<T>(a_inpAcc, a_outAcc, a_range_X);

			//return;

			MemAccessor_2D_REF(T) outAcc2 = a_outAcc->Clone();
			outAcc2->SwitchXY();

			tmpImgAcc->SwitchXY();

			AvgImage_H<T>(tmpImgAcc->GetMemAccessor(), outAcc2, a_window.GetRange_Y());
		}

		template<class T>
		void AvgImage_Weighted_H(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(float) a_weightAcc, MemAccessor_2D_REF(T) a_outAcc, Range<int> & a_range_X)
		{
			MemAccessor_1D_REF(T) acc_Inp_Y = a_inpAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Inp_X = a_inpAcc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Weight_Y = a_weightAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Weight_X = a_weightAcc->GenAccessor_1D_X();

			MemAccessor_1D_REF(T) acc_Out_Y = a_outAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Out_X = a_outAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Inp_Y->GetNofElms() == acc_Weight_Y->GetNofElms());
			Ncpp_ASSERT(acc_Inp_Y->GetNofElms() == acc_Out_Y->GetNofElms());

			PtrIterator<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Weight_Y = acc_Weight_Y->GenPtrIterator();
			PtrIterator<T> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; !ptrItr_Inp_Y.IsDone(); ptrItr_Inp_Y.Next(), ptrItr_Weight_Y.Next(), ptrItr_Out_Y.Next())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetCurrent();
				float * ptr_Weight_Y = ptrItr_Weight_Y.GetCurrent();
				T * ptr_Out_Y = ptrItr_Out_Y.GetCurrent();

				acc_Inp_X->SetDataPtr(ptr_Inp_Y);
				acc_Weight_X->SetDataPtr(ptr_Weight_Y);
				acc_Out_X->SetDataPtr(ptr_Out_Y);

				AvgLine_Weighted(acc_Inp_X, acc_Weight_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void AvgImage_Weighted(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(float) a_weightAcc, MemAccessor_2D_REF(T) a_outAcc, Window<int> & a_window)
		{
			TempImageAccessor_REF(T) tmpImgAcc = new TempImageAccessor<T>(a_outAcc->GetOffsetCalc());

			AvgImage_Weighted_H(a_inpAcc, a_weightAcc, tmpImgAcc->GetMemAccessor(), a_window.GetRange_X());

			MemAccessor_2D_REF(T) outAcc2 = a_outAcc->Clone();
			outAcc2->SwitchXY();

			tmpImgAcc->SwitchXY();

			AvgImage_H<T>(tmpImgAcc->GetMemAccessor(), outAcc2, a_window.GetRange_Y());
		}





		template<class T>
		void CalcSqrtImage(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(float) a_outAcc)
		{
			MemAccessor_1D_REF(T) acc_Inp_Y = a_inpAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Inp_X = a_inpAcc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Out_Y = a_outAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Out_X = a_outAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Inp_Y->GetNofElms() ==
				acc_Out_Y->GetNofElms());

			PtrIterator<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; !ptrItr_Inp_Y.IsDone(); ptrItr_Inp_Y.Next(), ptrItr_Out_Y.Next())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetCurrent();
				float * ptr_Out_Y = ptrItr_Out_Y.GetCurrent();

				acc_Inp_X->SetDataPtr(ptr_Inp_Y);
				acc_Out_X->SetDataPtr(ptr_Out_Y);

				CalcSqrtLine<T>(acc_Inp_X, acc_Out_X);
			}
		}

		template<class T>
		void Calc_Avg_And_Standev_Image(MemAccessor_2D_REF(T) a_inp_Acc, MemAccessor_2D_REF(T) a_out_Avg_Acc,
			MemAccessor_2D_REF(float) a_out_Standev_Acc, Window<int> & a_Win)
		{
			//TempImageAccessor_REF(T) avg_Img = new TempImageAccessor_REF<T>(a_inp_Acc->GetOffsetCalc());
			AvgImage(a_inp_Acc, a_out_Avg_Acc, a_Win);

			//ShowImage(avg_Img->GetSrcImg(), "avg_Img->GetSrcImg()");
			
			TempImageAccessor_REF(float) magSqr_Img = new TempImageAccessor<float>(a_inp_Acc->GetOffsetCalc());
			CalcMagSqrImage(a_inp_Acc, magSqr_Img->GetMemAccessor());

			TempImageAccessor_REF(float) avg_MagSqr_Img = new TempImageAccessor<float>(a_inp_Acc->GetOffsetCalc());
			AvgImage(magSqr_Img->GetMemAccessor(), avg_MagSqr_Img->GetMemAccessor(), a_Win);

			//standev_Img = new F32ImageAccessor1C(a_inp_Acc->GetOffsetCalc());
			CalcStandevImage(a_out_Avg_Acc, avg_MagSqr_Img->GetMemAccessor(), a_out_Standev_Acc);
		}

		template<class T>
		void CalcStandevImage(MemAccessor_2D_REF(T) a_avg_Acc, MemAccessor_2D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_2D_REF(float) a_outAcc)
		{
			MemAccessor_1D_REF(T) acc_Avg_Y = a_avg_Acc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Avg_X = a_avg_Acc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Avg_MagSqr_X = a_avg_MagSqr_Acc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Out_Y = a_outAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Out_X = a_outAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Avg_Y->GetNofElms() == acc_Avg_MagSqr_Y->GetNofElms());
			Ncpp_ASSERT(acc_Avg_Y->GetNofElms() == acc_Out_Y->GetNofElms());

			//Ncpp_ASSERT(acc_Avg_X->GetNofElms() == acc_Avg_MagSqr_X->GetNofElms());
			//Ncpp_ASSERT(acc_Avg_X->GetNofElms() == acc_Out_X->GetNofElms());

			PtrIterator<T> ptrItr_Avg_Y = acc_Avg_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; !ptrItr_Avg_Y.IsDone();
				ptrItr_Avg_Y.Next(), ptrItr_Avg_MagSqr_Y.Next(), ptrItr_Out_Y.Next())
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetCurrent();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetCurrent();
				float * ptr_Out_Y = ptrItr_Out_Y.GetCurrent();

				acc_Avg_X->SetDataPtr(ptr_Avg_Y);
				acc_Avg_MagSqr_X->SetDataPtr(ptr_Avg_MagSqr_Y);
				acc_Out_X->SetDataPtr(ptr_Out_Y);

				CalcStandevLine<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X);
			}
		}

		template<class T>
		void CalcConflictImage_H(MemAccessor_2D_REF(T) a_avg_Acc, MemAccessor_2D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_2D_REF(ConflictInfo) a_outAcc, Range<int> & a_range_X)
		{
			MemAccessor_1D_REF(T) acc_Avg_Y = a_avg_Acc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Avg_X = a_avg_Acc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Avg_MagSqr_X = a_avg_MagSqr_Acc->GenAccessor_1D_X();

			MemAccessor_1D_REF(ConflictInfo) acc_Out_Y = a_outAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(ConflictInfo) acc_Out_X = a_outAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Avg_Y->GetNofElms() == acc_Avg_MagSqr_Y->GetNofElms());
			Ncpp_ASSERT(acc_Avg_Y->GetNofElms() == acc_Out_Y->GetNofElms());

			PtrIterator<T> ptrItr_Avg_Y = acc_Avg_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y->GenPtrIterator();
			PtrIterator<ConflictInfo> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; !ptrItr_Avg_Y.IsDone();
				ptrItr_Avg_Y.Next(), ptrItr_Avg_MagSqr_Y.Next(), ptrItr_Out_Y.Next())
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetCurrent();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetCurrent();
				ConflictInfo * ptr_Out_Y = ptrItr_Out_Y.GetCurrent();

				acc_Avg_X->SetDataPtr(ptr_Avg_Y);
				acc_Avg_MagSqr_X->SetDataPtr(ptr_Avg_MagSqr_Y);
				acc_Out_X->SetDataPtr(ptr_Out_Y);

				CalcConflictLine<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void Calc_ConflictDiff_Image_H(MemAccessor_2D_REF(T) a_avg_Acc, MemAccessor_2D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_2D_REF(float) a_outAcc, Range<int> & a_range_X)
		{
			MemAccessor_1D_REF(T) acc_Avg_Y = a_avg_Acc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(T) acc_Avg_X = a_avg_Acc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Avg_MagSqr_X = a_avg_MagSqr_Acc->GenAccessor_1D_X();

			MemAccessor_1D_REF(float) acc_Out_Y = a_outAcc->GenAccessor_1D_Y();
			MemAccessor_1D_REF(float) acc_Out_X = a_outAcc->GenAccessor_1D_X();

			Ncpp_ASSERT(acc_Avg_Y->GetNofElms() == acc_Avg_MagSqr_Y->GetNofElms());
			Ncpp_ASSERT(acc_Avg_Y->GetNofElms() == acc_Out_Y->GetNofElms());

			PtrIterator<T> ptrItr_Avg_Y = acc_Avg_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y->GenPtrIterator();
			PtrIterator<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; !ptrItr_Avg_Y.IsDone();
				ptrItr_Avg_Y.Next(), ptrItr_Avg_MagSqr_Y.Next(), ptrItr_Out_Y.Next())
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetCurrent();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetCurrent();
				float * ptr_Out_Y = ptrItr_Out_Y.GetCurrent();

				acc_Avg_X->SetDataPtr(ptr_Avg_Y);
				acc_Avg_MagSqr_X->SetDataPtr(ptr_Avg_MagSqr_Y);
				acc_Out_X->SetDataPtr(ptr_Out_Y);

				Calc_ConflictDiff_Line<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void Cala_AvgStandevImage_H(MemAccessor_2D_REF(T) a_inpAcc, MemAccessor_2D_REF(float) a_magSqrAcc,
			MemAccessor_2D_REF(float) a_outAcc, Range<int> a_standevRange_X, Range<int> a_avgRange_Y)
		{
			Ncpp_ASSERT(a_inpAcc->GetNofElms_X() == a_magSqrAcc->GetNofElms_X());
			Ncpp_ASSERT(a_inpAcc->GetNofElms_X() == a_outAcc->GetNofElms_X());

			Ncpp_ASSERT(a_inpAcc->GetNofElms_Y() == a_magSqrAcc->GetNofElms_Y());
			Ncpp_ASSERT(a_inpAcc->GetNofElms_Y() == a_outAcc->GetNofElms_Y());



			TempImageAccessor_REF(T) tmpAvgAcc_H = new TempImageAccessor<T>(a_inpAcc->GetOffsetCalc());
			AvgImage_H(a_inpAcc, tmpAvgAcc_H->GetMemAccessor(), a_standevRange_X);

			TempImageAccessor_REF(float) tmpAvg_MagSqr_H_Acc = new TempImageAccessor<float>(a_outAcc->GetOffsetCalc());
			AvgImage_H(a_magSqrAcc, tmpAvg_MagSqr_H_Acc->GetMemAccessor(), a_standevRange_X);

			TempImageAccessor_REF(float) tmpStandev_H_Acc = new TempImageAccessor<float>(a_outAcc->GetOffsetCalc());
			CalcStandevImage(tmpAvgAcc_H->GetMemAccessor(), tmpAvg_MagSqr_H_Acc->GetMemAccessor(),
				tmpStandev_H_Acc->GetMemAccessor());

			MemAccessor_2D_REF(float) outAcc_2 = a_outAcc->Clone();
			outAcc_2->SwitchXY();

			MemAccessor_2D_REF(float) standev_H_Acc_2 = tmpStandev_H_Acc->GetMemAccessor()->Clone();
			standev_H_Acc_2->SwitchXY();

			AvgImage_H(standev_H_Acc_2, outAcc_2, a_avgRange_Y);
		}




	};
}