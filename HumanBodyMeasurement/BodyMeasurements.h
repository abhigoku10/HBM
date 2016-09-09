#include"DataStructure.h"
#include"CommonHeaders.h"

namespace GymBodyFitness
{
	namespace Process
	{
		namespace Module
		{
			class CBodyMeasurements
			{
			public:
				void PerformMeasurements(cv::vector<cv::Point> v_pLftFeaturePoints, 
					int nResizeNumber, double dPixelToMeterFactor, cv::Mat oMatInputImage, string strImagesFolderPath);

			};
		}
	}
}