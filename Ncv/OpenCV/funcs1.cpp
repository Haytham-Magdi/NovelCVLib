#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\PixelTypes.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>
#include <vector>

#include <NovelCVLib\Ncv\OpenCV\funcs1.h>


namespace Ncv
{
	using namespace Ncpp;

	F32ColorVal F32ColorVal::m_intesityFactors = { 0.51, 1.44, 1.048 };
	//F32ColorVal F32ColorVal::m_intesityFactors( 0.51, 1.44, 1.048 );

	void CvtRgbToHsl0(U8ImageRef a_src, U8ImageRef a_dst)
	{
		// HTODO : validate identical sizes

		U8ChannelRef bluCh = a_src->GetAt(0);
		U8ChannelRef grnCh = a_src->GetAt(1);
		U8ChannelRef redCh = a_src->GetAt(2);

		U8ChannelRef hueCh = a_dst->GetAt(0);
		U8ChannelRef satCh = a_dst->GetAt(1);
		U8ChannelRef lumCh = a_dst->GetAt(2);

		for (int y = 0; y<a_src->GetHeight(); y++)
		for (int x = 0; x<a_src->GetWidth(); x++)
		{
			Uint8 nRed = redCh->GetAt(x, y);
			Uint8 nGrn = grnCh->GetAt(x, y);
			Uint8 nBlu = bluCh->GetAt(x, y);

			Uint8 nMax = 0;
			if (nRed > nMax)
				nMax = nRed;
			if (nGrn > nMax)
				nMax = nGrn;
			if (nBlu > nMax)
				nMax = nBlu;

			Uint8 nMin = 255;
			if (nRed < nMin)
				nMin = nRed;
			if (nGrn < nMin)
				nMin = nGrn;
			if (nBlu < nMin)
				nMin = nBlu;


			int nHue;

			if (0 == (nMax - nMin))
				nHue = 0;
			else
			{
				if (nMax == nRed)
					nHue = 60 * (nGrn - nBlu) / (nMax - nMin);
				else if (nMax == nGrn)
					nHue = 2 * 60 + 60 * (nBlu - nRed) / (nMax - nMin);
				else	//	(nMax == nBlu)
					nHue = 4 * 60 + 60 * (nRed - nGrn) / (nMax - nMin);

				if (nHue < 0)
					nHue += 360;

				nHue = nHue * 256 / 360;
			}



			Uint8 nSat = (Uint8)((nMax - nMin) * 255 / nMax);
			//Uint8 nSat = (Uint8)((ULONG)(nMax-nMin)*255/nMax); 


			Uint8 nLum = (nMax + nMin) / 2;
			/*		Uint8 nLum;
			nTmp = (nMax + nMin) / 2;
			if(nTmp > 255)
			nLum = 255;
			else
			nLum = nTmp;*/


			hueCh->SetAt(x, y, nHue);
			satCh->SetAt(x, y, nSat);
			lumCh->SetAt(x, y, nLum);

		}
	}




	void CvtRgbToHsl(U8ImageRef a_src, U8ImageRef a_dst)
	{
		// HTODO : validate identical sizes

		U8ChannelRef bluCh = a_src->GetAt(0);
		U8ChannelRef grnCh = a_src->GetAt(1);
		U8ChannelRef redCh = a_src->GetAt(2);

		U8ChannelRef hueCh = a_dst->GetAt(0);
		U8ChannelRef satCh = a_dst->GetAt(1);
		U8ChannelRef lumCh = a_dst->GetAt(2);

		for (int y = 0; y < a_src->GetHeight(); y++)
		for (int x = 0; x < a_src->GetWidth(); x++)
		{
			Uint8 nRed = redCh->GetAt(x, y);
			Uint8 nGrn = grnCh->GetAt(x, y);
			Uint8 nBlu = bluCh->GetAt(x, y);

			Uint8 nHue;
			Uint8 nSat;
			Uint8 nVal;

			Hsv::GetHsvOfRgb(nRed, nGrn, nBlu, &nHue, &nSat, &nVal);

			hueCh->SetAt(x, y, nHue);
			satCh->SetAt(x, y, nSat);
			lumCh->SetAt(x, y, nVal);

		}
	}



	void Convolve2D(const CvMat* a, CvMat* b, const CvMat* kernel, CvPoint anchor)
	{
		ThrowNcvException();

		/*
				int i, j, k;
				int cn, ncols, a_step;
				int ker_size = kernel->rows*kernel->cols;
				int* offset = (int*)malloc( ker_size*sizeof(offset[0]));
				float* k_data = (float*)malloc( ker_size*sizeof(k_data[0]));
				int all_same = 1;
				float first = kernel->data.fl[0];
				uchar *a_data, *b_data;

				cn = CV_MAT_CN(a->type);
				ncols = b->cols*cn;
				a_step = a->step / CV_ELEM_SIZE(a->type & ~CV_MAT_CN_MASK);

				assert( a->cols == b->cols + kernel->cols - 1 &&
				a->rows == b->rows + kernel->rows - 1 && CV_ARE_TYPES_EQ( a, b ) );
				assert( CV_MAT_TYPE(kernel->type) == CV_32FC1 );
				assert( 0 <= anchor.x && anchor.x < kernel->cols &&
				0 <= anchor.y && anchor.y < kernel->rows );

				for( i = 0, k = 0; i < kernel->rows; i++ )
				for( j = 0; j < kernel->cols; j++ )
				{
				float f = ((float*)(kernel->data.ptr + kernel->step*i))[j];
				if( f )
				{
				k_data[k] = f;
				offset[k++] = (i - anchor.y)*a_step + (j - anchor.x)*cn;
				}
				if( f != first )
				all_same = 0;
				}

				ker_size = k;
				a_data = a->data.ptr + a->step*anchor.y + CV_ELEM_SIZE(a->type)*anchor.x;
				b_data = b->data.ptr;

				for( i = 0; i < b->rows; i++, a_data += a->step, b_data += b->step )
				{
				switch( CV_MAT_DEPTH(a->type) )
				{
				case CV_8U:
				for( j = 0; j < ncols; j++ )
				{
				double s = 0;
				int val;
				for( k = 0; k < ker_size; k++ )
				s += ((uchar*)a_data)[j+offset[k]]*k_data[k];
				val = cvRound(s);
				((uchar*)b_data)[j] = CV_CAST_8U(val);
				}
				break;
				case CV_8S:
				for( j = 0; j < ncols; j++ )
				{
				double s = 0;
				int val;
				for( k = 0; k < ker_size; k++ )
				s += ((char*)a_data)[j+offset[k]]*k_data[k];
				val = cvRound(s);
				((char*)b_data)[j] = CV_CAST_8S(val);
				}
				break;
				case CV_16U:
				for( j = 0; j < ncols; j++ )
				{
				double s = 0;
				int val;
				for( k = 0; k < ker_size; k++ )
				s += ((ushort*)a_data)[j+offset[k]]*k_data[k];
				val = cvRound(s);
				((ushort*)b_data)[j] = CV_CAST_16U(val);
				}
				break;
				case CV_16S:
				for( j = 0; j < ncols; j++ )
				{
				double s = 0;
				int val;
				for( k = 0; k < ker_size; k++ )
				s += ((short*)a_data)[j+offset[k]]*k_data[k];
				val = cvRound(s);
				((short*)b_data)[j] = CV_CAST_16S(val);
				}
				break;
				case CV_32S:
				for( j = 0; j < ncols; j++ )
				{
				double s = 0;
				for( k = 0; k < ker_size; k++ )
				s += ((int*)a_data)[j+offset[k]]*k_data[k];
				((int*)b_data)[j] = cvRound(s);
				}
				break;
				case CV_32F:
				if( !all_same )
				{
				for( j = 0; j < ncols; j++ )
				{
				double s = 0;
				for( k = 0; k < ker_size; k++ )
				s += (double)((float*)a_data)[j+offset[k]]*k_data[k];
				((float*)b_data)[j] = (float)s;
				}
				}
				else
				{
				// special branch to speedup feature selection and blur tests
				for( j = 0; j < ncols; j++ )
				{
				double s = 0;
				for( k = 0; k < ker_size; k++ )
				s += (double)((float*)a_data)[j+offset[k]];
				((float*)b_data)[j] = (float)(s*first);
				}
				}
				break;
				case CV_64F:
				for( j = 0; j < ncols; j++ )
				{
				double s = 0;
				for( k = 0; k < ker_size; k++ )
				s += ((double*)a_data)[j+offset[k]]*k_data[k];
				((double*)b_data)[j] = (double)s;
				}
				break;
				default:
				assert(0);
				}
				}

				free( offset );
				free( k_data );
				*/

	}

	void GetMaxImg(S16ImageRef a_src1, S16ImageRef a_src2, S16ImageRef a_dst)
	{
		// HTODO : validate identical sizes

		for (int nChnl = 0; nChnl < a_src1->GetNofChannels(); nChnl++)
		{
			S16ChannelRef src1Ch = a_src1->GetAt(nChnl);
			S16ChannelRef src2Ch = a_src2->GetAt(nChnl);
			S16ChannelRef dstCh = a_dst->GetAt(nChnl);

			for (int y = 0; y < src1Ch->GetHeight(); y++)
			{
				for (int x = 0; x<src1Ch->GetWidth(); x++)
				{
					Int16 nSrc1 = src1Ch->GetAt(x, y);
					Int16 nSrc2 = src2Ch->GetAt(x, y);

					if (nSrc1 > nSrc2)
						dstCh->SetAt(x, y, nSrc1);
					else
						dstCh->SetAt(x, y, nSrc2);
				}
			}

		}
	}

	void CalcColorSblXY(S16ImageRef a_srcX, S16ImageRef a_srcY, S16ImageRef a_dst)
	{
		// HTODO : validate identical sizes

		S16ChannelRef dstCh = a_dst->GetAt(0);

		S16ChannelRef srcXCh0 = a_srcX->GetAt(0);
		S16ChannelRef srcXCh1 = a_srcX->GetAt(1);
		S16ChannelRef srcXCh2 = a_srcX->GetAt(2);

		S16ChannelRef srcYCh0 = a_srcY->GetAt(0);
		S16ChannelRef srcYCh1 = a_srcY->GetAt(1);
		S16ChannelRef srcYCh2 = a_srcY->GetAt(2);

		for (int y = 0; y < dstCh->GetHeight(); y++)
		{
			for (int x = 0; x < dstCh->GetWidth(); x++)
			{
				int nSrcX0 = srcXCh0->GetAt(x, y);
				int nSrcX1 = srcXCh1->GetAt(x, y);
				int nSrcX2 = srcXCh2->GetAt(x, y);

				int nSrcY0 = srcYCh0->GetAt(x, y);
				int nSrcY1 = srcYCh1->GetAt(x, y);
				int nSrcY2 = srcYCh2->GetAt(x, y);

				double nSum = 0;

				nSum += nSrcX0 * nSrcX0 * 0.51;
				nSum += nSrcX1 * nSrcX1 * 1.44;
				nSum += nSrcX2 * nSrcX2 * 1.048;

				nSum += nSrcY0 * nSrcY0 * 0.51;
				nSum += nSrcY1 * nSrcY1 * 1.44;
				nSum += nSrcY2 * nSrcY2 * 1.048;

				nSum /= 6;

				Int16 nRes = (Int16)sqrt(nSum);
				Uint8 nMaxRes = 255;
				if (nRes >= nMaxRes)
					nRes = 255;
				else
					nRes = nRes * 255 / nMaxRes;

				dstCh->SetAt(x, y, nRes);
			}
		}



	}

	void GetColorMidean(S16ImageRef a_src, S16ImageRef a_dst)
	{
		int nAprSiz = 3;
		int nMarg = nAprSiz / 2;
		double minDif = sqrt((double)3 * 255 * 255);

		std::vector<S16ColorVal> nbrVals(nAprSiz * nAprSiz);
		const int nofNbrs = nbrVals.size();

		S16ChannelRef srcCh0 = a_src->GetAt(0);
		S16ChannelRef srcCh1 = a_src->GetAt(1);
		S16ChannelRef srcCh2 = a_src->GetAt(2);

		S16ChannelRef dstCh0 = a_dst->GetAt(0);
		S16ChannelRef dstCh1 = a_dst->GetAt(1);
		S16ChannelRef dstCh2 = a_dst->GetAt(2);

		for (int y = nMarg; y < dstCh0->GetHeight() - nMarg; y++)
		{
			for (int x = nMarg; x < dstCh0->GetWidth() - nMarg; x++)
			{
				int k = 0;

				int nSrcX = x - nMarg;
				int nSrcY = y - nMarg;

				for (int i = 0; i < nAprSiz; i++, nSrcY++)
				{
					for (int j = 0; j < nAprSiz; j++, nSrcX++)
					{
						S16ColorVal & cv = nbrVals[k++];

						cv.val0 = srcCh0->GetAt(nSrcX, nSrcY);
						cv.val1 = srcCh1->GetAt(nSrcX, nSrcY);
						cv.val2 = srcCh2->GetAt(nSrcX, nSrcY);
					}
				}

				/////////////////////////////////

				int nMinIndex = 0;
				int nMinIndexSum = 1000000;
				for (int i = 0; i < nofNbrs; i++)
				{
					S16ColorVal & cv1 = nbrVals[i];
					int nSum = 0;

					for (int j = 0; j < nofNbrs; j++)
					{
						S16ColorVal & cv2 = nbrVals[j];

						nSum += (int)sqrt((double)
							Sqr(cv1.val0 - cv2.val0) +
							Sqr(cv1.val1 - cv2.val1) +
							Sqr(cv1.val2 - cv2.val2));
					}

					if (nSum < nMinIndexSum)
					{
						nMinIndexSum = nSum;
						nMinIndex = i;
					}
				}

				S16ColorVal & cv = nbrVals[nMinIndex];

				dstCh0->SetAt(x, y, cv.val0);
				dstCh1->SetAt(x, y, cv.val1);
				dstCh2->SetAt(x, y, cv.val2);


				/////////////////////////////////

				/*				int nSum0 = 0;
				int nSum1 = 0;
				int nSum2 = 0;

				for(int i=0; i<nofNbrs; i++)
				{
				S16ColorVal & cv0 = nbrVals[i];

				nSum0 += cv0.val0;
				nSum1 += cv0.val1;
				nSum2 += cv0.val2;
				}

				S16ColorVal cvm;

				cvm.val0 = nSum0 / nofNbrs;
				cvm.val1 = nSum1 / nofNbrs;
				cvm.val2 = nSum2 / nofNbrs;

				S16ColorVal cv1;

				double minDif1 = minDif;

				int nMinIdx = 0;
				for(int i=0; i < nofNbrs; i++)
				{
				cv1 = nbrVals[i];

				int nDif0 = cv1.val0 - cvm.val0;
				int nDif1 = cv1.val1 - cvm.val1;
				int nDif2 = cv1.val2 - cvm.val2;

				double dif = sqrt( (double)
				(nDif0 * nDif0) +
				(nDif1 * nDif1) +
				(nDif2 * nDif2) );

				if(dif < minDif1)
				{
				nMinIdx = i;
				minDif1 = dif;
				}
				}
				cv1 = nbrVals[nMinIdx];

				dstCh0->SetAt(x, y, cv1.val0);
				dstCh1->SetAt(x, y, cv1.val1);
				dstCh2->SetAt(x, y, cv1.val2);
				*/
			}
		}

	}

	S16ImageRef GenColorMideanImg(S16ImageRef a_src)
	{
		S16ImageRef ret = S16Image::Create(
			a_src->GetSize(), a_src->GetNofChannels());

		GetColorMidean(a_src, ret);
		return ret;
	}

	S16ImageRef GenWeightedColorMideanImg(
		S16ImageRef a_src, S16ImageRef a_srcGrad, int a_nAprSiz)
	{
		S16ImageRef ret = S16Image::Create(
			a_src->GetSize(), a_src->GetNofChannels());

		//		GetColorMidean(a_src, ret);

		//void GetColorMidean(S16ImageRef a_src, S16ImageRef a_dst)
		//{

		S16ImageRef a_dst = ret;

		int nAprSiz = a_nAprSiz;
		int nMarg = nAprSiz / 2;
		double minDif = sqrt((double)3 * 255 * 255);

		std::vector<S16ColorVal> nbrVals(nAprSiz * nAprSiz);
		const int nofNbrs = nbrVals.size();

		std::vector<int> nbrValWts(nofNbrs);

		S16ChannelRef srcCh0 = a_src->GetAt(0);
		S16ChannelRef srcCh1 = a_src->GetAt(1);
		S16ChannelRef srcCh2 = a_src->GetAt(2);

		S16ChannelRef gradCh0 = a_srcGrad->GetAt(0);

		S16ChannelRef dstCh0 = a_dst->GetAt(0);
		S16ChannelRef dstCh1 = a_dst->GetAt(1);
		S16ChannelRef dstCh2 = a_dst->GetAt(2);

		for (int y = nMarg; y < dstCh0->GetHeight() - nMarg; y++)
		{
			for (int x = nMarg; x < dstCh0->GetWidth() - nMarg; x++)
			{
				int k = 0;

				int nSrcX = x - nMarg;
				int nSrcY = y - nMarg;

				int orgK;
				for (int i = 0; i < nAprSiz; i++, nSrcY++)
				{
					for (int j = 0; j<nAprSiz; j++, nSrcX++)
					{
						if (nSrcX == x && nSrcY == y)
							orgK = k;

						nbrValWts[k] = gradCh0->GetAt(nSrcX, nSrcY);

						if (nbrValWts[k] > 15)
							nbrValWts[k] = 100;
						else
							nbrValWts[k] = 0;

						nbrValWts[k]++;


						S16ColorVal & cv = nbrVals[k++];

						cv.val0 = srcCh0->GetAt(nSrcX, nSrcY);
						cv.val1 = srcCh1->GetAt(nSrcX, nSrcY);
						cv.val2 = srcCh2->GetAt(nSrcX, nSrcY);
					}
				}

				/////////////////////////////////

				int nMinIndex = 0;
				int nMinIndexSum = 1000000;
				for (int i = 0; i < nofNbrs; i++)
				{
					S16ColorVal & cv1 = nbrVals[i];
					int nSum = 0;

					for (int j = 0; j < nofNbrs; j++)
					{
						S16ColorVal & cv2 = nbrVals[j];

						int nFact = 1;

						if (j == orgK)
							nFact = 6;


						nSum += nFact * (int)sqrt((double)
							Sqr(cv1.val0 - cv2.val0) +
							Sqr(cv1.val1 - cv2.val1) +
							Sqr(cv1.val2 - cv2.val2));
					}

					nSum *= nbrValWts[i];

					if (nSum < nMinIndexSum)
					{
						nMinIndexSum = nSum;
						nMinIndex = i;
					}
				}

				S16ColorVal & cv = nbrVals[nMinIndex];

				dstCh0->SetAt(x, y, cv.val0);
				dstCh1->SetAt(x, y, cv.val1);
				dstCh2->SetAt(x, y, cv.val2);
			}
		}



		return ret;
	}

	U8ImageRef GenColorDsp(U8ImageRef a_src)
	{
		Uint8 colors0[256];
		memset(colors0, 0, 256);

		Uint8 colors1[256];
		memset(colors1, 0, 256);

		Uint8 colors2[256];
		memset(colors2, 0, 256);

		for (int i = 0; i < 128; i++)
		{
			colors1[i] = 255;
			colors2[i] = i * 2;
		}

		for (int i = 128, j = 0; i < 256; i++, j++)
		{
			colors1[i] = 255 - j * 2;
			colors2[i] = 255;
		}

		for (int i = 0; i < 255; i++)
		{
			colors0[i] = (Uint8)(colors0[i] * (0.25 + 0.75 * i / 255));
			colors1[i] = (Uint8)(colors1[i] * (0.25 + 0.75 * i / 255));
			colors2[i] = (Uint8)(colors2[i] * (0.25 + 0.75 * i / 255));

			//colors2[i] = colors2[i] * i / 255;
		}

		U8ImageRef ret = U8Image::Create(a_src->GetSize(), 3);

		U8ChannelRef srcCh = a_src->GetAt(0);

		U8ChannelRef retCh0 = ret->GetAt(0);
		U8ChannelRef retCh1 = ret->GetAt(1);
		U8ChannelRef retCh2 = ret->GetAt(2);

		for (int y = 0; y < srcCh->GetHeight(); y++)
		{
			for (int x = 0; x < srcCh->GetWidth(); x++)
			{
				retCh0->SetAt(x, y,
					colors0[srcCh->GetAt(x, y)]);

				retCh1->SetAt(x, y,
					colors1[srcCh->GetAt(x, y)]);
				//colors2[ srcCh->GetAt(x, y) ] );

				retCh2->SetAt(x, y,
					colors2[srcCh->GetAt(x, y)]);
				//colors1[ srcCh->GetAt(x, y) ] );
			}
		}

		return ret;
	}



