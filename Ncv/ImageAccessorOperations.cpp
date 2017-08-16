#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>
//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>

#include <NovelCVLib\Ncv\Image_Operations.h>
#include <NovelCVLib\Ncv\ImageAccessorOperations.h>


namespace Ncv
{
	namespace ImageAccessorOperations
	{
		using namespace Ncpp;
		using namespace Ncv::Image_Operations;


		////-------------------------------------------------------------------

		//F32ImageAccessor1C_Ref FillImage_Stripes_H(
		//	F32ImageAccessor3C_Ref a_imgAcc,
		//	F32ColorVal & a_val1, F32ColorVal & a_val2, int a_stripWidth)

		F32ImageAccessor3C_Ref GenFillImage_Stripes_H(F32ImageAccessor3C_Ref a_imgAcc,
			F32ColorVal & a_val1, F32ColorVal & a_val2, int a_stripWidth)
		{
			//F32ImageAccessor1C_Ref ret = nullptr;

			//F32ImageAccessor1C_Ref ret =
			F32ImageAccessor3C_Ref ret =
				//new F32ImageAccessor1C(a_imgAcc->GetSrcImg()->CloneNew_WithChannels(1));
				//new F32ImageAccessor3C(a_imgAcc->GetSrcImg()->CloneNew());
				new F32ImageAccessor3C(a_imgAcc->GetSrcImg()->Clone());
			//new F32ImageAccessor1C(a_imgAcc->GetSrcImg()->CloneNew());

			//new F32ImageAccessor1C(a_imgAcc->GetSrcImg()->Clone());

			auto aut1 = ret->GetMemAccessor();

			FillImage_Stripes_H<F32ColorVal>(aut1, a_val1, a_val2, a_stripWidth);


			//FillImage_Stripes_H(a_imgAcc, a_val1, a_val2, a_stripWidth);
			////FillImage_Stripes_H(ret->GetMemAccessor(), a_val1, a_val2, a_stripWidth);

			//CalcMagSqrImage(a_imgAcc->GetMemAccessor(), ret->GetMemAccessor());

			return ret;
		}

		F32ImageAccessor1C_Ref Create_F32ImageAccessor1C(CvSize & a_imgSize)
		{
			F32ImageRef img = F32Image::Create(a_imgSize, 1);
			F32ImageAccessor1C_Ref ret = new F32ImageAccessor1C(img);

			return ret;
		}

		F32ImageAccessor3C_Ref Create_F32ImageAccessor3C(CvSize & a_imgSize)
		{
			F32ImageRef img = F32Image::Create(a_imgSize, 3);
			F32ImageAccessor3C_Ref ret = new F32ImageAccessor3C(img);

			return ret;
		}




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