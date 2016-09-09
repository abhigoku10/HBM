
#pragma once


		///*This enum is used to know the order in which the modules are 
		//executed.
		//If change in calling order is desired - That change in order needs 
		//to be registered here, rest will be taken care by the program itself
		//e.g. If Edge Enhancement has to be done before Contrast Enhancement
		//then just place the Module_EdgeEnhancement before Module_ContrastEnhancement
		//in the eModuleCallingSequence.
		//*Pos_Start and Pos_End position shall not be changed.*/
		//RADIOGRAPHICENHANCEMENTDLL_API typedef enum E_MODULEEXECUTIONSEQUENCE 
		//{
		//	POS_START = 0,
		//	MODULE_PRE_GRAYSCALE_TRANSFORMATION,
		//	MODULE_NOISE_FILTERING,
		//	MODULE_CONTRAST_ENHANCEMENT,
		//	MODULE_EDGE_ENHANCEMENT,
		//	MODULE_POST_GRAYSCALE_TRANSFORMATION,
		//	POS_END

		//}E_MODULEEXECUTIONSEQUENCE;

		//// Enumerator for selection of modules
		//RADIOGRAPHICENHANCEMENTDLL_API typedef enum E_BLOCKNAME
		//{
		//	PRE_GRAYSCALE_TRANSFORMATION = 0,
		//	NOISE_FILTERING,
		//	CONTRAST_ENHANCEMENT,
		//	EDGE_ENHANCEMENT,
		//	POST_GRAYSCALE_TRANSFORMATION,
		//	SPECIFIED_BLOCK_NOTFOUND

		//}E_BLOCKNAME;

		// Enumerator to notify errors in each module
		// RADIOGRAPHICENHANCEMENTDLL_API typedef enum E_ERRORCODE
		//{
		//	SUCCESS = 0,
		//	PRE_GRAYSCALE_TRANSFORMATION_FAIL,
		//	NOISE_FILTERING_FAIL,
		//	CONTRAST_ENHANCEMENT_FAIL,
		//	EDGE_ENHANCEMENT_FAIL,
		//	POST_GRAYSCALE_TRANSFORMATION_FAIL,
		//	NULL_INPUT_ARGUMENT,
		//	INVALID_USER_INPUT,
		//	MISCERR,
		//	ERROR_TYPE_UNRECOGNISED

		//} E_ERRORCODE;
		
		// Enumerator to validate input information provided
		typedef  enum E_VALIDATEIP
		{
			VALIDATE_DATA_INFO = 0,
			INVALID_INPUT_IMAGE,
			INVALID_ANATOMY_NUM,
			MISC

		} E_VALIDATEIP;

		// Enumerator for selection of Anatomy
		//RADIOGRAPHICENHANCEMENTDLL_API typedef  enum E_ANATOMY
		//{
		//	SPINE = 0,
		//	HEAD,
		//	CHEST,
		//	ABDOMEN,
		//	SHOULDER,              //SKULL_PA
		//	UPPER_EXTREMITIES,
		//	LOWER_EXTREMITIES,
		//	DENTAL,					//IT HAS BEEN ADDED AS 8TH ANATOMY(21/10/2015)
		//	ANATOMY_NOT_FOUND

		//} E_ANATOMY;

		
		typedef struct SUShortImage
		{
			unsigned int unBitDepth;	// Gives BitDepth of an Image
			unsigned int nImageHeight;	// Gives Height of an Image 
			unsigned int nImageWidth;	// Gives Width of an Image 
			unsigned short* pusnData;	// Gives Pointer to an Image Data 
			
		}SUShortImage;

		
		typedef  struct SDblImage
		{
			signed int unBitDepth;		//Gives BitDepth of an Image 
			unsigned int nImageHeight;	// Gives Height of an Image
			unsigned int nImageWidth;	// Gives Width of an Image 
			double* pusnData;			// Gives Pointer to an Image Data 
			
	    }SDblImage;

			
			typedef struct SRange			
			{
				double dLow;
				double dHigh;

			}SRange;
			
			
			typedef struct SPoint			
			{
				unsigned int x;
				unsigned int y;

			}SPoint;

			typedef struct SFeaturePoints
			{
				double dXValue;
				double dYValue;
			}SFeaturePoints;

			typedef enum E_BODYTYPE
			{
				HEAD_HEIGHT = 0,
				NECK_HEIGHT,
				SHOULDER_WIDTH,
				CHEST_WIDTH,
				LEFTSHOULDERTOELBOW_HEIGHT,
				LEFTWAISTHIP_HEIGHT,
				RIGHTWAISTHIP_HEIGHT,
				RIGHTSHOULDERTOELBOW_HEIGHT,
				LEFTELBOWTOWRIST_HEIGHT,
				RIGHTELBOWTOWRIST_HEIGHT,
				LEFTHEAPTOKNEE_HEIGHT,
				RIGHTHEAPTOKNEE_HEIGHT,
				LEFTKNEETOTANKLE_HEIGHT,
				RIGHTKNEETOTANKLE_HEIGHT,
				FULLBODY_HEIGHT
			};

			
