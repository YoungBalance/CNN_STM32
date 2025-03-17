#include "nnom.h"

/* Weights, bias and Q format */
#define TENSOR_CONV1D_KERNEL_0 {18, -21, 24, 83, 27, -58, 88, 21, 7, -70, -9, -12, -39, -47, 50, 52, -61, -39, -44, -26, 64, -67, -3, -29, 17, 81, 28, 29, 69, 50, -52, 95, -9, -81, 72, 31, 17, 7, 2, 76, 75, -59, -40, 82, -78, 80, 38, -3, -79, 23, -10, 21, 21, -74, -91, -91, 47, -43, -51, -24, 47, 54, 70, 18, 34, -98, 58, 55, 50, -35, 74, 23, -85, 34, 74, 61, 59, 78, -51, -45, 47, -32, 10, 60, 76, 33, -54, -12, 46, -6, 88, -74, -77, 51, -18, 11, 85, -41, 2, 53, 93, 46, -94, 79, -34, -79, 70, 61, 75, -26, 10, 9, -18, -24, -33, 56, -88, 82, 61, -87, -22, -56, -62, -79, -54, -74, -85, -18, -22, -61, -65, -24, -53, -19, -78}

#define TENSOR_CONV1D_KERNEL_0_DEC_BITS {8}

#define TENSOR_CONV1D_BIAS_0 {24, 32, -6, 3, 19, 71, -8, 0, -4, -20, 96, -23, 6, -14, 76}

#define TENSOR_CONV1D_BIAS_0_DEC_BITS {10}

#define CONV1D_BIAS_LSHIFT {3}

#define CONV1D_OUTPUT_RSHIFT {9}

