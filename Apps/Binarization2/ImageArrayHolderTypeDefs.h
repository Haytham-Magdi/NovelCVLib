

#include <NovelCVLib\OpenCV\ImageArrayHolder.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <NovelCVLib\Common\BasicTypes.h>
#include <NovelCVLib\Ncv\VectorVal.h>



typedef Ncv::ImageArrayHolder< Ncpp::Float, Ncv::F32ColorVal, 3 > F32ImageArrayHolder3C;
typedef Ncv::ImageArrayHolderRef< Ncpp::Float, Ncv::F32ColorVal, 3 > F32ImageArrayHolder3C_Ref;

typedef Ncv::ImageArrayHolder< Ncpp::Float, float, 1 > F32ImageArrayHolder1C;
typedef Ncv::ImageArrayHolderRef< Ncpp::Float, float, 1 > F32ImageArrayHolder1C_Ref;

typedef Ncv::ImageArrayHolder< Ncpp::Int32, int, 1 > S32ImageArrayHolder1C;
typedef Ncv::ImageArrayHolderRef< Ncpp::Int32, int, 1 > S32ImageArrayHolder1C_Ref;


template<class T_ImgElm, int const V_NofChannels>
using VectorValImageArrayHolder = Ncv::ImageArrayHolder<T_ImgElm, VectorVal<T_ImgElm, V_NofChannels>, V_NofChannels>;

template<class T_ImgElm, int const V_NofChannels>
using VectorValImageArrayHolderRef = Ncpp::ObjRef<Ncv::ImageArrayHolder<T_ImgElm, VectorVal<T_ImgElm, V_NofChannels>, V_NofChannels>>;


///////////////////////////////////////////////

typedef VectorValImageArrayHolder< Ncpp::Float, 4 > F32VectorValImageArrayHolder_4C;
typedef Ncpp::ObjRef< F32VectorValImageArrayHolder_4C > F32VectorValImageArrayHolder_4C_Ref;

typedef VectorValImageArrayHolder< Ncpp::Float, 3 > F32VectorValImageArrayHolder_3C;
typedef Ncpp::ObjRef< F32VectorValImageArrayHolder_3C > F32VectorValImageArrayHolder_3C_Ref;

typedef VectorValImageArrayHolder< Ncpp::Float, 1 > F32VectorValImageArrayHolder_1C;
typedef Ncpp::ObjRef< F32VectorValImageArrayHolder_1C > F32VectorValImageArrayHolder_1C_Ref;

typedef VectorValImageArrayHolder< Ncpp::Int32, 1 > S32VectorValImageArrayHolder_1C;
typedef Ncpp::ObjRef< S32VectorValImageArrayHolder_1C > S32VectorValImageArrayHolder_1C_Ref;







