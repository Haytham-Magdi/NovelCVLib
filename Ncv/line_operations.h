#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <Novel-Lib\Ncv\OpenCV\funcs1.h>
#include <vector>
#include <Novel-Lib\Ncv\OpenCV\Image.h>
#include <Novel-Lib\Ncv\ConflictInfo.h>

//#include <Novel-Lib\Ncpp\Common\commonLib.h>



namespace Ncv
{
	using namespace Ncpp;

	namespace Line_Operations
	{
		template<class T>
		void FillLine(MemAccessor_1D_REF(T) a_memAcc, T & a_val)
		{
			PtrIterator<T> ptrItr = a_memAcc->GenPtrIterator();

			for (; !ptrItr.IsDone(); ptrItr.Next())
			{
				T * ptr = ptrItr.GetCurrent();
				Element_Operations::Copy_ByPtr<T>(ptr, &a_val);
			}
		}

		template<class T>
		void DivideLineByNum(MemAccessor_1D_REF(T) a_memAcc, float a_num)
		{
			PtrIterator<T> ptrItr = a_memAcc->GenPtrIterator();

			for (; !ptrItr.IsDone(); ptrItr.Next())
			{
				T * ptr = ptrItr.GetCurrent();
				Element_Operations::DivideByNum_ByPtr<T>(ptr, a_num, ptr);
			}
		}

		template<class T>
		void MultiplyLineByNum(MemAccessor_1D_REF(T) a_memAcc, float a_num)
		{
			PtrIterator<T> ptrItr = a_memAcc->GenPtrIterator();

			for (; !ptrItr.IsDone(); ptrItr.Next())
			{
				T * ptr = ptrItr.GetCurrent();
				Element_Operations::MultiplyByNum_ByPtr<T>(ptr, a_num, ptr);
			}
		}

		template<class T>
		void CopyLine(MemAccessor_1D_REF(T) a_destAcc, MemAccessor_1D_REF(T) a_srcAcc)
		{
			Ncpp_ASSERT(a_srcAcc->GetIndexSize() ==
				a_destAcc->GetIndexSize());

			PtrIterator<T> ptrItr_Src = a_srcAcc->GenPtrIterator();
			PtrIterator<T> ptrItr_Dest = a_destAcc->GenPtrIterator();

			for (; !ptrItr_Src.IsDone(); ptrItr_Src.Next(), ptrItr_Dest.Next())
			{
				T * ptr_Src = ptrItr_Src.GetCurrent();
				T * ptr_Dest = ptrItr_Dest.GetCurrent();

				Element_Operations::Copy_ByPtr<T>(ptr_Dest, ptr_Src);
			}
		}

		template<class T>
		void CalcMagLine(MemAccessor_1D_REF(T) a_inpAcc, MemAccessor_1D_REF(float) a_outAcc)
		{
			Ncpp_ASSERT(a_inpAcc->GetIndexSize() ==
				a_outAcc->GetIndexSize());

			PtrIterator<T> ptrItr_Inp = a_inpAcc->GenPtrIterator();
			PtrIterator<float> ptrItr_Out = a_outAcc->GenPtrIterator();

			for (; !ptrItr_Inp.IsDone(); ptrItr_Inp.Next(), ptrItr_Out.Next())
			{
				T * ptr_Inp = ptrItr_Inp.GetCurrent();
				float * ptr_Out = ptrItr_Out.GetCurrent();

				*ptr_Out = Element_Operations::CalcMag_ByPtr<T>(ptr_Inp);
			}
		}

		template<class T>
		void CalcMagSqrLine(MemAccessor_1D_REF(T) a_inpAcc, MemAccessor_1D_REF(float) a_outAcc)
		{
			Ncpp_ASSERT(a_inpAcc->GetIndexSize() == a_outAcc->GetIndexSize());

			PtrIterator<T> ptrItr_Inp = a_inpAcc->GenPtrIterator();
			PtrIterator<float> ptrItr_Out = a_outAcc->GenPtrIterator();

			const float rate1 = 0.5;
			int i = 0;

			for (; !ptrItr_Inp.IsDone(); ptrItr_Inp.Next(), ptrItr_Out.Next())
			{
				T * ptr_Inp = ptrItr_Inp.GetCurrent();
				float * ptr_Out = ptrItr_Out.GetCurrent();

				*ptr_Out = Element_Operations::CalcMagSqr_ByPtr<T>(ptr_Inp);
				//*ptr_Out = rate1 * i++;
			}
		}

