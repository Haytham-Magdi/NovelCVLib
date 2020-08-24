#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>

#include <NovelCVLib\Ncpp\Math\mathLib.h>

#include <NovelCVLib\OpenCV\Types.h>


//#include <NovelCVLib\Ncpp\Math\funcs.h>

//#include <NovelCVLib\Ncv\Signal1DViewer.h>


namespace Ncv
{
	using namespace Ncpp;
	using namespace Ncpp::Math;


	typedef struct _U8ColorVal
	{
		struct _U8ColorVal( ) {}

		struct _U8ColorVal( Uint8 a_val0, Uint8 a_val1, Uint8 a_val2 )
		{
			val0 = a_val0;
			val1 = a_val1;
			val2 = a_val2;
		}

		void AssignVal( float a_val0, float a_val1, float a_val2 )
		{
			this->val0 = (Uint8)a_val0;
			this->val1 = (Uint8)a_val1;
			this->val2 = (Uint8)a_val2;
		}

		Uint8 val0;
		Uint8 val1;
		Uint8 val2;

	}U8ColorVal;

	typedef struct _S16ColorVal
	{
		Int16 val0;
		Int16 val1;
		Int16 val2;
	}S16ColorVal;
	
	typedef struct _S32ColorVal
	{
		Int32 val0;
		Int32 val1;
		Int32 val2;

		static struct _S32ColorVal Add( 
			struct _S32ColorVal & a_rArg1, 
			struct _S32ColorVal & a_rArg2)
		{
			struct _S32ColorVal ret;

			ret.val0 = a_rArg1.val0 + a_rArg2.val0;
			ret.val1 = a_rArg1.val1 + a_rArg2.val1;
			ret.val2 = a_rArg1.val2 + a_rArg2.val2;

			return ret;
		}

		struct _S32ColorVal MultBy( int a_num )
		{
			struct _S32ColorVal ret;

			ret.val0 = this->val0 * a_num;
			ret.val1 = this->val1 * a_num;
			ret.val2 = this->val2 * a_num;

			return ret;
		}

		struct _S32ColorVal DividBy( int a_num )
		{
			struct _S32ColorVal ret;

			ret.val0 = this->val0 / a_num;
			ret.val1 = this->val1 / a_num;
			ret.val2 = this->val2 / a_num;

			return ret;
		}

	}S32ColorVal;


	class F32ColorVal
	{
	public:

		float val0;
		float val1;
		float val2;

		F32ColorVal()
		{
		}

		F32ColorVal(const float a_val0, const float a_val1, const float a_val2)
		{
			val0 = a_val0;
			val1 = a_val1;
			val2 = a_val2;
		}

		U8ColorVal ToU8()
		{
			U8ColorVal ret( val0, val1, val2 );

			return ret;
		}

		void CopyU8( U8ColorVal & a_src )
		{
			this->AssignVal( a_src.val0, a_src.val1, a_src.val2 );
		}


/*
		typedef F32ColorVal()
		{
		}

		typedef F32ColorVal(F32ColorVal & a_src)
		{
			*this = a_src;
		}

		typedef F32ColorVal(float a_val0, float a_val1, float a_val2)
		{
			val0 = a_val0;
			val1 = a_val1;
			val2 = a_val2;
		}
*/

		static F32ColorVal Add( 
			F32ColorVal & a_rArg1, 
			F32ColorVal & a_rArg2)
		{
			F32ColorVal ret;

			ret.val0 = a_rArg1.val0 + a_rArg2.val0;
			ret.val1 = a_rArg1.val1 + a_rArg2.val1;
			ret.val2 = a_rArg1.val2 + a_rArg2.val2;

			return ret;
		}

		void IncBy( F32ColorVal & a_rArg)
		{
			this->val0 += a_rArg.val0;
			this->val1 += a_rArg.val1;
			this->val2 += a_rArg.val2;
		}

		void DecBy( F32ColorVal & a_rArg)
		{
			this->val0 -= a_rArg.val0;
			this->val1 -= a_rArg.val1;
			this->val2 -= a_rArg.val2;
		}

