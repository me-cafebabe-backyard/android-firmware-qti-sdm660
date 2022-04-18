/*============================================================================
@file matrix_float.c

Magnetometer calibration algorithm source file 

Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
============================================================================*/

/* $Header: //components/rel/ssc.slpi/2.2/common/util/mathtools/src/matrix_float.c#1 $ */
/* $DateTime: 2017/04/17 22:20:39 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
EDIT HISTORY

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when        who  what, where, why
----------  ---  -----------------------------------------------------------
2013-06-18  ks   initial version

============================================================================*/
#include <math.h>
#include "matrix_float.h"

/*=========================================================================
FUNCTION:  matrix_float_malloc_mem_req
=========================================================================*/
/*!
@brief
Provides the algorithm state memory requirement for the specified matrix size

@return
algorithm state memory requirement in bytes if successful, 0 if error
*/
/*=======================================================================*/
int32_t matrix_float_malloc_mem_req(uint32_t rows, uint32_t cols)
{
   return (rows * (sizeof(float *)+cols*sizeof(float)) );
}

/*=========================================================================
FUNCTION:  matrix_float_malloc
=========================================================================*/
/*!
@brief
Allocate memory for a 2D float matrix

@param[o] mat:  pointer to pointer to pointer to float set to NULL
when function is called. *mat is used to return the
allocated memory for the 2D matrix
@param[i] rows: the number of rows of the matrix
@param[i] cols: the number of columns of the matrix

@return true if successful, false otherwise.
*/
/*=======================================================================*/
bool matrix_float_malloc(float ***mat, uint32_t rows, uint32_t cols)
{
   uint32_t i;
   uint8_t *buff_p; 
   bool   retVal = false;
   *mat = (float **)MATRIX_FLOAT_MALLOC(matrix_float_malloc_mem_req(rows, cols));

   if(*mat != NULL)
   {
      retVal = true;
      buff_p = (uint8_t*)(*mat) + rows*(sizeof(float *));

      for (i=0; i<rows; i++)
      {
         (*mat)[i] =  (float *)(buff_p+i*cols*sizeof(float));  
      }
   }
   return retVal;
}

/*=========================================================================
FUNCTION:  matrix_float_free
=========================================================================*/
/*!
@brief
Free memory associated with a 2D float matrix

@param[o] mat:  pointer to pointer to pointer to float that needs to be freed
@param[i] rows: the number of rows of the matrix
@param[i] cols: the number of columns of the matrix

@return None
*/
/*=======================================================================*/
void matrix_float_free(float ***mat)
{
   MATRIX_FLOAT_FREE(*mat);
}


/*=========================================================================
FUNCTION:  matrix_float_reset
=========================================================================*/
/*!
@brief
Init 2D float matrix

@param[o] mat:  pointer to pointer to pointer.
@param[i] rows: the number of rows of the matrix
@param[i] cols: the number of columns of the matrix
@param[i] mem: pointer to the memory allocated earlier for the matrix
@return None
*/
/*=======================================================================*/
void matrix_float_reset(float ***mat, uint32_t rows, uint32_t cols, void *mem)
{
   uint32_t i;
   uint8_t *buff_p; 

   *mat = (float **)mem;

   buff_p = (uint8_t*)(*mat) + rows*(sizeof(float *));

   for (i=0; i<rows; i++)
   {
      (*mat)[i] =  (float *)(buff_p+i*cols*sizeof(float));
   }
}


/*=========================================================================
FUNCTION:  matrix_float_inversion_buffer_mem_req
=========================================================================*/
/*!
@brief
Provides the matrix inversion buffers memory requirement for the specified square matrix size

@param[i] max_inverted_matrix_rows: maximum square matrix dimensions in the algo 
that needs to be inverted

@return
buffer memory requirement in bytes if successful, 0 if error
*/
/*=======================================================================*/
#ifdef PREALLOCATE_MATRIX_INVERSION_BUFFER   

