#pragma once

//#include <Lib\Novel\Ncpp\Common\common.h>
#include <Lib\Novel\Ncpp\Common\Object.h>
#include <Lib\Novel\Ncpp\Common\ObjRef.h>

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