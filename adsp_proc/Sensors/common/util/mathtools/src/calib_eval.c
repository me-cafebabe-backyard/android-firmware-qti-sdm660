/*============================================================================
@file calib_eval.c

Calibration evaluation source file 

Copyright (c) 2013, 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

/* $Header: //components/rel/ssc.slpi/2.2/common/util/mathtools/src/calib_eval.c#1 $ */
/* $DateTime: 2017/04/17 22:20:39 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
EDIT HISTORY

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when        who  what, where, why
----------  ---  -----------------------------------------------------------
2015-03-26  ps   Updated license header
2013-06-13  ks   initial version

============================================================================*/

#include "calib_eval.h"

#define CALIB_EVAL_BISECTOR_NUM (4)
#define INVERSE_SQRT_3 (0.5574f)
/*=========================================================================
FUNCTION:  calib_eval_statistics
=========================================================================*/
/*!
@brief
Computes statistics associated with the quality of hard iron calibration

@param[i] matX: pointer to pointer to float containing N *(>=3) array
of triaxial sensor data points for which the quality of
calibration needs to be evaluated. In case of HI only 
can be calibrated or raw , in case of SI must be Smat-calibrated (at least)
@param[i] rowsX: the number of sensor data points.
@param[i] radius: radius of the estimated sphere
@param[i] mag_noise_std_for_variance: magnetometer noise standard deviation
@param[i] cov_mat: offset adjusted sensor data covariance
@param[o] min_3d_span: computed minimum 3D span
@param[o] max_3d_span: computed maximum 3D span
@param[o] rel_data_span_min: computed relative minimum 3D span to radius
@param[o] rel_data_span_max: computed minimum 3D span to radius

@return boolean set to true if evaluation was succesful,
false otherwise
*/
/*=======================================================================*/
bool calib_eval_statistics(float **matX, 
                           uint32_t rowsX,
                           float radius, 
#ifdef COMPUTE_HI_COV_MAT
                           float mag_noise_std_for_variance,
                           float cov_mat[CALIB_EVAL_COVMAT_COL_NUM][CALIB_EVAL_COVMAT_COL_NUM],
#endif
                           float *min_3d_span, float *max_3d_span,
                           float *rel_data_span_min, float *rel_data_span_max)
{
   bool flag_success = false;
   uint32_t i, row; 
   float value, span;
   float minvalue = FLT_MAX, maxvalue = (float)(-1.0f*FLT_MAX); // for one column
   float minspan  = FLT_MAX, maxspan  = (float)(-1.0f*FLT_MAX);  // across all columns


   // find decimated mag XYZ & bisectors min and max span
   for (i = 0; i < 3+CALIB_EVAL_BISECTOR_NUM; i++) // 3 stands for num XYZ columns, same as QMAG_CAL_COL
   {
      for (row = 0; row < rowsX; row++)
      {
         switch (i)
         {
         case 0:
         case 1:
         case 2:
            {
               value = matX[row][i]; // matX contains CALIBRATED XYZ in columns 0-2
               break;
            }
         case 3:
            {
               value = (matX[row][0] + matX[row][1] + matX[row][2]);  // X + Y + Z
               break;
            }
         case 4:
            {
               value = (matX[row][0] + matX[row][1] - matX[row][2]);  // X + Y - Z
               break;
            }
         case 5:
            {
               value = (matX[row][0] - matX[row][1] + matX[row][2]);  // X - Y + Z
               break;
            }
         case 6:
            {
               value = (matX[row][0] - matX[row][1] - matX[row][2]);  // X - Y - Z
               break;
            }
         } // switch
         if (value < minvalue)
         {
            minvalue = value;
         }
         else if (value > maxvalue)
         {
            maxvalue = value;
         }
      } // for row

      span = maxvalue-minvalue; // this column
      if (i >= 3) span = INVERSE_SQRT_3*span; // for bisectors only

      if (span < minspan) 
      {
         minspan = span; // across all columns
      }
      else if (span > maxspan)
      {
         maxspan = span; // across all columns
      }
   } // for i (column)
   if ((minspan < FLT_MAX)&&
      (maxspan > (float)(-1.0f*FLT_MAX)))
   {
      *min_3d_span = minspan;
      *max_3d_span = maxspan;
      *rel_data_span_min = *min_3d_span / radius;
      *rel_data_span_max = *max_3d_span / radius;
      flag_success = true;
   }
#ifdef COMPUTE_HI_COV_MAT
   {
      float mag_sq_variance;
      int col;

      mag_sq_variance = 4.0f * (radius*radius)*(mag_noise_std_for_variance*mag_noise_std_for_variance);

      for (row = 0; row < CALIB_EVAL_COVMAT_COL_NUM; row++)
      {
         for (col = 0; col < CALIB_EVAL_COVMAT_COL_NUM; col++)
         {
            cov_mat[row][col] = mag_sq_variance*cov_mat[row][col];
         }
      }
   }
#endif
   return flag_success;
}