int32_t matrix_float_inversion_buffer_mem_req (int max_inverted_matrix_rows) // same as num columns, of course
{
   int32_t mem_size = 0, num_rows_in_buffer = 0;
   if (max_inverted_matrix_rows >= MIN_INV_MATRIX_ROWS_THAT_REQUIRE_BUFFER) 
   {
      int sub_matrix_for_det_rows;
      mem_size = sizeof(matrix_inversion_buffer_s) + 
         matrix_float_malloc_mem_req(max_inverted_matrix_rows-1, max_inverted_matrix_rows-1); // just one buffer of max size, will be used for any smaller matrix as well
      for (sub_matrix_for_det_rows = MIN_INV_MATRIX_ROWS_THAT_REQUIRE_BUFFER-1;
         sub_matrix_for_det_rows <= max_inverted_matrix_rows-1; sub_matrix_for_det_rows++)
      { 
         // stack of buffers of different size for recursive matrix_float_sq_determinant()
         num_rows_in_buffer += sub_matrix_for_det_rows; 
      }
      // See matching buffer start computation for (rows = 3; rows < rowsA; rows++) buff_start += (rows-1); 
      // for simplicity allocate rectangular (rather than square) matrices with required 
      // number of rows but common number of columns equal to that of largest matrix
      mem_size += matrix_float_malloc_mem_req(num_rows_in_buffer, max_inverted_matrix_rows-1);
   }  
   return (mem_size);
}
#endif
/*=========================================================================
FUNCTION:  matrix_float_inversion_buffer_reset
=========================================================================*/
/*!
@brief
Reset the buffer

@param[i] pointer to matrix_inversion_buffer_s type structure 
@param[i] max_inverted_matrix_rows: maximum square matrix dimensions in the algo 
that needs to be inverted
@param[i] mem: pointer to the memory allocated earlier for the (cofactor_buff + determinant_buff)

@return
true on success
*/
/*=======================================================================*/

#ifdef PREALLOCATE_MATRIX_INVERSION_BUFFER   

bool matrix_float_inversion_buffer_reset (matrix_inversion_buffer_s *inversion_buff_p,
                                          int max_inverted_matrix_rows, void *mem)
{
   int sub_matrix_for_det_rows, num_rows_in_buffer = 0;
   bool allocated;
   uint8_t *buff_p; 

   // just in case
   inversion_buff_p->max_inverted_matrix_rows = 0;
   inversion_buff_p->cofactor_buff = NULL;
   inversion_buff_p->determinant_buff = NULL;
   allocated = false;

   if (max_inverted_matrix_rows >= MIN_INV_MATRIX_ROWS_THAT_REQUIRE_BUFFER) 
   {
      inversion_buff_p->max_inverted_matrix_rows = max_inverted_matrix_rows;

      buff_p = (uint8_t*)mem;
      // just one cofactor_buff of max size, will be used for any smaller matrix as well
      matrix_float_reset(&inversion_buff_p->cofactor_buff, max_inverted_matrix_rows-1, max_inverted_matrix_rows-1, buff_p);  

      // point to first address after memory already used for the cofactor_buff:
      buff_p += matrix_float_malloc_mem_req(max_inverted_matrix_rows-1, max_inverted_matrix_rows-1); 
      for (sub_matrix_for_det_rows = MIN_INV_MATRIX_ROWS_THAT_REQUIRE_BUFFER-1;
         sub_matrix_for_det_rows < max_inverted_matrix_rows; sub_matrix_for_det_rows++)
      { 
         // stack of buffers of different size for recursive matrix_float_sq_determinant()
         num_rows_in_buffer += sub_matrix_for_det_rows; 
      }
      // See matching buffer start computation for (rows = 3; rows < rowsA; rows++) buff_start += (rows-1); 
      // for simplicity allocate rectangular (rather than square) matrices with required 
      // number of rows but common number of columns equal to that of largest matrix
      matrix_float_reset(&inversion_buff_p->determinant_buff, num_rows_in_buffer, max_inverted_matrix_rows-1, buff_p);
   }  
   return (allocated);
}
#endif

