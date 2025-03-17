#include "CyberryPotter.h"
#include "weights.h"
#include "nnom.h"
extern Cyberry_Potter_Status_Typedef Cyberry_Potter_Status;
//extern uint16_t IMU_Data_ACC[3*IMU_SEQUENCE_LENGTH_MAX];
//extern float IMU_Data_ACC[3*IMU_SEQUENCE_LENGTH_MAX];
extern float IMU_Data_mGyro[IMU_SEQUENCE_LENGTH_MAX][3];
extern float IMU_Data_mAcc[IMU_SEQUENCE_LENGTH_MAX][3];
int8_t model_output = -1;
#define SCALE (pow(2,INPUT_1_OUTPUT_DEC))

typedef enum eModel_Output{
	Unrecognized = -1,
	up = 0,
	down = 1,
	left = 2,
	right = 3,
	front = 4,
	back = 5
}eModel_Output;

#ifdef NNOM_USING_STATIC_MEMORY
	uint8_t static_buf[1024 * 8];
#endif //NNOM_USING_STATIC_MEMORY

/*
  This code defines a function called model_feed_data, 
  whose main function is to scale and round the gyroscope data in the IMU_Data_mGyro array,
  and then store the processed data in the nnom_input_data array. 
  For subsequent input data to the model. 
*/
void model_feed_data(void)
{
    // Define a constant scale whose value is taken from the macro SCALE
    const double scale = SCALE;
    // Defines an unsigned 16-bit integer i for cycle counting
    uint16_t i = 0;
    // Loop through the IMU_Data_mGyro array with the number of loops being IMU_SEQUENCE_LENGTH_MAX
    for(i = 0; i < IMU_SEQUENCE_LENGTH_MAX;i++){
        // Scale the 0th element of the I-th data in the IMU_Data_mGyro array (gyroscope X-axis data)
        // The round function is used after scaling and the result is cast to int8_t type
        // Stored at position i*3 of the nnom_input_data array
        nnom_input_data[i*3] = (int8_t)round(IMU_Data_mGyro[i][0] * scale);
        nnom_input_data[i*3+1] = (int8_t)round(IMU_Data_mGyro[i][1] * scale);
        nnom_input_data[i*3+2] = (int8_t)round(IMU_Data_mGyro[i][2] * scale);
    }
}

int8_t model_get_output(void)
{
	uint8_t i = 0;
	int8_t max_output = -128;
	int8_t ret = 0;
	//Iterate through 13 classification results to find the maximum accuracy
	for(i = 0; i < 6;i++){
		printf("Output[%d] = %.2f %%\r\n",i,(nnom_output_data[i] / 127.0)*100);
		if(nnom_output_data[i] >= max_output){
			max_output = nnom_output_data[i] ;
			ret = i;
		}
	}
	if(max_output >= OUPUT_THRESHOLD){		//The accuracy threshold is set

		ret = ret;
	}
	else{
		ret = -1;
	}
	
	switch(ret){
		case Unrecognized:
			printf("Unrecognized");
			break;
		case up:
			printf("up");
			break;
		case down:
			printf("down");
			break;
		case left:
			printf("left");
			break;
		case right:
			printf("right");
			break;
		case front:
			printf("front");
			break;
		case back:
			printf("back");
			break;
	}
	printf("\n");
	return ret;
}

int main(void)
{       
    // Call System_Init function for system initialization
    System_Init();
    
    printf("Hello!\n");

    // If the NNOM_USING_STATIC_MEMORY macro is defined, static memory is used
    #ifdef NNOM_USING_STATIC_MEMORY
        // Call the nnom_set_static_buf function to static_buf as a static memory buffer, specifying its size
        nnom_set_static_buf(static_buf, sizeof(static_buf)); 
    #endif //NNOM_USING_STATIC_MEMORY

    // Define a pointer model to type nnom_model_t
    nnom_model_t* model;
    // Call the nnom_model_create function to create a new model and assign the returned pointer to the model
    model = nnom_model_create();
    
    while(1)
    {
        if(Cyberry_Potter_Status.Button_Status == BUTTON_HOLD && Cyberry_Potter_Status.IMU_Status == IMU_Idle)
        {
            IMU_Sample_Start();	
        }
        else if(Cyberry_Potter_Status.Button_Status != BUTTON_IDLE)
        {
            Cyberry_Potter_Status.Button_Status = BUTTON_IDLE;
        }

        if(Cyberry_Potter_Status.IMU_Status == IMU_Sampled)
        {
            LED_OFF;

            // If the SYSTEM_MODE_DATA_COLLECT macro is defined, the data collection mode is entered
            #ifdef SYSTEM_MODE_DATA_COLLECT
                Delay_ms(200);
                IMU_Data_Print();
            #endif //SYSTEM_MODE_DATA_COLLECT
            
            // If the SYSTEM_MODE_DATA_COLLECT macro is not defined, enter the model run mode
            #ifndef SYSTEM_MODE_DATA_COLLECT
                //The gyroscope data is processed and saved to the model input array
                model_feed_data();  
                model_run(model);
                // Model output
                model_output = model_get_output();	
                printf("%d",model_output);
            #endif //SYSTEM_MODE_DATA_COLLECT

            Cyberry_Potter_Status.IMU_Status = IMU_Idle;
            EXTI_Restore();
        }
    } 
}