#define TENSOR_CONV1D_1_KERNEL_0 {13, 25, 59, 7, -12, -51, 75, 48, -18, 41, 6, -17, 0, 11, 61, -1, -3, 72, 12, -12, -34, 12, 14, 78, -57, -47, 22, -45, -37, 21, -42, 83, 3, -33, -58, 50, -26, -34, 22, -55, 55, -21, 66, 3, 37, -6, 64, 13, 33, 41, -43, -73, 66, -46, 25, 63, -19, -49, 29, 24, -1, -16, -9, 49, 35, 23, 8, -4, -16, -54, 52, 62, -39, -19, -27, -65, 6, -58, 51, -17, 76, -7, 63, 2, 34, -31, -32, -1, 65, 47, 62, 0, -50, -39, -4, -34, -16, 14, -53, -45, 5, 23, 64, 2, -31, 30, 25, 43, -62, -5, 85, -50, 43, -11, 60, -10, 5, -30, -62, 8, 80, 5, -39, -44, 61, 22, -52, 34, -20, -55, 20, 41, -25, 46, 23, -26, -14, 14, 58, 40, 70, -48, 14, -49, -20, 11, 0, -30, -34, -7, 16, -34, -1, 44, -16, 16, -19, -28, 37, 21, -32, -21, 40, -53, -23, 18, -36, -11, -17, 10, 70, -71, 42, 65, 76, 71, -33, -31, 3, 16, -36, -38, 31, 82, 83, 30, 54, -33, 45, 29, -25, 27, -25, -62, 33, -39, 46, -24, -11, 22, 32, -37, 9, 59, -33, -16, 53, 68, -13, 47, 34, 61, -46, 33, 8, 45, 33, -44, 14, 77, -71, -24, -30, 25, -11, -12, -4, 45, -42, 64, 33, 39, 63, 2, -3, -32, 51, 46, -22, -51, -16, -69, -39, 72, -41, 45, 47, 23, -11, -44, -45, -50, 60, -9, -50, 50, 20, 29, 25, 35, 44, -85, 36, -54, 46, 52, 36, 5, -18, 23, 31, -46, 65, 44, -44, 3, 62, -57, 83, 40, 24, -47, 0, 23, 57, 56, -44, 6, 6, -26, -68, 71, -63, 53, 47, 13, 70, -39, -35, -29, 3, 48, 57, -44, 28, 15, 51, -2, 34, -28, -16, 48, 18, 51, -29, -35, -3, -40, 38, 38, -13, -52, 41, 41, 41, -35, 21, 5, -22, 41, -24, -47, -13, 26, 34, 1, -15, -68, -1, -65, 33, 41, 55, -37, 40, -25, 51, -39, -48, -33, 57, 20, 30, -30, -47, 11, -58, 45, 66, 65, 47, 48, 20, 48, -27, 6, -39, 36, 1, -65, 41, -51, 62, 15, -67, -2, -57, -64, -47, -7, 63, -33, -59, -33, 55, 28, 52, 25, 69, -40, -43, -15, 50, 35, 67, -2, -33, 50, -55, -68, 67, -68, -39, -51, -53, 17, 4, 67, 7, 23, -9, -30, -39, 17, -45, 9, 14, 53, 33, -18, -57, -14, 29, 52, 64, -1, -5, 52, -47, -48, -51, 55, -43, -38, -26, 8, -10, 67, 20, -2, 73, 10, 6, 42, -17, -62, 29, 48, 33, 52, -49, -58, 41, -33, 59, 56, -20, 8, -63, -31, 38, -31, 65, 61, 1, -32, 52, -9, -20, -17, -22, 33, 11, -51, 71, -61, 19, -46, -19, 35, 23, -65, -10, -31, 50, 66, -13, 36, 19, -13, -27, -50, 52, 19, -44, -9, -25, -54, 59, -38, 5, -77, -35, -5, -44, -9, 39, -32, 51, -45, 8, -32, -7, 51, 49, 34, -58, 62, 67, 32, 38, 31, -52, 20, 18, -8, -19, 31, -8, 31, -30, -18, -44, -31, 18, -41, 34, 5, -51, 43, -38, -30, 53, 41, -40, -47, -72, 19, -64, 35, 53, -20, 4, 63, -47, -30, -40, -64, 46, 17, 29, 36, 41, -29, -10, 62, -41, 80, 20, -16, 67, -49, -37, -34, 46, 47, -60, -38, 46, -57, -4, -21, 87, 35, -42, 2, 24, -25, -68, -37, 67, 37, -33, 6, 48, 52, 58, 1, -50, 27, -25, 46, 26, 21, -52, 11, -31, 3, 29, 32, 39, -56, 65, -17, -40, 56, 53, -2, -53, 65, -21, -20, 55, 16, 21, 14, -6, 32, 8, 9, 48, 65, 33, -68, 65, 23, -16, 25, 0, 35, -22, 5, -27, 74, 39, 20, 75, -27, 56, 57, 15, 57, -42, 34, -59, 27, -11, -5, -50, 63, 41, 49, 17, -27, -44, -3, 18, -53, -67, -22, 17, -10, -48, -37, -46}

#define TENSOR_CONV1D_1_KERNEL_0_DEC_BITS {8}

#define TENSOR_CONV1D_1_BIAS_0 {102, -4, 90, 114, -17, 4, -45, 4, -12, -14, 21, 42, 62, -26, 70}

#define TENSOR_CONV1D_1_BIAS_0_DEC_BITS {10}

#define CONV1D_1_BIAS_LSHIFT {2}

#define CONV1D_1_OUTPUT_RSHIFT {8}