		void IncByNum( float a_num )
		{
			this->val0 += a_num;
			this->val1 += a_num;
			this->val2 += a_num;
		}

		static F32ColorVal Sub( 
			F32ColorVal & a_rArg1, 
			F32ColorVal & a_rArg2)
		{
			F32ColorVal ret;

			ret.val0 = a_rArg1.val0 - a_rArg2.val0;
			ret.val1 = a_rArg1.val1 - a_rArg2.val1;
			ret.val2 = a_rArg1.val2 - a_rArg2.val2;

			return ret;
		}

		F32ColorVal MultBy( const float a_num )
		{
			F32ColorVal ret;

			ret.val0 = this->val0 * a_num;
			ret.val1 = this->val1 * a_num;
			ret.val2 = this->val2 * a_num;

			return ret;
		}

		F32ColorVal DividBy( const float a_num )
		{
			return MultBy( 1 / a_num );
		}

		void MultSelfBy( const float a_num )
		{
			this->val0 *= a_num;
			this->val1 *= a_num;
			this->val2 *= a_num;
		}

		void AssignVal( F32ColorVal & a_src )
		{
			AssignVal( a_src.val0, a_src.val1, a_src.val2 );
		}

		void AssignVal( float a_val0, float a_val1, float a_val2 )
		{
			this->val0 = a_val0;
			this->val1 = a_val1;
			this->val2 = a_val2;
		}

		void DividSelfBy( const float a_num )
		{
			MultSelfBy( 1 / a_num );
		}

		void MultSelfBy( F32ColorVal & a_arg )
		{
			this->val0 *= a_arg.val0;
			this->val1 *= a_arg.val1;
			this->val2 *= a_arg.val2;
		}

		

		float CalcMagSqr()
		{
			float ret = Sqr(this->val0) + 
				Sqr(this->val1) + Sqr(this->val2);

			return ret;			
		}

		float CalcMag()
		{
			return sqrt(this->CalcMagSqr());
		}

		void MultSelfByIntensityFactors()
		{
/*			this->val0 *= 0.51;
			this->val1 *= 1.44;
			this->val2 *= 1.048;*/

			MultSelfBy( *GetIntesityFactorsPtr() );
		}

		F32ColorVal Clone()
		{
			F32ColorVal ret = *this;

			return ret;
		}

		F32ColorVal IncLessToNum( float a_num )
		{
			//F32ColorVal ret = *this;
			F32ColorVal ret;

			float max_012 = this->val0;

			if( this->val1 > max_012 )
				max_012 = this->val1;

			if( this->val2 > max_012 )
				max_012 = this->val2;

			float numDif = a_num - max_012;

			if( numDif > 0 )
			{
				ret.val0 = this->val0 + numDif;
				ret.val1 = this->val1 + numDif;
				ret.val2 = this->val2 + numDif;
			}
			else
			{
				ret = *this;
			}

			return ret;
		}

		void ZeroSelfUnder( float a_thrVal )
		{
			if( this->val0 < a_thrVal )
				this->val0 = 0;

			if( this->val1 < a_thrVal )
				this->val1 = 0;

			if( this->val2 < a_thrVal )
				this->val2 = 0;
		}

		static F32ColorVal FromNum(const float a_num)
		{
			F32ColorVal ret(a_num, a_num, a_num);

			return ret;
		}

		F32ColorVal GetUnitVect()
		{
			F32ColorVal ret = *this;

			ret = ret.IncLessToNum( 40 );
			ret.DividSelfBy( ret.CalcMag() );

			return ret;
		}


/*
		void Copy( F32ColorVal & a_arg )
		{
			this->val0 = a_arg.val0;
			this->val1 = a_arg.val1;
			this->val2 = a_arg.val2;
		}
*/

		protected:
			static F32ColorVal * GetIntesityFactorsPtr()
			{
				return &m_intesityFactors;
			}
			static F32ColorVal m_intesityFactors;



	};


///////////////////////////////////////////////////////////////////////////////////////



