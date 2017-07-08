#pragma once

#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>

#define HCV_CALL( Func )                                             \
{                                                                   \
    Func;                                                           \
    HCV_CHECK();                                                     \
}

#define HCV_CHECK()                                                  \
{                                                                   \
    if( cvGetErrStatus() < 0 )                                      \
        HCV_ERROR();      \
}


#define HCV_ERROR()                                             \
{                                                                   \
    Ncpp_ASSERT(false);                                          \
    cvError( -1, "Ncv", "", __FILE__, __LINE__ );        \
}
	//goto Error;											\