#define TENSOR_DENSE_KERNEL_0 {54, 19, -10, 18, -25, -50, 30, 17, 10, 20, -22, -19, -4, 2, -3, 4, -11, -22, -41, 12, -51, 24, 15, 19, -45, -26, -26, -11, -1, 18, 31, -38, 14, -41, 21, 8, -29, 23, -31, 9, -44, -24, 10, 6, -6, 12, -25, -32, -35, 37, 44, -24, 23, -49, 39, -54, 26, -6, -33, 20, 16, -26, -24, -16, -39, 7, 21, 7, 19, -6, -44, -23, 26, 19, 15, -31, -24, -25, -55, -12, -10, -7, 18, 6, -36, 48, 42, -17, -40, 10, 24, -16, -29, 31, 38, -29, -12, -63, -11, -10, 8, -26, -55, 30, -17, -6, -32, 1, -34, -28, -33, -60, -44, -38, 27, -19, 2, -12, 10, -12, -3, 26, 26, -16, 25, -44, -20, 42, 31, 1, -39, -38, -22, -39, -7, 8, 34, -33, 10, 9, -18, 40, -7, -4, 9, -52, -24, 8, 1, -4, 24, -32, -28, 35, 13, -9, 2, 15, -37, 43, -22, -24, 4, -36, -47, -22, -19, -29, -4, -53, -9, -25, -46, 53, 27, -39, -50, 5, -46, 24, 45, -57, 35, 45, 9, 13, 3, -12, -16, -45, -34, -57, 36, 16, -31, 17, -57, 25, -27, 4, -54, -4, -28, -44, -54, 6, 35, -5, -4, 26, -37, 8, -19, -28, -8, 37, 12, -18, 19, -25, 4, 2, -8, 16, -11, -52, 13, -42, -17, 41, 26, -5, -39, -18, -24, -3, 3, 12, 15, -64, -39, 25, -21, -44, -40, -64, -12, -34, -2, -33, 33, -65, -10, -22, -20, 37, 2, -8, -26, -19, -1, 54, 23, 13, 15, -16, -51, -18, 33, 38, -23, 24, -14, -22, 9, 15, -40, -42, 29, -37, -45, -7, -18, 20, 21, 6, -33, 12, -3, -37, -10, 49, 11, -26, -6, -4, -14, -41, 29, 46, 7, -36, -53, -14, -35, -10, -4, 8, 33, -24, -34, -47, 15, -4, -48, 4, -40, -26, 39, 49, -22, -1, 8, -10, 32, -2, 3, 33, -10, 14, -12, -27, -20, 26, 2, -40, 3, 22, -24, -5, 40, 22, -1, -12, 20, -24, 27, -36, -5, 26, -56, -13, 33, 10, 10, 7, 8, -5, -61, -31, -21, 49, 1, -46, -6, -48, -11, 11, -21, 24, -20, 12, -11, -10, -9, 21, 10, 13, 0, -39, -9, -31, 39, -15, -44, 0, -19, 19, -18, -17, -17, -40, -23, 32, -37, -44, -28, -24, -4, -7, 29, 25, 30, -12, -24, 19, -20, -53, 4, 8, -33, -11, 3, -33, 12, -12, -36, 18, 0, 2, -60, 22, 18, 36, 23, 13, -23, 0, -48, 46, -11, -16, -22, 42, 1, -32, -4, -41, 38, -48, -43, -1, -5, -10, 32, -46, 19, 25, 16, -43, -23, -38, 3, -1, 34, 20, 13, -22, -9, 22, -27, 1, -4, -34, -16, -16, -14, -49, -24, 10, -52, -28, 2, 31, -6, -9, -40, -38, -47, -27, -23, 20, -21, -33, -36, 21, -3, -34, 25, 9, 15, 20, 41, 9, 18, -11, -25, 2, -41, -55, -12, -5, -20, 33, -7, 19, 8, 10, 58, -25, -25, -34, -19, -2, 35, -13, -7, -48, 19, -33, -2, -28, -16, -4, -11, -57, 35, -6, 11, 16, 23, 4, -43, -57, -3, 20, -55, 20, -3, 3, -23, 19, 18, 15, 25, 6, 1, 38, 5, -28, -18, 1, -22, 45, 28, -41, 13, -2, 4, -35, -16, -11, 16, -18, 55, -25, -2, -3, 3, -25, 10, -12, -25, -30, -10, -8, -22, -22, -3, -49, 10, -50, 1, -11, -12, -39, 23, -9, -35, -23, -46, -13, 18, -2, -24, -36, -12, 27, -60, -15, 20, 3, -17, -36, -7, -1, -6, 27, -7, 35, 24, -28, 10, -22, 23, -49, 21, 39, -10, 37, 30, -11, 25, 29, 13, -8, -14, 27, 15, 16, -6, -30, 38, -4, 3, -41, 8, 9, 45, -23, -35, 31, -52, -30, -46, -8, -41, -31, -40, 0, -15, 21, 41, -33, 23, -19, 1, 31, -37, 16, -1, 9, -25, 29, 39, -1, -29, 24, -29, 5, -47, -43, -12, 51, 3, -19, -13, -37, 14, -45, 6, -7, -22, -39, -24, 9, -33, -24, -22, -18, -10, 15, -30, 0, 46, -53, -51, -6, -35, 35, -10, 26, 8, -8, -20, 12, 0, 33, 17, 18, 5, 22, 13, 7, -32, -34, 16, 18, -14, -21, 54, -10, 27, 22, -43, 7, 28, -50, 38, 9, 46, -10, -25, -29, -11, -8, -35, 12, 13, 22, -33, -15, -32, 6, -4, -1, -32, 4, 44, 2, -5, -17, 5, 8, 28, -13, -13, 10, 6, -20, -32, -14, 41, -21, 5, 6, -17, -19, -3, 49, 23, 27, 7, 3, -30, 25, -26, -20, -12, -34, -34, -3, -17, -18, -20, 16, 40, -7, 18, -7, -61, -38, 17, 36, -32, -19, -28, -59, 7, 22, -27, -8, -6, 9, 24, 6, 36, -32, -44, 28, 25, -16, 0, 17, 25, 24, 34, 4, -22, -4, 35, -35, 27, 4, -5, -35, 44, 1, -11, -33, -38, -42, 19, 34, 49, -21, -38, -9, -32, 23, -3, -27, 16, 12, -13, -12, 25, -27, 25, 35, 7, -10, -56, -3, -44, 33, 56, 44, -38, 4, -20, -16, -5, 15, 18, -19, -31, -8, -9, 37, 16, 25, -1, 7, -22, -40, 26, 8, -35, 38, -23, -10, -27, -16, -5, -5, 13, -41, 43, 35, 6, -19, 5, 7, -49, 26, 33, 28, 0, -18, 1, 7, 3, -47, 17, -2, -23, 22, -57, -30, 25, -35, 27, -16, -42, -26, -59, 1, -22, -23, -9, 6, -2, -22, -2, -28, -24, -3, 1, 13, 11, -8, -9, -38, 5, -26, -47, 47, -39, -34, -9, -10, 30, -1, 38, 22, -3, 25, 18, -25, -42, 7, -20, 11, -6, 29, 22, -28, -47, 2, -60, -7, -59, -16, 16, -38, 37, -24, -10, 24, -15, 7, -64, -35, 5, -35, 21, -6, -2, 43, -30, 33, 7, 1, 1, -21, -23, 12, 0, 25, 32, -36, 16, -43, 26, 9, 52, 29, -18, -24, -26, 10, -6, -22, -37, 48, -4, -37, -46, 45, 8, 43, 4, -5, 12, -20, -28, -46, -14, 17, -5, -32, -27, -21, -24, -45, -23, -10, -17, 18, 27, 2, -21, 13, 4, 30, 20, 18, 46, 17, -21, 6, 21, 38, -42, 15, -45, -26, 27, -33, 24, -16, -20, 40, -32, 36, -4, 13, -8, -44, -46, -49, 4, 38, -36, -66, -22, 11, 17, -15, -27, 29, -18, 37, -25, -35, -17, 30, -18, 27, -43, 14, -4, 3, 10, 4, -37, 0, 28, 9, -30, -25, 4, 7, -25, -43, -3, 6, -45, -35, -5, -16, 15, 4, 20, -37, 7, 35, -2, 5, 5, 1, 5, -25, -12, -13, 6, -47, 52, -11, -25, -49, 49, -29, -2, 12, -38, 0, 16, -19, -48, 24, -35, 15, 15, -38, -47, -16, -27, 11, -41, 6, -14, -24, -40, -61, -9, 21, -8, -49, -23, -38, 31, -40, 27, 16, 5, -34, -31, -37, -37, 34, -19, 32, 36, 20, 32, -4, -42, 23, 20, 0, 16, -18, -32, -10, -35, -11, -3, 22, 45, -1, -10, -5, -15, 13, 18, -44, 7, -26, -29, -15, 28, 20, 18, -19, 15, 6, 25, 0, -13, -51, -34, -6, -21, 1, -3, -42, 17, -12, -31, -52, 42, -44, 10, -39, -27, 38, 24, 6, 10, 21, -44, -6, -14, 37, -50, 42, 6, 23, -24, -30, 2, -17, -59, 29, 19, -34, 42, -42, -16, -28, 11, 34, 24, -58, 25, 45, -34, -41, -33, 33, -49, -19, -6, -17, -34, 53, 24, 25, 1, -4, 35, -4, -2, 9, 39, 5, 48, -30, -30, 17, -8, 12, -4, -43, -1, 23, 9, -9, -31, 33, -30, 20, 13, 18, -38, 15, -27, -61, -13, 15, -48, -61, -10, -23, -40, 23, -16, -16, 19, 9, -33, 9, -27, 8, 13, -19, 17, -38, -59, 25, -32, 1, 3, -45, 13, 13, 22, -44, -15, 29, -42, -54, -26, -44, 14, -22, -29, 22, -25, 18, -35, -39, -13, 45, -10, -7, 2, 21, 0, 42, 2, 2, 25, 11, -17, -14, 23, 10, 4, -31, -55, -42, 22, 6, -1, -6, 12, 38, 11, -11, -33, -41, -25, 24, -39, -39, -36, -4, 0, -12, 9, 16, 8, -42, 3, -4, 35, -21, 5, -40, -9, -40, -8, 12, 36, -32, -4, 34, -24, -19, -3, -9, 12, -14, 18, -27, -3, 23, -38, -23, -43, -7, -37, -15, -1, -46, -39, -44, -40, -25, -6, -43, 5, -51, -2, -8, -36, -19, -41, 11, -32, -35, -51, -63, -34, 6, -51, 12, -31, 18, -37, -30, -5, -34, -20, 4, -44, -37}

