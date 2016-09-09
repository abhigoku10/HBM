#include"BodyMeasurements.h"
#include <fstream>

using namespace GymBodyFitness::Process::Module;


void CBodyMeasurements::PerformMeasurements(cv::vector<cv::Point> v_pLftFeaturePoints,
	int nResizeNumber, double dPixelToMeterFactor, cv::Mat oMatInputImage, string  strImagesFolderPath)
{
	if (v_pLftFeaturePoints.empty() || v_pLftFeaturePoints.size() != 20)
	{
		cout << "Please provide all body feature points" << endl;
	}
	/*vector<SPoint> vpHeadHt(2), vpNeckHt(2), vShoulderToStomachHt(2), vpThightoKneeHt(2), vpKneeToToeHt(2),
		vpShouldetToElbowHt(2), vpElbowToWristHt(2), vpWristToPalmHt(2), vpFullPersonHt(2);
		vector<SPoint> vpShoulderwidth(2), vpChestWidth(2), vpBiceptsWidth(2);*/

	vector<SPoint> v_ptTopHeadPt(1), v_ptBottomHeadTopNeckPt(1), v_ptLeftShoulderPt(1), v_ptBottomNeckCenterShoulderPt(1),
		vPRgtShoulderPt(1), vPLftChestPt(1), vPRgtChestPt(1), vPLftElbowPt(1), vPRgtElbowPt(1), v_ptLftWaistPt(1),
		v_ptRgtWaistpt(1), v_ptLftWristPt(1), v_ptLftHipPt(1), v_ptRgtHipPt(1), v_ptRightWristPt(1),
		v_ptLftKneePt(1), v_ptRgtKneePt(1), v_ptLeftAnklePt(1), v_ptRightAnklePt(1), v_ptEndBodyPt(1);

	vector<float> fAllBodyMeasurementPxl;

	fAllBodyMeasurementPxl.resize(15);
	vector< float > fHeadHgtPxl, fNeckHgtPxl, fShoulderWidthPxl, fChestWidthPxl, fWaistWidthPxl, fHipWidthPxl, fLftArmHgtPxl,
		fRgtArmHgtPxl, fLftWristHghtPxl, fRgtWristHgtPxl, fLftKneeHgtPxl, fLftAnkleHgtPxl, fRgtKneeHgtPxl, fRgtAnkleHgtPxl;


	for (size_t Anatomy = 0; Anatomy < 15; ++Anatomy)
	{
		switch (Anatomy)
		{
		case HEAD_HEIGHT:
		{

							v_ptTopHeadPt[0].x = v_pLftFeaturePoints[0].x * nResizeNumber;
							v_ptTopHeadPt[0].y = v_pLftFeaturePoints[0].y * nResizeNumber;
							v_ptBottomHeadTopNeckPt[0].x = v_pLftFeaturePoints[1].x * nResizeNumber;
							v_ptBottomHeadTopNeckPt[0].y = v_pLftFeaturePoints[1].y * nResizeNumber;

							////performing cropping of segments

							/*	int nHeadHeight = v_ptBottomHeadTopNeckPt[0].y - v_ptTopHeadPt[0].y;
								int nHeadWidth = nHeadHeight/2;
								int nHeadStartptX = v_ptTopHeadPt[0].x - nHeadWidth;
								int nHeadStartptY = v_ptTopHeadPt[0].y;*/


							int nHeadxCordinates = v_pLftFeaturePoints[0].x * nResizeNumber;
							int nHeadyCordinates = v_pLftFeaturePoints[0].y * nResizeNumber;
							int nHeadWidth = abs(nHeadxCordinates - (v_pLftFeaturePoints[1].x * nResizeNumber));
							int nHeadHeight = abs(nHeadyCordinates - (v_pLftFeaturePoints[1].y * nResizeNumber));
							int nHeadCropBoundary = nHeadxCordinates - nHeadHeight;
							int nHeadCropWidth = nHeadHeight * 2;

							//fAllBodyMeasurementPxl.push_back(float(nHeadHeight));
							fAllBodyMeasurementPxl[0] = (float(nHeadHeight));


							//// exception handling of cropping at the boundaries 
							if (nHeadCropBoundary < 0)
							{
								nHeadCropBoundary = 0;
							}
							if (oMatInputImage.cols < (nHeadCropWidth + nHeadCropBoundary))
							{
								nHeadCropWidth = abs(nHeadCropBoundary - oMatInputImage.cols);
							}
							cv::Rect HeadROI((nHeadCropBoundary), (nHeadyCordinates), (nHeadCropWidth), nHeadHeight);
							cv::Mat oMatHeadCropped = oMatInputImage(HeadROI);

							
							cv::imwrite(strImagesFolderPath + "\\Headcropped.jpg", oMatHeadCropped);
							break;
		}

		case NECK_HEIGHT:
		{

							v_ptBottomNeckCenterShoulderPt[0].x = v_pLftFeaturePoints[3].x * nResizeNumber;
							v_ptBottomNeckCenterShoulderPt[0].y = v_pLftFeaturePoints[3].y * nResizeNumber;

							int nNeckHeight = v_ptBottomNeckCenterShoulderPt[0].y - v_ptBottomHeadTopNeckPt[0].y;
							fAllBodyMeasurementPxl[1] = (float(nNeckHeight));

							break;
		}
		case SHOULDER_WIDTH:
		{
							   v_ptLeftShoulderPt[0].x = v_pLftFeaturePoints[2].x * nResizeNumber;
							   v_ptLeftShoulderPt[0].y = v_pLftFeaturePoints[2].y * nResizeNumber;
							   vPRgtShoulderPt[0].x = v_pLftFeaturePoints[4].x * nResizeNumber;
							   vPRgtShoulderPt[0].y = v_pLftFeaturePoints[4].y * nResizeNumber;

							   ////to crop the shoulder width from image 
							   int nShoulderWidth = vPRgtShoulderPt[0].x - v_ptLeftShoulderPt[0].x;
							   int nShoulderHeight = v_ptBottomNeckCenterShoulderPt[0].y - v_ptBottomHeadTopNeckPt[0].y;
							   int nDiff = v_ptBottomNeckCenterShoulderPt[0].x - v_ptLeftShoulderPt[0].x;

							   int nShoulderStartptX = v_ptBottomHeadTopNeckPt[0].x - nDiff;
							   int nShoulderStartptY = v_ptLeftShoulderPt[0].y - nShoulderHeight;

							   fAllBodyMeasurementPxl[2] = (float(nShoulderWidth));


							   cv::Rect ShoulderROI((nShoulderStartptX), (nShoulderStartptY), (nShoulderWidth), nShoulderHeight);
							   cv::Mat oMatShoulderCropped = oMatInputImage(ShoulderROI);
							   cv::imwrite(strImagesFolderPath + "\\ShoulderCropped.jpg", oMatShoulderCropped);


							   break;
		}
		case CHEST_WIDTH:
		{
							vPLftChestPt[0].x = v_pLftFeaturePoints[5].x * nResizeNumber;
							vPLftChestPt[0].y = v_pLftFeaturePoints[5].y * nResizeNumber;
							vPRgtChestPt[0].x = v_pLftFeaturePoints[6].x * nResizeNumber;
							vPRgtChestPt[0].y = v_pLftFeaturePoints[6].y * nResizeNumber;

							////to crop the chest width from image 

							int nChestWidth = vPRgtChestPt[0].x - vPLftChestPt[0].x;
							int nChestHeight = nChestWidth / 2;
							int nChestStartptX = vPLftChestPt[0].x;
							int nChestStartptY = vPLftChestPt[0].y - nChestHeight;

							fAllBodyMeasurementPxl[4] = (float(nChestWidth));

							cv::Rect ChestROI((nChestStartptX), (nChestStartptY), (nChestWidth), nChestHeight * 2);
							cv::Mat oMatChestCropped = oMatInputImage(ChestROI);
							cv::imwrite(strImagesFolderPath + "\\ChestCropped.jpg", oMatChestCropped);





							break;
		}
		case LEFTSHOULDERTOELBOW_HEIGHT:
		{
										   vPLftElbowPt[0].x = v_pLftFeaturePoints[7].x * nResizeNumber;
										   vPLftElbowPt[0].y = v_pLftFeaturePoints[7].y * nResizeNumber;

										   ////to crop the elbow  width from image 

										   int nElbowHeight = vPLftElbowPt[0].y - v_ptLeftShoulderPt[0].y;
										   int nElbowWidth = nElbowHeight / 4;
										   int nElbowStartptX = v_ptLeftShoulderPt[0].y - nElbowWidth;
										   int nElbowStartptY = v_ptLeftShoulderPt[0].y;

										   fAllBodyMeasurementPxl[3] = (float(nElbowHeight));

										   cv::Rect ElbowROI((nElbowStartptX), (nElbowStartptY), (nElbowWidth * 2), nElbowHeight);
										   cv::Mat oMatElbowCropped = oMatInputImage(ElbowROI);
										   cv::imwrite(strImagesFolderPath + "\\LftElbowCropped.jpg", oMatElbowCropped);

										   break;
		}
		case RIGHTSHOULDERTOELBOW_HEIGHT:
		{
											vPRgtElbowPt[0].x = v_pLftFeaturePoints[10].x * nResizeNumber;
											vPRgtElbowPt[0].y = v_pLftFeaturePoints[10].y * nResizeNumber;

											////to crop the elbow  width from image 

											int nRgtElbowHeight = vPRgtElbowPt[0].y - vPRgtShoulderPt[0].y;
											int nRgtElbowWidth = nRgtElbowHeight / 4;
											int nRgtElbowStartptX = vPRgtShoulderPt[0].x - nRgtElbowWidth;
											int nRgtElbowStartptY = vPRgtShoulderPt[0].y;

											fAllBodyMeasurementPxl[5] = (float(nRgtElbowHeight));


											cv::Rect RgtElbowROI((nRgtElbowStartptX), (nRgtElbowStartptY), (nRgtElbowWidth * 2), nRgtElbowHeight);
											cv::Mat oMatRgtElbowCropped = oMatInputImage(RgtElbowROI);
											cv::imwrite(strImagesFolderPath + "\\RgtElbowCropped.jpg", oMatRgtElbowCropped);

											break;
		}
		case LEFTWAISTHIP_HEIGHT:
		{
									v_ptLftWaistPt[0].x = v_pLftFeaturePoints[8].x * nResizeNumber;
									v_ptLftWaistPt[0].y = v_pLftFeaturePoints[8].y * nResizeNumber;

									v_ptRgtWaistpt[0].x = v_pLftFeaturePoints[9].x * nResizeNumber;
									v_ptRgtWaistpt[0].y = v_pLftFeaturePoints[9].y * nResizeNumber;

									////to crop the elbow  width from image 

									int nWaistWidth = v_ptRgtWaistpt[0].x - v_ptLftWaistPt[0].x;
									int nWaistHeight = (v_ptLftWaistPt[0].y - vPLftChestPt[0].y) / 2;
									int nWaistStartptX = v_ptLftWaistPt[0].x;
									int nWaistStartptY = v_ptLftWaistPt[0].y - nWaistHeight;

									fAllBodyMeasurementPxl[6] = (float(nWaistWidth));


									cv::Rect WaistROI((nWaistStartptX), (nWaistStartptY), (nWaistWidth), nWaistHeight * 4);
									cv::Mat oMatWaistCropped = oMatInputImage(WaistROI);
									cv::imwrite(strImagesFolderPath + "\\WaistCropped.jpg", oMatWaistCropped);


									break;
		}
		case RIGHTWAISTHIP_HEIGHT:
		{
									 v_ptLftHipPt[0].x = v_pLftFeaturePoints[12].x * nResizeNumber;
									 v_ptLftHipPt[0].y = v_pLftFeaturePoints[12].y * nResizeNumber;
									 v_ptRgtHipPt[0].x = v_pLftFeaturePoints[13].x * nResizeNumber;
									 v_ptRgtHipPt[0].y = v_pLftFeaturePoints[13].y * nResizeNumber;

									 ////to crop the elbow  width from image 

									 int nHipWidth = v_ptRgtHipPt[0].x - v_ptLftHipPt[0].x;
									 int nHipHeight = (v_ptLftHipPt[0].y - v_ptLftWaistPt[0].y) / 2;
									 int nHipStartptX = v_ptLftHipPt[0].x;
									 int nHipStartptY = v_ptLftHipPt[0].y - nHipHeight;

									 fAllBodyMeasurementPxl[8] = (float(nHipWidth));

									 cv::Rect HipROI((nHipStartptX), (nHipStartptY), (nHipWidth), nHipHeight * 4);
									 cv::Mat oMatHipCropped = oMatInputImage(HipROI);
									 cv::imwrite(strImagesFolderPath + "\\HipCropped.jpg", oMatHipCropped);

									 break;
		}


		case LEFTELBOWTOWRIST_HEIGHT:
		{
										v_ptLftWristPt[0].x = v_pLftFeaturePoints[11].x * nResizeNumber;
										v_ptLftWristPt[0].y = v_pLftFeaturePoints[11].y * nResizeNumber;

										////to crop the elbow  width from image 

										int nLftWristHeight = v_ptLftWristPt[0].y - vPLftElbowPt[0].y;
										int nLftWristWidth = (nLftWristHeight) / 2;
										int nLftWristStartPtX = vPLftElbowPt[0].x - nLftWristWidth;
										int nLftWristStartPtY = vPLftElbowPt[0].y;

										fAllBodyMeasurementPxl[7] = (float(nLftWristHeight));

										cv::Rect LftWristROI((nLftWristStartPtX), (nLftWristStartPtY), (nLftWristWidth * 2), nLftWristHeight);
										cv::Mat oMatWristCropped = oMatInputImage(LftWristROI);
										cv::imwrite(strImagesFolderPath + "\\LftWristCropped.jpg", oMatWristCropped);

										break;
		}
		case RIGHTELBOWTOWRIST_HEIGHT:
		{

										 v_ptRightWristPt[0].x = v_pLftFeaturePoints[14].x * nResizeNumber;
										 v_ptRightWristPt[0].y = v_pLftFeaturePoints[14].y * nResizeNumber;

										 ////to crop the elbow  width from image 

										 int nRgtWristHeight = v_ptRightWristPt[0].y - vPRgtElbowPt[0].y;
										 int nRgtWristWidth = (nRgtWristHeight) / 2;
										 int nRgtWristStartPtX = vPRgtElbowPt[0].x - nRgtWristWidth;
										 int nRgtWristStartPtY = vPRgtElbowPt[0].y;

										 fAllBodyMeasurementPxl[9] = (float(nRgtWristHeight));

										 cv::Rect RgtWristROI((nRgtWristStartPtX), (nRgtWristStartPtY), (nRgtWristWidth * 2), nRgtWristHeight);
										 cv::Mat oMatRgtWristCropped = oMatInputImage(RgtWristROI);
										 cv::imwrite(strImagesFolderPath + "\\RgtWristCropped.jpg", oMatRgtWristCropped);


										 break;
		}
		case LEFTHEAPTOKNEE_HEIGHT:
		{


									  v_ptLftKneePt[0].x = v_pLftFeaturePoints[15].x * nResizeNumber;
									  v_ptLftKneePt[0].y = v_pLftFeaturePoints[15].y * nResizeNumber;

									  ////to crop the elbow  width from image 

									  int nLftKneeHeight = v_ptLftKneePt[0].y - v_ptLftHipPt[0].y;
									  int nLftKneeWidth = nLftKneeHeight / 4;
									  int nLftStartptX = v_ptLftHipPt[0].x - nLftKneeWidth;
									  int nLftStartptY = v_ptLftHipPt[0].y;

									  fAllBodyMeasurementPxl[10] = (float(nLftKneeHeight));


									  cv::Rect LftKneeROI((nLftStartptX), (nLftStartptY), (nLftKneeWidth * 2), nLftKneeHeight);
									  cv::Mat oMatLftKneeCropped = oMatInputImage(LftKneeROI);
									  cv::imwrite(strImagesFolderPath + "\\LftKneeCropped.jpg", oMatLftKneeCropped);



									  break;
		}
		case RIGHTHEAPTOKNEE_HEIGHT:
		{
									   v_ptRgtKneePt[0].x = v_pLftFeaturePoints[16].x * nResizeNumber;
									   v_ptRgtKneePt[0].y = v_pLftFeaturePoints[16].y * nResizeNumber;


									   ////to crop the elbow  width from image 

									   int nRgtKneeHeight = v_ptRgtKneePt[0].y - v_ptRgtHipPt[0].y;
									   int nRgtKneeWidth = nRgtKneeHeight / 4;
									   int nRgtStartptX = v_ptRgtHipPt[0].x - nRgtKneeWidth;
									   int nRgtStartptY = v_ptRgtHipPt[0].y;

									   fAllBodyMeasurementPxl[11] = (float(nRgtKneeHeight));

									   cv::Rect RgtKneeROI((nRgtStartptX), (nRgtStartptY), (nRgtKneeWidth * 2), nRgtKneeHeight);
									   cv::Mat oMatRgtKneeCropped = oMatInputImage(RgtKneeROI);
									   cv::imwrite(strImagesFolderPath + "\\RgtKneeCropped.jpg", oMatRgtKneeCropped);

									   break;
		}
		case LEFTKNEETOTANKLE_HEIGHT:
		{

										v_ptLeftAnklePt[0].x = v_pLftFeaturePoints[17].x * nResizeNumber;
										v_ptLeftAnklePt[0].y = v_pLftFeaturePoints[17].y * nResizeNumber;

										////to crop the elbow  width from image 

										int nLftAnkleHeight = v_ptLeftAnklePt[0].y - v_ptLftKneePt[0].y;
										int nLftAnkleWidth = nLftAnkleHeight / 4;
										int nLftAnklestartX = v_ptLftKneePt[0].x;
										int nLftAnklestartY = v_ptLftKneePt[0].y;

										fAllBodyMeasurementPxl[12] = (float(nLftAnkleHeight));


										cv::Rect LftAnkleROI((nLftAnklestartX), (nLftAnklestartY), (nLftAnkleWidth * 2), nLftAnkleHeight);
										cv::Mat oMatLftAnkleCropped = oMatInputImage(LftAnkleROI);
										cv::imwrite(strImagesFolderPath + "\\LftAnkleCropped.jpg", oMatLftAnkleCropped);

										break;

		}




		case RIGHTKNEETOTANKLE_HEIGHT:
		{
										 v_ptRightAnklePt[0].x = v_pLftFeaturePoints[18].x * nResizeNumber;
										 v_ptRightAnklePt[0].y = v_pLftFeaturePoints[18].y * nResizeNumber;

										 int nRgtAnkleHeight = v_ptLeftAnklePt[0].y - v_ptLftKneePt[0].y;
										 int nRgtAnkleWidth = nRgtAnkleHeight / 4;
										 int nRgtAnklestartX = v_ptLftKneePt[0].x;
										 int nRgtAnklestartY = v_ptLftKneePt[0].y;

										 fAllBodyMeasurementPxl[13] = (float(nRgtAnkleHeight));



										 cv::Rect RgtAnkleROI((nRgtAnklestartX), (nRgtAnklestartY), (nRgtAnkleWidth * 2), nRgtAnkleHeight);
										 cv::Mat oMatRgtAnkleCropped = oMatInputImage(RgtAnkleROI);
										 cv::imwrite(strImagesFolderPath + "\\RgtAnkleCropped.jpg", oMatRgtAnkleCropped);


										 break;
		}

		case FULLBODY_HEIGHT:
		{
								v_ptEndBodyPt[0].x = v_pLftFeaturePoints[19].x * nResizeNumber;
								v_ptEndBodyPt[0].y = v_pLftFeaturePoints[19].y * nResizeNumber;

								int nBodyHeight = v_ptEndBodyPt[0].y - v_ptTopHeadPt[0].y;
								int nBodyWidth = nBodyHeight / 8;
								int ndiff = nBodyWidth / 4;
								int nBodyStartX = v_ptTopHeadPt[0].x - ndiff;
								int nBodyStartY = v_ptTopHeadPt[0].y;

								fAllBodyMeasurementPxl[14] = (float(nBodyHeight));


								cv::Rect BodyROI((nBodyStartX), (nBodyStartY), (nBodyWidth), nBodyHeight);
								cv::Mat oMatBodyCrop = oMatInputImage(BodyROI);
								cv::imwrite(strImagesFolderPath + "\\Cropped.jpg", oMatBodyCrop);


								break;

		}


		}
		
	}
	/// to logg the values into the excel sheet 

	std::ofstream  fileMeasure(strImagesFolderPath + "\\Measurement.csv", std::ofstream::out | std::ofstream::app);

	std::ofstream  fileMarkedPoints(strImagesFolderPath + "\\MarkedCordinates.csv", std::ofstream::out | std::ofstream::app);

	
		fileMeasure << "BodyParts" << "," << "BodyMeasurementPiels" << endl << endl;
		fileMeasure << "HeadHeight" << "," << fAllBodyMeasurementPxl[0] << endl;
		fileMeasure << "NeckHeight" << "," << fAllBodyMeasurementPxl[1] << endl;
		fileMeasure << "ShoulderWidht" << "," << fAllBodyMeasurementPxl[2] << endl;
		fileMeasure << "LeftElbowHeight" << "," << fAllBodyMeasurementPxl[3] << endl;
		fileMeasure << "ChestWidth" << "," << fAllBodyMeasurementPxl[4] << endl;
		fileMeasure << "RightElbowHeight" << "," << fAllBodyMeasurementPxl[5] << endl;
		fileMeasure << "WaistWidth" << "," << fAllBodyMeasurementPxl[6] << endl;
		fileMeasure << "LeftWristHeight" << "," << fAllBodyMeasurementPxl[7] << endl;
		fileMeasure << "HipWidth" << "," << fAllBodyMeasurementPxl[8] << endl;
		fileMeasure << "RightWristHeight" << "," << fAllBodyMeasurementPxl[9] << endl;
		fileMeasure << "LeftKneeHeight" << "," << fAllBodyMeasurementPxl[10] << endl;
		fileMeasure << "RightKneeHeight" << "," << fAllBodyMeasurementPxl[11] << endl;
		fileMeasure << "LeftAnkleHeight" << "," << fAllBodyMeasurementPxl[12] << endl;
		fileMeasure << "RightAnkleHeight" << "," << fAllBodyMeasurementPxl[13] << endl;
		fileMeasure << "TotalHeight" << "," << fAllBodyMeasurementPxl[14] << endl;

		fileMarkedPoints << "PointNumber" << "," << "MarkedPoints X" << "," << "MarkedPoints Y" << endl;

		for (int nItr = 0; nItr < v_pLftFeaturePoints.size(); ++nItr)
		{
			fileMarkedPoints << nItr << "," << v_pLftFeaturePoints[nItr].x << "," << v_pLftFeaturePoints[nItr].y << endl;
		
		}

	

	fileMeasure.close();
	fileMarkedPoints.close();
}


