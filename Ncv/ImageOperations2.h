#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\ElementOperations2\ElementOperations2.h>
#include <NovelCVLib\Ncv\LineOperations2.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderUtil.h>



namespace Ncv
{
	using namespace Ncpp;
	using namespace LineOperations2;
	using namespace ElementOperations2;

	namespace ImageOperations2
	{
		template<class T>
		void FillImage_Stripes_X(const VirtArrayAccessor_2D<T> & a_acc, const T & a_val1, const T & a_val2, int a_stripWidth)
		{
			T * valArr[2];
			valArr[0] = &a_val1;
			valArr[1] = &a_val2;

			int valIdx = 1;

			const VirtArrayAccessor_1D<T> acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y.GenPtrIterator();

			for (int i = 0; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn(), i++)
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				if (0 == i % a_stripWidth)
				{
					valIdx = 1 - valIdx;
				}

				acc_X.SetData(ptr_Y);
				FillLine<T>(acc_X, *valArr[valIdx]);
			}
		}

		template<class T>
		void FillImage(const VirtArrayAccessor_2D<T> & a_acc, const T & a_val)
		{
			const VirtArrayAccessor_1D<T> acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y.GenPtrIterator();

			//for (int i = 0; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn(), i++)
			for (; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn())
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				FillLine<T>(acc_X, a_val);
			}
		}

		template<class T>
		void SetImageToUndefined(const VirtArrayAccessor_2D<T> & a_acc)
		{
			const VirtArrayAccessor_1D<T> acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y.GenPtrIterator();

			//for (int i = 0; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn(), i++)
			for (; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn())
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				SetLineToUndefined<T>(acc_X);
			}
		}

		template<class T>
		void SetUndefinedInImageToValue(const VirtArrayAccessor_2D<T> & a_acc, const T & a_value)
		{
			const VirtArrayAccessor_1D<T> acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y.GenPtrIterator();

			//for (int i = 0; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn(), i++)
			for (; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn())
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				SetUndefinedInLineToValue<T>(acc_X, a_value);
			}
		}

		template<class T>
		void SetUndefinedInImageToZero(const VirtArrayAccessor_2D<T> & a_acc)
		{
			SetUndefinedInImageToValue(a_acc, CreateZeroVal<T>());
		}

		template<class T>
		void SetImageToBadValue(const VirtArrayAccessor_2D<T> & a_acc)
		{
			const VirtArrayAccessor_1D<T> acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y.GenPtrIterator();

			//for (int i = 0; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn(), i++)
			for (; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn())
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				SetLineToBadValue<T>(acc_X);
			}
		}


		template<class T>
		void AssertImageValues(const VirtArrayAccessor_2D<T> & a_acc)
		{
			const VirtArrayAccessor_1D<T> acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y.GenPtrIterator();

			//for (int i = 0; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn(), i++)
			for (; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn())
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				AssertLineValues<T>(acc_X);
			}
		}

		template<class T>
		void AssertImageUndefinedOrValid(const VirtArrayAccessor_2D<T> & a_acc)
		{
			const VirtArrayAccessor_1D<T> acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y.GenPtrIterator();

			//for (int i = 0; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn(), i++)
			for (; ptrItr_Y.HasValidPos(); ptrItr_Y.MoveBgn())
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				AssertLineUndefinedOrValid<T>(acc_X);
			}
		}


		template<class T>
		void DivideImageByNum(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const float a_num)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());


			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				T * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				DivideLineByNum<T>(acc_Inp_X, acc_Out_X, a_num);
			}
		}

		template<class T>
		void AddValueToImage(const VirtArrayAccessor_2D<T> & a_inpAcc, const T & a_value)
		{
			AddValueToImage(a_inpAcc, a_inpAcc, a_value);
		}

		template<class T>
		void AddValueToImage(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const T & a_value)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());


			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				T * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				AddValueToLine<T>(acc_Inp_X, acc_Out_X, a_value);
			}
		}


		template<class T>
		void DivideImageByNum(const VirtArrayAccessor_2D<T> & a_inpAcc, const float a_num)
		{
			DivideImageByNum(a_inpAcc, a_inpAcc, a_num);
		}


		template<class T>
		void MultiplyImageByNum(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const float a_num)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());


			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				T * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				MultiplyLineByNum<T>(acc_Inp_X, acc_Out_X, a_num);
			}
		}


		template<class T>
		void MultiplyImageByNum(const VirtArrayAccessor_2D<T> & a_inpAcc, const float a_num)
		{
			MultiplyImageByNum(a_inpAcc, a_inpAcc, a_num);
		}


		template<class T>
		void CopyImage(const VirtArrayAccessor_2D<T> & a_destAcc, const VirtArrayAccessor_2D<T> & a_srcAcc)
		{
			const VirtArrayAccessor_1D<T> acc_Src_Y = a_srcAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Src_X = a_srcAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> acc_Dest_Y = a_destAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Dest_X = a_destAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Src_Y.GetSize() == acc_Dest_Y.GetSize());

			PtrIterator2<T> ptrItr_Src_Y = acc_Src_Y.GenPtrIterator();
			PtrIterator2<T> ptrItr_Dest_Y = acc_Dest_Y.GenPtrIterator();

			for (; ptrItr_Src_Y.HasValidPos(); ptrItr_Src_Y.MoveBgn(), ptrItr_Dest_Y.MoveBgn())
			{
				T * ptr_Src_Y = ptrItr_Src_Y.GetBgn();
				T * ptr_Dest_Y = ptrItr_Dest_Y.GetBgn();

				acc_Src_X.SetData(ptr_Src_Y);
				acc_Dest_X.SetData(ptr_Dest_Y);

				CopyLine<T>(acc_Dest_X, acc_Src_X);
			}
		}

		template<class T>
		void CopyImageWithShift(const VirtArrayAccessor_2D<T> & a_destAcc, const VirtArrayAccessor_2D<T> & a_srcAcc, const S32Point & a_shiftPnt)
		{
			const VirtArrayAccessor_1D<T> acc_Src_Y = a_srcAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Src_X = a_srcAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> acc_Dest_Y = a_destAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Dest_X = a_destAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Src_Y.GetSize() == acc_Dest_Y.GetSize());

			PtrIterator2<T> ptrItr_Src_Y = acc_Src_Y.GenPtrIterator();
			PtrIterator2<T> ptrItr_Dest_Y = acc_Dest_Y.GenPtrIterator();


			if (a_shiftPnt.GetY() > 0)
			{
				for (int i = 0; ptrItr_Dest_Y.HasValidPos() && i < a_shiftPnt.GetY();
					ptrItr_Src_Y.MoveEnd(), ptrItr_Dest_Y.MoveBgn(), i++)
				{
					T * ptr_Dest_Y = ptrItr_Dest_Y.GetBgn();

					acc_Dest_X.SetData(ptr_Dest_Y);
					SetLineToUndefined(acc_Dest_X);
				}
			}
			else if (a_shiftPnt.GetY() < 0)
			{
				for (int i = 0; ptrItr_Src_Y.HasValidPos() && ptrItr_Dest_Y.HasValidPos() && i > a_shiftPnt.GetY();
					ptrItr_Src_Y.MoveBgn(), ptrItr_Dest_Y.MoveEnd(), i--)
				{
					T * ptr_Dest_Y = ptrItr_Dest_Y.GetEnd();
					
					acc_Dest_X.SetData(ptr_Dest_Y);
					SetLineToUndefined(acc_Dest_X);
				}
			}

			/////////////////


			for (; ptrItr_Src_Y.HasValidPos(); ptrItr_Src_Y.MoveBgn(), ptrItr_Dest_Y.MoveBgn())
			{
				T * ptr_Src_Y = ptrItr_Src_Y.GetBgn();
				T * ptr_Dest_Y = ptrItr_Dest_Y.GetBgn();

				acc_Src_X.SetData(ptr_Src_Y);
				acc_Dest_X.SetData(ptr_Dest_Y);

				CopyLineWithShift<T>(acc_Dest_X, acc_Src_X, a_shiftPnt.GetX());
			}
		}

		template<class T>
		void CalcMagImage(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<float> & a_outAcc)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcMagLine<T>(acc_Inp_X, acc_Out_X);
			}
		}

		template<class T>
		void CalcMagSqrImage(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<float> & a_outAcc)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcMagSqrLine<T>(acc_Inp_X, acc_Out_X);
			}
		}


		template<class T>
		void AvgImage_X(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				T * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				AvgLine(acc_Inp_X, acc_Out_X, a_range_X);
				// to be revised.
				AssertLineUndefinedOrValid(acc_Out_X);
			}
		}

		template<class T>
		void AvgImage(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const Window<int> & a_window)
		{
			ArrayHolder_2D_Ref<T> tmpHolder = ArrayHolderUtil::CreateFrom<T>(a_outAcc.GetSize());
			AvgImage_X<T>(a_inpAcc, tmpHolder->GetVirtAccessor(), a_window.GetRange_X());

			//tmpHolder_T = ArrayHolderUtil<T>::CreateTransposedProxyFrom(tmpHolder);
			//const VirtArrayAccessor_2D<float> tmpHolder_Acc_T = tmpHolder->GetVirtAccessor().GenTranspose();
			const VirtArrayAccessor_2D<T> tmpHolder_Acc_T = tmpHolder->GetVirtAccessor().GenTranspose();

			VirtArrayAccessor_2D<T> outAcc_T = a_outAcc.GenTranspose();
			//AvgImage_X<T>(tmpHolder_T->GetVirtAccessor(), outAcc_T, a_window.GetRange_Y());
			AvgImage_X<T>(tmpHolder_Acc_T, outAcc_T, a_window.GetRange_Y());
		}

		template<class T>
		void AvgImage_Weighted_X(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<float> & a_weightAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Weight_Y = a_weightAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Weight_X = a_weightAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Weight_Y.GetSize());
			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Weight_Y = acc_Weight_Y.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Weight_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				float * ptr_Weight_Y = ptrItr_Weight_Y.GetBgn();
				T * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Weight_X.SetData(ptr_Weight_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				AvgLine_Weighted(acc_Inp_X, acc_Weight_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void AvgImage_Weighted(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<float> & a_weightAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const Window<int> & a_window)
		{
			ArrayHolder_2D_Ref<T> tmpHolder = ArrayHolderUtil<T>::CreateFrom(a_outAcc.GetSize());
			AvgImage_Weighted_X(a_inpAcc, a_weightAcc, tmpHolder->GetVirtAccessor(), a_window.GetRange_X());

			//tmpHolder_T = ArrayHolderUtil<T>::CreateTransposedProxyFrom(tmpHolder);
			const VirtArrayAccessor_2D<float> tmpHolder_Acc_T = tmpHolder->GetVirtAccessor().GenTranspose();

			VirtArrayAccessor_2D<T> outAcc_T = a_outAcc.GenTranspose();
			//AvgImage_X<T>(tmpHolder_T->GetVirtAccessor(), outAcc_T, a_window.GetRange_Y());
			AvgImage_X<T>(tmpHolder_Acc_T, outAcc_T, a_window.GetRange_Y());
		}


		template<class T>
		void CalcSqrtImage(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<float> & a_outAcc)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcSqrtLine<T>(acc_Inp_X, acc_Out_X);
			}
		}

		template<class T>
		void Calc_Avg_And_Standev_Image(const VirtArrayAccessor_2D<T> & a_inp_Acc, const VirtArrayAccessor_2D<T> & a_out_Avg_Acc,
			const VirtArrayAccessor_2D<float> & a_out_Standev_Acc, const Window<int> & a_Win)
		{
			AvgImage(a_inp_Acc, a_out_Avg_Acc, a_Win);

			ArrayHolder_2D_Ref<float> magSqrHolder = ArrayHolderUtil::CreateFrom<float>(a_inp_Acc.GetSize());
			CalcMagSqrImage(a_inp_Acc, magSqrHolder->GetVirtAccessor());

			ArrayHolder_2D_Ref<float> avg_MagSqr_Holder = ArrayHolderUtil::CreateFrom<float>(a_inp_Acc.GetSize());
			AvgImage(magSqrHolder->GetVirtAccessor(), avg_MagSqr_Holder->GetVirtAccessor(), a_Win);

			CalcStandevImage(a_out_Avg_Acc, avg_MagSqr_Holder->GetVirtAccessor(), a_out_Standev_Acc);
		}

		template<class T>
		void CalcStandevImage(const VirtArrayAccessor_2D<T> & a_avg_Acc, const VirtArrayAccessor_2D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_2D<float> & a_outAcc)
		{
			const VirtArrayAccessor_1D<T> acc_Avg_Y = a_avg_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Avg_X = a_avg_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Avg_MagSqr_X = a_avg_MagSqr_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Avg_MagSqr_Y.GetSize());
			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Avg_Y = acc_Avg_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			int cnt = 0;
			for (; ptrItr_Avg_Y.HasValidPos();
				ptrItr_Avg_Y.MoveBgn(), ptrItr_Avg_MagSqr_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn(), cnt++)
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetBgn();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Avg_X.SetData(ptr_Avg_Y);
				acc_Avg_MagSqr_X.SetData(ptr_Avg_MagSqr_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcStandevLine<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X);
			}
		}

		template<class T>
		void CalcConflictImage_X(const VirtArrayAccessor_2D<T> & a_avg_Acc, const VirtArrayAccessor_2D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_2D<ConflictInfo2> a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> acc_Avg_Y = a_avg_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Avg_X = a_avg_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Avg_MagSqr_X = a_avg_MagSqr_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<ConflictInfo2> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<ConflictInfo2> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Avg_MagSqr_Y.GetSize());
			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Avg_Y = acc_Avg_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y.GenPtrIterator();
			PtrIterator2<ConflictInfo2> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Avg_Y.HasValidPos();
				ptrItr_Avg_Y.MoveBgn(), ptrItr_Avg_MagSqr_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetBgn();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetBgn();
				ConflictInfo2 * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Avg_X.SetData(ptr_Avg_Y);
				acc_Avg_MagSqr_X.SetData(ptr_Avg_MagSqr_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcConflictLine<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void Calc_ConflictDiff_Image_X(const VirtArrayAccessor_2D<T> & a_avg_Acc, const VirtArrayAccessor_2D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_2D<float> & a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> acc_Avg_Y = a_avg_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Avg_X = a_avg_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Avg_MagSqr_X = a_avg_MagSqr_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Avg_MagSqr_Y.GetSize());
			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Avg_Y = acc_Avg_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Avg_Y.HasValidPos();
				ptrItr_Avg_Y.MoveBgn(), ptrItr_Avg_MagSqr_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetBgn();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Avg_X.SetData(ptr_Avg_Y);
				acc_Avg_MagSqr_X.SetData(ptr_Avg_MagSqr_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				Calc_ConflictDiff_Line<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void CalcDiffImageX(const VirtArrayAccessor_2D<T> & a_inp_Acc,
			const VirtArrayAccessor_2D<T> & a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> acc_Inp_Y = a_inp_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Inp_X = a_inp_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out_Y = acc_Out_Y.GenPtrIterator();

			for (; ptrItr_Inp_Y.HasValidPos();
				ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				T * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcDiffLine<T>(acc_Inp_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void PrepareBidiffInfoImageFromDiffImages(const VirtArrayAccessor_2D<T> & a_diff_Acc,
			const VirtArrayAccessor_2D<BidiffInfo> & a_outAcc, const int a_posDiff)
		{

			VirtArrayAccessor_2D<float> outBkwdAcc;
			VirtArrayAccessor_2D<float> outFwdAcc;
			{
				const int nofMembersInBidiffInfo = sizeof(BidiffInfo) / sizeof(float);

				const float * pOutData_Fwd = &a_outAcc.GetData()->Diff1_FwdMag;
				const float * pOutData_Bkwd = &a_outAcc.GetData()->Diff1_BkwdMag;

				const float * pOutActualData_Fwd = &a_outAcc.GetActualData()->Diff1_FwdMag;
				const float * pOutActualData_Bkwd = &a_outAcc.GetActualData()->Diff1_BkwdMag;

				outBkwdAcc.Init(pOutData_Bkwd, pOutActualData_Bkwd, 
					a_outAcc.GetSize_X(), a_outAcc.GetStepSize_X() * nofMembersInBidiffInfo,
					a_outAcc.GetSize_Y(), a_outAcc.GetStepSize_Y() * nofMembersInBidiffInfo
					);
			
				outFwdAcc.Init(pOutData_Fwd, pOutActualData_Fwd, 
					a_outAcc.GetSize_X(), a_outAcc.GetStepSize_X() * nofMembersInBidiffInfo,
					a_outAcc.GetSize_Y(), a_outAcc.GetStepSize_Y() * nofMembersInBidiffInfo
					);
			}

			CalcMagImage(a_diff_Acc, outBkwdAcc);
			CopyImageWithShift(outFwdAcc, outBkwdAcc, S32Point(-a_posDiff, 0));
		}


		template<class T>
		void Calc_AvgStandevImage_X(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<float> & a_magSqrAcc,
			const VirtArrayAccessor_2D<float> & a_outAcc, const Range<int> a_standevRange_X, const Range<int> a_avgRange_Y)
		{
			Ncpp_ASSERT(a_inpAcc.GetSize_Y() == a_magSqrAcc.GetSize_Y());
			Ncpp_ASSERT(a_inpAcc.GetSize_Y() == a_outAcc.GetSize_Y());

			Ncpp_ASSERT(a_inpAcc.GetSize_X() == a_magSqrAcc.GetSize_X());
			Ncpp_ASSERT(a_inpAcc.GetSize_X() == a_outAcc.GetSize_X());


			ArrayHolder_2D_Ref<T> tmpAvgHolder_X = ArrayHolderUtil::CreateFrom<T>(a_inpAcc.GetSize());
			AvgImage_X(a_inpAcc, tmpAvgHolder_X->GetVirtAccessor(), a_standevRange_X);

			//AssertImageValues(a_magSqrAcc);
			//AssertImageUndefinedOrValid(a_magSqrAcc);

			ArrayHolder_2D_Ref<float> tmpAvg_MagSqr_X_Holder = ArrayHolderUtil::CreateFrom<float>(a_outAcc.GetSize());
			AvgImage_X(a_magSqrAcc, tmpAvg_MagSqr_X_Holder->GetVirtAccessor(), a_standevRange_X);

			ArrayHolder_2D_Ref<float> tmpStandev_X_Holder = ArrayHolderUtil::CreateFrom<float>(a_outAcc.GetSize());
			CalcStandevImage(tmpAvgHolder_X->GetVirtAccessor(), tmpAvg_MagSqr_X_Holder->GetVirtAccessor(),
				tmpStandev_X_Holder->GetVirtAccessor());

			VirtArrayAccessor_2D<float> outAcc_T = a_outAcc.GenTranspose();
			const VirtArrayAccessor_2D<float> standev_X_Acc_T = tmpStandev_X_Holder->GetVirtAccessor().GenTranspose();

			AvgImage_X(standev_X_Acc_T, outAcc_T, a_avgRange_Y);
		}




	};
}