		template<class T>
		void AssertValues_Line(MemAccessor_1D_REF(T) a_inpAcc)
		{
			PtrIterator<T> ptrItr_Inp = a_inpAcc->GenPtrIterator();

			for (; !ptrItr_Inp.IsDone(); ptrItr_Inp.Next())
			{
				T * ptr_Inp = ptrItr_Inp.GetCurrent();

				Element_Operations::AssertValue_ByPtr<T>(ptr_Inp);
			}
		}

		template<class T>
		void AvgLine(MemAccessor_1D_REF(T) a_inpAcc, MemAccessor_1D_REF(T) a_outAcc, Range<int> & a_range)
		{
			Ncpp_ASSERT(a_inpAcc->GetIndexSize() == a_outAcc->GetIndexSize());
			Ncpp_ASSERT(a_range.GetBgn() <= 0);
			Ncpp_ASSERT(0 <= a_range.GetEnd());

			T zeroVal;
			SetToZero_ByPtr<T>(&zeroVal);

			FillLine<T>(a_outAcc, zeroVal);

			MemSimpleAccessor_1D<T> sac_Inp = a_inpAcc->GenSimpleAccessor();
			MemSimpleAccessor_1D<T> sac_Out = a_outAcc->GenSimpleAccessor();

			const int nSize_1D = a_inpAcc->GetIndexSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			T sum;
			T * pDest;
			SetToZero_ByPtr<T>(&sum);

			for (int i = 0; i < nRangeLen; i++)
			{
				Add_ByPtr(&sum, &sac_Inp[i], &sum);
			}
			pDest = &sac_Out[nBefDiff];
			Copy_ByPtr(pDest, &sum);
			DivideByNum_ByPtr(pDest, nRangeLen, pDest);

			for (int i = nBefDiff + 1; i <= nCenterEnd; i++)
			{
				pDest = &sac_Out[i];

				Subtract_ByPtr(&sum, &sac_Inp[(i - 1) - nBefDiff], &sum);
				Add_ByPtr(&sum, &sac_Inp[i + nAftDiff], &sum);

				Copy_ByPtr(pDest, &sum);
				DivideByNum_ByPtr(pDest, nRangeLen, pDest);
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				T * pSrc = &sac_Out[nBefDiff];
				for (int i = 0; i < nBefDiff; i++)
				{
					pDest = &sac_Out[i];
					Copy_ByPtr(pDest, pSrc);
				}
			}

			//	Fill end gap in output
			{
				const int nSrcIdx = (nSize_1D - 1) - nAftDiff;
				T * pSrc = &sac_Out[nSrcIdx];

				for (int i = nSrcIdx + 1; i < nSize_1D; i++)
				{
					pDest = &sac_Out[i];
					Copy_ByPtr(pDest, pSrc);
				}
			}

		}