	class CovMat
	{
	public:

		//float val0;
		//float val1;
		//float val2;

		float b_b;
		float g_g;
		float r_r;

		float b_g;
		float b_r;

		float g_r;

		void Reset()
		{
			b_b = 0;
			g_g = 0;
			r_r = 0;

			b_g = 0;
			b_r = 0;

			g_r = 0;
		}


		void AddColorVal( F32ColorVal & a_color )
		{
			b_b += a_color.val0 * a_color.val0;
			g_g += a_color.val1 * a_color.val1;
			r_r += a_color.val2 * a_color.val2;

			b_g += a_color.val0 * a_color.val1;
			b_r += a_color.val0 * a_color.val2;

			g_r += a_color.val1 * a_color.val2;
		}


		void SetByColor( F32ColorVal & a_color )
		{
			b_b = a_color.val0 * a_color.val0;
			g_g = a_color.val1 * a_color.val1;
			r_r = a_color.val2 * a_color.val2;

			b_g = a_color.val0 * a_color.val1;
			b_r = a_color.val0 * a_color.val2;

			g_r = a_color.val1 * a_color.val2;
		}


		void CalcPureMat( F32ColorVal & a_mean, CovMat * a_pOutMat )
		{
			a_pOutMat->b_b = b_b - a_mean.val0 * a_mean.val0;
			a_pOutMat->g_g = g_g - a_mean.val1 * a_mean.val1;
			a_pOutMat->r_r = r_r - a_mean.val2 * a_mean.val2;

			a_pOutMat->b_g = b_g - a_mean.val0 * a_mean.val1;
			a_pOutMat->b_r = b_r - a_mean.val0 * a_mean.val2;

			a_pOutMat->g_r = g_r - a_mean.val1 * a_mean.val2;
		}

/*
		typedef CovMat()
		{
		}

		typedef CovMat(CovMat & a_src)
		{
			*this = a_src;
		}

		typedef CovMat(float a_val0, float a_val1, float a_val2)
		{
			val0 = a_val0;
			val1 = a_val1;
			val2 = a_val2;
		}
*/

		static void Add( CovMat & a_rArg1, CovMat & a_rArg2,
			CovMat * a_pOutMat )
		{
			a_pOutMat->b_b = a_rArg1.b_b + a_rArg2.b_b;
			a_pOutMat->g_g = a_rArg1.g_g + a_rArg2.g_g;
			a_pOutMat->r_r = a_rArg1.r_r + a_rArg2.r_r;

			a_pOutMat->b_g = a_rArg1.b_g + a_rArg2.b_g;
			a_pOutMat->b_r = a_rArg1.b_r + a_rArg2.b_r;

			a_pOutMat->g_r = a_rArg1.g_r + a_rArg2.g_r;
		}


		static CovMat Add( CovMat & a_rArg1, CovMat & a_rArg2 )
		{
			CovMat ret;

			Add( a_rArg1, a_rArg2, & ret );

			return ret;
		}


		static void Sub( CovMat & a_rArg1, CovMat & a_rArg2,
			CovMat * a_pOutMat )
		{
			a_pOutMat->b_b = a_rArg1.b_b - a_rArg2.b_b;
			a_pOutMat->g_g = a_rArg1.g_g - a_rArg2.g_g;
			a_pOutMat->r_r = a_rArg1.r_r - a_rArg2.r_r;

			a_pOutMat->b_g = a_rArg1.b_g - a_rArg2.b_g;
			a_pOutMat->b_r = a_rArg1.b_r - a_rArg2.b_r;

			a_pOutMat->g_r = a_rArg1.g_r - a_rArg2.g_r;
		}


		static CovMat Sub( CovMat & a_rArg1, CovMat & a_rArg2 )
		{
			CovMat ret;

			Sub( a_rArg1, a_rArg2, & ret );

			return ret;
		}



		void IncBy( CovMat & a_rArg)
		{
			b_b += a_rArg.b_b;
			g_g += a_rArg.g_g;
			r_r += a_rArg.r_r;

			b_g += a_rArg.b_g;
			b_r += a_rArg.b_r;

			g_r += a_rArg.g_r;
		}

