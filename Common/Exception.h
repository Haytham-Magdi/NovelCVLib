#pragma once

//#include <NovelCVLib\Ncpp\Common\common.h>
#include <NovelCVLib\Ncpp\Common\Object.h>
#include <NovelCVLib\Ncpp\Common\ObjRef.h>

namespace Ncpp
{

	class Exception : public Ncpp::Object
	{
	public:

		static void Throw(ObjRef<Exception> a_exp)
		{
		}

		static void Throw(char * a_sText)
		{
		}

	};

}