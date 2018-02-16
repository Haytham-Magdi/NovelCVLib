#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>
//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>

#include <NovelCVLib\Ncv\ImageOperations2.h>




namespace Ncv
{
	namespace ImageAccessorOperations
	{
		using namespace Ncpp;
		using namespace Ncv::ImageOperations2;


		////-------------------------------------------------------------------

		//F32ImageAccessor1C_Ref FillImage_Stripes_H(
		//	F32ImageAccessor3C_Ref a_imgAcc,
		//	F32ColorVal & a_val1, F32ColorVal & a_val2, int a_stripWidth)
		
		F32ImageAccessor3C_Ref GenFillImage_Stripes_H(
			F32ImageAccessor3C_Ref a_imgAcc,
			F32ColorVal & a_val1, F32ColorVal & a_val2, int a_stripWidth);

		F32ImageAccessor1C_Ref Create_F32ImageAccessor1C(CvSize & a_imgSize);
		F32ImageAccessor3C_Ref Create_F32ImageAccessor3C(CvSize & a_imgSize);

		//template<class T_ImgElm, class T_AccElm, int V_NofChannels>
		//F32ImageAccessor1C_Ref Create_F32ImageAccessor1C(ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) a_srcImgAcc)
		//{
		//	F32ImageRef img = F32Image::Create(a_srcImgAcc->GetSize(), 1);
		//	F32ImageAccessor1C_Ref ret = new F32ImageAccessor1C(img);

		//	return ret;
		//}



		//F32ImageAccessor1C_Ref FillImage_Stripes_H(
		//	F32ImageAccessor3C_Ref a_imgAcc,
		//	F32ColorVal & a_val1, F32ColorVal & a_val2, int a_stripWidth)
		//{
		//	F32ImageAccessor1C_Ref ret = nullptr;
		//		//F32ImageAccessor1C_Ref ret = F32ImageAccessor1C(
		//		//F32Image::Create(a_imgAcc->GetSrcImg()->GetSize(), 1));

		//	//F32ImageAccessor3C_Ref ret = a_imgAcc->CloneNew();
		//	//ret->SetSrcImg(a_imgAcc->GetSrcImg()->CloneNew());
		//	//ret->Lock();

		//	//FillImage_Stripes_H(a_imgAcc, a_val1, a_val2, a_stripWidth);

		//	return ret;
		//}

		////F32ImageAccessor3C_Ref imgAcc1 = new F32ImageAccessor3C(src);

		////F32ImageAccessor3C_Ref imgAcc0 = new F32ImageAccessor3C(src->CloneNew());
		////CopyImage(imgAcc0->GetMemAccessor(), imgAcc1->GetMemAccessor());


		////-------------------------------------------------------------------



	};
}