	U8ImageRef GenScaledImage(U8ImageRef a_src)
	{
		U8ImageRef ret;
		ret = U8Image::Create(a_src->GetSize(), 1);

		double nMin, nMax;

		HCV_CALL(cvMinMaxLoc(a_src->GetIplImagePtr(), &nMin, &nMax));

		HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr(),
			255 / (nMax - nMin),
			-nMin));

		return ret;
	}

	S16ImageRef GenDownSampledImage(S16ImageRef a_src, int a_nStep)
	{
		return GenDownSampledImage(a_src, a_nStep, a_nStep);
	}

	S16ImageRef GenDownSampledImage(S16ImageRef a_src, int a_nStepX, int a_nStepY)
	{
		CvSize retSiz = cvSize(a_src->GetWidth() / a_nStepX,
			a_src->GetHeight() / a_nStepY);

		S16ImageRef ret;
		ret = S16Image::Create(retSiz, a_src->GetNofChannels());


		for (int nCh = 0; nCh < ret->GetNofChannels(); nCh++)
		{
			S16ChannelRef srcCh = a_src->GetAt(nCh);
			S16ChannelRef retCh = ret->GetAt(nCh);


			for (int y = 0, nSrcY = 0; y < retCh->GetHeight(); y++, nSrcY += a_nStepY)
			{
				for (int x = 0, nSrcX = 0; x < retCh->GetWidth(); x++, nSrcX += a_nStepX)
				{
					retCh->SetAt(x, y,
						srcCh->GetAt(nSrcX, nSrcY));
				}
			}

		}

		return ret;
	}


	S16ImageRef GenUpSampledImage(S16ImageRef a_src, int a_nStep)
	{
		return GenUpSampledImage(a_src, a_nStep, a_nStep);
	}

	S16ImageRef GenUpSampledImage(S16ImageRef a_src, int a_nStepX, int a_nStepY)
	{
		CvSize retSiz = cvSize(a_src->GetWidth() * a_nStepX,
			a_src->GetHeight() * a_nStepY);

		S16ImageRef ret;
		ret = S16Image::Create(retSiz, a_src->GetNofChannels());


		for (int nCh = 0; nCh < ret->GetNofChannels(); nCh++)
		{
			S16ChannelRef srcCh = a_src->GetAt(nCh);
			S16ChannelRef retCh = ret->GetAt(nCh);


			for (int y = 0; y < retCh->GetHeight(); y++)
			{
				for (int x = 0; x < retCh->GetWidth(); x++)
				{
					retCh->SetAt(x, y,
						srcCh->GetAt(x / a_nStepX, y / a_nStepY));
				}
			}

		}

		return ret;
	}


	F32ImageRef GenUpSampledImage(F32ImageRef a_src, int a_nStep)
	{
		return GenUpSampledImage(a_src, a_nStep, a_nStep);
	}

	F32ImageRef GenUpSampledImage(F32ImageRef a_src, int a_nStepX, int a_nStepY)
	{
		CvSize retSiz = cvSize(a_src->GetWidth() * a_nStepX,
			a_src->GetHeight() * a_nStepY);

		F32ImageRef ret;
		ret = F32Image::Create(retSiz, a_src->GetNofChannels());


		for (int nCh = 0; nCh < ret->GetNofChannels(); nCh++)
		{
			F32ChannelRef srcCh = a_src->GetAt(nCh);
			F32ChannelRef retCh = ret->GetAt(nCh);


			for (int y = 0; y < retCh->GetHeight(); y++)
			{
				for (int x = 0; x < retCh->GetWidth(); x++)
				{
					retCh->SetAt(x, y,
						srcCh->GetAt(x / a_nStepX, y / a_nStepY));
				}
			}

		}

		return ret;
	}


	F32ImageRef GenImageWithGrid(F32ImageRef a_src, int a_nStepX, int a_nStepY)
	{
		//return a_src;

		//int nofChannels = a_src->GetNofChannels();

		Ncpp_ASSERT(3 == a_src->GetNofChannels());

		CvSize retSiz = a_src->GetSize();

		int nSrcSiz1D = retSiz.width * retSiz.height;

		F32ImageRef ret;
		//ret = F32Image::Create( retSiz, a_src->GetNofChannels());
		ret = a_src->Clone();

		F32ColorVal * colorBuf = (F32ColorVal *)ret->GetPixAt(0, 0);

		IndexCalc2D idxCalc1(retSiz.width, retSiz.height);

		for (int y = a_nStepY; y < retSiz.height; y += a_nStepY)
		{
			for (int x = 0; x < retSiz.width; x++)
			{
				int i = idxCalc1.Calc(x, y);

				F32ColorVal & rC1 = colorBuf[i];

				rC1.MultSelfBy(-1);
				rC1.IncByNum(255);
			}
		}


		for (int x = a_nStepX; x < retSiz.width; x += a_nStepX)
		{
			for (int y = 0; y < retSiz.height; y++)
			{
				int i = idxCalc1.Calc(x, y);

				F32ColorVal & rC1 = colorBuf[i];

				rC1.MultSelfBy(-1);
				rC1.IncByNum(255);
			}
		}


		return ret;
	}

	//S16ImageRef GenColorSobelGradImage(S16ImageRef a_src, int a_nAprSiz)
	//{
	//	S16ImageRef ret;

	//	// X

	//	ConvKernelRef sblKer = ConvKernel::CreateSobel(1, 0, a_nAprSiz);

	//	S16ImageRef resX = S16Image::Create(
	//		a_src->GetSize(), a_src->GetNofChannels());

	//	sblKer->Process(a_src, resX);

	//	// Y

	//	sblKer = ConvKernel::CreateSobel(0, 1, a_nAprSiz);

	//	S16ImageRef resY = S16Image::Create(
	//		a_src->GetSize(), a_src->GetNofChannels());

	//	sblKer->Process(a_src, resY);

	//	//	XY

	//	ret = S16Image::Create(
	//		a_src->GetSize(), 1);

	//	CalcColorSblXY(resX, resY, ret);


	//	return ret;
	//}

	F32ImageRef GenF32FromS16Image(S16ImageRef a_src)
	{
		F32ImageRef ret;

		ret = F32Image::Create(
			cvGetSize(a_src->GetIplImagePtr()), a_src->GetNofChannels());

		HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr()));

		return ret;
	}

	F32ImageRef GenF32FromU8Image(U8ImageRef a_src)
	{
		return GenF32FromS16Image(
			GenS16FromU8Image(a_src));
	}

	S16ImageRef GenS16FromF32Image(F32ImageRef a_src)
	{
		S16ImageRef ret;

		Ncpp_ASSERT(nullptr != a_src->GetIplImagePtr());

		ret = S16Image::Create(
			cvGetSize(a_src->GetIplImagePtr()), a_src->GetNofChannels());

		HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr()));

		return ret;
	}

	S16ImageRef GenS16FromU8Image(U8ImageRef a_src)
	{
		S16ImageRef ret;

		ret = S16Image::Create(
			cvGetSize(a_src->GetIplImagePtr()), a_src->GetNofChannels());

		HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr()));

		return ret;
	}

	U8ImageRef GenU8FromS16Image(S16ImageRef a_src)
	{
		U8ImageRef ret;

		ret = U8Image::Create(
			cvGetSize(a_src->GetIplImagePtr()), a_src->GetNofChannels());

		if (1 == a_src->GetNofChannels())
		{
			double dMin, dMax;

			HCV_CALL(cvMinMaxLoc(a_src->GetIplImagePtr(), &dMin, &dMax));

			if (dMin < 0 || dMax > 255)
			{
				HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
					ret->GetIplImagePtr(), (255 / (dMax - dMin)), -dMin));
			}
			else
			{
				HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
					ret->GetIplImagePtr()));
			}
		}
		else
		{
			HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
				ret->GetIplImagePtr()));
		}


		return ret;
	}

	U8ImageRef GenU8FromF32Image(F32ImageRef a_src)
	{
		return GenU8FromS16Image(
			GenS16FromF32Image(a_src));
	}


	S16ImageRef GenScaledS16FromS32Image(S32ImageRef a_src)
	{
		S16ImageRef ret;

		ret = S16Image::Create(
			cvGetSize(a_src->GetIplImagePtr()), a_src->GetNofChannels());

		double dMin, dMax;

		HCV_CALL(cvMinMaxLoc(a_src->GetIplImagePtr(), &dMin, &dMax));

		if (dMin < 0 || dMax > 255)
		{
			double scale = (255 / (dMax - dMin));
			double shift = -dMin * scale;

			HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
				a_src->GetIplImagePtr(), scale, shift));
		}
		else
		{
			HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
				ret->GetIplImagePtr()));
		}

		return ret;
	}

	void ShowImage(IplImage * a_iplImagePtr, const char * a_sWndName)
	{
		//	hthm 241012
		//return;

		bool bFstShow = (nullptr == cvGetWindowHandle(a_sWndName));

		HCV_CALL(cvNamedWindow(a_sWndName, 1));
		HCV_CALL(cvShowImage(a_sWndName, a_iplImagePtr));

		if (bFstShow)
			//HCV_CALL( cvMoveWindow( a_sWndName, 100, 100 ) );
			HCV_CALL(cvMoveWindow(a_sWndName, 100, 10));
	}


	S16ImageRef GenMinimaImage(S16ImageRef a_src)
	{
		S16ImageRef ret;

		ret = S16Image::Create(
			cvGetSize(a_src->GetIplImagePtr()), 1);

		int nAprSiz = 3;
		int nMarg = nAprSiz / 2;

		FillBorder(ret->GetAt(0), (Int16)0, nMarg);

		S16ChannelRef srcCh = a_src->GetAt(0);
		S16ChannelRef retCh = ret->GetAt(0);


		for (int y = nMarg; y < retCh->GetHeight() - nMarg; y++)
		{
			for (int x = nMarg; x < retCh->GetWidth() - nMarg; x++)
			{
				int nVal = srcCh->GetAt(x, y);
				int nRank = nAprSiz * nAprSiz;
				int nMax = nRank - 1;
				bool bNotLvl = false;

				for (int nSrcY = y - nMarg, nMaskY = 0; nMaskY < nAprSiz; nSrcY++, nMaskY++)
				{
					for (int nSrcX = x - nMarg, nMaskX = 0; nMaskX < nAprSiz; nSrcX++, nMaskX++)
					{
						int nNbrVal = srcCh->GetAt(nSrcX, nSrcY);

						if (nVal <= nNbrVal)
							nRank--;
						if (nVal != nNbrVal)
							bNotLvl = true;
					}
				}

				/*				if(0 == nVal)
				retCh->SetAt(x, y, 0);
				else
				retCh->SetAt(x, y, 255);*/

				//						if(0 == nVal)
				//					retCh->SetAt(x, y, (Int16)(nMax / 1.3));

				//				if(703 == x && 334 == y)
				//					x = x;

				if (0 == nVal && bNotLvl)
					retCh->SetAt(x, y, 0);
				else if (0 == nRank && bNotLvl)
					retCh->SetAt(x, y, nMax / 4);
				else if (0 == nRank)
					retCh->SetAt(x, y, nMax / 2);
				else
					retCh->SetAt(x, y, nMax);

				/*				if(0 == nVal && bNotLvl)
				retCh->SetAt(x, y, 0);
				else if(0 == nVal)
				retCh->SetAt(x, y, nMax / 2);
				else
				retCh->SetAt(x, y, nMax);*/

				/*				if(bNotLvl)
				retCh->SetAt(x, y, nRank);
				else
				retCh->SetAt(x, y, nMax * 2);*/


				/*				if(0 == nRank)
				retCh->SetAt(x, y, 0);
				else
				retCh->SetAt(x, y, 255);*/
			}
		}

		return ret;
	}



	S16ImageRef GenMaximaImage(S16ImageRef a_src)
	{
		S16ImageRef ret;

		ret = S16Image::Create(
			cvGetSize(a_src->GetIplImagePtr()), 1);

		int nAprSiz = 3;
		int nMarg = nAprSiz / 2;

		FillBorder(ret->GetAt(0), (Int16)0, nMarg);

		S16ChannelRef srcCh = a_src->GetAt(0);
		S16ChannelRef retCh = ret->GetAt(0);


		for (int y = nMarg; y < retCh->GetHeight() - nMarg; y++)
		{
			for (int x = nMarg; x < retCh->GetWidth() - nMarg; x++)
			{
				int nVal = srcCh->GetAt(x, y);
				int nRank = nAprSiz * nAprSiz;
				int nMax = nRank - 1;
				bool bNotLvl = false;

				for (int nSrcY = y - nMarg, nMaskY = 0; nMaskY < nAprSiz; nSrcY++, nMaskY++)
				{
					for (int nSrcX = x - nMarg, nMaskX = 0; nMaskX < nAprSiz; nSrcX++, nMaskX++)
					{
						int nNbrVal = srcCh->GetAt(nSrcX, nSrcY);

						if (nVal >= nNbrVal)
							nRank--;
						if (nVal != nNbrVal)
							bNotLvl = true;
					}
				}

				/*				if(0 == nVal)
				retCh->SetAt(x, y, 0);
				else
				retCh->SetAt(x, y, 255);*/

				if (bNotLvl)
					retCh->SetAt(x, y, nRank);
				else
					retCh->SetAt(x, y, nMax);


				/*				if(0 == nRank)
				retCh->SetAt(x, y, 0);
				else
				retCh->SetAt(x, y, 255);*/
			}
		}

		return ret;
	}



	U8ImageRef GenNegativeImage(U8ImageRef a_src)
	{
		U8ImageRef ret;

		ret = U8Image::Create(
			a_src->GetSize(), a_src->GetNofChannels());

		for (int nCh = 0; nCh < ret->GetNofChannels(); nCh++)
		{
			U8ChannelRef srcCh = a_src->GetAt(nCh);
			U8ChannelRef retCh = ret->GetAt(nCh);


			for (int y = 0; y < retCh->GetHeight(); y++)
			{
				for (int x = 0; x < retCh->GetWidth(); x++)
				{
					retCh->SetAt(x, y,
						255 - srcCh->GetAt(x, y));
				}
			}

		}

		return ret;
	}


	S32ImageRef GenNeighbourhoodImage(S16ImageRef a_src)
	{
		S32ImageRef ret;

		ret = S32Image::Create(
			cvSize(256, 256), 1);


		S16ChannelRef srcCh = a_src->GetAt(0);
		S32ChannelRef retCh = ret->GetAt(0);

		retCh->SetAll(0);

		for (int y = 0; y < srcCh->GetHeight() - 1; y++)
		{
			for (int x = 1; x < srcCh->GetWidth() - 1; x++)
			{
				int nVal = srcCh->GetAt(x, y);

				retCh->IncAt(nVal, srcCh->GetAt(x + 1, y), 1);
				retCh->IncAt(nVal, srcCh->GetAt(x + 1, y + 1), 1);
				retCh->IncAt(nVal, srcCh->GetAt(x, y + 1), 1);
				retCh->IncAt(nVal, srcCh->GetAt(x - 1, y + 1), 1);
			}
		}

		for (int y = 0, x = 0; y < srcCh->GetHeight() - 1; y++)
		{
			int nVal = srcCh->GetAt(x, y);

			retCh->IncAt(nVal, srcCh->GetAt(x + 1, y), 1);
			retCh->IncAt(nVal, srcCh->GetAt(x + 1, y + 1), 1);
			retCh->IncAt(nVal, srcCh->GetAt(x, y + 1), 1);
		}

		for (int y = srcCh->GetHeight() - 1, x = 0; x < srcCh->GetWidth() - 1; x++)
		{
			int nVal = srcCh->GetAt(x, y);
			retCh->IncAt(nVal, srcCh->GetAt(x + 1, y), 1);
		}

		for (int y = 0, x = srcCh->GetWidth() - 1; y < srcCh->GetHeight() - 1; y++)
		{
			int nVal = srcCh->GetAt(x, y);

			retCh->IncAt(nVal, srcCh->GetAt(x, y + 1), 1);
			retCh->IncAt(nVal, srcCh->GetAt(x - 1, y + 1), 1);
		}

		///////////////////

		for (int y = 0; y < retCh->GetHeight(); y++)
		{
			for (int x = y + 1; x < retCh->GetWidth(); x++)
			{
				int nVal = (retCh->GetAt(x, y) +
					retCh->GetAt(y, x)) / 2;
				retCh->SetAt(x, y, nVal);
				retCh->SetAt(y, x, nVal);
			}
		}

		return ret;
	}

	S16ImageRef GenPyrUpImg(S16ImageRef a_src, int a_nIterCnt)
	{
		S16ImageRef ret = a_src;

		S16ImageRef src = a_src;

		for (int i = 0; i < a_nIterCnt; i++)
		{
			CvSize retSiz = cvGetSize(src->GetIplImagePtr());
			retSiz.width *= 2; retSiz.width;
			retSiz.height *= 2; retSiz.height;

			//ret = S16Image::Create(retSiz, src->GetNofChannels());
			//ret->SetAll(0);

			//cvPyrUp (src->GetIplImagePtr(), ret->GetIplImagePtr());

			ret = GenUpSampledImage(src, 2);

			for (int i = 0; i < ret->GetNofChannels(); i++)
			{
				FillBorder(ret->GetAt(i), (Int16)0, 1);
			}

			src = ret;
		}

		return ret;
	}


	F32ImageRef GenPyrUpImg(F32ImageRef a_src, int a_nIterCnt)
	{
		F32ImageRef ret = nullptr;

		F32ImageRef src = a_src;

		for (int i = 0; i < a_nIterCnt; i++)
		{
			CvSize retSiz = cvGetSize(src->GetIplImagePtr());
			retSiz.width *= 2; retSiz.width;
			retSiz.height *= 2; retSiz.height;

			{
				ret = F32Image::Create(retSiz, src->GetNofChannels());
				//ret->SetAll(0);

				cvPyrUp(src->GetIplImagePtr(), ret->GetIplImagePtr());
			}

			//ret = GenUpSampledImage( src, 2 );

			/*
			for(int i=0; i<ret->GetNofChannels(); i++)
			{
			FillBorder(ret->GetAt(i), (Float)0, 1);
			}
			*/

			src = ret;
		}

		return ret;
	}



	S16ImageRef GenPyrDownImg(S16ImageRef a_src, int a_nIterCnt)
	{
		S16ImageRef ret = a_src;

		S16ImageRef src = a_src;

		for (int i = 0; i < a_nIterCnt; i++)
		{
			CvSize retSiz = cvGetSize(src->GetIplImagePtr());
			retSiz.width /= 2; retSiz.width;
			retSiz.height /= 2; retSiz.height;

			//ret = S16Image::Create(retSiz, src->GetNofChannels());
			//ret->SetAll(0);

			//cvPyrDown (src->GetIplImagePtr(), ret->GetIplImagePtr());

			ret = GenDownSampledImage(src, 2);

			for (int i = 0; i < ret->GetNofChannels(); i++)
			{
				FillBorder(ret->GetAt(i), (Int16)0, 1);
			}

			src = ret;
		}

		return ret;
	}

	F32ImageRef GenPyrDownImg(F32ImageRef a_src, int a_nIterCnt)
	{
		F32ImageRef ret = nullptr;

		F32ImageRef src = a_src;

		for (int i = 0; i < a_nIterCnt; i++)
		{
			CvSize retSiz = cvGetSize(src->GetIplImagePtr());
			retSiz.width /= 2; retSiz.width;
			retSiz.height /= 2; retSiz.height;

			ret = F32Image::Create(retSiz, src->GetNofChannels());
			//ret->SetAll(0);

			cvPyrDown(src->GetIplImagePtr(), ret->GetIplImagePtr());

			//ret = GenDownSampledImage( src, 2 );

			/*
			for(int i=0; i<ret->GetNofChannels(); i++)
			{
			FillBorder(ret->GetAt(i), (Float)0, 1);
			}
			*/

			src = ret;
		}

		return ret;
	}

	std::vector<CvPoint> GenDataPoints(S16ImageRef a_src, const int nDataVal)
	{
		std::vector<CvPoint> dataPts(1000);
		dataPts.resize(0);

		S16ChannelRef ch0 = a_src->GetAt(0);

		for (int y = 0; y < ch0->GetHeight(); y++)
		{
			for (int x = 0; x < ch0->GetWidth(); x++)
			{
				if (nDataVal == ch0->GetAt(x, y))
					dataPts.push_back(cvPoint(x, y));
			}
		}

		return dataPts;
	}

	S16ImageRef GenDataImage(std::vector<CvPoint> a_data, CvSize a_imgSiz,
		int nDataVal, const int nBkgVal)
	{
		S16ImageRef ret;

		ret = S16Image::Create(a_imgSiz, 1);
		ret->SetAll(nBkgVal);

		S16ChannelRef ch0 = ret->GetAt(0);

		for (int i = 0; i < a_data.size(); i++)
		{
			ch0->SetAt(a_data[i].x, a_data[i].y, nDataVal);
		}

		return ret;
	}

	S16ImageRef GenHDensityImg(S16ImageRef a_hdifImg)
	{
		S16ImageRef ret;

		const int nIntvX = 23;

		CvSize retSiz = cvGetSize(a_hdifImg->GetIplImagePtr());
		retSiz.width /= nIntvX; retSiz.width--;

		ret = S16Image::Create(retSiz, 1);
		//ret->SetAll(0);

		S16ChannelRef srcCh0 = a_hdifImg->GetAt(0);
		S16ChannelRef retCh0 = ret->GetAt(0);

		const int nScanSiz = nIntvX * 2;

		for (int y = 0; y < retCh0->GetHeight(); y++)
		{
			for (int x = 0; x < retCh0->GetWidth(); x++)
			{
				int srcX = x * nIntvX;

				int nSum = 0;

				for (int i = 0; i < nScanSiz; i++, srcX++)
					nSum += srcCh0->GetAt(srcX, y);

				retCh0->SetAt(x, y, nSum);
			}
		}

		return ret;
	}


	S16ImageRef GenThresholdImg(S16ImageRef a_src, int a_nVal)
	{
		S16ImageRef ret;

		//const int nIntvX = 23;

		CvSize retSiz = cvGetSize(a_src->GetIplImagePtr());

		ret = S16Image::Create(retSiz, a_src->GetNofChannels());

		//S16ChannelRef srcCh0 = a_src->GetAt(0);
		//		S16ChannelRef srcCh1 = a_src->GetAt(1);
		//		S16ChannelRef srcCh2 = a_src->GetAt(2);

		//S16ChannelRef retCh0 = ret->GetAt(0);
		//		S16ChannelRef retCh1 = ret->GetAt(1);
		//		S16ChannelRef retCh2 = ret->GetAt(2);

		for (int ch = 0; ch < ret->GetNofChannels(); ch++)
		{
			S16ChannelRef srcCh = a_src->GetAt(ch);
			S16ChannelRef retCh = ret->GetAt(ch);


			for (int y = 0; y < retCh->GetHeight(); y++)
			{
				for (int x = 0; x < retCh->GetWidth(); x++)
				{
					int nVal;

					nVal = srcCh->GetAt(x, y);
					if (nVal >= a_nVal)
						retCh->SetAt(x, y, 255);
					else
						retCh->SetAt(x, y, 0);

					/*				nVal = srcCh1->GetAt(x, y);
					if(nVal >= a_nVal)
					retCh1->SetAt(x, y, 255);
					else
					retCh1->SetAt(x, y, 0);

					nVal = srcCh2->GetAt(x, y);
					if(nVal >= a_nVal)
					retCh2->SetAt(x, y, 255);
					else
					retCh2->SetAt(x, y, 0);*/
				}
			}
		}

		return ret;
	}

	F32ImageRef GenClippedPixValImg(F32ImageRef a_src,
		float a_maxVal, float a_minVal)
	{
		F32ImageRef ret;

		CvSize srcSiz = a_src->GetSize();
		int nSrcSiz1D = srcSiz.width * srcSiz.height;

		float * srcBuf = a_src->GetPixAt(0, 0);

		int nBufSiz = nSrcSiz1D * a_src->GetNofChannels();

		ret = F32Image::Create(srcSiz, a_src->GetNofChannels());

		float * retBuf = ret->GetPixAt(0, 0);

		for (int i = 0; i < nBufSiz; i++)
		{
			float val = srcBuf[i];

			if (val > a_maxVal)
				val = a_maxVal;

			if (val < a_minVal)
				val = a_minVal;

			retBuf[i] = val;
		}

		return ret;
	}

	F32ImageRef GenThresholdImg(F32ImageRef a_src, float a_val)
	{
		F32ImageRef ret;

		//const int nIntvX = 23;

		CvSize retSiz = cvGetSize(a_src->GetIplImagePtr());

		ret = F32Image::Create(retSiz, a_src->GetNofChannels());


		F32ColorVal colorMin = { 0, 0, 0 };
		F32ColorVal colorMax = { 255, 255, 255 };


		for (int y = 0; y < retSiz.height; y++)
		{
			for (int x = 0; x < retSiz.width; x++)
			{
				F32ColorVal * srcPix = (F32ColorVal *)a_src->GetPixAt(x, y);
				F32ColorVal * dstPix = (F32ColorVal *)ret->GetPixAt(x, y);

				float val = srcPix->CalcMag();

				if (val >= a_val)
					*dstPix = colorMax;
				else
					*dstPix = colorMin;
			}
		}


		return ret;
	}




	void DrawPoints(std::vector<CvPoint> a_data, S16ImageRef a_img, CvScalar a_color)
	{
		DrawPoints(&a_data[0], a_data.size(), a_img, a_color);
	}


	void DrawPoints(CvPoint * a_data, int a_nofPoints,
		S16ImageRef a_img, CvScalar a_color)
	{
		const int nBlue = a_color.val[0];
		const int nGreen = a_color.val[1];
		const int nRed = a_color.val[2];

		S16ChannelRef chB = a_img->GetAt(0);
		S16ChannelRef chG = a_img->GetAt(1);
		S16ChannelRef chR = a_img->GetAt(2);

		for (int i = 0; i < a_nofPoints; i++)
		{
			chB->SetAt(a_data[i].x, a_data[i].y, nBlue);
			chG->SetAt(a_data[i].x, a_data[i].y, nGreen);
			chR->SetAt(a_data[i].x, a_data[i].y, nRed);
		}
	}








	void DrawPoints(S16ImageRef a_img, std::vector<CvPoint> * a_pPointArr,
		std::vector<int> * a_pPointIDs, std::vector<U8ColorVal> * a_pColorArr)
	{
		std::vector<CvPoint> & pointArr = *a_pPointArr;
		std::vector<int> & pointIDs = *a_pPointIDs;
		std::vector<U8ColorVal> & colorArr = *a_pColorArr;

		HCV_ERROR();


		//DrawPoints(a_img, &pointArr[0], 
		//	pointArr.size(), &pointIDs[0], &colorArr[0]);
	}


	//void DrawPoints(S16ImageRef a_img, CvPoint * a_points,
	//	//int a_nofPoints, int * a_ids, U8ColorVal * a_colors)
	//	int a_nofPoints, ClusteringMgr & a_rCm, U8ColorVal * a_colors)
	//{
	//	S16ChannelRef ch0 = a_img->GetAt(0);
	//	S16ChannelRef ch1 = a_img->GetAt(1);
	//	S16ChannelRef ch2 = a_img->GetAt(2);

	//	for (int i = 0; i < a_nofPoints; i++)
	//	{
	//		U8ColorVal color =
	//			a_colors[a_rCm.GetPatClusterID(i)];

	//		ch0->SetAt(a_points[i].x, a_points[i].y, color.val0);
	//		ch1->SetAt(a_points[i].x, a_points[i].y, color.val1);
	//		ch2->SetAt(a_points[i].x, a_points[i].y, color.val2);
	//	}
	//}

	U8ColorVal u8ColorVal(Uint8 a_val0, Uint8 a_val1, Uint8 a_val2)
	{
		U8ColorVal ret;

		ret.val0 = a_val0;
		ret.val1 = a_val1;
		ret.val2 = a_val2;

		return ret;
	}

	S16ImageRef GenFastAvgHImg(S16ImageRef a_src, int a_nAprSiz)
	{
		S16ImageRef ret;

		const int nMarg = a_nAprSiz / 2;

		CvSize srcSiz = a_src->GetSize();
		CvSize retSiz = cvSize(srcSiz.width - 2 * nMarg, srcSiz.height);

		ret = S16Image::Create(retSiz, a_src->GetNofChannels());

		for (int nCh = 0; nCh < a_src->GetNofChannels(); nCh++)
		{
			S16ChannelRef srcCh = a_src->GetAt(nCh);
			S16ChannelRef retCh = ret->GetAt(nCh);

			for (int y = 0; y < retCh->GetHeight(); y++)
			{
				int nSum = 0;

				for (int nSrcX = 0; nSrcX < a_nAprSiz; nSrcX++)
				{
					nSum += srcCh->GetAt(nSrcX, y);
				}
				retCh->SetAt(0, y, nSum / a_nAprSiz);

				int nSrcXSub = 0;
				int nSrcXAdd = a_nAprSiz;

				for (int x = 1; x < retCh->GetWidth(); x++, nSrcXSub++, nSrcXAdd++)
				{
					nSum -= srcCh->GetAt(nSrcXSub, y);
					nSum += srcCh->GetAt(nSrcXAdd, y);

					retCh->SetAt(x, y, nSum / a_nAprSiz);
				}
			}
		}

		return ret;
	}





	S16ImageRef GenFastAvgVImg(S16ImageRef a_src, int a_nAprSiz)
	{
		S16ImageRef ret;

		const int nMarg = a_nAprSiz / 2;

		CvSize srcSiz = a_src->GetSize();
		CvSize retSiz = cvSize(srcSiz.width, srcSiz.height - 2 * nMarg);

		ret = S16Image::Create(retSiz, a_src->GetNofChannels());

		for (int nCh = 0; nCh < a_src->GetNofChannels(); nCh++)
		{
			S16ChannelRef srcCh = a_src->GetAt(nCh);
			S16ChannelRef retCh = ret->GetAt(nCh);

			for (int x = 0; x < retCh->GetWidth(); x++)
			{
				int nSum = 0;

				for (int nSrcY = 0; nSrcY < a_nAprSiz; nSrcY++)
				{
					nSum += srcCh->GetAt(x, nSrcY);
				}
				retCh->SetAt(x, 0, nSum / a_nAprSiz);

				int nSrcYSub = 0;
				int nSrcYAdd = a_nAprSiz;

				for (int y = 1; y < retCh->GetHeight(); y++, nSrcYSub++, nSrcYAdd++)
				{
					nSum -= srcCh->GetAt(x, nSrcYSub);
					nSum += srcCh->GetAt(x, nSrcYAdd);

					retCh->SetAt(x, y, nSum / a_nAprSiz);
				}
			}
		}

		return ret;
	}

	S16ImageRef GenFastAvgImg(S16ImageRef a_src, int a_nAprSiz)
	{
		S16ImageRef ret = a_src;

		ret = GenFastAvgHImg(ret, a_nAprSiz);
		ret = GenFastAvgVImg(ret, a_nAprSiz);

		return ret;
	}


	F32ImageRef GenMagSqrImg(F32ImageRef a_src)
	{
		F32ColorVal * src_Buf = (F32ColorVal *)a_src->GetPixAt(0, 0);

		F32ImageRef ret = F32Image::Create(
			a_src->GetSize(), 1);

		float * magSqr_Buf = ret->GetPixAt(0, 0);

		int nImgSiz1D = a_src->GetSize1D();

		for (int i = 0; i < nImgSiz1D; i++)
		{
			F32ColorVal & rSrcColor = src_Buf[i];

			magSqr_Buf[i] = rSrcColor.CalcMagSqr();
		}

		return ret;
	}

	F32ImageRef GenMagImg(F32ImageRef a_src)
	{
		F32ColorVal * src_Buf = (F32ColorVal *)a_src->GetPixAt(0, 0);

		F32ImageRef ret = F32Image::Create(
			a_src->GetSize(), 1);

		float * mag_Buf = ret->GetPixAt(0, 0);

		int nImgSiz1D = a_src->GetSize1D();

		for (int i = 0; i < nImgSiz1D; i++)
		{
			F32ColorVal & rSrcColor = src_Buf[i];

			mag_Buf[i] = rSrcColor.CalcMag();
		}

		return ret;
	}



	F32ImageRef GenFastAvgHImg(F32ImageRef a_src, int a_nAprSiz)
	{
		Ncpp::Debug::Assert(1 == a_nAprSiz % 2);

		F32ImageRef ret;

		const int nMarg = a_nAprSiz / 2;

		CvSize srcSiz = a_src->GetSize();
		//CvSize retSiz = cvSize( srcSiz.width - 2 * nMarg, srcSiz.height);
		CvSize retSiz = cvSize(srcSiz.width, srcSiz.height);

		ret = F32Image::Create(retSiz, a_src->GetNofChannels());

		const int nBgnX = nMarg + 1;
		const int nLimX = retSiz.width - nMarg;

		const int nBgnY = 0;
		const int nLimY = retSiz.height;

		for (int nCh = 0; nCh < a_src->GetNofChannels(); nCh++)
		{
			F32ChannelRef srcCh = a_src->GetAt(nCh);
			F32ChannelRef retCh = ret->GetAt(nCh);

			FillBorder(retCh, (float)0, nMarg, nMarg, 0, 0);

			for (int y = nBgnY; y < nLimY; y++)
			{
				float sum = 0;

				for (int nSrcX = 0; nSrcX < a_nAprSiz; nSrcX++)
				{
					sum += srcCh->GetAt(nSrcX, y);
				}

				// Hthm Tmp.
				if (sum < -1)
					sum = sum;

				retCh->SetAt(nMarg, y, sum / a_nAprSiz);

				int nSrcXSub = 0;
				int nSrcXAdd = a_nAprSiz;

				for (int x = nBgnX; x < nLimX; x++, nSrcXSub++, nSrcXAdd++)
				{
					sum -= srcCh->GetAt(nSrcXSub, y);
					sum += srcCh->GetAt(nSrcXAdd, y);

					// Hthm Tmp.
					if (sum < -1)
						sum = sum;

					retCh->SetAt(x, y, sum / a_nAprSiz);
				}
			}

			{
				for (int x = 0; x < nMarg; x++)
				{
					int nSrcX = nMarg;

					for (int y = 0; y < retCh->GetHeight(); y++)
						retCh->SetAt(x, y,
						retCh->GetAt(nSrcX, y));
				}

				for (int x = retCh->GetWidth() - nMarg; x < retCh->GetWidth(); x++)
				{
					int nSrcX = retCh->GetWidth() - nMarg - 1;

					for (int y = 0; y < retCh->GetHeight(); y++)
						retCh->SetAt(x, y,
						retCh->GetAt(nSrcX, y));
				}
			}





		}

		return ret;
	}

	F32ImageRef GenFastAvgVImg(F32ImageRef a_src, int a_nAprSiz)
	{
		Ncpp::Debug::Assert(1 == a_nAprSiz % 2);

		F32ImageRef ret;

		const int nMarg = a_nAprSiz / 2;

		CvSize srcSiz = a_src->GetSize();
		//CvSize retSiz = cvSize( srcSiz.width - 2 * nMarg, srcSiz.height);
		CvSize retSiz = cvSize(srcSiz.width, srcSiz.height);

		ret = F32Image::Create(retSiz, a_src->GetNofChannels());

		const int nBgnY = nMarg + 1;
		const int nLimY = retSiz.height - nMarg;

		const int nBgnX = 0;
		const int nLimX = retSiz.width;

		for (int nCh = 0; nCh < a_src->GetNofChannels(); nCh++)
		{
			F32ChannelRef srcCh = a_src->GetAt(nCh);
			F32ChannelRef retCh = ret->GetAt(nCh);

			FillBorder(retCh, (float)0, 0, 0, nMarg, nMarg);

			for (int x = nBgnX; x < nLimX; x++)
			{
				float sum = 0;

				for (int nSrcY = 0; nSrcY < a_nAprSiz; nSrcY++)
				{
					sum += srcCh->GetAt(x, nSrcY);
				}

				// Hthm Tmp.
				if (sum < -1)
					sum = sum;

				retCh->SetAt(x, nMarg, sum / a_nAprSiz);

				int nSrcYSub = 0;
				int nSrcYAdd = a_nAprSiz;

				for (int y = nBgnY; y < nLimY; y++, nSrcYSub++, nSrcYAdd++)
				{
					sum -= srcCh->GetAt(x, nSrcYSub);
					sum += srcCh->GetAt(x, nSrcYAdd);

					// Hthm Tmp.
					if (sum < -1)
						sum = sum;

					retCh->SetAt(x, y, sum / a_nAprSiz);
				}
			}


			{
				int x, y;

				for (y = 0; y < nMarg; y++)
				{
					int nSrcY = nMarg;

					for (x = 0; x < retCh->GetWidth(); x++)
						retCh->SetAt(x, y,
						retCh->GetAt(x, nSrcY));
				}

				for (y = retCh->GetHeight() - nMarg; y < retCh->GetHeight(); y++)
				{
					int nSrcY = retCh->GetHeight() - nMarg - 1;

					for (x = 0; x < retCh->GetWidth(); x++)
						retCh->SetAt(x, y,
						retCh->GetAt(x, nSrcY));
				}

			}


		}

		return ret;
	}

	F32ImageRef GenFastAvgImg(F32ImageRef a_src, int a_nAprSizH, int a_nAprSizV)
	{
		Ncpp::Debug::Assert(1 == a_nAprSizH % 2);

		if (-1 == a_nAprSizV)
			a_nAprSizV = a_nAprSizH;
		Ncpp::Debug::Assert(1 == a_nAprSizV % 2);

		F32ImageRef ret = a_src;

		ret = GenFastAvgHImg(ret, a_nAprSizH);
		ret = GenFastAvgVImg(ret, a_nAprSizV);

		//FillBorder(ret->GetAt(0), (float)0, a_nAprSiz / 2);

		return ret;
	}




	S16ImageRef GenDifMagImg(S16ImageRef a_src)
	{
		S16ImageRef ret = S16Image::Create(
			a_src->GetSize(), 1);

		const int nMaxDif = (int)sqrt((double)3 * Sqr(255));

		S16ChannelRef srcCh0 = a_src->GetAt(0);
		S16ChannelRef srcCh1 = a_src->GetAt(1);
		S16ChannelRef srcCh2 = a_src->GetAt(2);

		S16ChannelRef retCh0 = ret->GetAt(0);


		for (int y = 0; y < retCh0->GetHeight(); y++)
		{
			for (int x = 0; x < retCh0->GetWidth(); x++)
			{
				short nVal = (short)sqrt((double)
					Sqr(srcCh0->GetAt(x, y)) +
					Sqr(srcCh1->GetAt(x, y)) +
					Sqr(srcCh2->GetAt(x, y)));

				nVal = (nVal * 255) / nMaxDif;


				retCh0->SetAt(x, y, nVal);
			}
		}

		return ret;
	}


	F32ImageRef Gen4DirEdgeImg(F32ImageRef a_src)
	{
		if (a_src->GetNofChannels() == 1)
			return a_src;

		F32ImageRef ret = F32Image::Create(
			a_src->GetSize(), 1);

		const float nMaxDif = (float)sqrt((double)3 * Sqr(255));

		F32ChannelRef srcCh0 = a_src->GetAt(0);
		F32ChannelRef srcCh1 = a_src->GetAt(1);
		F32ChannelRef srcCh2 = a_src->GetAt(2);

		F32ChannelRef retCh0 = ret->GetAt(0);


		for (int y = 0; y < retCh0->GetHeight(); y++)
		{
			for (int x = 0; x < retCh0->GetWidth(); x++)
			{
				float nVal = (float)sqrt((float)
					Sqr(srcCh0->GetAt(x, y)) +
					Sqr(srcCh1->GetAt(x, y)) +
					Sqr(srcCh2->GetAt(x, y)));

				nVal = (nVal * 255) / nMaxDif;


				retCh0->SetAt(x, y, nVal);
			}
		}

		return ret;
	}




	F32ImageRef GenMagImgF32(F32ImageRef a_src)
	{
		if (a_src->GetNofChannels() == 1)
			return a_src;

		F32ImageRef ret = F32Image::Create(
			a_src->GetSize(), 1);

		const float nMaxDif = (float)sqrt((double)3 * Sqr(255));

		F32ChannelRef srcCh0 = a_src->GetAt(0);
		F32ChannelRef srcCh1 = a_src->GetAt(1);
		F32ChannelRef srcCh2 = a_src->GetAt(2);

		F32ChannelRef retCh0 = ret->GetAt(0);


		for (int y = 0; y < retCh0->GetHeight(); y++)
		{
			for (int x = 0; x < retCh0->GetWidth(); x++)
			{
				float nVal = (float)sqrt((float)
					//0.51 * Sqr( srcCh0->GetAt( x, y ) ) +
					//1.44 * Sqr( srcCh1->GetAt( x, y ) ) +
					//1.048 * Sqr( srcCh2->GetAt( x, y ) ) );

					Sqr(srcCh0->GetAt(x, y)) +
					Sqr(srcCh1->GetAt(x, y)) +
					Sqr(srcCh2->GetAt(x, y)));

				nVal = (nVal * 255) / nMaxDif;


				retCh0->SetAt(x, y, nVal);
			}
		}

		return ret;
	}


	S16ImageRef GenCenterPixImg(CvSize a_siz, int a_nofChannels)
	{
		S16ImageRef ret = S16Image::Create(a_siz, a_nofChannels);

		ret->SetAll(0);


		int centerX = ret->GetSize().width / 2;
		int centerY = ret->GetSize().height / 2;

		for (int ch = 0; ch < ret->GetNofChannels(); ch++)
		{
			S16ChannelRef retCh = ret->GetAt(ch);
			retCh->SetAt(centerX, centerY, 255);
		}

		return ret;
	}


	S16ImageRef GenBinImposedImg(S16ImageRef a_src, S16ImageRef a_binImg)
	{
		/*		S16ImageRef ret2 = GenCvDilateImg(
					GenCenterPixImg(
					a_src->GetSize(), a_src->GetNofChannels() ),
					5 );

					HCV_CALL(
					cvRectangle(
					ret2->GetIplImagePtr(),
					cvPoint(50, 50),
					cvPoint( 150, 150),
					CV_RGB(255, 255, 255),
					-1)
					);

					return ret2;*/

		S16ImageRef ret = S16Image::Create(
			a_src->GetSize(), a_src->GetNofChannels());

		HCV_CALL(cvConvertScale(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr(),
			//255 / (nMax - nMin), 
			//- nMin) );
			//0.75, 50) );
			1, 0));

		//cvSetCOI( ret->GetIplImagePtr() , 1 );

		//double dMin, dMax;
		//HCV_CALL( cvMinMaxLoc( ret->GetIplImagePtr(), &dMin, &dMax) );


		S16ChannelRef binCh = a_binImg->GetAt(0);

		for (int ch = 0; ch < ret->GetNofChannels(); ch++)
		{
			S16ChannelRef retCh = ret->GetAt(ch);

			for (int y = 0; y < retCh->GetHeight(); y++)
			{
				for (int x = 0; x < retCh->GetWidth(); x++)
				{
					if (1 >= binCh->GetAt(x, y))
						retCh->SetAt(x, y, 0);
				}
			}
		}


		return ret;
		//return a_src;
	}





	void NormalizeEdgeDirImages(F32ImageRef a_gradMagX, F32ImageRef a_gradMagY,
		float a_normVal)
	{
		F32ChannelRef gradCh0X = a_gradMagX->GetAt(0);
		F32ChannelRef gradCh0Y = a_gradMagY->GetAt(0);

		for (int y = 0; y < gradCh0X->GetHeight(); y++)
		{
			for (int x = 0; x < gradCh0X->GetWidth(); x++)
			{
				double nValOrgX = gradCh0X->GetAt(x, y);
				double nValOrgY = gradCh0Y->GetAt(x, y);

				//double orgTot = nValOrgX + nValOrgY;
				double orgTot = sqrt((double)Sqr(nValOrgX) +
					Sqr(nValOrgY));

				double modRatio;

				if (orgTot > 0)
					modRatio = a_normVal / orgTot;
				else
					modRatio = 0;

				gradCh0X->SetAt(x, y, nValOrgX * modRatio);
				gradCh0Y->SetAt(x, y, nValOrgY * modRatio);
			}
		}

	}














	S16ImageRef GenColorEdgeDirImg(S16ImageRef a_gradMagX,
		S16ImageRef a_gradMagY, S16ImageRef a_maskImg)
	{
		float inCnt = 0;
		float outCnt = 0;

		S16ImageRef ret = S16Image::Create(
			a_gradMagX->GetSize(), 3);

		S16ChannelRef retCh0 = ret->GetAt(0);
		S16ChannelRef retCh1 = ret->GetAt(1);
		S16ChannelRef retCh2 = ret->GetAt(2);

		S16ChannelRef gradCh0X = a_gradMagX->GetAt(0);
		S16ChannelRef gradCh0Y = a_gradMagY->GetAt(0);

		S16ChannelRef maskCh0 = a_maskImg->GetAt(0);


		for (int y = 0; y < ret->GetHeight(); y++)
		{
			for (int x = 0; x < ret->GetWidth(); x++)
			{
				retCh0->SetAt(x, y, 0);

				int nMaskVal = maskCh0->GetAt(x, y);

				if (nMaskVal > 1)
					//if(true)
				{
					if (
						0 == gradCh0X->GetAt(x, y) &&
						0 == gradCh0Y->GetAt(x, y))
					{
						outCnt++;
					}
					else
					{
						inCnt++;
					}

					retCh1->SetAt(x, y,
						gradCh0X->GetAt(x, y));

					retCh2->SetAt(x, y,
						gradCh0Y->GetAt(x, y));
				}
				else
				{
					retCh1->SetAt(x, y, 0);
					retCh2->SetAt(x, y, 0);
				}

			}
		}

		return ret;
	}










	S16ImageRef GenWeightImg4(S16ImageRef a_grad1, int a_nDist)
	{
		//a_nDist = 45;

		S16ImageRef ret = S16Image::Create(
			a_grad1->GetSize(), 1);
		S16ChannelRef retCh0 = ret->GetAt(0);

		S16ImageRef grad1Dil = GenCvDilateImg(a_grad1, a_nDist);

		//return grad1Dil;

		S16ImageRef grad1Erode = GenCvErodeImg(a_grad1, a_nDist);

		S16ChannelRef grad1Ch0 = a_grad1->GetAt(0);
		S16ChannelRef grad1DilCh0 = grad1Dil->GetAt(0);
		S16ChannelRef grad1ErodeCh0 = grad1Erode->GetAt(0);




		for (int y = 0; y < grad1DilCh0->GetHeight(); y++)
		{
			for (int x = 0; x < grad1DilCh0->GetWidth(); x++)
			{
				float val = 1;

				int grad1Val = grad1Ch0->GetAt(x, y);
				int grad1DilVal = grad1DilCh0->GetAt(x, y);
				int grad1ErodeVal = grad1ErodeCh0->GetAt(x, y);

				int dilErodeDiff = grad1DilVal - grad1ErodeVal;
				int dilGrad1Diff = grad1DilVal - grad1Val;
				int grad1ErodeDiff = grad1Val - grad1ErodeVal;

				if (
					/*					 //grad1DilVal >= 3 &&
										 grad1Val >= 3 &&
										 (grad1Val * 2) <= grad1DilVal */

										 //grad1Val == grad1ErodeVal &&
										 //dilErodeDiff >= 10

										 //	Org Tested.
										 //( (double)grad1ErodeDiff / dilErodeDiff ) <= 0.0 
										 //&& dilErodeDiff >= 5

										 //( 0.0  == (double)dilGrad1Diff )
										 //&& dilErodeDiff >= 5


										 //(  1 == grad1Val )  
										 //&& dilErodeDiff >= 5



										 //	Edge
										 (grad1Val >= (grad1DilVal * 0.4))
										 && dilErodeDiff >= 5
										 && grad1Val != grad1ErodeVal

										 //&& grad1Val <= 4
										 //&& grad1Val >= 1


										 )
										 val = 255;

				retCh0->SetAt(x, y, val);
			}
		}

		return ret;
	}





	F32ImageRef GenWeightImg3(S16ImageRef a_src, S16ImageRef a_grad1,
		S16ImageRef a_grad2, int a_nDist)
	{
		a_nDist = 5;

		F32ImageRef ret = F32Image::Create(
			a_grad1->GetSize(), 1);
		F32ChannelRef retCh0 = ret->GetAt(0);

		S16ImageRef distGrad1 = GenMorphGradImg(a_src, a_nDist);

		S16ChannelRef grad1Ch0 = a_grad1->GetAt(0);
		S16ChannelRef distGrad1Ch0 = distGrad1->GetAt(0);


		for (int y = 0; y < distGrad1Ch0->GetHeight(); y++)
		{
			for (int x = 0; x < distGrad1Ch0->GetWidth(); x++)
			{
				float val = 1;

				if (distGrad1Ch0->GetAt(x, y) > 10 &&
					grad1Ch0->GetAt(x, y) < 3)
					val = 255;

				retCh0->SetAt(x, y, val);
			}
		}

		return ret;
	}



	S16ImageRef GenWeightImg5(F32ImageRef a_grad1, int a_nDist)
	{
		//a_nDist = 45;

		if (1 != a_grad1->GetNofChannels())
			return nullptr;

		S16ImageRef ret = S16Image::Create(
			a_grad1->GetSize(), 1);
		S16ChannelRef retCh0 = ret->GetAt(0);

		F32ImageRef grad1Dil = GenCvDilateImg(a_grad1, a_nDist);

		F32ImageRef grad1ForErode = a_grad1->Clone();
		{
			F32ChannelRef grad1ForErodeCh0 = grad1ForErode->GetAt(0);

			//const float reqMinVal = 0.1;
			for (int y = 0; y < grad1ForErodeCh0->GetHeight(); y++)
			{
				for (int x = 0; x < grad1ForErodeCh0->GetWidth(); x++)
				{
					float val = grad1ForErodeCh0->GetAt(x, y);

					//if( val < 0.1 )
					//if( val < 1 )
					if (val < 0.0)
						grad1ForErodeCh0->SetAt(x, y, 255);
				}
			}

		}

		F32ImageRef grad1Erode = GenCvErodeImg(grad1ForErode, a_nDist);

		F32ChannelRef grad1Ch0 = a_grad1->GetAt(0);
		F32ChannelRef grad1DilCh0 = grad1Dil->GetAt(0);
		F32ChannelRef grad1ErodeCh0 = grad1Erode->GetAt(0);




		for (int y = 0; y < grad1DilCh0->GetHeight(); y++)
		{
			for (int x = 0; x < grad1DilCh0->GetWidth(); x++)
			{
				float val = 1;

				float grad1Val = grad1Ch0->GetAt(x, y);
				float grad1DilVal = grad1DilCh0->GetAt(x, y);
				float grad1ErodeVal = grad1ErodeCh0->GetAt(x, y);

				float dilErodeDiff = grad1DilVal - grad1ErodeVal;
				float grad1ErodeDiff = grad1Val - grad1ErodeVal;

				if (
					//( grad1Val >= ( grad1DilVal * 0.8 )  )
					//( grad1Val >= ( grad1DilVal * 0.5 )  )
					//( grad1Val >= ( grad1DilVal * 0.4 )  )
					//( grad1Val >= ( grad1DilVal * 0.6 )  )
					(grad1Val >= (grad1DilVal * 1.4))	//	Should not happen
					&& dilErodeDiff >= 5
					//&& grad1Val != grad1ErodeVal
					)
					val = -255;

				if (
					/*					 //grad1DilVal >= 3 &&
										 grad1Val >= 3 &&
										 (grad1Val * 2) <= grad1DilVal */

										 //grad1Val == grad1ErodeVal &&
										 //dilErodeDiff >= 10

										 //	Org Tested.
										 //( (double)grad1ErodeDiff / dilErodeDiff ) <= 0.0 
										 //&& dilErodeDiff >= 5

										 //( (double)grad1ErodeDiff / dilErodeDiff ) <= 0.0 
										 grad1Val == grad1ErodeVal
										 && dilErodeDiff >= 5
										 //&& dilErodeDiff >= 9
										 //&& dilErodeDiff >= 3
										 // && dilErodeDiff >= 45

										 //&& grad1Val <= 4
										 //&& grad1Val >= 1


										 )
										 val = 255;

				retCh0->SetAt(x, y, val);
			}
		}

		return ret;
	}






	F32ImageRef GenWeightImg2(S16ImageRef a_grad1, int a_nDist)
	{
		//a_nDist = 45;

		F32ImageRef ret = F32Image::Create(
			a_grad1->GetSize(), 1);
		F32ChannelRef retCh0 = ret->GetAt(0);

		S16ImageRef grad1Dil = GenCvDilateImg(a_grad1, a_nDist);
		S16ImageRef grad1Erode = GenCvErodeImg(a_grad1, a_nDist);

		S16ChannelRef grad1Ch0 = a_grad1->GetAt(0);
		S16ChannelRef grad1DilCh0 = grad1Dil->GetAt(0);
		S16ChannelRef grad1ErodeCh0 = grad1Erode->GetAt(0);




		for (int y = 0; y < grad1DilCh0->GetHeight(); y++)
		{
			for (int x = 0; x < grad1DilCh0->GetWidth(); x++)
			{
				float val = 1;

				int grad1Val = grad1Ch0->GetAt(x, y);
				int grad1DilVal = grad1DilCh0->GetAt(x, y);
				int grad1ErodeVal = grad1ErodeCh0->GetAt(x, y);

				int dilErodeDiff = grad1DilVal - grad1ErodeVal;
				int grad1ErodeDiff = grad1Val - grad1ErodeVal;

				if (
					//( grad1Val >= ( grad1DilVal * 0.8 )  )
					//( grad1Val >= ( grad1DilVal * 0.5 )  )
					//( grad1Val >= ( grad1DilVal * 0.4 )  )
					//( grad1Val >= ( grad1DilVal * 0.6 )  )
					(grad1Val >= (grad1DilVal * 1.4))	//	Should not happen
					&& dilErodeDiff >= 5
					//&& grad1Val != grad1ErodeVal
					)
					val = -255;

				if (
					/*					 //grad1DilVal >= 3 &&
										 grad1Val >= 3 &&
										 (grad1Val * 2) <= grad1DilVal */

										 //grad1Val == grad1ErodeVal &&
										 //dilErodeDiff >= 10

										 //	Org Tested.
										 //( (double)grad1ErodeDiff / dilErodeDiff ) <= 0.0 
										 //&& dilErodeDiff >= 5

										 ((double)grad1ErodeDiff / dilErodeDiff) <= 0.0
										 && dilErodeDiff >= 5
										 // && dilErodeDiff >= 45

										 //&& grad1Val <= 4
										 //&& grad1Val >= 1


										 )
										 val = 255;

				retCh0->SetAt(x, y, val);
			}
		}

		return ret;
	}



	F32ImageRef GenWeightImg(S16ImageRef a_grad1, S16ImageRef a_grad2)
	{
		F32ImageRef ret = F32Image::Create(
			a_grad2->GetSize(), 1);
		F32ChannelRef retCh0 = ret->GetAt(0);

		S16ChannelRef grad1Ch0 = a_grad1->GetAt(0);
		S16ChannelRef grad2Ch0 = a_grad2->GetAt(0);


		for (int y = 0; y < grad2Ch0->GetHeight(); y++)
		{
			for (int x = 0; x < grad2Ch0->GetWidth(); x++)
			{
				/*				float val = grad2Ch0->GetAt( x, y );

								val = val * val * val * val;
								//val = val * val;
								//val = (int)pow( val, 2);
								//val /= (int)pow( 128, 2);

								if( 0 == val )
								val = 1;

								val = 1;
								if( grad2Ch0->GetAt( x, y ) > 2)
								val = 255;

								if( grad1Ch0->GetAt( x, y ) > 2)
								val = 1;
								*/

				float val = 1;

				int grad1Val = grad1Ch0->GetAt(x, y);
				int grad2Val = grad2Ch0->GetAt(x, y);

				if (
					grad2Val >= 2 &&
					grad1Val <= 2
					//grad2Val >= ( 1 * grad1Val ) &&
					//grad1Val <= 3 
					)
					val = 255;

				retCh0->SetAt(x, y, val);
			}
		}

		return ret;
	}

	S16ImageRef GenFlattenedImg(S16ImageRef a_src, F32ImageRef a_weightImg, int a_nAprSiz)
	{
		S32ImageRef srcByGradImg = S32Image::Create(
			a_src->GetSize(), a_src->GetNofChannels());

		F32ChannelRef gradCh = a_weightImg->GetAt(0);

		const int nSrcWidth = a_src->GetSize().width;
		const int nSrcHeight = a_src->GetSize().height;


		//	Preparing Weight Img.
		/*		for(int ch=0; ch < a_srcGrad->GetNofChannels(); ch++)
				{
				S16ChannelRef srcGradCh = a_srcGrad->GetAt( ch );

				long long nValSum = 0;
				int nValCnt = 0;

				int nMaxVal = 0;

				for(int y=0; y < srcGradCh->GetHeight(); y++)
				{
				for(int x=0; x < srcGradCh->GetWidth(); x++)
				{
				int nVal = srcGradCh->GetAt( x, y );


				//nVal = nVal * nVal * nVal * nVal;
				nVal = nVal * nVal;
				//nVal = (int)pow( nVal, 2);
				//nVal /= (int)pow( 128, 2);

				if( nMaxVal < nVal )
				nMaxVal = nVal;

				if( 0 == nVal )
				nVal = 1;

				nValSum += nVal;

				nValCnt++;

				//if( nVal > 255 )
				//nVal = 255;

				//nVal = 255 - nVal;

				//					if( nVal < 230 )
				//						nVal /= 1000;

				if( 0 == nVal )
				nVal = 1;

				srcGradCh->SetAt(x, y, nVal );
				}
				}
				}*/


		//	Multipling a_src by grad.
		{
			for (int ch = 0; ch < a_src->GetNofChannels(); ch++)
			{
				S16ChannelRef srcCh = a_src->GetAt(ch);
				S32ChannelRef srcByGradCh = srcByGradImg->GetAt(ch);

				for (int y = 0; y < nSrcHeight; y++)
				{
					for (int x = 0; x < nSrcWidth; x++)
					{
						srcByGradCh->SetAt(x, y,
							srcCh->GetAt(x, y) * gradCh->GetAt(x, y));
					}
				}
			}
		}
		//	End of Multipling.

		////////////////////////////////////////////////////////

		S16ImageRef horzImg;
		{
			S16ImageRef ret;

			const int nMarg = a_nAprSiz / 2;

			CvSize srcSiz = a_src->GetSize();
			CvSize retSiz = cvSize(srcSiz.width - 2 * nMarg, srcSiz.height);

			ret = S16Image::Create(retSiz, a_src->GetNofChannels());
			ret->SetAll(0);

			for (int nCh = 0; nCh < a_src->GetNofChannels(); nCh++)
			{
				S16ChannelRef retCh = ret->GetAt(nCh);
				S32ChannelRef srcByGradCh = srcByGradImg->GetAt(nCh);

				for (int y = 0; y < retCh->GetHeight(); y++)
				{
					int nSumSbg = 0;
					int nSumGrad = 0;

					for (int nSrcX = 0; nSrcX < a_nAprSiz; nSrcX++)
					{
						nSumSbg += srcByGradCh->GetAt(nSrcX, y);
						nSumGrad += gradCh->GetAt(nSrcX, y);

					}
					retCh->SetAt(0, y, nSumSbg / nSumGrad);

					int nSrcXSub = 0;
					int nSrcXAdd = a_nAprSiz;

					for (int x = 1; x < retCh->GetWidth(); x++, nSrcXSub++, nSrcXAdd++)
					{
						nSumSbg -= srcByGradCh->GetAt(nSrcXSub, y);
						nSumSbg += srcByGradCh->GetAt(nSrcXAdd, y);

						nSumGrad -= gradCh->GetAt(nSrcXSub, y);
						nSumGrad += gradCh->GetAt(nSrcXAdd, y);

						if (nSumGrad < 70)
							nSumGrad = nSumGrad;

						retCh->SetAt(x, y, nSumSbg / nSumGrad);
					}
				}
			}

			horzImg = ret;

			//	Multipling Horz by grad.
			{
				for (int ch = 0; ch < horzImg->GetNofChannels(); ch++)
				{
					S16ChannelRef srcCh = horzImg->GetAt(ch);
					S32ChannelRef srcByGradCh = srcByGradImg->GetAt(ch);

					for (int y = 0; y < nSrcHeight; y++)
					{
						for (int x = 0; x < nSrcWidth; x++)
						{
							srcByGradCh->SetAt(x, y,
								srcCh->GetAt(x, y) * gradCh->GetAt(x + nMarg, y));
						}
					}
				}
			}
			//	End of Multipling Horz.

		}
		//	End of Horz




		////////////////////////////////////////////////////////////


		//return srcByGradImg;

		S16ImageRef vertImg;
		{
			S16ImageRef src = horzImg;
			S16ImageRef ret;

			const int nMarg = a_nAprSiz / 2;



			CvSize srcSiz = src->GetSize();
			CvSize retSiz = cvSize(srcSiz.width, srcSiz.height - 2 * nMarg);

			ret = S16Image::Create(retSiz, src->GetNofChannels());
			ret->SetAll(0);

			for (int nCh = 0; nCh < src->GetNofChannels(); nCh++)
			{
				S16ChannelRef retCh = ret->GetAt(nCh);
				S32ChannelRef srcByGradCh = srcByGradImg->GetAt(nCh);

				for (int x = 0; x < retCh->GetWidth(); x++)
				{
					int nSumSbg = 0;
					int nSumGrad = 0;

					for (int nSrcY = 0; nSrcY < a_nAprSiz; nSrcY++)
					{
						nSumSbg += srcByGradCh->GetAt(x, nSrcY);
						//nSumGrad += gradCh->GetAt( x, nSrcY);
						nSumGrad += gradCh->GetAt(x + nMarg, nSrcY);

					}
					retCh->SetAt(x, 0, nSumSbg / nSumGrad);
					//retCh->SetAt( x, 0, 
					//	srcByGradCh->GetAt( x, 0) );

					int nSrcYSub = 0;
					int nSrcYAdd = a_nAprSiz;

					for (int y = 1; y < retCh->GetHeight(); y++, nSrcYSub++, nSrcYAdd++)
					{
						nSumSbg -= srcByGradCh->GetAt(x, nSrcYSub);
						nSumSbg += srcByGradCh->GetAt(x, nSrcYAdd);

						//nSumGrad -= gradCh->GetAt( x, nSrcYSub);
						//nSumGrad += gradCh->GetAt( x, nSrcYAdd);

						nSumGrad -= gradCh->GetAt(x + nMarg, nSrcYSub);
						nSumGrad += gradCh->GetAt(x + nMarg, nSrcYAdd);

						retCh->SetAt(x, y, nSumSbg / nSumGrad);
						//retCh->SetAt( x, y, 
						//	srcByGradCh->GetAt( x, y) );
					}
				}
			}

			vertImg = ret;
		}
		//	End of Vert


		return vertImg;
	}




	F32ImageRef GenImageFromChannel(F32ImageRef a_src, int a_nChannel)
	{
		F32ImageRef ret;

		ret = F32Image::Create(a_src->GetSize(), 1);

		F32ChannelRef srcCh = a_src->GetAt(a_nChannel);

		F32ChannelRef retCh0 = ret->GetAt(0);

		for (int y = 0; y < srcCh->GetHeight(); y++)
		{
			for (int x = 0; x < srcCh->GetWidth(); x++)
			{
				float val = srcCh->GetAt(x, y);

				retCh0->SetAt(x, y, val);
			}
		}

		return ret;
	}



	F32ImageRef GenTriChGrayImg(F32ImageRef a_src)
	{
		F32ImageRef ret;

		//ret = F32Image::Create(a_src->GetSize(), a_src->GetNofChannels());
		ret = F32Image::Create(a_src->GetSize(), 3);

		F32ChannelRef srcCh0 = a_src->GetAt(0);
		F32ChannelRef srcCh1;
		F32ChannelRef srcCh2;

		if (3 == a_src->GetNofChannels())
		{
			srcCh1 = a_src->GetAt(1);
			srcCh2 = a_src->GetAt(2);
		}
		else if (1 == a_src->GetNofChannels())
		{
			srcCh1 = srcCh0;
			srcCh2 = srcCh0;
		}
		else
		{
			ThrowNcvException();
		}

		F32ChannelRef retCh0 = ret->GetAt(0);
		F32ChannelRef retCh1 = ret->GetAt(1);
		F32ChannelRef retCh2 = ret->GetAt(2);

		for (int y = 0; y < srcCh0->GetHeight(); y++)
		{
			for (int x = 0; x < srcCh0->GetWidth(); x++)
			{
				float val = (
					srcCh0->GetAt(x, y) * 0.51 +
					srcCh1->GetAt(x, y) * 1.44 +
					srcCh2->GetAt(x, y) * 1.048
					) / 3;

				retCh0->SetAt(x, y, val);
				retCh1->SetAt(x, y, val);
				retCh2->SetAt(x, y, val);
			}
		}

		return ret;

	}


	S16ImageRef GenTriChGrayImg(S16ImageRef a_src)
	{
		S16ImageRef ret;

		ret = S16Image::Create(a_src->GetSize(), a_src->GetNofChannels());

		S16ChannelRef srcCh0 = a_src->GetAt(0);
		S16ChannelRef srcCh1 = a_src->GetAt(1);
		S16ChannelRef srcCh2 = a_src->GetAt(2);

		S16ChannelRef retCh0 = ret->GetAt(0);
		S16ChannelRef retCh1 = ret->GetAt(1);
		S16ChannelRef retCh2 = ret->GetAt(2);

		for (int y = 0; y < srcCh0->GetHeight(); y++)
		{
			for (int x = 0; x < srcCh0->GetWidth(); x++)
			{
				int nVal = (
					srcCh0->GetAt(x, y) * 0.51 +
					srcCh1->GetAt(x, y) * 1.44 +
					srcCh2->GetAt(x, y) * 1.048
					) / 3;

				retCh0->SetAt(x, y, (short)nVal);
				retCh1->SetAt(x, y, (short)nVal);
				retCh2->SetAt(x, y, (short)nVal);
			}
		}

		return ret;

	}




	//SignalOneDimRef GenHorzLineFromImage(S16ImageRef a_src)
	//{
	//	return GenHorzLineFromImage(a_src, a_src->GetHeight() / 2);
	//}


	//SignalOneDimRef GenHorzLineFromImage(S16ImageRef a_src, int a_y, int a_nChannel)
	//{
	//	SignalOneDimRef retSign = new SignalOneDim();

	//	retSign->m_nBgn = 0;

	//	std::vector<int> & rData = retSign->m_data;
	//	rData.resize(a_src->GetWidth());

	//	S16ChannelRef srcCh = a_src->GetAt(a_nChannel);

	//	for (int x = 0; x < srcCh->GetWidth(); x++)
	//		rData[x] = srcCh->GetAt(x, a_y);


	//	return retSign;
	//}



	F32ImageRef GenMorphG1S2Img(F32ImageRef a_src, int a_nAprSiz)
	{
		F32ImageRef img1 = GenMorphGradImg(
			a_src, a_nAprSiz);

		F32ImageRef img2 = GenMorphGradImg(
			img1, a_nAprSiz);

		F32ImageRef img3 = img1->Clone();

		HCV_CALL(
			cvSub(
			img1->GetIplImagePtr(),
			img2->GetIplImagePtr(),
			img3->GetIplImagePtr())
			);

		return img3;
	}


	F32ImageRef GenMorphGradImg(F32ImageRef a_src, int a_nAprSiz)
	{
		F32ImageRef resF32 = a_src;
		const int nAprSiz = a_nAprSiz;


		//F32ImageRef resF32 = GenF32FromS16Image(res);


		/*

		F32ImageRef resMax =  F32Image::Create( resF32->GetSize(),
		resF32->GetNofChannels() );

		F32ImageRef resMin =  F32Image::Create( resF32->GetSize(),
		resF32->GetNofChannels() );

		//int j = ( nAprSiz / 2 ) + 1;
		//int j = ( nAprSiz / 2 );
		int j = nAprSiz;



		for(int i=0; i<1; i++)
		{
		cvDilate( resF32->GetIplImagePtr(),
		resMax->GetIplImagePtr(), 0, j );

		cvErode( resF32->GetIplImagePtr(),
		resMin->GetIplImagePtr(), 0, j );

		}
		*/

		F32ImageRef resMax = GenCvDilateCircleImg(a_src, a_nAprSiz);
		F32ImageRef resMin = GenCvErodeCircleImg(a_src, a_nAprSiz);

		F32ImageRef resDif = F32Image::Create(resF32->GetSize(),
			resF32->GetNofChannels());

		HCV_CALL(
			cvSub(
			resMax->GetIplImagePtr(),
			resMin->GetIplImagePtr(),
			resDif->GetIplImagePtr())
			);

		resF32 = resDif;

		if (3 == resDif->GetNofChannels())
			resF32 = GenMagImgF32(resF32);

		return resF32;
	}






	S16ImageRef GenMorphGradImg(S16ImageRef a_src, int a_nAprSiz)
	{
		S16ImageRef res = a_src;
		const int nAprSiz = a_nAprSiz;


		F32ImageRef resF32 = GenF32FromS16Image(res);

		F32ImageRef resMax = F32Image::Create(resF32->GetSize(),
			resF32->GetNofChannels());

		F32ImageRef resMin = F32Image::Create(resF32->GetSize(),
			resF32->GetNofChannels());

		//int j = ( nAprSiz / 2 ) + 1;
		//int j = ( nAprSiz / 2 );
		int j = nAprSiz;

		/*		{
					CvSize siz1 = cvSize(300, 200);
					F32ImageRef f32img1 = F32Image::Create( siz1 , 3);
					f32img1->SetAll(0);

					F32ImageRef f32img2 = F32Image::Create( siz1 , 3);

					cvDilate( f32img1->GetIplImagePtr(),
					f32img2->GetIplImagePtr(), 0, 5 );
					}*/

		for (int i = 0; i < 1; i++)
		{
			cvDilate(resF32->GetIplImagePtr(),
				resMax->GetIplImagePtr(), 0, j);

			cvErode(resF32->GetIplImagePtr(),
				resMin->GetIplImagePtr(), 0, j);

		}

		F32ImageRef resDif = F32Image::Create(resF32->GetSize(),
			resF32->GetNofChannels());

		HCV_CALL(
			cvSub(
			resMax->GetIplImagePtr(),
			resMin->GetIplImagePtr(),
			resDif->GetIplImagePtr())
			);

		res = GenS16FromF32Image(resDif);

		if (3 == res->GetNofChannels())
			res = GenDifMagImg(res);

		return res;
	}


	void ShowImage(U8ImageRef dsp, const char * a_sWndName)
	{
		ShowImage(dsp->GetIplImagePtr(), a_sWndName);
	}

	void ShowImage(S16ImageRef a_src, const char * a_sWndName)
	{
		U8ImageRef dsp = GenU8FromS16Image(a_src);
		ShowImage(dsp->GetIplImagePtr(), a_sWndName);
	}

	void ShowImage(F32ImageRef a_src, const char * a_sWndName)
	{
		U8ImageRef dsp = GenU8FromF32Image(a_src);
		ShowImage(dsp->GetIplImagePtr(), a_sWndName);
	}

	void SaveImage(S16ImageRef a_src, char * a_sFilePath)
	{
		U8ImageRef dsp = GenU8FromS16Image(a_src);

		//char sFullPath[50] = "E:\\ResPics\\";
		char sFullPath[50] = "E:\\HthmWork\\Lib\\Ncv\\ResPics\\";


		strcat(sFullPath, a_sFilePath);

		//HCV_CALL( cvvSaveImage(a_sFilePath, 
		HCV_CALL(cvvSaveImage(sFullPath,
			//HCV_CALL( cvvSaveImage("e:\\res.jpg", 


			dsp->GetIplImagePtr()));
	}

	void SaveImage(F32ImageRef a_src, char * a_sFilePath)
	{
		U8ImageRef dsp = GenU8FromF32Image(a_src);

		//char sFullPath[50] = "E:\\ResPics\\";
		//char sFullPath[50] = "E:\\HthmWork\\Lib\\Ncv\\ResPics\\";
		//char sFullPath[50] = "E:\\HthmWork\\Lib\\ResPics\\";
		char sFullPath[150] = "E:\\HthmWork\\Computer-Vision\\Car-Dent-Detection\\Images\\";



		strcat(sFullPath, a_sFilePath);

		//HCV_CALL( cvvSaveImage(a_sFilePath, 
		HCV_CALL(cvvSaveImage(sFullPath,
			//HCV_CALL( cvvSaveImage("e:\\res.jpg", 

			dsp->GetIplImagePtr()));
	}

	//S16ImageRef GenImageFromHorzSignal(SignalOneDimRef a_sig, int a_nHeight)
	//{
	//	S16ImageRef ret = S16Image::Create(
	//		cvSize(a_sig->m_data.size(), a_nHeight), 3);

	//	S16ChannelRef retCh0 = ret->GetAt(0);
	//	S16ChannelRef retCh1 = ret->GetAt(1);
	//	S16ChannelRef retCh2 = ret->GetAt(2);

	//	for (int x = 0; x < a_sig->m_data.size(); x++)
	//	{
	//		short nVal = a_sig->m_data[x];

	//		for (int y = 0; y < a_nHeight; y++)
	//		{
	//			retCh0->SetAt(x, y, nVal);
	//			retCh1->SetAt(x, y, nVal);
	//			retCh2->SetAt(x, y, nVal);
	//		}
	//	}

	//	return ret;
	//}

	/////////// aaaaaaaaaaaaaaaaa


	F32ImageRef GenCvErodeCircleImg(F32ImageRef a_src, int a_nAprSiz)
	{
		F32ImageRef ret = F32Image::Create(a_src->GetSize(),
			a_src->GetNofChannels());

		IplConvKernel* pKernel;

		HCV_CALL(
			pKernel = cvCreateStructuringElementEx(
			(a_nAprSiz * 2) + 1,
			(a_nAprSiz * 2) + 1,
			a_nAprSiz,
			a_nAprSiz,
			CV_SHAPE_ELLIPSE,
			nullptr
			)
			);

		HCV_CALL(
			cvErode(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr(), pKernel, 1)
			);

		return ret;
	}



	F32ImageRef GenCvErodeImg(F32ImageRef a_src, int a_nAprSiz)
	{
		return GenCvErodeCircleImg(a_src, a_nAprSiz);

		F32ImageRef ret = F32Image::Create(a_src->GetSize(),
			a_src->GetNofChannels());

		HCV_CALL(
			cvErode(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr(), 0, a_nAprSiz)
			);

		return ret;
	}



	F32ImageRef GenCvDilateCircleImg(F32ImageRef a_src, int a_nAprSiz)
	{
		F32ImageRef ret = F32Image::Create(a_src->GetSize(),
			a_src->GetNofChannels());

		IplConvKernel* pKernel;

		HCV_CALL(
			pKernel = cvCreateStructuringElementEx(
			(a_nAprSiz * 2) + 1,
			(a_nAprSiz * 2) + 1,
			a_nAprSiz,
			a_nAprSiz,
			CV_SHAPE_ELLIPSE,
			nullptr
			)
			);

		HCV_CALL(
			cvDilate(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr(), pKernel, 1)
			);

		return ret;
	}



	F32ImageRef GenCvDilateImg(F32ImageRef a_src, int a_nAprSiz)
	{
		return GenCvDilateCircleImg(a_src, a_nAprSiz);

		F32ImageRef ret = F32Image::Create(a_src->GetSize(),
			a_src->GetNofChannels());

		HCV_CALL(
			cvDilate(a_src->GetIplImagePtr(),
			ret->GetIplImagePtr(), 0, a_nAprSiz)
			);

		return ret;
	}








	/////////// bbbbbbbbbbbbb

	S16ImageRef GenCvErodeCircleImg(S16ImageRef a_src, int a_nAprSiz)
	{
		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		IplConvKernel* pKernel;

		HCV_CALL(
			pKernel = cvCreateStructuringElementEx(
			(a_nAprSiz * 2) + 1,
			(a_nAprSiz * 2) + 1,
			a_nAprSiz,
			a_nAprSiz,
			CV_SHAPE_ELLIPSE,
			nullptr
			)
			);

		HCV_CALL(
			cvErode(srcU8->GetIplImagePtr(),
			retU8->GetIplImagePtr(), pKernel, 1)
			);


		S16ImageRef ret = GenS16FromU8Image(retU8);

		return ret;
	}



	S16ImageRef GenCvErodeImg(S16ImageRef a_src, int a_nAprSiz)
	{
		return GenCvErodeCircleImg(a_src, a_nAprSiz);

		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		HCV_CALL(
			cvErode(srcU8->GetIplImagePtr(),
			retU8->GetIplImagePtr(), 0, a_nAprSiz)
			);


		S16ImageRef ret = GenS16FromU8Image(retU8);

		return ret;
	}



	S16ImageRef GenCvDilateCircleImg(S16ImageRef a_src, int a_nAprSiz)
	{
		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		IplConvKernel* pKernel;

		HCV_CALL(

			pKernel = cvCreateStructuringElementEx(
			(a_nAprSiz * 2) + 1,
			(a_nAprSiz * 2) + 1,
			a_nAprSiz,
			a_nAprSiz,
			CV_SHAPE_ELLIPSE,
			nullptr
			)
			);

		HCV_CALL(
			cvDilate(srcU8->GetIplImagePtr(),
			retU8->GetIplImagePtr(), pKernel, 1)
			);


		S16ImageRef ret = GenS16FromU8Image(retU8);

		return ret;
	}



	S16ImageRef GenCvDilateImg(S16ImageRef a_src, int a_nAprSiz)
	{
		return GenCvDilateCircleImg(a_src, a_nAprSiz);

		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		HCV_CALL(
			cvDilate(srcU8->GetIplImagePtr(),
			retU8->GetIplImagePtr(), 0, a_nAprSiz)
			);


		S16ImageRef ret = GenS16FromU8Image(retU8);

		return ret;
	}



	F32ImageRef GenCvEqualizeHistImg(F32ImageRef a_src)
	{
		U8ImageRef srcU8 = GenU8FromF32Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());


		HCV_CALL(
			cvEqualizeHist(srcU8->GetIplImagePtr(), retU8->GetIplImagePtr())
			);

		F32ImageRef ret = GenF32FromU8Image(retU8);

		return ret;
	}


	F32ImageRef Gen_CovMatNonPure_Img(F32ImageRef a_src, int a_nAprSiz)
	{
		CvSize srcSiz = a_src->GetSize();

		F32ImageRef ret = F32Image::Create(
			srcSiz, 6);

		F32ColorVal * color_Buf = (F32ColorVal *)a_src->GetPixAt(0, 0);

		CovMat * covMat_Buf = (CovMat *)ret->GetPixAt(0, 0);

		int nSize1D = srcSiz.width * srcSiz.height;

		ret->SetAll(0);

		for (int i = 0; i < nSize1D; i++)
		{
			covMat_Buf[i].AddColorVal(color_Buf[i]);
		}

		ret = GenFastAvgImg(ret, a_nAprSiz);

		return ret;
	}


	F32ImageRef Gen_CovMatPure_Img(F32ImageRef a_src, int a_nAprSiz,
		F32ImageRef * a_pMeanImg, F32ColorVal * a_mean_Buf)
	{
		F32ImageRef nonPureImg = Gen_CovMatNonPure_Img(a_src, a_nAprSiz);

		F32ColorVal * mean_Buf = a_mean_Buf;

		F32ImageRef meanImg;

		if (nullptr == a_mean_Buf)
		{
			meanImg = GenFastAvgImg(a_src, a_nAprSiz);

			if (nullptr != a_pMeanImg)
				*a_pMeanImg = meanImg;

			mean_Buf = (F32ColorVal *)meanImg->GetPixAt(0, 0);
		}


		CvSize srcSiz = a_src->GetSize();

		F32ImageRef ret = F32Image::Create(
			srcSiz, 6);



		CovMat * nonPure_Buf = (CovMat *)nonPureImg->GetPixAt(0, 0);

		CovMat * covMat_Buf = (CovMat *)ret->GetPixAt(0, 0);

		int nSize1D = srcSiz.width * srcSiz.height;

		for (int i = 0; i < nSize1D; i++)
		{
			nonPure_Buf[i].CalcPureMat(
				mean_Buf[i], &covMat_Buf[i]);
		}

		return ret;
	}



	F32ImageRef Gen_CovMatMag_Img(F32ImageRef a_src)
	{
		if (6 != a_src->GetNofChannels())
			ThrowNcvException();

		CvSize srcSiz = a_src->GetSize();

		F32ImageRef ret = F32Image::Create(
			srcSiz, 1);

		CovMat * covMat_Buf = (CovMat *)a_src->GetPixAt(0, 0);

		float * mag_Buf = ret->GetPixAt(0, 0);

		int nSize1D = srcSiz.width * srcSiz.height;

		for (int i = 0; i < nSize1D; i++)
		{
			mag_Buf[i] = covMat_Buf[i].CalcMag();
		}

		return ret;
	}



	F32ImageRef GenCvMedianImg(F32ImageRef a_src, int a_nAprSiz)
	{
		U8ImageRef srcU8 = GenU8FromF32Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		HCV_CALL(
			cvSmooth(srcU8->GetIplImagePtr(), retU8->GetIplImagePtr(),
			CV_MEDIAN, a_nAprSiz)
			);


		F32ImageRef ret = GenF32FromU8Image(retU8);

		return ret;
	}



	S16ImageRef GenCvMedianImg(S16ImageRef a_src, int a_nAprSiz)
	{
		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());


		HCV_CALL(
			cvSmooth(srcU8->GetIplImagePtr(), retU8->GetIplImagePtr(),
			CV_MEDIAN, a_nAprSiz)
			);


		S16ImageRef ret = GenS16FromU8Image(retU8);

		return ret;
	}


	S16ImageRef GenCvMedGausImg(S16ImageRef a_src, int a_nAprSiz)
	{
		//S16ImageRef ret = S16Image::Create( a_src->GetSize(),
		//	a_src->GetNofChannels());

		/*		HCV_CALL(
				cvSmooth( a_src->GetIplImagePtr(), ret->GetIplImagePtr(),
				CV_GAUSSIAN, a_nAprSiz)
				//CV_BILATERAL, 30, 5)
				);*/

		int i = 1;

		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		do
		{

			HCV_CALL(
				cvSmooth(srcU8->GetIplImagePtr(), retU8->GetIplImagePtr(),
				//CV_GAUSSIAN, a_nAprSiz)
				//CV_BILATERAL, a_nAprSiz, 0, 30, a_nAprSiz / 2)
				//CV_BILATERAL, a_nAprSiz, 0, 300, 100)
				CV_MEDIAN, a_nAprSiz)
				);

			srcU8 = retU8;

			retU8 = U8Image::Create(srcU8->GetSize(),
				srcU8->GetNofChannels());

			HCV_CALL(
				cvSmooth(srcU8->GetIplImagePtr(), retU8->GetIplImagePtr(),
				//CV_GAUSSIAN, a_nAprSiz)
				CV_GAUSSIAN, (a_nAprSiz - 1) * 2 + 1)
				//CV_BILATERAL, a_nAprSiz, 0, 10, 10)
				//CV_BILATERAL, a_nAprSiz, 0, 50, a_nAprSiz)
				//CV_BILATERAL, a_nAprSiz, 0, 300, 100)
				//CV_MEDIAN, a_nAprSiz)
				);

			i++;
			i = 1000;
		} while (i <= (a_nAprSiz / 2));

		S16ImageRef ret = GenS16FromU8Image(retU8);

		return ret;
	}


	S16ImageRef GenCvSmoothedImg(S16ImageRef a_src, int a_nAprSiz)
	{
		//S16ImageRef ret = S16Image::Create( a_src->GetSize(),
		//	a_src->GetNofChannels());

		/*		HCV_CALL(
				cvSmooth( a_src->GetIplImagePtr(), ret->GetIplImagePtr(),
				CV_GAUSSIAN, a_nAprSiz)
				//CV_BILATERAL, 30, 5)
				);*/

		int i = 1;

		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		U8ImageRef retU8 = U8Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());

		do
		{

			/*			HCV_CALL(
						cvSmooth( srcU8->GetIplImagePtr(), retU8->GetIplImagePtr(),
						//CV_GAUSSIAN, a_nAprSiz)
						//CV_BILATERAL, a_nAprSiz, 0, 30, a_nAprSiz / 2)
						//CV_BILATERAL, a_nAprSiz, 0, 300, 100)
						CV_MEDIAN, a_nAprSiz)
						);

						srcU8 = retU8;*/

			retU8 = U8Image::Create(srcU8->GetSize(),
				srcU8->GetNofChannels());

			HCV_CALL(
				cvSmooth(srcU8->GetIplImagePtr(), retU8->GetIplImagePtr(),
				//CV_GAUSSIAN, a_nAprSiz)
				//CV_GAUSSIAN, (a_nAprSiz - 1) * 2 + 1
				CV_GAUSSIAN, a_nAprSiz
				//CV_BILATERAL, a_nAprSiz, 0, 10, 10)
				//CV_BILATERAL, a_nAprSiz, 0, 50, a_nAprSiz)
				//CV_BILATERAL, a_nAprSiz, 0, 300, 100)
				//CV_MEDIAN, a_nAprSiz)
				));

			i++;
			i = 1000;
		} while (i <= (a_nAprSiz / 2));

		S16ImageRef ret = GenS16FromU8Image(retU8);

		return ret;
	}



	F32ImageRef GenCvSmoothedImg(F32ImageRef a_src, int a_nAprSiz)
	{
		//S16ImageRef ret = S16Image::Create( a_src->GetSize(),
		//	a_src->GetNofChannels());

		/*		HCV_CALL(
				cvSmooth( a_src->GetIplImagePtr(), ret->GetIplImagePtr(),
				CV_GAUSSIAN, a_nAprSiz)
				//CV_BILATERAL, 30, 5)
				);*/

		int i = 1;

		//U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		F32ImageRef retF32 = F32Image::Create(a_src->GetSize(),
			a_src->GetNofChannels());

		do
		{

			/*			HCV_CALL(
						cvSmooth( srcU8->GetIplImagePtr(), retU8->GetIplImagePtr(),
						//CV_GAUSSIAN, a_nAprSiz)
						//CV_BILATERAL, a_nAprSiz, 0, 30, a_nAprSiz / 2)
						//CV_BILATERAL, a_nAprSiz, 0, 300, 100)
						CV_MEDIAN, a_nAprSiz)
						);

						srcU8 = retU8;*/

			//retU8 = U8Image::Create( srcU8->GetSize(),
			//	srcU8->GetNofChannels());

			HCV_CALL(
				cvSmooth(a_src->GetIplImagePtr(), retF32->GetIplImagePtr(),
				//CV_GAUSSIAN, a_nAprSiz)
				//CV_GAUSSIAN, (a_nAprSiz - 1) * 2 + 1
				CV_GAUSSIAN, a_nAprSiz
				//CV_BLUR_NO_SCALE, (a_nAprSiz - 1) * 2 + 1)
				//CV_BILATERAL, a_nAprSiz, 0, 10, 10)
				//CV_BILATERAL, a_nAprSiz, 0, 50, a_nAprSiz)
				//CV_BILATERAL, a_nAprSiz, 0, 300, 100)
				//CV_MEDIAN, a_nAprSiz)
				));

			i++;
			i = 1000;
		} while (i <= (a_nAprSiz / 2));

		//S16ImageRef ret = GenS16FromU8Image( retU8 );

		return retF32;
	}






	S16ImageRef GenCvLaplaceImg(S16ImageRef a_src, int a_nAprSiz)
	{
		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		//U8ImageRef retU8 = U8Image::Create( srcU8->GetSize(),
		//	srcU8->GetNofChannels());

		S16ImageRef ret = S16Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());


		HCV_CALL(
			cvLaplace(srcU8->GetIplImagePtr(),
			ret->GetIplImagePtr(), a_nAprSiz)
			);


		//S16ImageRef ret = GenS16FromU8Image( retU8 );

		return ret;
	}


	S16ImageRef GenCvSobelImg(S16ImageRef a_src,
		int a_xorder, int a_yorder, int a_nAprSiz)
	{
		U8ImageRef srcU8 = GenU8FromS16Image(a_src);

		//U8ImageRef retU8 = U8Image::Create( srcU8->GetSize(),
		//	srcU8->GetNofChannels());

		S16ImageRef ret = S16Image::Create(srcU8->GetSize(),
			srcU8->GetNofChannels());


		HCV_CALL(

			cvSobel(
			srcU8->GetIplImagePtr(),
			ret->GetIplImagePtr(),
			a_xorder,
			a_yorder,
			a_nAprSiz
			);
		);


		//S16ImageRef ret = GenS16FromU8Image( retU8 );

		return ret;
	}


	S16ImageRef GenImageFromChannel(S16ImageRef a_src, int a_nChannel)
	{
		S16ImageRef ret = S16Image::Create(a_src->GetSize(), 1);

		S16ChannelRef srcCh = a_src->GetAt(a_nChannel);
		S16ChannelRef retCh = ret->GetAt(a_nChannel);

		for (int y = 0; y < srcCh->GetHeight(); y++)
		{
			for (int x = 0; x < srcCh->GetWidth(); x++)
			{
				retCh->SetAt(x, y,
					srcCh->GetAt(x, y));
			}
		}

		return ret;
	}




	F32ImageRef GenMultByColorImg(F32ImageRef a_src, F32ColorVal & a_rColor)
	{
		CvSize srcSiz = a_src->GetSize();

		F32ImageRef ret = F32Image::Create(
			srcSiz, a_src->GetNofChannels());

		//		for(int ch = 0; ch < ret->GetNofChannels(); ch++)
		{
			//			F32ChannelRef srcCh = a_src->GetAt( ch );
			//			F32ChannelRef retCh = ret->GetAt( ch );

			for (int y = 0; y < srcSiz.height; y++)
			{
				for (int x = 0; x < srcSiz.width; x++)
				{
					float * srcPix = a_src->GetPixAt(x, y);
					float * retPix = ret->GetPixAt(x, y);

					retPix[0] = srcPix[0] * a_rColor.val0;
					retPix[1] = srcPix[1] * a_rColor.val1;
					retPix[2] = srcPix[2] * a_rColor.val2;
				}
			}
		}

		return ret;
	}



	F32ImageRef GenMultByNumImg(F32ImageRef a_src, float a_num)
	{
		F32ImageRef ret = F32Image::Create(
			a_src->GetSize(), a_src->GetNofChannels());

		for (int ch = 0; ch < ret->GetNofChannels(); ch++)
		{
			F32ChannelRef srcCh = a_src->GetAt(ch);
			F32ChannelRef retCh = ret->GetAt(ch);

			for (int y = 0; y < srcCh->GetHeight(); y++)
			{
				for (int x = 0; x < srcCh->GetWidth(); x++)
				{
					retCh->SetAt(x, y,
						srcCh->GetAt(x, y) * a_num);
				}
			}
		}

		return ret;
	}


	void BalanceImageWithIntensityFactors(F32ImageRef a_img)
	{
		CvSize siz = a_img->GetSize();

		for (int y = 0; y < siz.height; y++)
		{
			for (int x = 0; x < siz.width; x++)
			{
				F32ColorVal * pixColors =
					(F32ColorVal *)a_img->GetPixAt(x, y);

				pixColors->MultSelfByIntensityFactors();
			}
		}
	}


	F32ImageRef GenClipedImg(F32ImageRef a_src, F32Point & a_p1, F32Point & a_p2)
	{
		CvSize siz = cvSize(a_p2.x - a_p1.x + 1, a_p2.y - a_p1.y + 1);


		F32ImageRef ret = F32Image::Create(siz, a_src->GetNofChannels());


		for (int y = 0; y < siz.height; y++)
		{
			for (int x = 0; x < siz.width; x++)
			{
				F32ColorVal * pSrcPix = (F32ColorVal *)a_src->GetPixAt(
					a_p1.x + x, a_p1.y + y);

				F32ColorVal * pDstPix = (F32ColorVal *)ret->GetPixAt(x, y);

				*pDstPix = *pSrcPix;
			}
		}

		return ret;
	}

	bool AreEqualCvSizes(CvSize & rSize1, CvSize & rSize2)
	{
		return (rSize1.width == rSize2.width) && (rSize1.height == rSize2.height);
	}

	//F32ImageRef GenAvgColorsImg(F32ImageRef a_src, F32Point & a_p1, F32Point & a_p2)
	//{
	//	CvSize clipSiz = cvSize(a_p2.x - a_p1.x + 1, a_p2.y - a_p1.y + 1);
	//	int nofPixes = clipSiz.width * clipSiz.height;


	//	ImgDataElm_C7 colorSum;

	//	colorSum.SetZeroVal();


	//	for (int y = a_p1.y; y <= a_p2.y; y++)
	//	{
	//		for (int x = a_p1.x; x <= a_p2.x; x++)
	//		{
	//			F32ColorVal * pSrcPix = (F32ColorVal *)a_src->GetPixAt(
	//				x, y);

	//			ImgDataElm_C7 colorSrc;

	//			colorSrc.SetFrom_F32ColorVal(*pSrcPix);

	//			colorSum.IncBy(colorSrc);

	//			//F32ColorVal * pDstPix = (F32ColorVal *) ret->GetPixAt( x, y );

	//			//*pDstPix = *pSrcPix;
	//		}
	//	}

	//	colorSum.DividSelfBy(nofPixes);


	//	FixedVector< F32ColorVal > & rColorArr =
	//		ImgDataElm_C7::GetDisplayColors();

	//	/*

	//			FixedVector< F32ColorVal > colorArr( 500 );

	//			colorArr.IncSize();
	//			colorArr.GetBack().AssignVal( 255, 0, 0 );

	//			colorArr.IncSize();
	//			colorArr.GetBack().AssignVal( 0, 255, 0 );

	//			colorArr.IncSize();
	//			colorArr.GetBack().AssignVal( 0, 0, 255 );

	//			colorArr.IncSize();
	//			colorArr.GetBack().AssignVal( 255, 255, 0 );

	//			colorArr.IncSize();
	//			colorArr.GetBack().AssignVal( 255, 0, 255 );

	//			colorArr.IncSize();
	//			colorArr.GetBack().AssignVal( 0, 255, 255 );

	//			colorArr.IncSize();
	//			colorArr.GetBack().AssignVal( 255, 255, 255 );
	//			*/


	//	//int nofColors = 3;

	//	CvSize barSiz = cvSize(30, 500);

	//	CvSize retSiz = cvSize(0, 500);
	//	retSiz.width = rColorArr.GetSize() * barSiz.width;
	//	retSiz.width = (retSiz.width < 300) ? 300 : retSiz.width;


	//	F32ImageRef ret = F32Image::Create(retSiz, 3);

	//	ret->SetAll(0);

	//	int nLim = (ImgDataElm_C7::GetNofColors() < rColorArr.GetSize()) ?
	//		ImgDataElm_C7::GetNofColors() : rColorArr.GetSize();


	//	for (int i = 0; i < nLim; i++)
	//	{
	//		F32ColorVal & dspColor = rColorArr[i];

	//		CvPoint p1 = cvPoint(i * barSiz.width, 0);
	//		CvPoint p2 = cvPoint(
	//			p1.x + barSiz.width, colorSum.ColorBuff[i]);


	//		HCV_CALL(
	//			cvRectangle(
	//			ret->GetIplImagePtr(),
	//			p1,
	//			p2,
	//			CV_RGB(dspColor.val2, dspColor.val1, dspColor.val0),
	//			-1)
	//			);


	//	}



	//	return ret;
	//}




	void ThrowNcvException()
	{
		Ncpp::Debug::Assert(false);

		throw "NcvException!";
	}


	//void Try17May10(F32ImageRef a_img)
	//{
	//	CvSize imgSiz = a_img->GetSize();

	//	//std::vector<int> vect1;
	//	//vect1.resize(2000);

	//	FixedVector<int> vect1(2000);


	//	int a;
	//	float f;

	//	std::queue<float> que1;

	//	std::deque<float> deque1;

	//	FixedDeque<int> fd1(1000);

	//	{
	//		for (int i = 0; i < 25; i++)
	//		{
	//			que1.push(70);
	//			fd1.PushBack(70);
	//		}
	//		que1.pop();
	//		que1.pop();
	//	}


	//	for (int y = 0; y < imgSiz.height; y++)
	//	{
	//		for (int x = 0; x < imgSiz.width; x++)
	//		{
	//			for (int i = 0; i < 300; i++)
	//			{
	//				//fd1.PushBack( 70 );
	//				//fd1.PopFront();


	//				vect1[i] = a;
	//				a = vect1[i];

	//				//que1.push( 70 );
	//				//que1.pop();

	//				//deque1.push_back(70);
	//				//deque1.pop_front();

	//			}

	//			//for( int j=0; j < 0; j++ )
	//			//{
	//			//}

	//		}
	//	}





	//}


	void DrawCircle(F32ImageRef a_img, F32Point & a_pt, U8ColorVal a_color, int a_nRadius)
	{
		HCV_CALL(

			cvCircle(
			a_img->GetIplImagePtr(),
			cvPoint(a_pt.x, a_pt.y),
			a_nRadius,
			CV_RGB(a_color.val2, a_color.val1, a_color.val0),
			-1 // CV_FILL
			));

	}



	void BreakAtPoint(F32Point a_p1, F32Point a_refPt, float a_marg)
	{
		if (fabs(a_p1.x - a_refPt.x) <= a_marg &&
			fabs(a_p1.y - a_refPt.y) <= a_marg)
			a_marg = a_marg;
	}


	S32ImageRef GenMinPosDepthImg(int a_nSizeX, int a_nSizeY)
	{
		return GenMinPosDepthImg(cvSize(a_nSizeX, a_nSizeY));
	}

	S32ImageRef GenMinPosDepthImg(CvSize a_siz)
	{
		S32ImageRef ret = S32Image::Create(a_siz, 1);

		for (int y = 0; y < a_siz.height; y++)
		{
			for (int x = 0; x < a_siz.width; x++)
			{
				int nMinDistX;
				{
					int nDistLim = a_siz.width - 1 - x;
					nMinDistX = (x < nDistLim) ? x : nDistLim;
				}

				int nMinDistY;
				{
					int nDistLim = a_siz.height - 1 - y;
					nMinDistY = (y < nDistLim) ? y : nDistLim;
				}

				int nMinDist = (nMinDistX < nMinDistY) ? nMinDistX : nMinDistY;

				*ret->GetPixAt(x, y) = nMinDist;
			}
		}

		return ret;
	}


	void FillCenterOfMassArr(F32ImageRef a_src, int a_nAprSiz,
		FixedVector< F32Point > * a_pPointArr, F32ImageRef * a_pAvgImgRef)
	{
		F32ImageRef src = GenImageFromChannel(a_src, 0);

		Ncpp::Debug::Assert(src->GetNofChannels() == 1);

		FixedVector< F32Point > & rPointArr = *a_pPointArr;

		CvSize srcSiz = a_src->GetSize();

		Ncpp::Debug::Assert(rPointArr.GetSize() == srcSiz.width * srcSiz.height);


		{
			F32ImageRef img0 = F32Image::Create(src->GetSize(), src->GetNofChannels());

			F32ImageRef img1 = src;
			src = img0;

			HCV_CALL(
				cvPow(
				img1->GetIplImagePtr(),
				src->GetIplImagePtr(),
				//				2)
				//				4)
				1)
				);
		}



		/*
				{
				F32ImageRef img0 = F32Image::Create( src->GetSize(), src->GetNofChannels() );

				F32ImageRef img1 = src;
				src = img0;

				HCV_CALL(
				cvMul(
				img1->GetIplImagePtr(),
				img1->GetIplImagePtr(),
				src->GetIplImagePtr())
				);
				}
				*/

		F32ImageRef avgImg = GenFastAvgImg(src, a_nAprSiz);

		const int nAprSizXY = Sqr(a_nAprSiz);

		//F32Point pntTest(187, 189);
		//F32Point pntTest(350, 160);
		F32Point pntTest(286, 175);
		//F32Point pntTest(121, 226);

		F32ImageRef posImgX;
		{
			F32ImageRef massPosImgX = F32Image::Create(srcSiz, 1);

			for (int y = 0; y < srcSiz.height; y++)
			{
				for (int x = 0; x < srcSiz.width; x++)
				{
					float val = *src->GetPixAt(x, y);

					//if( 16 == x && 442 == y )
					//if( srcSiz.width / 2 == x && srcSiz.height / 2 == y )
					if (pntTest.x == x && pntTest.y == y)
						x = x;

					if (255 != val)
						val = val;

					*massPosImgX->GetPixAt(x, y) = val * x;
				}
			}

			posImgX = GenFastAvgImg(massPosImgX, a_nAprSiz);

			//float 

			for (int y = 0; y < srcSiz.height; y++)
			{
				for (int x = 0; x < srcSiz.width; x++)
				{
					const float avgSrcVal = *avgImg->GetPixAt(x, y);
					//const float divFact = avgSrcVal * nAprSizXY;
					const float divFact = avgSrcVal;
					float * pVal = posImgX->GetPixAt(x, y);

					//if( 16 == x && 442 == y )
					//if( srcSiz.width / 2 == x && srcSiz.height / 2 == y )
					if (pntTest.x == x && pntTest.y == y)
						x = x;

					//if( *pVal < 0.01 )
					if (divFact < 0.01)
					{
						if (0 != *pVal)
							x = x;

						*pVal = x;
						continue;
					}

					*pVal /= divFact;

					if (*pVal > 200)
						x = x;
				}
			}
		}


		F32ImageRef posImgY;
		{
			F32ImageRef massPosImgY = F32Image::Create(srcSiz, 1);

			for (int y = 0; y < srcSiz.height; y++)
			{
				for (int x = 0; x < srcSiz.width; x++)
				{
					float val = *src->GetPixAt(x, y);

					if (pntTest.x == x && pntTest.y == y)
						y = y;

					*massPosImgY->GetPixAt(x, y) = val * y;
				}
			}

			posImgY = GenFastAvgImg(massPosImgY, a_nAprSiz);

			for (int y = 0; y < srcSiz.height; y++)
			{
				for (int x = 0; x < srcSiz.width; x++)
				{
					const float divFact = *avgImg->GetPixAt(x, y);
					float * pVal = posImgY->GetPixAt(x, y);

					if (pntTest.x == x && pntTest.y == y)
						y = y;

					//if( *pVal < 0.01 )
					if (divFact < 0.01)
					{
						if (0 != *pVal)
							y = y;

						*pVal = y;
						continue;
					}

					*pVal /= divFact;
				}
			}
		}



		{
			float * posX_Arr = posImgX->GetPixAt(0, 0);
			float * posY_Arr = posImgY->GetPixAt(0, 0);

			for (int i = 0; i < rPointArr.GetSize(); i++)
			{
				rPointArr[i].x = posX_Arr[i];
				rPointArr[i].y = posY_Arr[i];
			}
		}


		//a_pPointArr

		if (nullptr != a_pAvgImgRef)
			*a_pAvgImgRef = avgImg;
	}


	void FillSlidePointArr(F32ImageRef a_src, int a_nAprSiz,
		FixedVector< F32Point > * a_pPointArr, F32ImageRef * a_pAvgImgRef)
	{
		{
			int nMod = (a_nAprSiz - 1) % 4;

			if (nMod > 0)
			{
				a_nAprSiz += 4 - nMod;
			}
		}

		Ncpp::Debug::Assert(a_nAprSiz >= 5 && ((a_nAprSiz - 1) % 4 == 0));

		F32ImageRef src = GenImageFromChannel(a_src, 0);

		Ncpp::Debug::Assert(src->GetNofChannels() == 1);

		/*
				{
				F32ImageRef img0 = F32Image::Create( src->GetSize(), src->GetNofChannels() );

				F32ImageRef img1 = src;
				src = img0;

				HCV_CALL(
				cvPow(
				img1->GetIplImagePtr(),
				src->GetIplImagePtr(),
				//				2)
				4)
				//				1)
				);
				}
				*/



		FixedVector< F32Point > & rPointArr = *a_pPointArr;

		CvSize srcSiz = a_src->GetSize();

		Ncpp::Debug::Assert(rPointArr.GetSize() == srcSiz.width * srcSiz.height);


		const int nInrSize = (a_nAprSiz + 1) / 2;
		//const int nInrStep = (nInrSize - 1) / 2;
		const int nInrStep = a_nAprSiz / 2;

		const int nMarg = a_nAprSiz / 2 + 1;

		//F32ImageRef avgImg = GenFastAvgImg( src, a_nAprSiz );
		//F32ImageRef avgImg = GenFastAvgImg( src, nInrSize );

		src = GenFastAvgImg(src, nInrSize);

		//ShowImage( src, "srcTry" );


		//F32Point pntTest(187, 189);
		//F32Point pntTest(350, 160);
		//F32Point pntTest(286, 175);
		//F32Point pntTest(121, 226);
		//F32Point pntTest(257, 266);
		F32Point pntTest(134, 247);


		F32ImageRef posImgX = F32Image::Create(srcSiz, 1);
		//FillBorder( posImgX->GetAt(0), (float)0, nMarg );

		F32ImageRef posImgY = F32Image::Create(srcSiz, 1);
		//FillBorder( posImgY->GetAt(0), (float)0, nMarg );

		{
			int x, y;

			for (y = 0; y < nMarg; y++)
			for (x = 0; x < srcSiz.width; x++)
			{
				*posImgX->GetPixAt(x, y) = x;
				*posImgY->GetPixAt(x, y) = y;
			}

			for (y = srcSiz.height - 1 - nMarg; y < srcSiz.height; y++)
			for (x = 0; x < srcSiz.width; x++)
			{
				*posImgX->GetPixAt(x, y) = x;
				*posImgY->GetPixAt(x, y) = y;
			}

			for (x = 0; x < nMarg; x++)
			for (y = 0; y < srcSiz.height; y++)
			{
				*posImgX->GetPixAt(x, y) = x;
				*posImgY->GetPixAt(x, y) = y;
			}

			for (x = srcSiz.width - 1 - nMarg; x < srcSiz.width; x++)
			for (y = 0; y < srcSiz.height; y++)
			{
				*posImgX->GetPixAt(x, y) = x;
				*posImgY->GetPixAt(x, y) = y;
			}

		}


		static int dxArr[] = { 1, 1, 0, -1 };
		static int dyArr[] = { 0, 1, 1, 1 };

		const int nDirArrSiz = sizeof(dxArr) / sizeof(int);


		for (int y = nMarg; y < srcSiz.height - nMarg; y++)
		{
			for (int x = nMarg; x < srcSiz.width - nMarg; x++)
			{
				float val = *src->GetPixAt(x, y);

				float sumAbsVal = 0;
				float sumXVal = 0;
				float sumYVal = 0;

				if (pntTest.x == x && pntTest.y == y)
					x = x;

				int valArr[9];
				int i = 0;

				/*
								for( int k=0; k < nDirArrSiz; k++ )
								{
								const int dx = dxArr[ k ];
								const int dy = dyArr[ k ];

								const int nSrcX = x + dx * nInrStep;
								const int nSrcY = y + dy * nInrStep;

								const int nOpSrcX = x - dx * nInrStep;
								const int nOpSrcY = y - dy * nInrStep;

								//const float inrVal = *src->GetPixAt( nSrcX, nSrcY );

								const float inrVal = *src->GetPixAt( nSrcX, nSrcY );
								const float inrOpVal = *src->GetPixAt( nOpSrcX, nOpSrcY );

								//const float subVal = val - inrVal;
								const float subVal = ( inrVal - val ) + ( val - inrOpVal );

								valArr[ i++ ] = inrVal * 100;

								sumAbsVal += fabs( subVal );

								sumXVal += ( nSrcX - x ) * subVal;
								sumYVal += ( nSrcY - y ) * subVal;



								}
								*/


				for (int nSrcY = y - nInrStep; nSrcY <= y + nInrStep; nSrcY += nInrStep)
				{
					for (int nSrcX = x - nInrStep; nSrcX <= x + nInrStep; nSrcX += nInrStep)
					{
						const float inrVal = *src->GetPixAt(nSrcX, nSrcY);

						//const float subVal = val - inrVal;						
						float subVal = val - inrVal;

						if (subVal < 0)
							subVal = 0;

						valArr[i++] = inrVal * 100;

						//sumAbsVal += fabs( subVal );
						sumAbsVal += subVal;

						sumXVal += (x - nSrcX) * subVal;
						sumYVal += (y - nSrcY) * subVal;
					}
				}



				int nDstX;
				int nDstY;

				if (sumAbsVal > 0.1)
				{
					nDstX = x - sumXVal / sumAbsVal;
					nDstY = y - sumYVal / sumAbsVal;

					//F32Point sumPnt( sumXVal, sumYVal );
					//sumPnt.DividSelfBy( sumPnt.CalcMag() * 0.5 );

					//nDstX = x - sumPnt.x;
					//nDstY = y - sumPnt.y;
				}
				else
				{
					nDstX = x;
					nDstY = y;
				}

				float oldDstVal = *src->GetPixAt(nDstX, nDstY);

				*posImgX->GetPixAt(x, y) = nDstX;
				*posImgY->GetPixAt(x, y) = nDstY;

				if (pntTest.x == x && pntTest.y == y)
					x = x;
			}
		}




		/*
				const int nAprSizXY = Sqr( a_nAprSiz );

				F32ImageRef posImgX;
				{
				F32ImageRef massPosImgX = F32Image::Create( srcSiz, 1 );

				for( int y=0; y < srcSiz.height; y++ )
				{
				for( int x=0; x < srcSiz.width; x++ )
				{
				float val = *src->GetPixAt( x, y );

				//if( 16 == x && 442 == y )
				//if( srcSiz.width / 2 == x && srcSiz.height / 2 == y )
				if( pntTest.x == x && pntTest.y == y )
				x = x;

				if( 255 != val )
				val = val;

				*massPosImgX->GetPixAt( x, y ) = val * x;
				}
				}

				posImgX = GenFastAvgImg( massPosImgX, a_nAprSiz );

				//float

				for( int y=0; y < srcSiz.height; y++ )
				{
				for( int x=0; x < srcSiz.width; x++ )
				{
				const float avgSrcVal = *avgImg->GetPixAt( x, y );
				//const float divFact = avgSrcVal * nAprSizXY;
				const float divFact = avgSrcVal;
				float * pVal = posImgX->GetPixAt( x, y );

				//if( 16 == x && 442 == y )
				//if( srcSiz.width / 2 == x && srcSiz.height / 2 == y )
				if( pntTest.x == x && pntTest.y == y )
				x = x;

				//if( *pVal < 0.01 )
				if( divFact < 0.01 )
				{
				if( 0 != *pVal )
				x = x;

				*pVal = x;
				continue;
				}

				*pVal /= divFact;

				if( *pVal > 200 )
				x = x;
				}
				}
				}


				F32ImageRef posImgY;
				{
				F32ImageRef massPosImgY = F32Image::Create( srcSiz, 1 );

				for( int y=0; y < srcSiz.height; y++ )
				{
				for( int x=0; x < srcSiz.width; x++ )
				{
				float val = *src->GetPixAt( x, y );

				if( pntTest.x == x && pntTest.y == y )
				y = y;

				*massPosImgY->GetPixAt( x, y ) = val * y;
				}
				}

				posImgY = GenFastAvgImg( massPosImgY, a_nAprSiz );

				for( int y=0; y < srcSiz.height; y++ )
				{
				for( int x=0; x < srcSiz.width; x++ )
				{
				const float divFact = *avgImg->GetPixAt( x, y );
				float * pVal = posImgY->GetPixAt( x, y );

				if( pntTest.x == x && pntTest.y == y )
				y = y;

				//if( *pVal < 0.01 )
				if( divFact < 0.01 )
				{
				if( 0 != *pVal )
				y = y;

				*pVal = y;
				continue;
				}

				*pVal /= divFact;
				}
				}
				}
				*/


		{
			float * posX_Arr = posImgX->GetPixAt(0, 0);
			float * posY_Arr = posImgY->GetPixAt(0, 0);

			for (int i = 0; i < rPointArr.GetSize(); i++)
			{
				rPointArr[i].x = posX_Arr[i];
				rPointArr[i].y = posY_Arr[i];
			}
		}


		//a_pPointArr

		//if( nullptr != a_pAvgImgRef )
		//	*a_pAvgImgRef = avgImg;
	}









	void FillClimbPointArr(F32ImageRef a_src, int a_nAprSiz,
		FixedVector< F32Point > * a_pPointArr, F32ImageRef * a_pAvgImgRef)
	{
		{
			int nMod = (a_nAprSiz - 1) % 4;

			if (nMod > 0)
			{
				a_nAprSiz += 4 - nMod;
			}
		}

		Ncpp::Debug::Assert(a_nAprSiz >= 5 && ((a_nAprSiz - 1) % 4 == 0));

		F32ImageRef src = GenImageFromChannel(a_src, 0);

		Ncpp::Debug::Assert(src->GetNofChannels() == 1);

		/*
				{
				F32ImageRef img0 = F32Image::Create( src->GetSize(), src->GetNofChannels() );

				F32ImageRef img1 = src;
				src = img0;

				HCV_CALL(
				cvPow(
				img1->GetIplImagePtr(),
				src->GetIplImagePtr(),
				//				2)
				4)
				//				1)
				);
				}
				*/



		FixedVector< F32Point > & rPointArr = *a_pPointArr;

		CvSize srcSiz = a_src->GetSize();

		Ncpp::Debug::Assert(rPointArr.GetSize() == srcSiz.width * srcSiz.height);


		const int nInrSize = (a_nAprSiz + 1) / 2;
		//const int nInrStep = (nInrSize - 1) / 2;
		const int nInrStep = a_nAprSiz / 2;

		const int nMarg = a_nAprSiz / 2 + 1;

		//F32ImageRef avgImg = GenFastAvgImg( src, a_nAprSiz );
		//F32ImageRef avgImg = GenFastAvgImg( src, nInrSize );

		src = GenFastAvgImg(src, nInrSize);

		//ShowImage( src, "srcTry" );


		//F32Point pntTest(187, 189);
		//F32Point pntTest(350, 160);
		//F32Point pntTest(286, 175);
		//F32Point pntTest(121, 226);
		//F32Point pntTest(257, 266);
		//F32Point pntTest(134, 247);
		F32Point pntTest(264, 200);



		F32ImageRef posImgX = F32Image::Create(srcSiz, 1);
		//FillBorder( posImgX->GetAt(0), (float)0, nMarg );

		F32ImageRef posImgY = F32Image::Create(srcSiz, 1);
		//FillBorder( posImgY->GetAt(0), (float)0, nMarg );

		{
			int x, y;

			for (y = 0; y < nMarg; y++)
			for (x = 0; x < srcSiz.width; x++)
			{
				*posImgX->GetPixAt(x, y) = x;
				*posImgY->GetPixAt(x, y) = y;
			}

			for (y = srcSiz.height - 1 - nMarg; y < srcSiz.height; y++)
			for (x = 0; x < srcSiz.width; x++)
			{
				*posImgX->GetPixAt(x, y) = x;
				*posImgY->GetPixAt(x, y) = y;
			}

			for (x = 0; x < nMarg; x++)
			for (y = 0; y < srcSiz.height; y++)
			{
				*posImgX->GetPixAt(x, y) = x;
				*posImgY->GetPixAt(x, y) = y;
			}

			for (x = srcSiz.width - 1 - nMarg; x < srcSiz.width; x++)
			for (y = 0; y < srcSiz.height; y++)
			{
				*posImgX->GetPixAt(x, y) = x;
				*posImgY->GetPixAt(x, y) = y;
			}

		}


		static int dxArr[] = { 1, 1, 0, -1 };
		static int dyArr[] = { 0, 1, 1, 1 };

		const int nDirArrSiz = sizeof(dxArr) / sizeof(int);


		for (int y = nMarg; y < srcSiz.height - nMarg; y++)
		{
			for (int x = nMarg; x < srcSiz.width - nMarg; x++)
			{
				float val = *src->GetPixAt(x, y);

				float sumAbsVal = 0;
				float sumXVal = 0;
				float sumYVal = 0;

				if (pntTest.x == x && pntTest.y == y)
					x = x;

				int valArr[9];
				int i = 0;

				/*
								for( int k=0; k < nDirArrSiz; k++ )
								{
								const int dx = dxArr[ k ];
								const int dy = dyArr[ k ];

								const int nSrcX = x + dx * nInrStep;
								const int nSrcY = y + dy * nInrStep;

								const int nOpSrcX = x - dx * nInrStep;
								const int nOpSrcY = y - dy * nInrStep;

								//const float inrVal = *src->GetPixAt( nSrcX, nSrcY );

								const float inrVal = *src->GetPixAt( nSrcX, nSrcY );
								const float inrOpVal = *src->GetPixAt( nOpSrcX, nOpSrcY );

								//const float subVal = val - inrVal;
								const float subVal = ( inrVal - val ) + ( val - inrOpVal );

								valArr[ i++ ] = inrVal * 100;

								sumAbsVal += fabs( subVal );

								sumXVal += ( nSrcX - x ) * subVal;
								sumYVal += ( nSrcY - y ) * subVal;



								}
								*/


				for (int nSrcY = y - nInrStep; nSrcY <= y + nInrStep; nSrcY += nInrStep)
				{
					for (int nSrcX = x - nInrStep; nSrcX <= x + nInrStep; nSrcX += nInrStep)
					{
						const float inrVal = *src->GetPixAt(nSrcX, nSrcY);

						//const float subVal = val - inrVal;						
						//float subVal = val - inrVal;						
						float subVal = inrVal - val;

						if (subVal < 0)
							//if( subVal > 0 )
							subVal = 0;
						else if (subVal < 0)
							subVal = subVal;

						valArr[i++] = inrVal * 100;

						//sumAbsVal += fabs( subVal );
						sumAbsVal += subVal;

						sumXVal += (x - nSrcX) * subVal;
						sumYVal += (y - nSrcY) * subVal;
					}
				}



				int nDstX;
				int nDstY;

				if (sumAbsVal > 0.1)
				{
					nDstX = x - sumXVal / sumAbsVal;
					nDstY = y - sumYVal / sumAbsVal;

					//nDstX = x + sumXVal / sumAbsVal;
					//nDstY = y + sumYVal / sumAbsVal;
				}
				else
				{
					nDstX = x;
					nDstY = y;
				}

				float oldDstVal = *src->GetPixAt(nDstX, nDstY);

				*posImgX->GetPixAt(x, y) = nDstX;
				*posImgY->GetPixAt(x, y) = nDstY;

				if (pntTest.x == x && pntTest.y == y)
					x = x;
			}
		}




		/*
				const int nAprSizXY = Sqr( a_nAprSiz );

				F32ImageRef posImgX;
				{
				F32ImageRef massPosImgX = F32Image::Create( srcSiz, 1 );

				for( int y=0; y < srcSiz.height; y++ )
				{
				for( int x=0; x < srcSiz.width; x++ )
				{
				float val = *src->GetPixAt( x, y );

				//if( 16 == x && 442 == y )
				//if( srcSiz.width / 2 == x && srcSiz.height / 2 == y )
				if( pntTest.x == x && pntTest.y == y )
				x = x;

				if( 255 != val )
				val = val;

				*massPosImgX->GetPixAt( x, y ) = val * x;
				}
				}

				posImgX = GenFastAvgImg( massPosImgX, a_nAprSiz );

				//float

				for( int y=0; y < srcSiz.height; y++ )
				{
				for( int x=0; x < srcSiz.width; x++ )
				{
				const float avgSrcVal = *avgImg->GetPixAt( x, y );
				//const float divFact = avgSrcVal * nAprSizXY;
				const float divFact = avgSrcVal;
				float * pVal = posImgX->GetPixAt( x, y );

				//if( 16 == x && 442 == y )
				//if( srcSiz.width / 2 == x && srcSiz.height / 2 == y )
				if( pntTest.x == x && pntTest.y == y )
				x = x;

				//if( *pVal < 0.01 )
				if( divFact < 0.01 )
				{
				if( 0 != *pVal )
				x = x;

				*pVal = x;
				continue;
				}

				*pVal /= divFact;

				if( *pVal > 200 )
				x = x;
				}
				}
				}


				F32ImageRef posImgY;
				{
				F32ImageRef massPosImgY = F32Image::Create( srcSiz, 1 );

				for( int y=0; y < srcSiz.height; y++ )
				{
				for( int x=0; x < srcSiz.width; x++ )
				{
				float val = *src->GetPixAt( x, y );

				if( pntTest.x == x && pntTest.y == y )
				y = y;

				*massPosImgY->GetPixAt( x, y ) = val * y;
				}
				}

				posImgY = GenFastAvgImg( massPosImgY, a_nAprSiz );

				for( int y=0; y < srcSiz.height; y++ )
				{
				for( int x=0; x < srcSiz.width; x++ )
				{
				const float divFact = *avgImg->GetPixAt( x, y );
				float * pVal = posImgY->GetPixAt( x, y );

				if( pntTest.x == x && pntTest.y == y )
				y = y;

				//if( *pVal < 0.01 )
				if( divFact < 0.01 )
				{
				if( 0 != *pVal )
				y = y;

				*pVal = y;
				continue;
				}

				*pVal /= divFact;
				}
				}
				}
				*/


		{
			float * posX_Arr = posImgX->GetPixAt(0, 0);
			float * posY_Arr = posImgY->GetPixAt(0, 0);

			for (int i = 0; i < rPointArr.GetSize(); i++)
			{
				rPointArr[i].x = posX_Arr[i];
				rPointArr[i].y = posY_Arr[i];
			}
		}


		//a_pPointArr

		//if( nullptr != a_pAvgImgRef )
		//	*a_pAvgImgRef = avgImg;
	}



	/*
		void DrawValueSignals( FixedVector< float > & a_valArr, FixedVector< U8ColorVal > & a_colorArr )
		{
		Signal1DViewerRef a_sv1 = new Signal1DViewer();

		DrawValueSignals( a_valArr, a_colorArr,
		Signal1DViewerRef a_sv1 );


		ShowImage( sv1.GenDisplayImage(), "ValSig" );
		}
		*/


	//void DrawValueSignals( FixedVector< U8ColorVal > & a_colorArr, a_nValWidth )
	void DrawValueSignals(FixedVector< float > & a_valArr, FixedVector< U8ColorVal > & a_colorArr)
	{
		Ncpp::Debug::Assert(a_valArr.GetSize() == a_colorArr.GetSize());

		FixedVector< float > & valArr = a_valArr;

		{
			const int nScaleW = 800 / valArr.GetSize() + 1;

			Signal1DViewerRef a_sv1 = new Signal1DViewer();
			int i;

			for (int i = 0; i < valArr.GetSize(); i++)
			{
				Signal1DBuilder sb1(1000, i * nScaleW);

				float val = valArr[i];

				for (int k = 0; k < nScaleW; k++)
				{
					sb1.AddValue(val);
				}

				//U8ColorVal color1 = u8ColorVal( val, val, val );
				U8ColorVal color1 = a_colorArr[i];

				a_sv1->AddSignal(sb1.GetResult(), color1);
			}


		}

	}



	//void FillIsEdgeRootArr(F32ImageRef a_src, FixedVector< bool > * a_pIsRootArr)
	//{
	//	FixedVector< bool > & rIsRootArr = *a_pIsRootArr;

	//	for (int i = 0; i < rIsRootArr.GetSize(); i++)
	//		rIsRootArr[i] = 0;

	//	{
	//		CvSize siz1 = a_src->GetSize();
	//		const int nSiz1D = siz1.width * siz1.height;

	//		Ncpp_ASSERT(rIsRootArr.GetSize() == nSiz1D);
	//	}

	//	class IndexLQM : public MultiListQueMember< IndexLQM >
	//	{
	//	public:
	//		int Index;
	//	};

	//	class PixInfo
	//	{
	//	public:
	//		int index;
	//		F32Point pos;
	//		float val;
	//		float avgVal;

	//		PixInfo * pSlidePix;
	//		PixInfo * pAbovePix;

	//		PixInfo * pSlideSrc;

	//		bool bIsEdge;
	//		bool bIsValley;
	//	};




	//	//a_x = 187;
	//	//a_y = 189;

	//	//F32ImageRef src = GenImageFromChannel(			
	//	//	GlobalStuff::GetLinePathImg(), 0 );

	//	//F32ImageRef src = GlobalStuff::GetLinePathImg();
	//	F32ImageRef src = a_src;

	//	src = GenImageFromChannel(src, 0);

	//	CvSize srcSiz = src->GetSize();

	//	const int nSrcSiz1D = srcSiz.width * srcSiz.height;


	//	FixedVector< PixInfo > pixInfoArr;
	//	pixInfoArr.SetSize(nSrcSiz1D);


	//	FixedVector< IndexLQM > indexLQMArr;

	//	indexLQMArr.SetSize(nSrcSiz1D);

	//	float * srcPixPtr = src->GetPixAt(0, 0);

	//	const int nValScale = 10;



	//	MultiListQueMgr< IndexLQM > mlqMgr;
	//	mlqMgr.InitSize(500 * nValScale);

	//	for (int i = 0; i < nSrcSiz1D; i++)
	//	{
	//		IndexLQM & indexLQM = indexLQMArr[i];

	//		indexLQM.Index = i;

	//		float val = srcPixPtr[i];

	//		mlqMgr.PushPtr(val * nValScale, &indexLQM);
	//	}








	//	FixedVector< F32Point > pntArr;
	//	pntArr.SetSize(nSrcSiz1D);

	//	//FillCenterOfMassArr( src, GlobalStuff::AprSize1D, &pntArr );
	//	FillSlidePointArr(src, GlobalStuff::AprSize1D, &pntArr);

	//	Accessor2D< F32Point > acSlide(&pntArr[0], srcSiz.width, srcSiz.height);
	//	Accessor2D< PixInfo > acPixInfo(&pixInfoArr[0], srcSiz.width, srcSiz.height);

	//	F32ImageRef avgImg = GenFastAvgImg(src, GlobalStuff::AprSize1D);



	//	for (int y = 0; y < srcSiz.height; y++)
	//	{
	//		for (int x = 0; x < srcSiz.width; x++)
	//		{
	//			int i = acPixInfo.GetIndex1D(x, y);

	//			PixInfo & rPixInfo = pixInfoArr[i];


	//			rPixInfo.index = i;
	//			rPixInfo.pos = F32Point(x, y);

	//			F32Point & rPnt = acSlide.GetAt(x, y);
	//			F32Point pnt1 = rPnt.Round();

	//			//rPixInfo.pSlidePix = &pixInfoArr[ acSlide.GetIndex1D( pnt1.x, pnt1.y ) ];
	//			rPixInfo.pSlidePix = acPixInfo.GetPtrAt(pnt1.x, pnt1.y);

	//			{
	//				//int nAbvX = x - ( pnt1.x - x );

	//				int nAbvX = 2 * x - pnt1.x;
	//				int nAbvY = 2 * y - pnt1.y;

	//				rPixInfo.pAbovePix = acPixInfo.GetPtrAt(nAbvX, nAbvY);
	//			}

	//			rPixInfo.pSlideSrc = nullptr;

	//			rPixInfo.bIsEdge = false;
	//			rPixInfo.bIsValley = false;

	//			rPixInfo.val = *src->GetPixAt(x, y);
	//			rPixInfo.avgVal = *avgImg->GetPixAt(x, y);
	//		}
	//	}





	//	while (true)
	//	{
	//		IndexLQM * pIlqm = mlqMgr.PopPtrMax();

	//		if (nullptr == pIlqm)
	//			break;

	//		PixInfo * pPI = &pixInfoArr[pIlqm->Index];
	//		PixInfo * pDstPI = pPI->pSlidePix;


	//	}



	//	//F32ImageRef dsp = GenTriChGrayImg( GlobalStuff::GetLinePathImg() );
	//	//F32ImageRef res = F32Image::Create( srcSiz, 3 );

	//	//const F32Point testPnt( 393, 97 );
	//	//const F32Point testPnt( 434, 325 );
	//	const F32Point testPnt(409, 28);


	//	for (int y = 0; y < srcSiz.height; y++)
	//	{
	//		for (int x = 0; x < srcSiz.width; x++)
	//		{
	//			PixInfo * pSrcPI = acPixInfo.GetPtrAt(x, y);
	//			PixInfo * pDstPI = pSrcPI->pSlidePix;

	//			int a = pSrcPI->index;
	//			int b = pDstPI->index;

	//			F32Point & rDstPos = pDstPI->pos;

	//			if (testPnt.x == rDstPos.x && testPnt.y == rDstPos.y)
	//				x = x;

	//			//const float srcVal = *src->GetPixAt( x, y );
	//			const float srcVal = pSrcPI->val;

	//			const float avgSrcVal = *avgImg->GetPixAt(x, y);
	//			//F32Point & rPnt = acSlide.GetAt( x, y );
	//			//F32Point pnt1 = rPnt.Round();


	//			//const float dstVal = *src->GetPixAt( pnt1.x, pnt1.y );
	//			const float dstVal = pDstPI->val;

	//			//const float avgDstVal = *avgImg->GetPixAt( pnt1.x, pnt1.y );
	//			//const float avgDstVal = *avgImg->GetPixAt( pDstPI->pos.x, pDstPI->pos.y );
	//			const float avgDstVal = pDstPI->avgVal;

	//			const float abvVal = pSrcPI->pAbovePix->val;



	//			//F32ColorVal * resPix = (F32ColorVal *) res->GetPixAt( pDstPI->pos.x, pDstPI->pos.y );


	//			//U8ColorVal color1;
	//			F32ColorVal color1;

	//			/*
	//						//if( dstVal < avgDstVal * 0.8 )
	//						if( dstVal <= abvVal
	//						)
	//						{
	//						if( dstVal < abvVal )
	//						color1.AssignVal( 255, 70, 70 );
	//						else if( dstVal == abvVal )
	//						color1.AssignVal( 0, 0, 255 );
	//						else
	//						color1.AssignVal( 0, 0, 0 );
	//						}
	//						else
	//						//color1 = u8ColorVal( 0, 0, 0 );
	//						color1.AssignVal( 0, 0, 0 );
	//						*/



	//			//if( dstVal < avgDstVal * 0.8 )
	//			if (dstVal < avgDstVal * 0.8 &&
	//				dstVal < avgSrcVal
	//				)
	//			{
	//				if (dstVal < srcVal)
	//				{
	//					//color1.AssignVal( 255, 70, 70 );
	//					rIsRootArr[pDstPI->index] = true;
	//				}
	//				else if (dstVal == srcVal)
	//				{
	//					//color1.AssignVal( 0, 0, 255 );
	//					rIsRootArr[pDstPI->index] = true;
	//				}
	//				else
	//				{
	//					//color1.AssignVal( 0, 0, 0 );
	//					rIsRootArr[pDstPI->index] = false;
	//				}
	//			}
	//			else
	//			{
	//				//color1 = u8ColorVal( 0, 0, 0 );
	//				color1.AssignVal(0, 0, 0);
	//				rIsRootArr[pDstPI->index] = false;
	//			}

	//			//hthm tmp
	//			//rIsRootArr[ pDstPI->index ] = true;
	//			//rIsRootArr[ pSrcPI->index ] = true;


	//			//*resPix = color1;





	//		}
	//	}


	//	for (int y = 0; y < srcSiz.height; y++)
	//	{
	//		for (int x = 0; x < srcSiz.width; x++)
	//		{
	//			PixInfo * pSrcPI = acPixInfo.GetPtrAt(x, y);

	//			if (!rIsRootArr[pSrcPI->index])
	//				x = x;
	//		}
	//	}



	//	//ShowImage( res, "Result" );
	//}


	//void FillIsEdgePeakArr(F32ImageRef a_src, FixedVector< bool > * a_pIsRootArr)
	//{
	//	FixedVector< bool > & rIsRootArr = *a_pIsRootArr;

	//	for (int i = 0; i < rIsRootArr.GetSize(); i++)
	//		rIsRootArr[i] = 0;

	//	{
	//		CvSize siz1 = a_src->GetSize();
	//		const int nSiz1D = siz1.width * siz1.height;

	//		Ncpp_ASSERT(rIsRootArr.GetSize() == nSiz1D);
	//	}

	//	class IndexLQM : public MultiListQueMember< IndexLQM >
	//	{
	//	public:
	//		int Index;
	//	};

	//	class PixInfo
	//	{
	//	public:
	//		int index;
	//		F32Point pos;
	//		float val;
	//		float avgVal;

	//		PixInfo * pSlidePix;
	//		PixInfo * pAbovePix;

	//		PixInfo * pSlideSrc;

	//		bool bIsEdge;
	//		bool bIsValley;
	//	};




	//	//a_x = 187;
	//	//a_y = 189;

	//	//F32ImageRef src = GenImageFromChannel(			
	//	//	GlobalStuff::GetLinePathImg(), 0 );

	//	//F32ImageRef src = GlobalStuff::GetLinePathImg();
	//	F32ImageRef src = a_src;

	//	src = GenImageFromChannel(src, 0);

	//	CvSize srcSiz = src->GetSize();

	//	const int nSrcSiz1D = srcSiz.width * srcSiz.height;


	//	FixedVector< PixInfo > pixInfoArr;
	//	pixInfoArr.SetSize(nSrcSiz1D);


	//	FixedVector< IndexLQM > indexLQMArr;

	//	indexLQMArr.SetSize(nSrcSiz1D);

	//	float * srcPixPtr = src->GetPixAt(0, 0);

	//	const int nValScale = 10;



	//	MultiListQueMgr< IndexLQM > mlqMgr;
	//	mlqMgr.InitSize(500 * nValScale);

	//	for (int i = 0; i < nSrcSiz1D; i++)
	//	{
	//		IndexLQM & indexLQM = indexLQMArr[i];

	//		indexLQM.Index = i;

	//		float val = srcPixPtr[i];

	//		mlqMgr.PushPtr(val * nValScale, &indexLQM);
	//	}








	//	FixedVector< F32Point > pntArr;
	//	pntArr.SetSize(nSrcSiz1D);

	//	//FillCenterOfMassArr( src, GlobalStuff::AprSize1D, &pntArr );
	//	//FillSlidePointArr( src, GlobalStuff::AprSize1D, &pntArr );
	//	FillClimbPointArr(src, GlobalStuff::AprSize1D, &pntArr);

	//	Accessor2D< F32Point > acSlide(&pntArr[0], srcSiz.width, srcSiz.height);
	//	Accessor2D< PixInfo > acPixInfo(&pixInfoArr[0], srcSiz.width, srcSiz.height);

	//	F32ImageRef avgImg = GenFastAvgImg(src, GlobalStuff::AprSize1D);



	//	for (int y = 0; y < srcSiz.height; y++)
	//	{
	//		for (int x = 0; x < srcSiz.width; x++)
	//		{
	//			int i = acPixInfo.GetIndex1D(x, y);

	//			PixInfo & rPixInfo = pixInfoArr[i];


	//			rPixInfo.index = i;
	//			rPixInfo.pos = F32Point(x, y);

	//			F32Point & rPnt = acSlide.GetAt(x, y);
	//			F32Point pnt1 = rPnt.Round();

	//			//rPixInfo.pSlidePix = &pixInfoArr[ acSlide.GetIndex1D( pnt1.x, pnt1.y ) ];
	//			rPixInfo.pSlidePix = acPixInfo.GetPtrAt(pnt1.x, pnt1.y);

	//			{
	//				//int nAbvX = x - ( pnt1.x - x );

	//				int nAbvX = 2 * x - pnt1.x;
	//				int nAbvY = 2 * y - pnt1.y;

	//				rPixInfo.pAbovePix = acPixInfo.GetPtrAt(nAbvX, nAbvY);
	//			}

	//			rPixInfo.pSlideSrc = nullptr;

	//			rPixInfo.bIsEdge = false;
	//			rPixInfo.bIsValley = false;

	//			rPixInfo.val = *src->GetPixAt(x, y);
	//			rPixInfo.avgVal = *avgImg->GetPixAt(x, y);
	//		}
	//	}





	//	while (true)
	//	{
	//		IndexLQM * pIlqm = mlqMgr.PopPtrMax();

	//		if (nullptr == pIlqm)
	//			break;

	//		PixInfo * pPI = &pixInfoArr[pIlqm->Index];
	//		PixInfo * pDstPI = pPI->pSlidePix;


	//	}



	//	//F32ImageRef dsp = GenTriChGrayImg( GlobalStuff::GetLinePathImg() );
	//	//F32ImageRef res = F32Image::Create( srcSiz, 3 );

	//	//const F32Point testPnt( 393, 97 );
	//	const F32Point testPnt(434, 325);


	//	for (int y = 0; y < srcSiz.height; y++)
	//	{
	//		for (int x = 0; x < srcSiz.width; x++)
	//		{
	//			PixInfo * pSrcPI = acPixInfo.GetPtrAt(x, y);
	//			PixInfo * pDstPI = pSrcPI->pSlidePix;

	//			int a = pSrcPI->index;
	//			int b = pDstPI->index;

	//			F32Point & rDstPos = pDstPI->pos;

	//			if (testPnt.x == rDstPos.x && testPnt.y == rDstPos.y)
	//				x = x;

	//			//const float srcVal = *src->GetPixAt( x, y );
	//			const float srcVal = pSrcPI->val;

	//			const float avgSrcVal = *avgImg->GetPixAt(x, y);
	//			//F32Point & rPnt = acSlide.GetAt( x, y );
	//			//F32Point pnt1 = rPnt.Round();


	//			//const float dstVal = *src->GetPixAt( pnt1.x, pnt1.y );
	//			const float dstVal = pDstPI->val;

	//			//const float avgDstVal = *avgImg->GetPixAt( pnt1.x, pnt1.y );
	//			//const float avgDstVal = *avgImg->GetPixAt( pDstPI->pos.x, pDstPI->pos.y );
	//			const float avgDstVal = pDstPI->avgVal;

	//			const float abvVal = pSrcPI->pAbovePix->val;



	//			//F32ColorVal * resPix = (F32ColorVal *) res->GetPixAt( pDstPI->pos.x, pDstPI->pos.y );


	//			//U8ColorVal color1;
	//			F32ColorVal color1;

	//			/*
	//						//if( dstVal < avgDstVal * 0.8 )
	//						if( dstVal <= abvVal
	//						)
	//						{
	//						if( dstVal < abvVal )
	//						color1.AssignVal( 255, 70, 70 );
	//						else if( dstVal == abvVal )
	//						color1.AssignVal( 0, 0, 255 );
	//						else
	//						color1.AssignVal( 0, 0, 0 );
	//						}
	//						else
	//						//color1 = u8ColorVal( 0, 0, 0 );
	//						color1.AssignVal( 0, 0, 0 );
	//						*/



	//			//if( dstVal < avgDstVal * 0.8 )

	//			//if( dstVal < avgDstVal * 0.8 &&
	//			//dstVal < avgSrcVal 

	//			if (dstVal > avgDstVal * 1 &&
	//				dstVal > avgSrcVal
	//				)
	//			{
	//				//if( dstVal < srcVal )
	//				if (dstVal > srcVal)
	//				{
	//					//color1.AssignVal( 255, 70, 70 );
	//					rIsRootArr[pDstPI->index] = true;
	//				}
	//				/*else if( dstVal == srcVal )
	//				{
	//				//color1.AssignVal( 0, 0, 255 );
	//				rIsRootArr[ pDstPI->index ] = true;
	//				}*/
	//				else
	//				{
	//					//color1.AssignVal( 0, 0, 0 );
	//					rIsRootArr[pDstPI->index] = false;
	//				}
	//			}
	//			else
	//			{
	//				//color1 = u8ColorVal( 0, 0, 0 );
	//				//color1.AssignVal( 0, 0, 0 );
	//				rIsRootArr[pDstPI->index] = false;
	//			}



	//			//*resPix = color1;





	//		}
	//	}


	//	//ShowImage( res, "Result" );
	//}







	float CalcColorUnitDif(F32ColorVal & a_c1, F32ColorVal & a_c2)
	{
		F32ColorVal uc1 = a_c1.IncLessToNum(40).GetUnitVect();
		F32ColorVal uc2 = a_c2.IncLessToNum(40).GetUnitVect();

		float unitDif = F32ColorVal::Sub(uc1, uc2).CalcMag();

		return unitDif;
	}



	F32Point GetPntOfIndex(int a_nIndex, CvSize a_siz)
	{
		F32Point retPnt;

		retPnt.x = a_nIndex % a_siz.width;
		retPnt.y = a_nIndex / a_siz.width;

		return retPnt;
	}



}