		template<class T>
		void AvgLine_Weighted(MemAccessor_1D_REF(T) a_inpAcc, MemAccessor_1D_REF(float) a_weightAcc, MemAccessor_1D_REF(T) a_outAcc, Range<int> & a_range)
		{
			Ncpp_ASSERT(a_inpAcc->GetIndexSize() == a_outAcc->GetIndexSize());
			Ncpp_ASSERT(a_inpAcc->GetIndexSize() == a_weightAcc->GetIndexSize());
			Ncpp_ASSERT(a_range.GetBgn() <= 0);
			Ncpp_ASSERT(0 <= a_range.GetEnd());

			T zeroVal;
			SetToZero_ByPtr<T>(&zeroVal);

			FillLine<T>(a_outAcc, zeroVal);

			MemSimpleAccessor_1D<T> sac_Inp = a_inpAcc->GenSimpleAccessor();
			MemSimpleAccessor_1D<float> sac_Weight = a_weightAcc->GenSimpleAccessor();
			MemSimpleAccessor_1D<T> sac_Out = a_outAcc->GenSimpleAccessor();

			const int nSize_1D = a_inpAcc->GetIndexSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			T * pDest;

			T sum;
			SetToZero_ByPtr<T>(&sum);
			int sum_Wt = 0;

			T inp2;

			for (int i = 0; i < nRangeLen; i++)
			{
				Copy_ByPtr(&inp2, &sac_Inp[i]);
				MultiplyByNum_ByPtr(&inp2, sac_Weight[i], &inp2);

				sum_Wt += sac_Weight[i];
				Add_ByPtr(&sum, &inp2, &sum);
			}
			if (sum_Wt > 0.2f)
			{
				pDest = &sac_Out[nBefDiff];
				Copy_ByPtr(pDest, &sum);
				DivideByNum_ByPtr(pDest, sum_Wt, pDest);
			}

			for (int i = nBefDiff + 1; i <= nCenterEnd; i++)
			{
				pDest = &sac_Out[i];

				int idx = (i - 1) - nBefDiff;
				Copy_ByPtr(&inp2, &sac_Inp[idx]);
				MultiplyByNum_ByPtr(&inp2, sac_Weight[idx], &inp2);

				Subtract_ByPtr(&sum, &inp2, &sum);
				sum_Wt -= sac_Weight[idx];

				idx = i + nAftDiff;
				Copy_ByPtr(&inp2, &sac_Inp[idx]);
				MultiplyByNum_ByPtr(&inp2, sac_Weight[idx], &inp2);

				Add_ByPtr(&sum, &inp2, &sum);
				sum_Wt += sac_Weight[idx];

				if (sum_Wt > 0.2f)
				{
					Copy_ByPtr(pDest, &sum);
					DivideByNum_ByPtr(pDest, sum_Wt, pDest);
				}

				//float mag1 = CalcMag_ByPtr(pDest);
				//Ncpp_ASSERT(mag1 < 600);
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				T * pSrc = &sac_Out[nBefDiff];
				for (int i = 0; i < nBefDiff; i++)
				{
					pDest = &sac_Out[i];
					Copy_ByPtr(pDest, pSrc);
				}
			}

			//	Fill end gap in output
			{
				const int nSrcIdx = (nSize_1D - 1) - nAftDiff;
				T * pSrc = &sac_Out[nSrcIdx];

				for (int i = nSrcIdx + 1; i < nSize_1D; i++)
				{
					pDest = &sac_Out[i];
					Copy_ByPtr(pDest, pSrc);
				}
			}

		}

		template<class T>
		void CalcSqrtLine(MemAccessor_1D_REF(T) a_inpAcc, MemAccessor_1D_REF(float) a_outAcc)
		{
			Ncpp_ASSERT(a_inpAcc->GetIndexSize() ==
				a_outAcc->GetIndexSize());

			PtrIterator<T> ptrItr_Inp = a_inpAcc->GenPtrIterator();
			PtrIterator<float> ptrItr_Out = a_outAcc->GenPtrIterator();

			for (; !ptrItr_Inp.IsDone(); ptrItr_Inp.Next(), ptrItr_Out.Next())
			{
				T * ptr_Inp = ptrItr_Inp.GetCurrent();
				float * ptr_Out = ptrItr_Out.GetCurrent();

				*ptr_Out = Element_Operations::CalcSqrt_ByPtr<T>(ptr_Inp);
			}
		}

		template<class T>
		void CalcStandevLine(MemAccessor_1D_REF(T) a_avg_Acc, MemAccessor_1D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_1D_REF(float) a_outAcc)
		{
			Ncpp_ASSERT(a_avg_Acc->GetIndexSize() == a_avg_MagSqr_Acc->GetIndexSize());
			Ncpp_ASSERT(a_avg_Acc->GetIndexSize() == a_outAcc->GetIndexSize());

			PtrIterator<T> ptrItr_Avg = a_avg_Acc->GenPtrIterator();
			PtrIterator<float> ptrItr_Avg_MagSqr = a_avg_MagSqr_Acc->GenPtrIterator();
			PtrIterator<float> ptrItr_Out = a_outAcc->GenPtrIterator();

			for (; !ptrItr_Avg.IsDone();
				ptrItr_Avg.Next(), ptrItr_Avg_MagSqr.Next(), ptrItr_Out.Next())
			{
				T * ptr_Avg = ptrItr_Avg.GetCurrent();
				float * ptr_Avg_MagSqr = ptrItr_Avg_MagSqr.GetCurrent();
				float * ptr_Out = ptrItr_Out.GetCurrent();

				*ptr_Out = Element_Operations::CalcStandev_ByPtr<T>(ptr_Avg, *ptr_Avg_MagSqr);
			}
		}

