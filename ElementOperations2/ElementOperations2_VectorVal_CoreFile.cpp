
// ElementOperations2.

		void Assign(VectorVal<T_Elm, N_Dims> * a_pDest, const VectorVal<T_Elm, N_Dims> & a_src)
		{
			for (int i = 0; i < a_pArg->GetNofDims(); i++)
			{
				Assign(&a_pDest->Vals[i], a_src.Vals[i]);
				//a_pDest->Vals[i] = a_src.Vals[i];
			}
		}

		//void Copy_ByPtr(VectorVal<T_Elm, N_Dims> * a_pDest, VectorVal<T_Elm, N_Dims> * a_pSrc)
		//{
		//	memcpy(a_pDest, a_pSrc, sizeof(VectorVal));
		//}

		float CalcMagSqr(const VectorVal<T_Elm, N_Dims> & a_arg)
		{
			float sum = 0;
			for (int i = 0; i < a_arg.GetNofDims(); i++)
			{
				sum += CalcMagSqr(a_arg.Vals[i]);
				//sum += Sqr<float>((float)a_arg.Vals[i]);
			}
			return sum;
		}

		//float CalcMagSqr_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	float sum = 0;
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		sum += Sqr(a_pArg->Vals[i]);
		//	}

		//	return sum;
		//}

		//void AssertValue_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		T_Elm & rElm = a_pArg->Vals[i];
		//		Ncpp_ASSERT(rElm > -3000000.0f && rElm < 3000000.0f);
		//	}
		//}

		void Add(const VectorVal<T_Elm, N_Dims> & a_inp1, const VectorVal<T_Elm, N_Dims> & a_inp2, VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				Add(a_inp1.Vals[i], a_inp2.Vals[i], &a_pOut->Vals[i]);
				//a_pOut->Vals[i] = a_inp1.Vals[i] + a_inp2.Vals[i];

				//T_Elm & rElm = a_pOut->Vals[i];
				//Ncpp_ASSERT(rElm > -3000000.0f && rElm < 3000000.0f);
			}
		}

		//void Add_ByPtr(VectorVal<T_Elm, N_Dims> * a_pInp1, VectorVal<T_Elm, N_Dims> * a_pInp2, VectorVal<T_Elm, N_Dims> * a_pOut)
		//{
		//	for (int i = 0; i < a_pOut->GetNofDims(); i++)
		//	{
		//		a_pOut->Vals[i] = a_pInp1->Vals[i] + a_pInp2->Vals[i];

		//		T_Elm & rElm = a_pOut->Vals[i];
		//		Ncpp_ASSERT(rElm > -3000000.0f && rElm < 3000000.0f);
		//	}
		//}

		void Subtract(const VectorVal<T_Elm, N_Dims> & a_inp1, const VectorVal<T_Elm, N_Dims> & a_inp2, VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				Subtract(a_inp1.Vals[i], a_inp2.Vals[i], &a_pOut->Vals[i]);
				//a_pOut->Vals[i] = a_inp1.Vals[i] - a_inp2.Vals[i];
			}
		}

		//void Subtract_ByPtr(VectorVal<T_Elm, N_Dims> * a_pInp1, VectorVal<T_Elm, N_Dims> * a_pInp2, VectorVal<T_Elm, N_Dims> * a_pOut)
		//{
		//	for (int i = 0; i < a_pOut->GetNofDims(); i++)
		//	{
		//		a_pOut->Vals[i] = a_pInp1->Vals[i] - a_pInp2->Vals[i];
		//	}
		//}

		void DivideByNum(const VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				DivideByNum(a_inp.Vals[i], a_num, &a_pOut->Vals[i]);
				//a_pOut->Vals[i] = a_inp.Vals[i] / a_num;
			}
		}

		//void DivideByNum_ByPtr(VectorVal<T_Elm, N_Dims> * a_pInp, const float a_num, VectorVal<T_Elm, N_Dims> * a_pOut)
		//{
		//	for (int i = 0; i < a_pOut->GetNofDims(); i++)
		//	{
		//		a_pOut->Vals[i] = a_pInp->Vals[i] / a_num;
		//	}
		//}

		void MultiplyByNum(const VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				MultiplyByNum(a_inp.Vals[i], a_num, &a_pOut->Vals[i]);
				//a_pOut->Vals[i] = a_inp.Vals[i] * a_num;
			}
		}

		//void MultiplyByNum_ByPtr(VectorVal<T_Elm, N_Dims> * a_pInp, const float a_num, VectorVal<T_Elm, N_Dims> * a_pOut)
		//{
		//	for (int i = 0; i < a_pOut->GetNofDims(); i++)
		//	{
		//		a_pOut->Vals[i] = a_pInp->Vals[i] * a_num;
		//	}
		//}

		void SetToZero(VectorVal<T_Elm, N_Dims> * a_pArg)
		{
			for (int i = 0; i < a_pArg->GetNofDims(); i++)
			{
				SetToZero(&a_pArg->Vals[i]);
			}
		}

		//void SetToZero_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		SetToZero_ByPtr(&a_pArg->Vals[i]);
		//	}
		//}

		bool IsUndefined(const VectorVal<T_Elm, N_Dims> & a_arg)
		{
			return IsUndefined(&a_pArg[0]);
		}

		//bool IsUndefined_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	return IsUndefined_ByPtr(&a_pArg[0]);
		//}

		void SetToUndefined(const VectorVal<T_Elm, N_Dims> & a_arg)
		{
			for (int i = 0; i < a_pArg->GetNofDims(); i++)
			{
				SetToUndefined(&a_pArg->Vals[i]);
			}
		}

		//void SetToUndefined_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		SetToUndefined_ByPtr(&a_pArg->Vals[i]);
		//	}
		//}



//#undef T_Elm float
//#undef N_Dims 3

