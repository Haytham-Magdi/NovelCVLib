
// ElementOperations2.

		template<> void Assign(VectorVal<T_Elm, N_Dims> * a_pDest, const VectorVal<T_Elm, N_Dims> & a_src);

		template<> float CalcMagSqr(const VectorVal<T_Elm, N_Dims> & a_arg);

		//template<> void AssertValue(const VectorVal<T_Elm, N_Dims> & a_arg);

		template<> void Add(const VectorVal<T_Elm, N_Dims> & a_inp1, const VectorVal<T_Elm, N_Dims> & a_inp2, VectorVal<T_Elm, N_Dims> * a_pOut);

		template<> void Subtract(const VectorVal<T_Elm, N_Dims> & a_inp1, const VectorVal<T_Elm, N_Dims> & a_inp2, VectorVal<T_Elm, N_Dims> * a_pOut);

		template<> void DivideByNum(const VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, VectorVal<T_Elm, N_Dims> * a_pOut);

		template<> void MultiplyByNum(const VectorVal<T_Elm, N_Dims> & a_inp, const float a_num, VectorVal<T_Elm, N_Dims> * a_pOut);

		template<> void SetToZero(VectorVal<T_Elm, N_Dims> * a_pArg);

		template<> bool IsUndefined(const VectorVal<T_Elm, N_Dims> & a_arg);

		template<> void SetToUndefined(VectorVal<T_Elm, N_Dims> * a_pArg);




		//template<> float CalcMagSqr_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg);

		//template<> void AssertValue_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg);

		//template<> void Add_ByPtr(VectorVal<T_Elm, N_Dims> * a_pInp1, VectorVal<T_Elm, N_Dims> * a_pInp2, VectorVal<T_Elm, N_Dims> * a_pOut);

		//template<> void Subtract_ByPtr(VectorVal<T_Elm, N_Dims> * a_pInp1, VectorVal<T_Elm, N_Dims> * a_pInp2, VectorVal<T_Elm, N_Dims> * a_pOut);

		//template<> void DivideByNum_ByPtr(VectorVal<T_Elm, N_Dims> * a_pInp, float a_num, VectorVal<T_Elm, N_Dims> * a_pOut);

		//template<> void MultiplyByNum_ByPtr(VectorVal<T_Elm, N_Dims> * a_pInp, float a_num, VectorVal<T_Elm, N_Dims> * a_pOut);

		//template<> void SetToZero_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg);

		//template<> bool IsUndefined_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg);

		//template<> void SetToUndefined_ByPtr(VectorVal<T_Elm, N_Dims> * a_pArg);


