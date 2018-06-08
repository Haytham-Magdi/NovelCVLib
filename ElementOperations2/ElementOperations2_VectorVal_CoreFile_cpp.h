
// ElementOperations2.


		void Assign(Ncv::VectorVal<T_Elm, N_Dims> * a_pDest, const Ncv::VectorVal<T_Elm, N_Dims> & a_src)
		{
			for (int i = 0; i < a_src.GetNofDims(); i++)
			{
				Assign(&a_pDest->Vals[i], a_src.Vals[i]);
			}
		}

		void AssertValue(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg)
		{
			AssertValue(a_arg.Vals[0]);

			//for (int i = 0; i < a_arg.GetNofDims(); i++)
			//{
			//	AssertValue(a_arg.Vals[i]);
			//}
		}


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


		void Add(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp1, const Ncv::VectorVal<T_Elm, N_Dims> & a_inp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				Add(a_inp1.Vals[i], a_inp2.Vals[i], &a_pOut->Vals[i]);
			}
		}


		void Subtract(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp1, const Ncv::VectorVal<T_Elm, N_Dims> & a_inp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				Subtract(a_inp1.Vals[i], a_inp2.Vals[i], &a_pOut->Vals[i]);
			}
		}


		void DivideByNum(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				DivideByNum(a_inp.Vals[i], a_num, &a_pOut->Vals[i]);
			}
		}


		void MultiplyByNum(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut)
		{
			for (int i = 0; i < a_pOut->GetNofDims(); i++)
			{
				MultiplyByNum(a_inp.Vals[i], a_num, &a_pOut->Vals[i]);
			}
		}


		void SetToZero(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		{
			for (int i = 0; i < a_pArg->GetNofDims(); i++)
			{
				SetToZero(&a_pArg->Vals[i]);
			}
		}


		bool IsUndefined(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg)
		{
			return IsUndefined(a_arg.Vals[0]);
		}


		void SetToUndefined(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		{
			SetToUndefined(&a_pArg->Vals[0]);

			//for (int i = 0; i < a_pArg->GetNofDims(); i++)
			//{
			//	SetToUndefined(&a_pArg->Vals[i]);
			//}
		}

		void SetToBadValue(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg)
		{
			SetToBadValue(&a_pArg->Vals[0]);

			//for (int i = 0; i < a_pArg->GetNofDims(); i++)
			//{
			//	SetToUndefined(&a_pArg->Vals[i]);
			//}
		}


//#undef T_Elm float
//#undef N_Dims 3