#define TENSOR_DENSE_KERNEL_0_DEC_BITS {8}

#define TENSOR_DENSE_BIAS_0 {119, 106, -58, -61, -38, -117}

#define TENSOR_DENSE_BIAS_0_DEC_BITS {11}

#define DENSE_BIAS_LSHIFT {1}

#define DENSE_OUTPUT_RSHIFT {8}


/* output q format for each layer */
#define INPUT_1_OUTPUT_DEC 5
#define INPUT_1_OUTPUT_OFFSET 0
#define CONV1D_OUTPUT_DEC 4
#define CONV1D_OUTPUT_OFFSET 0
#define RE_LU_OUTPUT_DEC 4
#define RE_LU_OUTPUT_OFFSET 0
#define CONV1D_1_OUTPUT_DEC 4
#define CONV1D_1_OUTPUT_OFFSET 0
#define RE_LU_1_OUTPUT_DEC 4
#define RE_LU_1_OUTPUT_OFFSET 0
#define FLATTEN_OUTPUT_DEC 4
#define FLATTEN_OUTPUT_OFFSET 0
#define DROPOUT_OUTPUT_DEC 4
#define DROPOUT_OUTPUT_OFFSET 0
#define DENSE_OUTPUT_DEC 4
#define DENSE_OUTPUT_OFFSET 0
#define DROPOUT_1_OUTPUT_DEC 4
#define DROPOUT_1_OUTPUT_OFFSET 0
#define SOFTMAX_OUTPUT_DEC 7
#define SOFTMAX_OUTPUT_OFFSET 0