		void DecBy( CovMat & a_rArg)
		{
			b_b -= a_rArg.b_b;
			g_g -= a_rArg.g_g;
			r_r -= a_rArg.r_r;

			b_g -= a_rArg.b_g;
			b_r -= a_rArg.b_r;

			g_r -= a_rArg.g_r;
		}


		CovMat MultBy( const float a_num )
		{
			CovMat ret;

			ret.b_b *= a_num;
			ret.g_g *= a_num;
			ret.r_r *= a_num;

			ret.b_g *= a_num;
			ret.b_r *= a_num;

			ret.g_r *= a_num;

			return ret;
		}

		void MultSelfBy( const float a_num )
		{
			b_b *= a_num;
			g_g *= a_num;
			r_r *= a_num;

			b_g *= a_num;
			b_r *= a_num;

			g_r *= a_num;
		}




		CovMat DividBy( const float a_num )
		{
			CovMat ret;

			ret.b_b /= a_num;
			ret.g_g /= a_num;
			ret.r_r /= a_num;

			ret.b_g /= a_num;
			ret.b_r /= a_num;

			ret.g_r /= a_num;

			return ret;
		}

		void DividSelfBy( const float a_num )
		{
			b_b /= a_num;
			g_g /= a_num;
			r_r /= a_num;

			b_g /= a_num;
			b_r /= a_num;

			g_r /= a_num;
		}


		void AssignVal( CovMat & a_src )
		{
			*this = a_src;

			//AssignVal( a_src.val0, a_src.val1, a_src.val2 );
		}

		void AssignVal( float a_b_b, float a_g_g, float a_r_r,
			float a_b_g, float a_b_r, float a_g_r )
		{
			b_b = a_b_b;
			g_g = a_g_g;
			r_r = a_r_r;

			b_g = a_b_g;
			b_r = a_b_r;

			g_r = a_g_r;
		}


		float CalcMagSqr()
		{
			float ret = Sqr( b_b ) + Sqr( g_g ) + Sqr( r_r ) + 
				2 * Sqr( b_g ) + 2 * Sqr( b_r ) + 2 * Sqr( g_r );

			ret = sqrt( ret );

			//ret = sqrt( ret ) * 2;

			return ret;			
		}


		float CalcMag()
		{
			//return Sqr( this->CalcMag() );
			return sqrt( this->CalcMagSqr() );
		}

		CovMat Clone()
		{
			CovMat ret = *this;

			return ret;
		}
		

		static CovMat FromNum(const float a_num)
		{
			CovMat ret;

			ret.AssignVal( a_num, a_num, a_num, 
				a_num, a_num, a_num );

			return ret;
		}


		CovMat GetUnitVect()
		{
			CovMat ret = *this;

			ret.DividSelfBy( ret.CalcMag() );

			return ret;
		}

	};


///////////////////////////////////////////////////////////////////////////////////////





	class F32Point
	{
	public:

		float x;
		float y;

		F32Point()
		{
		}

		F32Point( const float a_x, const float a_y )
		{
			x = a_x;
			y = a_y;
		}

		F32Point GetUnitVect()
		{
			F32Point ret = this->Clone();

			ret.DividSelfBy( ret.CalcMag() );

			return ret;
		}

		static F32Point Add( 
			F32Point & a_rArg1, 
			F32Point & a_rArg2)
		{
			F32Point ret;

			ret.x = a_rArg1.x + a_rArg2.x;
			ret.y = a_rArg1.y + a_rArg2.y;
			
			return ret;
		}

		static bool Compare( 
			F32Point & a_rArg1, 
			F32Point & a_rArg2)
		{
			return ( a_rArg1.x == a_rArg2.x ) &&
				( a_rArg1.y == a_rArg2.y );
		}

		void IncBy( F32Point & a_rArg)
		{
			this->x += a_rArg.x;
			this->y += a_rArg.y;
		}

		void IncBy( const float a_num )
		{
			this->x += a_num;
			this->y += a_num;
		}

