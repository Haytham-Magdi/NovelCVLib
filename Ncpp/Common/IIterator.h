#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>



#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncpp
{
	template<class T>
	class IIterator : public Ncpp::Object
	{
	public:
		virtual bool MoveNext() = 0;
		virtual T GetCurrent() = 0;
	};


	#define IIterator_REF(T) Ncpp::ObjRef< IIterator<T> >



}