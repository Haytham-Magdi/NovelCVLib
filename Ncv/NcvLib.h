#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\VectorVal.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\OpenCVKillers.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <NovelCVLib\Ncv\OpenCV\PixelTypes.h>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>
#include <NovelCVLib\Ncv\OpenCV\funcs1.h>
//#include <NovelCVLib\Ncv\ConvKernel.h>
#include <NovelCVLib\Ncv\OpenCV\Hsv.h>
//#include <NovelCVLib\Ncv\HistoGram.h>
#include <NovelCVLib\Ncv\InitLib.h>
//#include <NovelCVLib\Ncv\RegionSegmentor.h>
//#include <NovelCVLib\Ncv\RegionSegmentor2.h>
//#include <NovelCVLib\Ncv\RegionSegmentor3.h>
//#include <NovelCVLib\Ncv\RegionSegmentor4.h>
//#include <NovelCVLib\Ncv\RegionSegmentor5.h>
//#include <NovelCVLib\Ncv\RegionSegmentor6.h>
//#include <NovelCVLib\Ncv\RegionSegmentor7.h>
//#include <NovelCVLib\Ncv\RegionSegmentor8.h>
//#include <NovelCVLib\Ncv\RegionSegmentor9.h>
//#include <NovelCVLib\Ncv\RegionSegmentor10.h>
//#include <NovelCVLib\Ncv\RegionSegmentor11.h>
//#include <NovelCVLib\Ncv\RegionSegmentor12.h>
//#include <NovelCVLib\Ncv\RegionSegmentor13.h>
//#include <NovelCVLib\Ncv\RegionSegmentor14.h>
//#include <NovelCVLib\Ncv\RegionSegmentor15.h>
//#include <NovelCVLib\Ncv\RegionSegmentor16.h>
//#include <NovelCVLib\Ncv\RegionSegmentor17.h>
//#include <NovelCVLib\Ncv\RegionSegmentor18.h>
//#include <NovelCVLib\Ncv\RegionSegmentor19.h>
//#include <NovelCVLib\Ncv\RegionSegmentor20.h>
//#include <NovelCVLib\Ncv\RegionSegmentor21.h>
//#include <NovelCVLib\Ncv\RegionSegmentor22.h>
//#include <NovelCVLib\Ncv\RegionSegmentor23.h>
//#include <NovelCVLib\Ncv\RegionSegmentor24.h>
//#include <NovelCVLib\Ncv\RegionSegmentor25.h>
//#include <NovelCVLib\Ncv\RegionSegmentor26.h>
//#include <NovelCVLib\Ncv\RegionSegmentor27.h>
//#include <NovelCVLib\Ncv\RegionSegmentor28.h>
//#include <NovelCVLib\Ncv\RegionSegmentor29.h>
//#include <NovelCVLib\Ncv\RegionSegmentor30.h>
//#include <NovelCVLib\Ncv\RegionSegmentor31.h>
//#include <NovelCVLib\Ncv\RegionSegmentor32.h>
//#include <NovelCVLib\Ncv\RegionSegmentor33.h>
//#include <NovelCVLib\Ncv\RegionSegmentor34.h>
//#include <NovelCVLib\Ncv\RegionSegmentor35.h>
//#include <NovelCVLib\Ncv\RegionSegmentor36.h>
//#include <NovelCVLib\Ncv\RegionSegmentor37.h>
//#include <NovelCVLib\Ncv\RegionSegmentor38.h>
//#include <NovelCVLib\Ncv\RegionSegmentor39.h>
//#include <NovelCVLib\Ncv\RegionSegmentor40.h>
//#include <NovelCVLib\Ncv\RegionSegmentor41.h>
//#include <NovelCVLib\Ncv\RegionSegmentor42.h>
//#include <NovelCVLib\Ncv\RegionSegmentor43.h>
//#include <NovelCVLib\Ncv\RegionSegmentor44.h>
//#include <NovelCVLib\Ncv\RegionSegmentor45.h>
//#include <NovelCVLib\Ncv\RegionSegmentor46.h>
//#include <NovelCVLib\Ncv\RegionSegmentor47.h>
//#include <NovelCVLib\Ncv\RegionSegmentor48.h>
//#include <NovelCVLib\Ncv\RegionSegmentor49.h>
//#include <NovelCVLib\Ncv\RegionSegmentor50.h>
//#include <NovelCVLib\Ncv\RegionSegmentor51.h>
//#include <NovelCVLib\Ncv\AdaptiveConv.h>
//#include <NovelCVLib\Ncv\AdaptiveConv2.h>
//#include <NovelCVLib\Ncv\CusteringTries.h>
//#include <NovelCVLib\Ncv\ClusteringMgr.h>
//#include <NovelCVLib\Ncv\ImageClusteringMgr.h>
//#include <NovelCVLib\Ncv\SignalOneDim.h>
//#include <NovelCVLib\Ncv\SobelBuilder.h>
//#include <NovelCVLib\Ncv\PNEdgeBuilder.h>
#include <NovelCVLib\Ncv\IOMgr.h>
//#include <NovelCVLib\Ncv\LinePath.h>
#include <NovelCVLib\Ncv\LinePathInt.h>
#include <NovelCVLib\Ncv\Signal1D.h>
#include <NovelCVLib\Ncv\Signal1DViewer.h>
//#include <NovelCVLib\Ncv\Filter1D.h>
//#include <NovelCVLib\Ncv\ConvFilter1D.h>
//#include <NovelCVLib\Ncv\LinearColorFilter1D.h>
//#include <NovelCVLib\Ncv\LinearAvgFilter1D.h>
//#include <NovelCVLib\Ncv\LinearDiffFilter1D.h>
//#include <NovelCVLib\Ncv\ImageLineViewer.h>
//#include <NovelCVLib\Ncv\ColorFilter1D.h>
//#include <NovelCVLib\Ncv\CompositeColorFilter1D.h>
//#include <NovelCVLib\Ncv\ColorFilter1DSystem.h>
//#include <NovelCVLib\Ncv\AbsFilter1D.h>
//#include <NovelCVLib\Ncv\ScaleFixFilter1D.h>
//#include <NovelCVLib\Ncv\PeakCleanerFilter1D.h>
//#include <NovelCVLib\Ncv\PeakMarkerFilter1D.h>
//#include <NovelCVLib\Ncv\ValleyMaximizerFilter1D.h>
//#include <NovelCVLib\Ncv\ImageLineViewer2.h>
//#include <NovelCVLib\Ncv\ImageLineViewer3.h>
//#include <NovelCVLib\Ncv\SerialColorMgr.h>
//#include <NovelCVLib\Ncv\ConflictScanner.h>
//#include <NovelCVLib\Ncv\ConflictScanner2.h>
//#include <NovelCVLib\Ncv\FiltSysDebug.h>
//#include <NovelCVLib\Ncv\ValleyMarkerFilter1D.h>
//#include <NovelCVLib\Ncv\DiagonalLinePath.h>
//#include <NovelCVLib\Ncv\NegDiagonalLinePath.h>
//#include <NovelCVLib\Ncv\MaxFilter1D.h>
//#include <NovelCVLib\Ncv\BadRootScanner.h>
//#include <NovelCVLib\Ncv\CircleContPath.h>
//#include <NovelCVLib\Ncv\CircleContourOfPix.h>
//#include <NovelCVLib\Ncv\CircleContourOfPix2.h>
//#include <NovelCVLib\Ncv\CircleContourOfPix3.h>
//#include <NovelCVLib\Ncv\CircleContourOfPix4.h>
//#include <NovelCVLib\Ncv\CircleContourOfPix5.h>
#include <NovelCVLib\Ncv\MultiColorSignal1DViewer.h>
//#include <NovelCVLib\Ncv\CircDiff.h>
//#include <NovelCVLib\Ncv\CircDiff2.h>
//#include <NovelCVLib\Ncv\SlideMgr.h>
//#include <NovelCVLib\Ncv\LineStepper.h>
//#include <NovelCVLib\Ncv\LineStepperByAngle.h>
//#include <NovelCVLib\Ncv\ScanDirMgr.h>
//#include <NovelCVLib\Ncv\ImgDataMgr_Simple.h>
//#include <NovelCVLib\Ncv\ImgDataMgr_Simple_2.h>
//#include <NovelCVLib\Ncv\ImgDataMgr_C7.h>
//#include <NovelCVLib\Ncv\ImgDataMgr_CovMat.h>
//#include <NovelCVLib\Ncv\IImgDataMgr.h>
//#include <NovelCVLib\Ncv\ImgDataElm_Simple.h>
//#include <NovelCVLib\Ncv\ScanDirMgrColl.h>
//#include <NovelCVLib\Ncv\SubGradMgr.h>
//#include <NovelCVLib\Ncv\ImgGradMgr.h>
//#include <NovelCVLib\Ncv\ImgGradMgr_2.h>
//#include <NovelCVLib\Ncv\ImgAvgingMgr.h>
//#include <NovelCVLib\Ncv\Avging_ScanDirMgrExt.h>
//#include <NovelCVLib\Ncv\DeltaSignal.h>
//#include <NovelCVLib\Ncv\Filt1D2.h>
//#include <NovelCVLib\Ncv\SingFilt1D2.h>
//#include <NovelCVLib\Ncv\Filt1D2DataMgr.h>
//#include <NovelCVLib\Ncv\AvgFilt1D2.h>
//#include <NovelCVLib\Ncv\Filt1D2System.h>
//#include <NovelCVLib\Ncv\Filt1D2SysProto.h>
//#include <NovelCVLib\Ncv\ScanTryMgr.h>
//#include <NovelCVLib\Ncv\DifFilt1D2.h>
//#include <NovelCVLib\Ncv\PeakMarkerFilt1D2.h>
//#include <NovelCVLib\Ncv\AbsFilt1D2.h>
//#include <NovelCVLib\Ncv\ZeroCrossingFilt1D2.h>
//#include <NovelCVLib\Ncv\MaxFilt1D2.h>
//#include <NovelCVLib\Ncv\EdgeScanMgr.h>
//#include <NovelCVLib\Ncv\EdgeScan.h>
//#include <NovelCVLib\Ncv\ScanTryMgr2.h>
//#include <NovelCVLib\Ncv\ScanTryMgr_3.h>
//#include <NovelCVLib\Ncv\ScanTryMgr_4.h>
//#include <NovelCVLib\Ncv\ScanTryMgr_5.h>
//#include <NovelCVLib\Ncv\ScanTryMgr_6.h>
//#include <NovelCVLib\Ncv\ScanTryMgr_7.h>
//#include <NovelCVLib\Ncv\ScanTryMgr_8.h>
//#include <NovelCVLib\Ncv\ScanTryMgr_9.h>
//#include <NovelCVLib\Ncv\ScanTryDbg.h>
//#include <NovelCVLib\Ncv\ZeroCrossing_2_Filt1D2.h>
//#include <NovelCVLib\Ncv\Ptr_Filt1D2DataMgr.h>
//#include <NovelCVLib\Ncv\ImageWatershedMgr.h>
//#include <NovelCVLib\Ncv\IImgPopulation.h>
//#include <NovelCVLib\Ncv\ImgPopulation_Simple.h>
//#include <NovelCVLib\Ncv\ImgPopulation_C7.h>
//#include <NovelCVLib\Ncv\ImgPopulation_CovMat.h>
//#include <NovelCVLib\Ncv\ImgSegDataMgr.h>
//#include <NovelCVLib\Ncv\ImgSeg_EvalMgr.h>
//#include <NovelCVLib\Ncv\ImgSeg_Method_EvalMgr.h>
//#include <NovelCVLib\Ncv\ImgSeg_GrandMethod_EvalMgr.h>
//#include <NovelCVLib\Ncv\CBIS_Berkeley_Executer.h>
//#include <NovelCVLib\Ncv\PeakMarkerFilt1D2_2.h>
//#include <NovelCVLib\Ncv\RgnSegmDiameter.h>
//#include <NovelCVLib\Ncv\ColorTryMgr.h>
//#include <NovelCVLib\Ncv\ImgDataElm_C7.h>
//#include <NovelCVLib\Ncv\ImgDataElm_C07.h>
//#include <NovelCVLib\Ncv\ImgDataElm_CovMat.h>
//#include <NovelCVLib\Ncv\ImgRotationMgr.h>
//#include <NovelCVLib\Ncv\ImgRotationMgr_3.h>
#include <NovelCVLib\Ncv\ImgSizeRotation.h>
#include <NovelCVLib\Ncv\ImgSizeRotationColl.h>
//#include <NovelCVLib\Ncv\ImageLineItr.h>
//#include <NovelCVLib\Ncv\ImageLineItrProvider.h>
//#include <NovelCVLib\Ncv\ImageItrMgr.h>
//#include <NovelCVLib\Ncv\ImageRotationMgr_Ex.h>
//#include <NovelCVLib\Ncv\IImgDataMgr_2.h>
//#include <NovelCVLib\Ncv\ImgDataMgr_2_CovMat.h>
//#include <NovelCVLib\Ncv\ImageNbrMgr.h>
//#include <NovelCVLib\Ncv\IImgDataGradMgr.h>
//#include <NovelCVLib\Ncv\ImgDataGradMgr_CovMat.h>
//#include <NovelCVLib\Ncv\IImgDataMgr_2_FactorySet.h>
//#include <NovelCVLib\Ncv\ImgDataMgr_2_FactorySet_CovMat.h>
//#include <NovelCVLib\Ncv\ImageRotationMgr_Friend.h>
//#include <NovelCVLib\Ncv\ImgBiMixGrad.h>
//#include <NovelCVLib\Ncv\ImgScanMgr.h>
//#include <NovelCVLib\Ncv\ImgClusteringTry.h>
#include <NovelCVLib\Ncv\ImageAccessor.h>
#include <NovelCVLib\Ncv\Image_Operations.h>
#include <NovelCVLib\Ncv\TempImageAccessor.h>
#include <NovelCVLib\Ncv\Line_Operations.h>
#include <NovelCVLib\Ncv\ImageAccessorOperations.h>
#include <NovelCVLib\Ncv\Element_Operations_VectorVal.h>
#include <NovelCVLib\Ncv\Element_Operations_F32ColorVal.h>
#include <NovelCVLib\Ncv\Element_Operations.h>
#include <NovelCVLib\Ncv\PixelStandevInfo.h>
#include <NovelCVLib\Ncv\ConflictInfo.h>


