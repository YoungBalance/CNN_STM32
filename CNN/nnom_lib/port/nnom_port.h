// 防止头文件被重复包含
#ifndef __NNOM_PORT_H__
#define __NNOM_PORT_H__

// 包含标准库头文件，stdlib.h 提供了内存分配等函数，stdio.h 提供了输入输出函数
#include <stdlib.h>
#include <stdio.h>

/* 使用静态内存 */
// 定义该宏以启用在一个大的静态内存块上使用内置的内存分配
// 在创建模型之前，必须使用 "nnom_set_static_buf()" 来设置缓冲区
#define NNOM_USING_STATIC_MEMORY    // enable to use built in memory allocation on a large static memory block
                                     // must set buf using "nnom_set_static_buf()" before creating a model. 

/* 动态内存接口 */
// 当没有使用静态内存时，使用标准库的内存分配和释放函数
// 若没有标准库可用，你需要实现下面的内存接口（等同于标准库函数）
#ifndef NNOM_USING_STATIC_MEMORY    
    #define nnom_malloc(n)      malloc(n)       
    #define nnom_free(p)        free(p)
#endif

/* 内存接口 */
// 当没有标准库可用时，你需要在这里实现等效的函数
// 使用标准库的 memset 函数进行内存设置
#define nnom_memset(p,v,s)        memset(p,v,s)        
// 使用标准库的 memcpy 函数进行内存复制
#define nnom_memcpy(dst,src,len)  memcpy(dst,src,len)  

/* 运行时和调试 */
// 定义一个宏，返回一个微秒级的时间戳，当前返回 0，需要根据实际情况实现
#define nnom_us_get()       0       // return a microsecond timestamp
// 定义一个宏，返回一个毫秒级的时间戳，当前返回 0，需要根据实际情况实现
#define nnom_ms_get()       0       // return a millisecond timestamp
// 定义一个宏，用于日志输出，使用标准库的 printf 函数
#define NNOM_LOG(...)       printf(__VA_ARGS__)

/* NNoM 配置 */
// 定义内存块的最大数量，当有日志请求时可以增大该值
#define NNOM_BLOCK_NUM  	(8)		// maximum number of memory blocks, increase it when log request.   
// 定义是否使用全连接层优化后的权重
#define DENSE_WEIGHT_OPT 	(1)		// if used fully connected layer optimized weights. 

// 注释掉该宏时，后端操作使用四舍五入到最接近的整数（默认）；定义该宏时，使用向下取整
//#define NNOM_TRUNCATE             // disable: backend ops use round to the nearest int (default). enable: floor 

/* 后端格式配置 */
// 取消注释以使用 CHW 格式，否则使用默认的 HWC 格式
// 注意，CHW 格式与 CMSIS-NN 不兼容
// 当使用硬件加速器（如 K210 芯片中的 KPU）时，必须使用 CHW 格式
//#define NNOM_USING_CHW            // uncomment if using CHW format. otherwise using default HWC format.
                                    // Notes, CHW is incompatible with CMSIS-NN. 
                                    // CHW must be used when using hardware accelerator such as KPU in K210 chip

/* 后端选择 */
// 取消注释以使用 CMSIS-NN 进行优化
//#define NNOM_USING_CMSIS_NN       // uncomment if use CMSIS-NN for optimation 

// 结束头文件保护
#endif