/*=========================================================================
FUNCTION:  matrix_float_sq_determinant
=========================================================================*/
/*!
@brief
Computes the determinant of a given square matrix

@param[i] matA: pointer to 2D square array representing the input matrix
for which determinant has to be computed.
@param[i] rowsA: the number of rows of the square matrix matA

determinant_buff can be NULL
@return
floating point value of the determinant of the square matrix matA
*/
/*=======================================================================*/
float matrix_float_sq_determinant(float **matA,int rowsA, 
                                  float **determinant_buff) // can be NULL
{
   if(rowsA == 0) {
      return 0;
   }
   if(rowsA == 2) {
      float result = matA[0][0]*matA[1][1] - matA[0][1]*matA[1][0];
      return result;
   }
   else if(rowsA ==1) {
      return matA[0][0];
   }
   else {
      int col;
      int r = 0;
      int c = 0;
      int subr = 0;
      int subc = 0;
      float ftmp, result = 0;

      float **sub;

      if (determinant_buff==NULL) 
      {
         matrix_float_malloc(&sub, (rowsA-1), (rowsA-1)); // min sub matrix size 2*2
         if (sub == NULL)
         {
            return result;
         }
      }
      else 
      {  
         int buff_start = 0, rows;
         // 3->0, 4->2, 5->2+3, 6->2+3+4.... 
         // For matrix size <= 4*4, as in HI calibration the following could be used instead: 
         // buff_start = (rowsA == 3)? 0:2;
         for (rows = 3; rows < rowsA; rows++) buff_start += (rows-1); 

         sub = &determinant_buff[buff_start]; 
      }

      for(col=0; col<rowsA; col++) {
         subc = 0;
         subr = 0;
         for(r=1; r<rowsA; r++) {
            subc = 0;
            for(c=0; c<rowsA; c++) {
               if(c != col) {
                  sub[subr][subc] = matA[r][c];
                  subc++;
               }
            }
            subr++;
         }
         ftmp = matA[0][col]*matrix_float_sq_determinant(sub, rowsA-1, determinant_buff);
         if (col%2 == 0) result = result + ftmp;
         else            result = result - ftmp;
      }

      if (determinant_buff==NULL) matrix_float_free(&sub); 

      return result;
   }
}

/*=========================================================================
FUNCTION:  matrix_float_sq_cofactor
=========================================================================*/
/*!
@brief
Computes the cofactor matrix for a given square matrix

@param[i] matA: pointer to 2D square array representing the input matrix
for which cofactor matrix has to be computed.
@param[i] rowsA: the number of rows of the square matrix matA
@param[o] matO: pointer to 2D square array to which cofactor matrix for
matA is written

@return true if successful, false otherwise.
*/
/*=======================================================================*/
bool matrix_float_sq_cofactor(float **matA,int rowsA,bool is_symmetric, 
                              matrix_inversion_buffer_s *matrix_inversion_buff_p, float **matO)
{
   if(rowsA == 0 || rowsA == 1) {
      return false;
   }
   else if(rowsA == 2)
   {
      matO[0][0] = matA[1][1]; // swap diag elements
      matO[0][1] = -matA[0][1]; // flip non-diag elements sign
      matO[1][0] = -matA[1][0];
      matO[1][1] = matA[0][0];
   }
   else 
   {
      int i, j;
      int si, sj;
      int pi, pj;
      int min_col;
      float result;

      float **sub;
      if (matrix_inversion_buff_p == NULL) 
      {
         return false;
      }
      else
      {
         sub = matrix_inversion_buff_p->cofactor_buff; // That implies that PREALLOCATE_MATRIX_INVERSION_BUFFER was defined
      }

      for(i=0; i<rowsA; i++) {
         min_col = is_symmetric? i:0; // for symmetric matrix only upper diagonal, then copy to lower
         for(j=min_col; j<rowsA; j++) {
            //begin to compute the cofactor for matA[i][j]
            si = 0;
            for(pi=0;pi<rowsA;pi++) {
               if(pi == i)
                  continue;
               sj = 0;
               for(pj=0;pj<rowsA;pj++) {
                  if(pj != j) {
                     sub[si][sj] = matA[pi][pj];
                     sj++;
                  }
               }
               si++;
            }
            //done with filling the submatrix
            result = matrix_float_sq_determinant(sub,rowsA-1, 
#ifdef PREALLOCATE_MATRIX_INVERSION_BUFFER
               matrix_inversion_buff_p->determinant_buff
#else
               NULL
#endif
               );

            if ((i+j)%2 == 0) matO[i][j] =  result;
            else              matO[i][j] = -result;
         } // for col
      } // for row
      if (is_symmetric)
      {
         // copy upper to lower diag
         int row, col;
         for (row = 1; row < rowsA; row ++)
         {
            for (col=0; col < row; col ++)
            {
               matO[row][col] = matO[col][row];
            }
         }
      }
   }
  return true;
}

/*=========================================================================
FUNCTION:  matrix_float_sq_transpose
=========================================================================*/
/*!
@brief
Transposes a given square matrix

@param[i] matA: pointer to 2D square array representing the input matrix
that needs to be transposed. matA is replaced with it's transpose.
@param[i] rowsA: the number of rows of the square matrix matA

@return None
*/
/*=======================================================================*/
void matrix_float_sq_transpose(float **matA,int rowsA)
{
   int i,j;
   float tmp;

   for (i=1;i<rowsA;i++)
   {
      for (j=0;j<i;j++)
      {
         tmp = matA[i][j];
         matA[i][j] = matA[j][i];
         matA[j][i] = tmp;
      }
   }
}

