# Import the serial library for serial port communication
import serial # type: ignore
# Import the tools.list_ports module in serial library to obtain the list of available serial ports
import serial.tools.list_ports # type: ignore
# Import os libraries to interact with the operating system, such as file and directory operations
import os
# Import the time library to handle time-related operations
import time
# Import the re library for regular expression operations
import re

# Gets the current local time
DEF_TIME_FOR_NOW = time.localtime()
# Converts the month of the current time to a string
DEF_TIME_MONTH = str(DEF_TIME_FOR_NOW.tm_mon)
# Converts the date of the current time to a string
DEF_TIME_DAY = str(DEF_TIME_FOR_NOW.tm_mday)
#DEF_TIME_HOUR = str(DEF_TIME_FOR_NOW.tm_hour)
#DEF_TIME_MINUTE = str(DEF_TIME_FOR_NOW.tm_min)

# Defines a file name separator to concatenate file names
DEF_FILE_NAME_SEPERATOR = '_'
# Define a path to save the data and name the folder with the current date
DEF_SAVE_TO_PATH = './TraningData'+DEF_FILE_NAME_SEPERATOR + DEF_TIME_MONTH + DEF_FILE_NAME_SEPERATOR + DEF_TIME_DAY+'/'
# Define the format to save the file as a text file
DEF_FILE_FORMAT = '.txt'
# Defines a header string for the data that is used to check whether the received data meets requirements
DEF_TITLE_STRING = 'IMU\n'
# Defines the baud rate for serial communication
DEF_BAUD_RATE = 921600

# Defines a list of action names from which users can select actions to record
motion_name = ['up','down','left','right','front','back']
maxmotionlen = 6
# Obtain a list of all available serial ports in the current system
port_list = list(serial.tools.list_ports.comports())

# Show all the port avaliable on current device
def show_all_com():
    # Initialize the index value to 0
    index = 0
    # A list of names used to store available serial ports
    port_list_name = []
    # Check the length of the available serial port list. If it is less than or equal to 0, no available serial port is found
    if len(port_list) <= 0:
        print("the serial port can't find!")
    else:
        # Iterate through the list of available serial ports
        for itms in port_list:
            # Add 1 to the index value
            index += 1
            # Print the index, name, and description of the serial port
            print(index,':',list(itms)[0], list(itms)[1])
            # Add the serial port device name to the list
            port_list_name.append(itms.device)

    return port_list_name

# 请求用户根据索引值选择并初始化一个串口的函数
# Ask a index number for serial port from user and initializes it.
def Serial_init():
    # 调用 show_all_com 函数获取可用串口名称列表
    port_avaliable = show_all_com()
    # 获取可用串口列表的长度
    port_avaliable_size = len(port_avaliable)
    # 提示用户输入要选择的串口索引
    index = int(input("\nChoose a port:"))

    # 检查用户输入的索引是否超出可用串口列表的范围
    while index > port_avaliable_size or index <= 0:
        if  index > port_avaliable_size or index <= 0:
            print("Invalid Input.Check and try again")
            # 若输入无效，再次提示用户输入
            index = int(input("Choose a port:"))
      
    # 打印初始化成功的串口信息
    print(f"\nSerial port",port_avaliable[index - 1],f"initalized successfully.\nBaud rate:{DEF_BAUD_RATE} Byte size:8  Parity:None  Stop bit:1")
    # 初始化并返回一个串口对象
    return serial.Serial(port=port_avaliable[index - 1],
                                baudrate=DEF_BAUD_RATE,
                                bytesize=serial.EIGHTBITS,
                                parity=serial.PARITY_NONE,
                                stopbits=serial.STOPBITS_ONE,
                                timeout=0.5) 

# 检查数据串口数据标题是否符合定义的标题的函数
# Check if the title from recerived data same as DEF_TITLE_STRING.
def Check_Title(Received_String):
    # 初始化索引值为 0
    i = 0
    # 用于存储接收到的数据的标题
    Title_Buffer = ''
    # 从接收到的数据中提取标题，直到遇到换行符
    while Received_String[i] != '\n':
        Title_Buffer += Received_String[i]
        i += 1
    # 在标题末尾添加换行符
    Title_Buffer+='\n'
    # 检查提取的标题是否与定义的标题字符串相同
    if(Title_Buffer == DEF_TITLE_STRING):
        return True
    else:
        return False

# 从数据标题之后裁剪出可用的数据的函数
# Cut off the tiltle from recerived data.
def IMU_String(Received_String):
        # 从定义的标题字符串长度位置开始截取数据
        return Received_String[len(DEF_TITLE_STRING)::1]