//#include <NovelCVLib\Ncv\LocHist\ImgDataGradMgr_LocHist.h>
//#include <NovelCVLib\Ncv\LocHist\ImgDataMgr_2_FactorySet_LocHist.h>
//#include <NovelCVLib\Ncv\LocHist\ImgDataMgr_2_LocHist.h>

//#include <NovelCVLib\Ncv\GridColorPalette.h>

//#include <NovelCVLib\Ncv\GridPal\ImgDataGradMgr_GridPal.h>
//#include <NovelCVLib\Ncv\GridPal\ImgDataMgr_2_FactorySet_GridPal.h>
//#include <NovelCVLib\Ncv\GridPal\ImgDataMgr_2_GridPal.h>

//#include <NovelCVLib\Ncv\ImgData_Simple\ImgDataGradMgr_Simple.h>
//#include <NovelCVLib\Ncv\ImgData_Simple\ImgDataMgr_2_FactorySet_Simple.h>
//#include <NovelCVLib\Ncv\ImgData_Simple\ImgDataMgr_2_Simple.h>

#include <NovelCVLib\Ncv\Binarization\ImgAngleDirMgr.h>
#include <NovelCVLib\Ncv\Binarization\AngleDirMgrColl.h>
#include <NovelCVLib\Ncv\Binarization\AngleDirMgrColl_Context.h>
//#include <NovelCVLib\Ncv\Binarization\RotationMgrColl.h>
#include <NovelCVLib\Ncv\Binarization\BinarizationProcess1.h>
#include <NovelCVLib\Ncv\Binarization\PixelInfo_1.h>