/* bias shift and output shift for none-weighted layer */

/* tensors and configurations for each layer */
static int8_t nnom_input_data[450] = {0};

const nnom_shape_data_t tensor_input_1_dim[] = {150, 3};
const nnom_qformat_param_t tensor_input_1_dec[] = {5};
const nnom_qformat_param_t tensor_input_1_offset[] = {0};
const nnom_tensor_t tensor_input_1 = {
    .p_data = (void*)nnom_input_data,
    .dim = (nnom_shape_data_t*)tensor_input_1_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_input_1_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_input_1_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 2,
    .bitwidth = 8
};

const nnom_io_config_t input_1_config = {
    .super = {.name = "input_1"},
    .tensor = (nnom_tensor_t*)&tensor_input_1
};
const int8_t tensor_conv1d_kernel_0_data[] = TENSOR_CONV1D_KERNEL_0;

const nnom_shape_data_t tensor_conv1d_kernel_0_dim[] = {3, 3, 15};
const nnom_qformat_param_t tensor_conv1d_kernel_0_dec[] = TENSOR_CONV1D_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_kernel_0 = {
    .p_data = (void*)tensor_conv1d_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 3,
    .bitwidth = 8
};
const int8_t tensor_conv1d_bias_0_data[] = TENSOR_CONV1D_BIAS_0;