/*=========================================================================
FUNCTION:  matrix_float_transpose
=========================================================================*/
/*!
@brief
Transposes a given rectangular matrix

@param[i] matA: pointer to 2D square array representing the input matrix
that needs to be transposed.
@param[i] rowsA: the number of rows of the matrix matA
@param[i] colsA: the number of columns of the matrix matA
@param[i] matO: pointer to 2D square array representing the output matrix
to which the transpose needs to be written to.
@param[i] rowsO: the number of rows of the matrix matO
@param[i] colsO: the number of columns of the matrix matO

@return boolean set to true if succesful
*/
/*=======================================================================*/
bool matrix_float_transpose(float **matA,int rowsA, int colsA,
                            float **matO, int rowsO, int colsO)
{
   int row,col;

   if ((rowsA != colsO) || (colsA !=rowsO))
   {
      return false;
   }

   for (row=0; row<rowsA; row++)
   {
      for (col=0; col<colsA; col++)
      {
         matO[col][row] = matA[row][col];
      }
   }

   return true;
}
/*=========================================================================
FUNCTION:  matrix_float_sq_inverse
=========================================================================*/
/*!
@brief
Computes the inverse of a given square matrix

@param[i] matA: pointer to 2D square array representing the input for which
the inverse needs to be computed
@param[i] rowsA: the number of rows of the square matrix matA
@param[i] detLimit: the determinant limit that must be exceeded in order for
inversion to be conducted. 

@return boolean set to true if inversion was succesful.
*/
/*=======================================================================*/
bool matrix_float_sq_inverse(float **matA,int rowsA,float detLimit, bool is_symmetric, // always true for HI cal
                             matrix_inversion_buffer_s *matrix_inversion_buff_p, // can be NULL
                             float **matO)
{
   float det = matrix_float_sq_determinant(matA,rowsA,
#ifdef PREALLOCATE_MATRIX_INVERSION_BUFFER
      matrix_inversion_buff_p->determinant_buff
#else
      NULL
#endif	   
      );

   // check determinant
   if (det < detLimit)
   {
      //return false;
   }

   matrix_float_sq_cofactor(matA,rowsA,is_symmetric,matrix_inversion_buff_p,matO);
   if (!is_symmetric)
   {
      matrix_float_sq_transpose(matO,rowsA); // for the HI calibration never come here becaue the XT*X matrix is symmetric
   }
   matrix_float_scalar_multiply(matO,rowsA,rowsA,(1/det));
   return true;
}

/*=========================================================================
FUNCTION:  matrix_float_multiply
=========================================================================*/
/*!
@brief
Computes the product of two matrices

@param[i] matA: pointer to 2D array representing the first matrix to be multiplied
@param[i] rowsA: the number of rows of the matrix matA
@param[i] colsA: the number of columns of the matrix matA
@param[i] matB: pointer to 2D array representing the second matrix to be multiplied with
The number of rows of matB must be equal to number of columns of matA
@param[i] colsB: the number of columns of the matrix matB
@param[o] matO: pointer to 2D array representing the product of matA & mat B

@return boolean set to true if multiplication was succesful.
*/
/*=======================================================================*/
bool matrix_float_multiply(float **matA,
                           int rowsA,
                           int colsA,
                           float **matB,
                           int colsB,
                           float **matO)
{
   int row, col, i;

   for (row = 0; row < rowsA; row++)
   {
      for (col = 0; col < colsB; col++)
      {
         matO[row][col] = 0;
         for (i = 0; i < colsA; i++)
         {
            matO[row][col] += matA[row][i] * matB[i][col];
         }
      }
   }

   return true;
}

