/*============================================================================
@file curve_fit.c

Curve fit source file 

Copyright (c) 2013, 2015 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

/* $Header: //components/rel/ssc.slpi/2.2/common/util/mathtools/src/curve_fit.c#1 $ */
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

#include "curve_fit.h"
#if defined(OFFTARGET_UNIT_TESTING)
#include <stdio.h>
#endif

/*=========================================================================
FUNCTION:  curve_fit_spheroid
=========================================================================*/
/*!
@brief
Estimate a spheroid that best fits the triaxial sensor data points

@param[i] data: pointer to pointer to float containing N * 4 array
of triaxial sensor data points for which the spheroidal fit needs
to be computed. The 3 columns should contain measurements from the
to the X,Y,Z axes of the sensor. The last column should contain 1.0
@param[i] data_length: the number of sensor data points.
@param[o] offset: offset of the estimated spheroid from origin
@param[o] radius: radius of the estimated sphere
@param[o] rel_rad_std: standard deviation of the fit residual error relative to radius
@param[o] rel_rad_std: span of the fit residual error relative to radius
@param[o] cov_mat: offset adjusted data covariance - conditionally compiled

@return boolean set to true if spheroidal fit was succesful, false otherwise
*/
/*=======================================================================*/

bool curve_fit_spheroid(float **data, // decim mag X,Y,Z,1.0
                        float **measurements, // (X^2+Y^2+Z^2)/2
                        float **curve_fit_buffer_16_by_4, 
                        matrix_inversion_buffer_s *matrix_inversion_buff_p, // can be NULL
                        uint32_t data_length,
                        float offset[CURVE_FIT_3D_COL], float *radius,
                        float *rel_rad_std, float *rel_rad_span
#ifdef COMPUTE_HI_COV_MAT
                        ,float cov_mat[CURVE_FIT_3D_COL+1][CURVE_FIT_3D_COL+1]
#endif
)
{
   bool flag_success = true, is_symmetric = true;
   uint32_t i, row, col, rowsX, colsX; 
   float **matX = data,  **matY = measurements; // input
   float **matXT_X = &curve_fit_buffer_16_by_4[0];
   float **matXT_X_Inv = &curve_fit_buffer_16_by_4[4];
   // note that 4*1 matrices matO1 and matO2 will be 4*4 here. Which is OK, extra columns do not matter (neither extra rows would've)
   float **matO1 =&curve_fit_buffer_16_by_4[8]; 
   float **matO2 =&curve_fit_buffer_16_by_4[12];

   // data are in first 3 columns of matX
   rowsX = data_length;
   colsX = CURVE_FIT_3D_COL + 1; 

   // the inverse routine below will call matrix_float_sq_cofactor() 
   // and matrix_float_sq_determinant() that will use malloc if not PREALLOCATE_MATRIX_INVERSION_BUFFER 

   // is_symmetric flag will be automatically assigned inside this routine because of equal adressess and sizez of A and B
   matrix_float_transpose_first_multiplicand_and_multiply(matX,rowsX,colsX,matX,colsX,matXT_X); // X' * X [4*4]

   if(matrix_float_sq_inverse(matXT_X, colsX, (1/2048), is_symmetric, matrix_inversion_buff_p, // can be NULL
      matXT_X_Inv)) // pinv(X'*X) [4*4]
   {
      float  sqsum, minval, maxval, radius_squared; // ,sum=0
      float sum =0;
      matrix_float_transpose_first_multiplicand_and_multiply(matX,rowsX,colsX,matY,1,matO1); // O1 = X' * Y [4*1]

      matrix_float_multiply(matXT_X_Inv,colsX,colsX,matO1,1,matO2); // O2 = pinv(X'*X) * (X'*Y)
      // offset ready
      sqsum = 0.0;
      for (i=0; i<CURVE_FIT_3D_COL; i++)
      {
         offset[i] = matO2[i][0];
         sqsum += offset[i] * offset[i];
      }
      *radius = (float)(sqrt(sqsum + 2.0 * matO2[CURVE_FIT_3D_COL][0]));

      sqsum = 0.0;
      minval = FLT_MAX;
      maxval = (float)(-1.0f*FLT_MAX);
      for (row=0; row<rowsX; row++)
      {
         radius_squared = 0.0;
         // calibrated XYZ
         for (col=0; col<(colsX-1); col++)
         {
            matX[row][col] = matX[row][col] - offset[col];
            radius_squared += matX[row][col]*matX[row][col]; 
         }

         if (radius_squared < minval)
         {
            minval = radius_squared;
         }
         if (radius_squared > maxval)
         {
            maxval = radius_squared;
         }

         sqsum += radius_squared; // sum(R^2) across all samples
         sum +=(float)(sqrt(radius_squared)); // sum(R) across all samples
      }
      minval = (float)sqrt(minval);
      maxval = (float)sqrt(maxval);
      //fabs used for precise calculations.  
      *rel_rad_std = (float)sqrt(fabs((sqsum/rowsX)-(sum/rowsX)*(sum/rowsX)))/(*radius); 
      *rel_rad_span = (maxval - minval) / (*radius);

      // printf("\nDelta R %f", (sum/rowsX)- *radius);

#ifdef COMPUTE_HI_COV_MAT
      // same formulae as above except that now X is calibrated
      // matrix_float_multiply(matXT,rowsXT,colsXT,matX,colsX,matXT_X); // X' * X [4*4], 
      matrix_float_transpose_first_multiplicand_and_multiply(matX,rowsX,colsX,matX,colsX,matXT_X); // X' * X [4*4]

      matrix_float_sq_inverse(matXT_X,colsX, (1/2048), is_symmetric,matrix_inversion_buff_p, matXT_X_Inv);

      for (row=0; row<colsX; row++)
      {
         for (col=0; col<colsX; col++)
         {
            cov_mat[row][col] = matXT_X_Inv[row][col];
         }
      }
#endif
   }
   else
   {
      flag_success = false;
   }

   return flag_success;
}