const nnom_shape_data_t tensor_conv1d_bias_0_dim[] = {15};
const nnom_qformat_param_t tensor_conv1d_bias_0_dec[] = TENSOR_CONV1D_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_bias_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_bias_0 = {
    .p_data = (void*)tensor_conv1d_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t conv1d_output_shift[] = CONV1D_OUTPUT_RSHIFT;
const nnom_qformat_param_t conv1d_bias_shift[] = CONV1D_BIAS_LSHIFT;
const nnom_conv2d_config_t conv1d_config = {
    .super = {.name = "conv1d"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_conv1d_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_conv1d_bias_0,
    .output_shift = (nnom_qformat_param_t *)&conv1d_output_shift, 
    .bias_shift = (nnom_qformat_param_t *)&conv1d_bias_shift, 
    .filter_size = 15,
    .kernel_size = {3},
    .stride_size = {3},
    .padding_size = {0, 0},
    .dilation_size = {1},
    .padding_type = PADDING_VALID
};
const int8_t tensor_conv1d_1_kernel_0_data[] = TENSOR_CONV1D_1_KERNEL_0;

const nnom_shape_data_t tensor_conv1d_1_kernel_0_dim[] = {3, 15, 15};
const nnom_qformat_param_t tensor_conv1d_1_kernel_0_dec[] = TENSOR_CONV1D_1_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_1_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_1_kernel_0 = {
    .p_data = (void*)tensor_conv1d_1_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_1_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_1_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_1_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 3,
    .bitwidth = 8
};
const int8_t tensor_conv1d_1_bias_0_data[] = TENSOR_CONV1D_1_BIAS_0;

const nnom_shape_data_t tensor_conv1d_1_bias_0_dim[] = {15};
const nnom_qformat_param_t tensor_conv1d_1_bias_0_dec[] = TENSOR_CONV1D_1_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_conv1d_1_bias_0_offset[] = {0};
const nnom_tensor_t tensor_conv1d_1_bias_0 = {
    .p_data = (void*)tensor_conv1d_1_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_conv1d_1_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_conv1d_1_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_conv1d_1_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t conv1d_1_output_shift[] = CONV1D_1_OUTPUT_RSHIFT;
const nnom_qformat_param_t conv1d_1_bias_shift[] = CONV1D_1_BIAS_LSHIFT;
const nnom_conv2d_config_t conv1d_1_config = {
    .super = {.name = "conv1d_1"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_conv1d_1_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_conv1d_1_bias_0,
    .output_shift = (nnom_qformat_param_t *)&conv1d_1_output_shift, 
    .bias_shift = (nnom_qformat_param_t *)&conv1d_1_bias_shift, 
    .filter_size = 15,
    .kernel_size = {3},
    .stride_size = {3},
    .padding_size = {0, 0},
    .dilation_size = {1},
    .padding_type = PADDING_VALID
};

const nnom_flatten_config_t flatten_config = {
    .super = {.name = "flatten"}
};
const int8_t tensor_dense_kernel_0_data[] = TENSOR_DENSE_KERNEL_0;

const nnom_shape_data_t tensor_dense_kernel_0_dim[] = {240, 6};
const nnom_qformat_param_t tensor_dense_kernel_0_dec[] = TENSOR_DENSE_KERNEL_0_DEC_BITS;
const nnom_qformat_param_t tensor_dense_kernel_0_offset[] = {0};
const nnom_tensor_t tensor_dense_kernel_0 = {
    .p_data = (void*)tensor_dense_kernel_0_data,
    .dim = (nnom_shape_data_t*)tensor_dense_kernel_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_dense_kernel_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_dense_kernel_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 2,
    .bitwidth = 8
};
const int8_t tensor_dense_bias_0_data[] = TENSOR_DENSE_BIAS_0;

const nnom_shape_data_t tensor_dense_bias_0_dim[] = {6};
const nnom_qformat_param_t tensor_dense_bias_0_dec[] = TENSOR_DENSE_BIAS_0_DEC_BITS;
const nnom_qformat_param_t tensor_dense_bias_0_offset[] = {0};
const nnom_tensor_t tensor_dense_bias_0 = {
    .p_data = (void*)tensor_dense_bias_0_data,
    .dim = (nnom_shape_data_t*)tensor_dense_bias_0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_dense_bias_0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_dense_bias_0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_qformat_param_t dense_output_shift[] = DENSE_OUTPUT_RSHIFT;
const nnom_qformat_param_t dense_bias_shift[] = DENSE_BIAS_LSHIFT;
const nnom_dense_config_t dense_config = {
    .super = {.name = "dense"},
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .weight = (nnom_tensor_t*)&tensor_dense_kernel_0,
    .bias = (nnom_tensor_t*)&tensor_dense_bias_0,
    .output_shift = (nnom_qformat_param_t *)&dense_output_shift,
    .bias_shift = (nnom_qformat_param_t *)&dense_bias_shift
};

const nnom_softmax_config_t softmax_config = {
    .super = {.name = "softmax"}
};
static int8_t nnom_output_data[6] = {0};

const nnom_shape_data_t tensor_output0_dim[] = {6};
const nnom_qformat_param_t tensor_output0_dec[] = {SOFTMAX_OUTPUT_DEC};
const nnom_qformat_param_t tensor_output0_offset[] = {0};
const nnom_tensor_t tensor_output0 = {
    .p_data = (void*)nnom_output_data,
    .dim = (nnom_shape_data_t*)tensor_output0_dim,
    .q_dec = (nnom_qformat_param_t*)tensor_output0_dec,
    .q_offset = (nnom_qformat_param_t*)tensor_output0_offset,
    .qtype = NNOM_QTYPE_PER_TENSOR,
    .num_dim = 1,
    .bitwidth = 8
};

const nnom_io_config_t output0_config = {
    .super = {.name = "output0"},
    .tensor = (nnom_tensor_t*)&tensor_output0
};
/* model version */
#define NNOM_MODEL_VERSION (10000*0 + 100*4 + 3)

/* nnom model */
static nnom_model_t* nnom_model_create(void)
{
	static nnom_model_t model;
	nnom_layer_t* layer[9];

	check_model_version(NNOM_MODEL_VERSION);
	new_model(&model);

	layer[0] = input_s(&input_1_config);
	layer[1] = model.hook(conv2d_s(&conv1d_config), layer[0]);
	layer[2] = model.active(act_relu(), layer[1]);
	layer[3] = model.hook(conv2d_s(&conv1d_1_config), layer[2]);
	layer[4] = model.active(act_relu(), layer[3]);
	layer[5] = model.hook(flatten_s(&flatten_config), layer[4]);
	layer[6] = model.hook(dense_s(&dense_config), layer[5]);
	layer[7] = model.hook(softmax_s(&softmax_config), layer[6]);
	layer[8] = model.hook(output_s(&output0_config), layer[7]);
	model_compile(&model, layer[0], layer[8]);
	return &model;
}
