





// ElementOperations2.

		//template<> void AssertValue(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg);

		template<> void Assign(Ncv::VectorVal<T_Elm, N_Dims> * a_pDest, const Ncv::VectorVal<T_Elm, N_Dims> & a_src);

		template<> float CalcMagSqr(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg);

		//template<> void AssertValue(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg);

		template<> void Add(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp1, const Ncv::VectorVal<T_Elm, N_Dims> & a_inp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut);

		template<> void Subtract(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp1, const Ncv::VectorVal<T_Elm, N_Dims> & a_inp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut);

		template<> void DivideByNum(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut);

		template<> void MultiplyByNum(const Ncv::VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut);

		template<> void SetToZero(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg);

		template<> bool IsUndefined(const Ncv::VectorVal<T_Elm, N_Dims> & a_arg);

		template<> void SetToUndefined(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg);




		//template<> float CalcMagSqr_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg);

		//template<> void AssertValue_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg);

		//template<> void Add_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pInp1, Ncv::VectorVal<T_Elm, N_Dims> * a_pInp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut);

		//template<> void Subtract_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pInp1, Ncv::VectorVal<T_Elm, N_Dims> * a_pInp2, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut);

		//template<> void DivideByNum_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pInp, float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut);

		//template<> void MultiplyByNum_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pInp, float a_num, Ncv::VectorVal<T_Elm, N_Dims> * a_pOut);

		//template<> void SetToZero_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg);

		//template<> bool IsUndefined_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg);

		//template<> void SetToUndefined_ByPtr(Ncv::VectorVal<T_Elm, N_Dims> * a_pArg);