		template<class T>
		void CalcConflictLine(MemAccessor_1D_REF(T) a_avg_Acc, MemAccessor_1D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_1D_REF(ConflictInfo) a_outAcc, Range<int> & a_range)
		{
			{
				ConflictInfo val_Init;
				val_Init.Exists = false;
				FillLine<ConflictInfo>(a_outAcc, val_Init);
			}

			Ncpp_ASSERT(a_avg_Acc->GetIndexSize() == a_avg_MagSqr_Acc->GetIndexSize());
			Ncpp_ASSERT(a_avg_Acc->GetIndexSize() == a_outAcc->GetIndexSize());

			MemSimpleAccessor_1D<T> sac_Avg = a_avg_Acc->GenSimpleAccessor();
			MemSimpleAccessor_1D<float> sac_Avg_MagSqr = a_avg_MagSqr_Acc->GenSimpleAccessor();
			MemSimpleAccessor_1D<ConflictInfo> sac_Out = a_outAcc->GenSimpleAccessor();

			const int nSize_1D = a_outAcc->GetIndexSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			for (int i = nBefDiff + 1; i <= nCenterEnd; i++)
			{
				ConflictInfo * pOut = &sac_Out[i];

				T * pAvg_1 = &sac_Avg[i - nBefDiff];
				float * pAvg_MagSqr_1 = &sac_Avg_MagSqr[i - nBefDiff];

				T * pAvg_2 = &sac_Avg[i + nAftDiff];
				float * pAvg_MagSqr_2 = &sac_Avg_MagSqr[i + nAftDiff];

				pOut->Exists = Element_Operations::CalcConflict_ByPtr(pAvg_1, *pAvg_MagSqr_1, pAvg_2, *pAvg_MagSqr_2);
				if (pOut->Exists)
				{
					pOut->Offset_Side_1 = pAvg_1 - a_avg_Acc->GetDataPtr_Org();
					Ncpp_ASSERT(pOut->Offset_Side_1 >= 0);

					pOut->Offset_Side_2 = pAvg_2 - a_avg_Acc->GetDataPtr_Org();
					Ncpp_ASSERT(pOut->Offset_Side_2 >= 0);
				}
				//else
				//{
				//	pOut->Offset_Side_1 = -7;
				//	pOut->Offset_Side_2 = -7;
				//}
			}
		}

		template<class T>
		void Calc_ConflictDiff_Line(MemAccessor_1D_REF(T) a_avg_Acc, MemAccessor_1D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_1D_REF(float) a_outAcc, Range<int> & a_range)
		{
			{
				float val_Init;
				val_Init = 0;
				FillLine<float>(a_outAcc, val_Init);
			}

			Ncpp_ASSERT(a_avg_Acc->GetIndexSize() == a_avg_MagSqr_Acc->GetIndexSize());
			Ncpp_ASSERT(a_avg_Acc->GetIndexSize() == a_outAcc->GetIndexSize());

			MemSimpleAccessor_1D<T> sac_Avg = a_avg_Acc->GenSimpleAccessor();
			MemSimpleAccessor_1D<float> sac_Avg_MagSqr = a_avg_MagSqr_Acc->GenSimpleAccessor();
			MemSimpleAccessor_1D<float> sac_Out = a_outAcc->GenSimpleAccessor();

			const int nSize_1D = a_outAcc->GetIndexSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			for (int i = nBefDiff + 1; i <= nCenterEnd; i++)
			{
				float * pOut = &sac_Out[i];

				T * pAvg_1 = &sac_Avg[i - nBefDiff];
				float * pAvg_MagSqr_1 = &sac_Avg_MagSqr[i - nBefDiff];

				T * pAvg_2 = &sac_Avg[i + nAftDiff];
				float * pAvg_MagSqr_2 = &sac_Avg_MagSqr[i + nAftDiff];

				*pOut = Element_Operations::Calc_ConflictDiff_ByPtr(pAvg_1, *pAvg_MagSqr_1, pAvg_2, *pAvg_MagSqr_2);
			}
		}

	};
}