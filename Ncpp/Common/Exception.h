#pragma once

//#include <Novel-Lib\Ncpp\Common\common.h>
#include <Novel-Lib\Ncpp\Common\Object.h>
#include <Novel-Lib\Ncpp\Common\ObjRef.h>

namespace Ncpp
{

	class Exception : FRM_Object
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