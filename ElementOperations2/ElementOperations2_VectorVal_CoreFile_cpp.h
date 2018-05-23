
// ElementOperations2.


		void Assign(Ncv::VectorVal<T_Elm, N_Dims> * a_pDest, const Ncv::VectorVal<T_Elm, N_Dims> & a_src)
		{
			for (int i = 0; i < a_src.GetNofDims(); i++)
			{
				Assign(&a_pDest->Vals[i], a_src.Vals[i]);
			}
		}

		//void AssertValue(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg)
		//{
		//	for (int i = 0; i < a_arg.GetNofDims(); i++)
		//	{
		//		AssertValue(a_arg.Vals[i]);
		//	}
		//}


		//void Copy_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pDest, Ncv::VectorVal<T_Elm, N_Dims> * a_pSrc)
		//{
		//	memcpy(a_pDest, a_pSrc, sizeof(Ncv::VectorVal));
		//}

		float CalcMagSqr(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg)
		{
			float sum = 0;
			for (int i = 0; i < a_arg.GetNofDims(); i++)
			{
				sum += CalcMagSqr(a_arg.Vals[i]);
				//sum += Sqr<float>((float)a_arg.Vals[i]);
			}
			return sum;
		}

		//float CalcMagSqr_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	float sum = 0;
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		sum += Sqr(a_pArg->Vals[i]);
		//	}

		//	return sum;
		//}

		//void AssertValue_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		T_Elm & rElm = a_pArg->Vals[i];
		//		Ncpp_ASSERT(rElm > -3000000.0f && rElm < 3000000.0f);
		//	}
		//}

		void Add(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp1, const Ncv::VectorVal<T_Elm, N_Dims> & a_inp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				Add(a_inp1.Vals[i], a_inp2.Vals[i], &a_pOut->Vals[i]);
				//a_pOut->Vals[i] = a_inp1.Vals[i] + a_inp2.Vals[i];

				//T_Elm & rElm = a_pOut->Vals[i];
				//Ncpp_ASSERT(rElm > -3000000.0f && rElm < 3000000.0f);
			}
		}

		//void Add_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pInp1, Ncv::VectorVal<T_Elm, N_Dims> * a_pInp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		//{
		//	for (int i = 0; i < a_pOut->GetNofDims(); i++)
		//	{
		//		a_pOut->Vals[i] = a_pInp1->Vals[i] + a_pInp2->Vals[i];

		//		T_Elm & rElm = a_pOut->Vals[i];
		//		Ncpp_ASSERT(rElm > -3000000.0f && rElm < 3000000.0f);
		//	}
		//}

		void Subtract(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp1, const Ncv::VectorVal<T_Elm, N_Dims> & a_inp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				Subtract(a_inp1.Vals[i], a_inp2.Vals[i], &a_pOut->Vals[i]);
				//a_pOut->Vals[i] = a_inp1.Vals[i] - a_inp2.Vals[i];
			}
		}

		//void Subtract_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pInp1, Ncv::VectorVal<T_Elm, N_Dims> * a_pInp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		//{
		//	for (int i = 0; i < a_pOut->GetNofDims(); i++)
		//	{
		//		a_pOut->Vals[i] = a_pInp1->Vals[i] - a_pInp2->Vals[i];
		//	}
		//}

		void DivideByNum(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				DivideByNum(a_inp.Vals[i], a_num, &a_pOut->Vals[i]);
				//a_pOut->Vals[i] = a_inp.Vals[i] / a_num;
			}
		}

		//void DivideByNum_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pInp, const float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		//{
		//	for (int i = 0; i < a_pOut->GetNofDims(); i++)
		//	{
		//		a_pOut->Vals[i] = a_pInp->Vals[i] / a_num;
		//	}
		//}

		void MultiplyByNum(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				MultiplyByNum(a_inp.Vals[i], a_num, &a_pOut->Vals[i]);
				//a_pOut->Vals[i] = a_inp.Vals[i] * a_num;
			}
		}

		//void MultiplyByNum_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pInp, const float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		//{
		//	for (int i = 0; i < a_pOut->GetNofDims(); i++)
		//	{
		//		a_pOut->Vals[i] = a_pInp->Vals[i] * a_num;
		//	}
		//}

		void SetToZero(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		{
			for (int i = 0; i < a_pArg->GetNofDims(); i++)
			{
				SetToZero(&a_pArg->Vals[i]);
			}
		}

		//void SetToZero_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		SetToZero_ByPtr(&a_pArg->Vals[i]);
		//	}
		//}

		bool IsUndefined(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg)
		{
			//return IsUndefined(&a_pArg[0]);
			return IsUndefined(a_arg.Vals[0]);
		}

		//bool IsUndefined_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	return IsUndefined_ByPtr(&a_pArg[0]);
		//}

		void SetToUndefined(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		{
			for (int i = 0; i < a_pArg->GetNofDims(); i++)
			{
				SetToUndefined(&a_pArg->Vals[i]);
			}
		}

		//void SetToUndefined_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		//{
		//	for (int i = 0; i < a_pArg->GetNofDims(); i++)
		//	{
		//		SetToUndefined_ByPtr(&a_pArg->Vals[i]);
		//	}
		//}



//#undef T_Elm float
//#undef N_Dims 3