		void IncBy( const float a_numX, const float a_numY )
		{
			this->x += a_numX;
			this->y += a_numY;
		}

		void DecBy( F32Point & a_rArg)
		{
			this->x -= a_rArg.x;
			this->y -= a_rArg.y;
		}

		static F32Point Sub( 
			F32Point & a_rArg1, 
			F32Point & a_rArg2)
		{
			F32Point ret;

			ret.x = a_rArg1.x - a_rArg2.x;
			ret.y = a_rArg1.y - a_rArg2.y;

			return ret;
		}

		F32Point MultBy( const float a_num )
		{
			F32Point ret;

			ret.x = this->x * a_num;
			ret.y = this->y * a_num;

			return ret;
		}

		F32Point DividBy( const float a_num )
		{
			return MultBy( 1 / a_num );
		}

		void MultSelfBy( const float a_num )
		{
			this->x *= a_num;
			this->y *= a_num;
		}

		void DividSelfBy( const float a_num )
		{
			MultSelfBy( 1 / a_num );
		}

		void MultSelfBy( F32Point & a_arg )
		{
			this->x *= a_arg.x;
			this->y *= a_arg.y;
		}

		

		float CalcMagSqr()
		{
			float ret = Sqr(this->x) + Sqr(this->y);

			return ret;			
		}

		float CalcMag()
		{
			return sqrt(this->CalcMagSqr());
		}

/*		void MultSelfByIntensityFactors()
		{
			MultSelfBy( *GetIntesityFactorsPtr() );
		}*/

		F32Point Clone()
		{
			F32Point ret = *this;

			return ret;
		}

		F32Point Round()
		{
			F32Point ret;

			if( this->x > 0 )
				ret.x = (int) ( this->x + 0.55555555555 );
			else
				ret.x = (int) ( this->x - 0.55555555555 );

			if( this->y > 0 )
				ret.y = (int) ( this->y + 0.55555555555 );
			else
				ret.y = (int) ( this->y - 0.55555555555 );

			return ret;
		}

		static F32Point CreateFromIndex( int a_nIndex, cv::Size & a_siz )
		{
			F32Point retPnt;

			retPnt.x = a_nIndex % a_siz.width;
			retPnt.y = a_nIndex / a_siz.width;

			return retPnt;
		}

		protected:
/*			static F32Point * GetIntesityFactorsPtr()
			{
				return &m_intesityFactors;
			}
			static F32Point m_intesityFactors;*/


	//}F32Point;
	};

 


	template<class T>
	void FillBorder(CHANNEL_REF(T) a_chnl, T a_val, int a_nThickness)		
	{
		FillBorder(a_chnl, a_val,
			a_nThickness, a_nThickness, a_nThickness, a_nThickness);
	}

	template<class T>
	void FillBorder(CHANNEL_REF(T) a_chnl, T a_val,
		int a_nThickLeft, int a_nThickRight, int a_nThickTop, int a_nThickBotom)
	{
		// HTODO : Validate size, and get ROI

		int x, y;

		for(y=0; y<a_nThickTop; y++)
			for(x=0; x<a_chnl->GetWidth(); x++)
				a_chnl->SetAt(x, y, a_val);

		//for(y=a_chnl->GetHeight()-1-a_nThickBotom; y<a_chnl->GetHeight(); y++)
		for(y=a_chnl->GetHeight() - a_nThickBotom; y<a_chnl->GetHeight(); y++)
			for(x=0; x<a_chnl->GetWidth(); x++)
				a_chnl->SetAt(x, y, a_val);

		for(x=0; x<a_nThickLeft; x++)
			for(y=0; y<a_chnl->GetHeight(); y++)
				a_chnl->SetAt(x, y, a_val);

		//for(x=a_chnl->GetWidth()-1-a_nThickRight; x<a_chnl->GetWidth(); x++)
		for(x=a_chnl->GetWidth() - a_nThickRight; x<a_chnl->GetWidth(); x++)
			for(y=0; y<a_chnl->GetHeight(); y++)
				a_chnl->SetAt(x, y, a_val);		
	}

