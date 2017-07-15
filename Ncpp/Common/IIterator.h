#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>



#include <NovelCVLib\Ncpp\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\Object.h>


namespace Ncpp
{
	template<class T>
	class IIterator : FRM_Object(IIterator<T>)
	{
	public:
		virtual bool MoveNext() = 0;
		virtual T GetCurrent() = 0;
	};


	#define IIterator_REF(T) Ncpp::ObjRef< IIterator<T> >



}