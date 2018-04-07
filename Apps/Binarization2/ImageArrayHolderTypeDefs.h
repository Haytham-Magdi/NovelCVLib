

#include <NovelCVLib\OpenCV\ImageArrayHolder.h>



typedef ImageArrayHolder< Float, F32ColorVal, 3 > F32ImageArrayHolder3C;
typedef ImageArrayHolderRef< Float, F32ColorVal, 3 > F32ImageArrayHolder3C_Ref;

typedef ImageArrayHolder< Float, float, 1 > F32ImageArrayHolder1C;
typedef ImageArrayHolderRef< Float, float, 1 > F32ImageArrayHolder1C_Ref;

typedef ImageArrayHolder< Int32, int, 1 > S32ImageArrayHolder1C;
typedef ImageArrayHolderRef< Int32, int, 1 > S32ImageArrayHolder1C_Ref;


template<class T_ImgElm, int const V_NofChannels>
using VectorValImageArrayHolder = ImageArrayHolder<T_ImgElm, VectorVal<T_ImgElm, V_NofChannels>, V_NofChannels>;

template<class T_ImgElm, int const V_NofChannels>
using VectorValImageArrayHolderRef = ObjRef<ImageArrayHolder<T_ImgElm, VectorVal<T_ImgElm, V_NofChannels>, V_NofChannels>>;


///////////////////////////////////////////////

typedef VectorValImageArrayHolder< Float, 4 > F32VectorValImageArrayHolder_4C;
typedef ObjRef< F32VectorValImageArrayHolder_4C > F32VectorValImageArrayHolder_4C_Ref;

typedef VectorValImageArrayHolder< Float, 3 > F32VectorValImageArrayHolder_3C;
typedef ObjRef< F32VectorValImageArrayHolder_3C > F32VectorValImageArrayHolder_3C_Ref;

typedef VectorValImageArrayHolder< Float, 1 > F32VectorValImageArrayHolder_1C;
typedef ObjRef< F32VectorValImageArrayHolder_1C > F32VectorValImageArrayHolder_1C_Ref;

typedef VectorValImageArrayHolder< Int32, 1 > S32VectorValImageArrayHolder_1C;
typedef ObjRef< S32VectorValImageArrayHolder_1C > S32VectorValImageArrayHolder_1C_Ref;