	void CvtRgbToHsl0(U8ImageRef a_src, U8ImageRef a_dst);
	void CvtRgbToHsl(U8ImageRef a_src, U8ImageRef a_dst);
	void Convolve2D( const cv::Mat* a, cv::Mat* b, const cv::Mat* kernel, cv::Point anchor );
	void GetMaxImg(S16ImageRef a_src1, S16ImageRef a_src2, S16ImageRef a_dst);
	void CalcColorSblXY(S16ImageRef a_srcX, S16ImageRef a_srcY, S16ImageRef a_dst);
	void GetColorMidean(S16ImageRef a_src, S16ImageRef a_dst);
	S16ImageRef GenColorMideanImg( S16ImageRef a_src);
	S16ImageRef GenWeightedColorMideanImg( 
		S16ImageRef a_src, S16ImageRef a_srcGrad, int a_nAprSiz );
	U8ImageRef GenColorDsp(U8ImageRef a_src);
	U8ImageRef GenScaledImage(U8ImageRef a_src);
	S16ImageRef GenDownSampledImage(S16ImageRef a_src, int a_nStep);
	S16ImageRef GenDownSampledImage(S16ImageRef a_src, int a_nStepX, int a_nStepY);
	S16ImageRef GenUpSampledImage(S16ImageRef a_src, int a_nStep);
	S16ImageRef GenUpSampledImage(S16ImageRef a_src, int a_nStepX, int a_nStepY);
	F32ImageRef GenUpSampledImage(F32ImageRef a_src, int a_nStep);
	F32ImageRef GenUpSampledImage(F32ImageRef a_src, int a_nStepX, int a_nStepY);
	F32ImageRef GenImageWithGrid(F32ImageRef a_src, int a_nStepX, int a_nStepY);
	S16ImageRef GenColorSobelGradImage(S16ImageRef a_src, int a_nAprSiz);
	F32ImageRef GenF32FromS16Image(S16ImageRef a_src);
	F32ImageRef GenF32FromU8Image(U8ImageRef a_src);
	S16ImageRef GenS16FromF32Image(F32ImageRef a_src);
	S16ImageRef GenS16FromU8Image(U8ImageRef a_src);
	U8ImageRef GenU8FromF32Image(F32ImageRef a_src);
	U8ImageRef GenU8FromS16Image(S16ImageRef a_src);
	S16ImageRef GenScaledS16FromS32Image(S32ImageRef a_src);
	void ShowImage(cv::Mat & a_mat, const char * a_sWndName);
	S16ImageRef GenMinimaImage(S16ImageRef a_src);
	S16ImageRef GenMaximaImage(S16ImageRef a_src);
	S32ImageRef GenNeighbourhoodImage(S16ImageRef a_src);
	U8ImageRef GenNegativeImage(U8ImageRef a_src);
	S16ImageRef GenPyrUpImg(S16ImageRef a_src, int a_nIterCnt = 1);
	S16ImageRef GenPyrDownImg(S16ImageRef a_src, int a_nIterCnt = 1);
	F32ImageRef GenPyrUpImg(F32ImageRef a_src, int a_nIterCnt = 1);
	F32ImageRef GenPyrDownImg(F32ImageRef a_src, int a_nIterCnt = 1);


	S16ImageRef GenHDensityImg(S16ImageRef a_hdifImg);

	std::vector<cv::Point> GenDataPoints(S16ImageRef a_src, const int nDataVal = 0);

	S16ImageRef GenDataImage(std::vector<cv::Point> a_data, cv::Size a_imgSiz,
		int nDataVal = 0, const int nBkgVal = 255);

	S16ImageRef GenThresholdImg(S16ImageRef a_src, int a_nVal);
	F32ImageRef GenThresholdImg(F32ImageRef a_src, float a_val);

	F32ImageRef GenClippedPixValImg( F32ImageRef a_src, 
		float a_maxVal, float a_minVal );

