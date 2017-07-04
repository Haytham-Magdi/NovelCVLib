#pragma once



//#ifdef Ncpp_DEBUG
#define Ncpp_ASSERT(C)  Ncpp::Debug::Assert((C))
//#else
//	#define Ncpp_ASSERT(C)  
//#endif





namespace Ncpp
{
	class Debug
	{
	public:
		static void Assert(int a_bCond)
		{
			if( ! a_bCond)
			{
				Break();

				//_CrtDbgBreak
				throw "Debug Assert Exp.";
			}
		}


		static void Break(void)
		{

		}

	};



}