# 指定需要录制的动作名的函数
# Assign a motion you wannna to record
def Motion_Assign():
    # 初始化索引值为 0
    i = 0
    # 初始化用户输入为 0
    user_input = 0
    # 提示用户从列表中选择一个动作
    print('\nChoose one from the fllowing name')
    # 遍历动作名称列表并打印索引和动作名称
    for i in range(0,maxmotionlen,1):
        print(i+1,motion_name[i])
    # 检查用户输入的索引是否在有效范围内
    while user_input > maxmotionlen or user_input < 1:
        # 提示用户输入要录制的动作索引
        user_input = int(input("Assign a motion you want to decord (1-13)"))
        if user_input > maxmotionlen or user_input < 1:
            print("Invalid Input.Check and try again")
        else:
                # 返回用户选择的动作索引减 1
                return user_input - 1

# 寻找特定动作相关的文件中最大的数字的函数
# :param motion: 动作名称，应为'motion_name'列表中的一个元素。
# :param folder_path: 包含文件的目录路径。
# :return: 匹配文件中找到的最大数字，如果没有匹配的文件，则返回 0。
def find_max_number_in_filenames(motion, folder_path):
    # 初始化最大数字为 0
    max_number = 0
    # 编译一个正则表达式，用于匹配文件名中的数字
    number_pattern = re.compile(r'\d+')
    # 用于存储匹配的文件名列表
    matching_filenames = []

    # 遍历指定文件夹中的所有文件
    for filename in os.listdir(folder_path):
        # 检查文件名是否包含特定的动作名称
        if motion in filename:
            # 将匹配的文件名添加到列表中
            matching_filenames.append(filename)

    # 在匹配的文件名中查找最大的数字
    for filename in matching_filenames:
        # 查找文件名中的所有数字
        numbers = number_pattern.findall(filename)
        # 更新最大数字
        for num_str in numbers:
            num = int(num_str)
            if num > max_number:
                max_number = num

    return max_number

# 主函数，程序的入口点
def main():
    # 调用 Serial_init 函数初始化串口
    serial_using = Serial_init()
    # 初始化用户输入为 'y'，表示继续录制
    user_input = 'y'
    # 检查保存数据的文件夹是否存在，如果不存在则创建
    if not os.path.exists(DEF_SAVE_TO_PATH):
        os.mkdir(DEF_SAVE_TO_PATH)
    # 当用户输入为 'y' 时，继续录制动作数据
    while user_input == 'y':
        # 调用 Motion_Assign 函数获取用户选择的动作名称
        motion_assigned = motion_name[Motion_Assign()]
        # 打印用户选择的动作名称
        print(motion_assigned)
        # 初始化已录制的数据组数为 0
        recorded_count = 0
        # 调用 find_max_number_in_filenames 函数获取特定动作相关文件中最大的数字，并加 1
        name_index = find_max_number_in_filenames(motion_assigned,DEF_SAVE_TO_PATH) + 1
        # 提示用户输入要录制的数据组数
        data_set_max = int(input("How many data set you want to record:"))
        # 当已录制的数据组数小于用户指定的最大组数时，继续录制
        while recorded_count < data_set_max:
            # 从串口读取所有数据并解码为 ASCII 字符串
            received = serial_using.readall().decode("ASCII")
            # 检查接收到的数据长度是否不为 0
            if len(received) != 0:
                # 调用 Check_Title 函数检查接收到的数据标题是否符合要求
                if Check_Title(received):
                    # 拼接保存数据的文件名
                    filename = DEF_SAVE_TO_PATH+motion_assigned+DEF_FILE_NAME_SEPERATOR+str(name_index)+DEF_FILE_FORMAT
                    # 以写入模式打开文件
                    with open(filename,"w") as file:
                        # 调用 IMU_String 函数裁剪出可用的数据并写入文件
                        file.write(IMU_String(received))
                        # 文件会在 with 语句块结束时自动关闭，这里的 file.close() 是多余的
                        file.close()
                    # 打印保存的文件名
                    print("Saved as",filename)
                    # 已录制的数据组数加 1
                    recorded_count += 1
                    # 文件名索引加 1
                    name_index += 1
                else:
                    # 若数据标题不符合要求，打印接收到的数据
                    print(received)
        # 打印录制完成信息
        print("Complete")
        # 提示用户是否继续录制另一个动作
        user_input = input("Record another motion (y/n)")
    # 打印结束信息
    print("Bye!")

# 调用主函数开始执行程序
main()