	void DrawPoints(cv::Point * a_data, int a_nofPoints, 
		S16ImageRef a_img, cv::Scalar a_color);

	void DrawPoints(std::vector<cv::Point> a_data, S16ImageRef a_img, cv::Scalar a_color);

	class ClusteringMgr;
	void DrawPoints(S16ImageRef a_img, cv::Point * a_points, 
		//int a_nofPoints, int * a_ids, U8ColorVal * a_colors);
		int a_nofPoints, ClusteringMgr & a_rCm, U8ColorVal * a_colors);

	

	void DrawPoints(S16ImageRef a_img, std::vector<cv::Point> * a_pPointArr,
		std::vector<int> * a_pPointIDs, std::vector<U8ColorVal> * a_pColorArr);

	U8ColorVal u8ColorVal(Uint8 a_val0, Uint8 a_val1, Uint8 a_val2);

	S16ImageRef GenFastAvgHImg(S16ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenFastAvgVImg(S16ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenFastAvgImg(S16ImageRef a_src, int a_nAprSiz);

	F32ImageRef GenMagSqrImg(F32ImageRef a_src);
	F32ImageRef GenMagImg(F32ImageRef a_src);

	F32ImageRef GenFastAvgHImg(F32ImageRef a_src, int a_nAprSiz);
	F32ImageRef GenFastAvgVImg(F32ImageRef a_src, int a_nAprSiz);
	F32ImageRef GenFastAvgImg(F32ImageRef a_src, int a_nAprSizH, int a_nAprSizV = -1);

	F32ImageRef Gen4DirEdgeImg(F32ImageRef a_src);
	F32ImageRef GenMagImgF32(F32ImageRef a_src);
	S16ImageRef GenDifMagImg(S16ImageRef a_src);
	S16ImageRef GenCenterPixImg( cv::Size a_siz, int a_nofChannels );
	S16ImageRef GenBinImposedImg( S16ImageRef a_src, S16ImageRef a_binImg );
	void NormalizeEdgeDirImages( F32ImageRef a_gradMagX, F32ImageRef a_gradMagY,
		float a_normVal = 254);
	S16ImageRef GenColorEdgeDirImg( S16ImageRef a_gradMagX, 
		S16ImageRef a_gradMagY,	S16ImageRef a_maskImg );
	S16ImageRef GenWeightImg5( F32ImageRef a_grad1, int a_nDist);
	S16ImageRef GenWeightImg4( S16ImageRef a_grad1, int a_nDist);
	F32ImageRef GenWeightImg3( S16ImageRef a_src,  S16ImageRef a_grad1, 
		 S16ImageRef a_grad2, int a_nDist);
	F32ImageRef GenWeightImg2( S16ImageRef a_grad1, int a_nDist);
	F32ImageRef GenWeightImg( S16ImageRef a_grad1, S16ImageRef a_grad2 );
	S16ImageRef GenFlattenedImg(S16ImageRef a_src, F32ImageRef a_weightImg, int a_nAprSiz);	
	S16ImageRef GenTriChGrayImg( S16ImageRef a_src );
	F32ImageRef GenTriChGrayImg( F32ImageRef a_src );

	void ShowImage(U8ImageRef dsp, const char * a_sWndName);
	void ShowImage(S16ImageRef a_src, const char * a_sWndName);
	void ShowImage(F32ImageRef a_src, const char * a_sWndName);
	void SaveImage(S16ImageRef a_src, char * a_sFilePath);
	void SaveImage(F32ImageRef a_src, char * a_sFilePath);

	S16ImageRef GenMorphGradImg(S16ImageRef a_src, int a_nAprSiz);
	F32ImageRef GenMorphGradImg(F32ImageRef a_src, int a_nAprSiz);
	
	F32ImageRef GenMorphG1S2Img(F32ImageRef a_src, int a_nAprSiz);

	F32ImageRef GenCvErodeCircleImg(F32ImageRef a_src, int a_nAprSiz);
	F32ImageRef GenCvErodeImg(F32ImageRef a_src, int a_nAprSiz);
	F32ImageRef GenCvDilateCircleImg(F32ImageRef a_src, int a_nAprSiz);
	F32ImageRef GenCvDilateImg(F32ImageRef a_src, int a_nAprSiz);

	S16ImageRef GenCvErodeCircleImg(S16ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenCvErodeImg(S16ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenCvDilateCircleImg(S16ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenCvDilateImg(S16ImageRef a_src, int a_nAprSiz);

	F32ImageRef GenCvEqualizeHistImg(F32ImageRef a_src);

	F32ImageRef GenCvMedianImg(F32ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenCvMedianImg(S16ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenCvMedGausImg(S16ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenCvSmoothedImg(S16ImageRef a_src, int a_nAprSiz);
	F32ImageRef GenCvSmoothedImg(F32ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenCvLaplaceImg(S16ImageRef a_src, int a_nAprSiz);
	S16ImageRef GenCvSobelImg(S16ImageRef a_src, 
		int a_xorder, int a_yorder, int a_nAprSiz);


	S16ImageRef GenImageFromChannel(S16ImageRef a_src, int a_nChannel);
	F32ImageRef GenImageFromChannel( F32ImageRef a_src, int a_nChannel );
	F32ImageRef GenMultByNumImg( F32ImageRef a_src, const float a_num);

	void BalanceImageWithIntensityFactors( F32ImageRef a_img );

	F32ImageRef GenMultByColorImg( F32ImageRef a_src, F32ColorVal & a_rColor);

	F32ImageRef GenClipedImg( F32ImageRef a_src, F32Point & a_p1, F32Point & a_p2 );

	//F32ImageRef GenAvgColorsImg( F32ImageRef a_src, F32Point & a_p1, F32Point & a_p2 );
	
	bool AreEqualCvSizes(cv::Size & rSize1, cv::Size & rSize2);

	void ThrowNcvException();
	//void Try17May10( F32ImageRef a_img  );

	void DrawCircle( F32ImageRef a_img, F32Point & a_pt, U8ColorVal a_color, int a_nRadius = 3 );

	void BreakAtPoint( F32Point a_p1, F32Point a_refPt, float a_marg );

	S32ImageRef GenMinPosDepthImg( int a_nSizeX, int a_nSizeY );
	S32ImageRef GenMinPosDepthImg( cv::Size a_siz );

	void FillCenterOfMassArr( F32ImageRef a_src, int a_nAprSiz,
		FixedVector< F32Point > * a_pPointArr, F32ImageRef * a_pAvgImgRef = nullptr );

	void FillSlidePointArr( F32ImageRef a_src, int a_nAprSiz,
		FixedVector< F32Point > * a_pPointArr, F32ImageRef * a_pAvgImgRef = nullptr );	

	void FillClimbPointArr( F32ImageRef a_src, int a_nAprSiz,
		FixedVector< F32Point > * a_pPointArr, F32ImageRef * a_pAvgImgRef = nullptr );	

	void DrawValueSignals( FixedVector< float > & a_valArr, FixedVector< U8ColorVal > & a_colorArr );
	//void DrawValueSignals( FixedVector< float > & a_valArr, FixedVector< U8ColorVal > & a_colorArr,
		//Signal1DViewerRef a_sv1 );

	void FillIsEdgeRootArr( F32ImageRef a_src, FixedVector< bool > * a_pIsRootArr );
	void FillIsEdgePeakArr( F32ImageRef a_src, FixedVector< bool > * a_pIsRootArr );

	float CalcColorUnitDif( F32ColorVal & a_c1, F32ColorVal & a_c2 );

	F32Point GetPntOfIndex( int a_nIndex, cv::Size a_siz );


	F32ImageRef Gen_CovMatPure_Img( F32ImageRef a_src, int a_nAprSiz, 
		F32ImageRef * a_pMeanImg = nullptr, F32ColorVal * a_mean_Buf = nullptr );

	F32ImageRef Gen_CovMatNonPure_Img( F32ImageRef a_src, int a_nAprSiz );

	F32ImageRef Gen_CovMatMag_Img( F32ImageRef a_src );

}