/*=========================================================================
FUNCTION:  matrix_float_transpose_first_multiplicand_and_multiply
=========================================================================*/
/*!
@brief
Computes the product of two matrices Atrans*B

@param[i] matA: pointer to 2D array representing the first matrix to be multiplied after transposition
@param[i] rowsA: the number of rows of the matrix matA
@param[i] colsA: the number of columns of the matrix matA
@param[i] matB: pointer to 2D array representing the second matrix to be multiplied with
The number of rows of matB must be equal to number of columns of matA
@param[i] colsB: the number of columns of the matrix matB
@param[o] matO: pointer to 2D array representing the product of matA & mat B

@return boolean set to true if multiplication was succesful.
*/
/*=======================================================================*/
bool matrix_float_transpose_first_multiplicand_and_multiply(float **matA,
                                                            int rowsA,
                                                            int colsA,
                                                            float **matB,
                                                            int colsB,
                                                            float **matO)
{
   int row, col, i, min_col;
   // are we computing AT*A?
   bool is_symmetric = ((matA == matB)&&(colsA==colsB));

   for (row = 0; row < colsA; row++) // note row < colsA
   {
      min_col = is_symmetric? row:0; // for symmetric (hence square) result compute only upper diagonal, then copy to lower
      for (col = min_col; col < colsB; col++)
      {
         matO[row][col] = 0;
         for (i = 0; i < rowsA; i++)
         {
            matO[row][col] += matA[i][row] * matB[i][col]; // note [i][row]
         }
      }
   }
   if (is_symmetric)
   {
      // copy upper to lower diag
      for (row = 1; row < colsA; row ++)
      {
         for (col = 0; col < row; col ++)
         {
            matO[row][col] = matO[col][row];
         }
      }
   }

   return true;
}
/*=========================================================================
FUNCTION:  matrix_float_scalar_multiply
=========================================================================*/
/*!
@brief
Multiplies all the elements of a given matrix by a scalar value

@param[i] matA: pointer to 2D array representing the matrix upon which scalar
multiplication needs to be performed. matA is replaced with
the scalara multiplied output.
@param[i] rowsA: the number of rows of the matrix matA
@param[i] colsA: the number of columns of the matrix matA
@param[i] mul: the scalar multiplier

@return boolean set to true if multiplication was succesful.
*/
/*=======================================================================*/
bool matrix_float_scalar_multiply(float **matA,
                                  int rowsA,
                                  int colsA,
                                  float mul)
{
   int row,col;

   for (row = 0; row < rowsA; row++)
   {
      for (col = 0; col < colsA; col++)
      {
         matA[row][col] = matA[row][col] * mul;
      }
   }

   return true;
}

/*=========================================================================
FUNCTION:  matrix_float_statistics
=========================================================================*/
/*!
@brief
Computes statistics of a specified row / column in a given 2D matrix array

@param[i] matA: pointer to 2D square array representing the input matrix
that needs to be evaluated
@param[i] rowsA: the number of rows of the matrix matA
@param[i] colsA: the number of columns of the matrix matA
@param[i] eval_type: enum specifying the kind of evaluation requested
@param[i] eval_num: the column / row of the matrix that needs to be evaluated
@param[o] stats: pointer to matrix_float_stats_s struct to which the evaluated
statistics are returned

@return boolean set to true if succesful
*/
/*=======================================================================*/
bool matrix_float_statistics(float **matA,
                             uint32_t rowsA,
                             uint32_t colsA,
                             matrix_float_stats_eval_type_e eval_type,
                             uint32_t eval_num,
                             matrix_float_stats_s *stats)
{
   bool flag_success = false;
   uint32_t row=0, col=0, i=0, dim=0;
   float mintemp = FLT_MAX, maxtemp = (float)(-1.0f*FLT_MAX);
   float sum=0, sqsum = 0;

   if (eval_type == MATRIX_FLOAT_EVAL_ROW)
   {
      dim = colsA;
   }
   else if(eval_type == MATRIX_FLOAT_EVAL_COL)
   {
      dim = rowsA;
   }
   else
   {
      return false;
   }

   for (i = 0; i < dim; i++)
   {
      if (eval_type == MATRIX_FLOAT_EVAL_ROW)
      {
         row = eval_num;
         col = i;
      }
      else if(eval_type == MATRIX_FLOAT_EVAL_COL)
      {
         row = i;
         col = eval_num;
      }

      if (matA[row][col] < mintemp)
      {
         mintemp = matA[row][col];
      }
      else if (matA[row][col] > maxtemp)
      {
         maxtemp = matA[row][col];
      }
      sum += matA[row][col];
      sqsum += matA[row][col]*matA[row][col];
   }

   if ((mintemp < FLT_MAX)&&
      (maxtemp > (float)(-1.0f*FLT_MAX)))
   {
      stats->min = mintemp;
      stats->max = maxtemp;
      stats->span = stats->max - stats->min;
      stats->variance = sqsum/dim - (sum/dim)*(sum/dim);
      flag_success = true;
   }
   return flag_success;
}

