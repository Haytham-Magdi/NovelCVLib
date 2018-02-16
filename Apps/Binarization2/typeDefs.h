

template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
class ImageAccessor;


#define ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) ObjRef< ImageAccessor< T_ImgElm, T_AccElm, V_NofChannels >>

//typedef ImageAccessor< float, float, 3 > F32Image3C_FloatAcc;
//typedef ObjRef< F32Image3C_FloatAcc > F32Image3C_FloatAcc_Ref;

typedef ImageAccessor< Float, F32ColorVal, 3 > F32ImageAccessor3C;
typedef ObjRef< F32ImageAccessor3C > F32ImageAccessor3C_Ref;

//typedef ImageAccessor< Ncpp::Float, float, 1 > F32ImageAccessor1C;
typedef ImageAccessor< Float, float, 1 > F32ImageAccessor1C;
typedef ObjRef< F32ImageAccessor1C > F32ImageAccessor1C_Ref;

typedef ImageAccessor< Int32, int, 1 > S32ImageAccessor1C;
typedef ObjRef< S32ImageAccessor1C > S32ImageAccessor1C_Ref;


//--====================================



template<class T, int const V_NofChannels>
using VectorValImageAcc = ImageAccessor<T, VectorVal<T, V_NofChannels>, V_NofChannels>;

template<class T, int const V_NofChannels>
using VectorValImageAcc_Ref = ObjRef< VectorValImageAcc<T, V_NofChannels> >;

//typedef VectorValImageAcc_Ref = ObjRef< VectorValImageAcc<T, V_NofChannels> >;


typedef VectorValImageAcc< Float, 4 > F32VectorValImageAcc_4C;
typedef ObjRef< F32VectorValImageAcc_4C > F32VectorValImageAcc_4C_Ref;

typedef VectorValImageAcc< Float, 3 > F32VectorValImageAcc_3C;
typedef ObjRef< F32VectorValImageAcc_3C > F32VectorValImageAcc_3C_Ref;

typedef VectorValImageAcc< Float, 1 > F32VectorValImageAcc_1C;
typedef ObjRef< F32VectorValImageAcc_1C > F32VectorValImageAcc_1C_Ref;

typedef VectorValImageAcc< Int32, 1 > S32VectorValImageAcc_1C;
typedef ObjRef< S32VectorValImageAcc_1C > S32VectorValImageAcc_1C_Ref;






