#pragma once

//#include <NovelCVLib\Ncpp\Common\common.h>
#include <NovelCVLib\Common\Object.h>
#include <NovelCVLib\Common\ObjRef.h>

namespace Ncpp
{

	class Exception : public Ncpp::Object
	{
	public:

		static void Throw(ObjRef<Exception> a_exp)
		{
			throw "Exception";
		}

		static void Throw(char * a_sText)
		{
			throw "Exception";
		}

		static void ThrowNotImplemented()
		{
			Throw("Not Implemented!");
		}

	};

}