import serial  # type: ignore
# 导入 serial 库，用于与串口设备进行通信，忽略类型检查提示

import serial.tools.list_ports  # type: ignore
# 从 serial 库中导入 tools.list_ports 模块，用于列出系统中可用的串口，忽略类型检查提示

import numpy as np  # type: ignore
# 导入 numpy 库，别名为 np，用于进行数值计算和数组操作，忽略类型检查提示

import tensorflow as tf  # type: ignore
# 导入 tensorflow 库，别名为 tf，用于构建和训练深度学习模型，忽略类型检查提示

from tensorflow.keras.models import load_model  # type: ignore
# 从 tensorflow.keras.models 模块中导入 load_model 函数，用于加载预训练的 Keras 模型，忽略类型检查提示

DEF_TITLE_STRING = 'IMU\n'
# 定义数据标题字符串常量，用于检查接收到的数据标题是否正确

DEF_MODEL_NAME = 'model.h5'
# 定义预训练模型的文件名常量

DEF_BAUD_RATE = 921600
# 定义串口通信的波特率常量

DEF_N_ROWS = 60
# 定义一个常量，但在当前代码中未使用

motion_name = ['up', 'down', 'left', 'right', 'front', 'back']
# 定义一个列表，包含运动的名称，用于预测结果的映射

port_list = list(serial.tools.list_ports.comports())
# 获取系统中所有可用的串口，并将其转换为列表

# 显示所有可用串口
# Show all the port avaliable on current device
def show_all_com():
    index = 0
    # 初始化索引变量，用于显示串口的编号
    port_list_name = []
    # 初始化一个空列表，用于存储可用串口的名称
    if len(port_list) <= 0:
        # 如果可用串口列表为空
        print("the serial port can't find!")
        # 打印提示信息，表示未找到可用串口
    else:
        for itms in port_list:
            # 遍历可用串口列表
            index += 1
            # 索引加 1
            print(index, ':', list(itms)[0], list(itms)[1])
            # 打印串口的编号、名称和描述信息
            port_list_name.append(itms.device)
            # 将串口名称添加到 port_list_name 列表中

    return port_list_name
    # 返回可用串口名称的列表

# 请求用户根据索引值选择并初始化一个串口
# Ask a index number for serial port from user and initializes it.
def Serial_init():
    port_avaliable = show_all_com()
    # 调用 show_all_com 函数，获取可用串口名称的列表
    port_avaliable_size = len(port_avaliable)
    # 获取可用串口的数量
    index = int(input("\nChoose a port:"))
    # 提示用户输入要选择的串口编号，并将其转换为整数

    #
    while index > port_avaliable_size or index <= 0:
        # 当用户输入的索引超出可用串口数量范围或小于等于 0 时
        if index > port_avaliable_size or index <= 0:
            # 再次检查输入的索引是否无效
            print("Invalid Input.Check and try again")
            # 打印提示信息，提示用户输入无效
            index = int(input("Choose a port:"))
            # 再次提示用户输入要选择的串口编号

    print(f"\nSerial port", port_avaliable[index - 1], f"initalized successfully.\nBaud rate:{DEF_BAUD_RATE} Byte size:8  Parity:None  Stop bit:1")
    # 打印所选串口初始化成功的信息，包括串口名称、波特率、字节大小、奇偶校验和停止位

    return serial.Serial(port=port_avaliable[index - 1],
                         baudrate=DEF_BAUD_RATE,
                         bytesize=serial.EIGHTBITS,
                         parity=serial.PARITY_NONE,
                         stopbits=serial.STOPBITS_ONE,
                         timeout=0.5)
    # 使用 serial.Serial 函数初始化所选串口，并返回串口对象

# 检查数据串口数据标题是否符合定义的标题，数据的标题可以修改 DEF_TITLE_STRING
# Check if the title from recerived data same as DEF_TITLE_STRING.
def Check_Title(Received_String):
    i = 0
    # 初始化索引变量，用于遍历接收到的字符串
    Title_Buffer = ''
    # 初始化一个空字符串，用于存储数据标题
    while Received_String[i] != '\n':
        # 当遍历到换行符时停止
        Title_Buffer += Received_String[i]
        # 将当前字符添加到标题缓冲区中
        i += 1
        # 索引加 1
    Title_Buffer += '\n'
    # 添加换行符到标题缓冲区末尾
    if (Title_Buffer == DEF_TITLE_STRING):
        # 如果标题缓冲区的内容与定义的标题字符串相同
        return True
        # 返回 True，表示标题匹配
    else:
        return False
        # 返回 False，表示标题不匹配

# 从数据标题之后裁剪出可用的数据
# Cut off the tiltle from recerived data.
def IMU_String(Received_String):
    return Received_String[len(DEF_TITLE_STRING)::1]
    # 从接收到的字符串中截取标题之后的部分并返回

def Str2Array(str):
    # 将字符串分割成行
    lines = str.split('\n')
    # 使用换行符将字符串分割成多行

    # 使用列表推导式将每一行转换为列表，并取第 1 列、第 2 列和第 3 列
    data_list = [list(map(float, [line.split()[0], line.split()[1], line.split()[2]])) for line in lines if line.strip()]
    # 遍历每一行，去除首尾空格后，如果不为空，则将每行的前三个元素转换为浮点数，并存储在列表中

    # 将列表转换为 NumPy 数组
    data_array = np.array(data_list)
    data_array = np.array(data_list).T  # 转置数组
    # 将列表转换为 NumPy 数组，并进行转置操作

    return data_array
    # 返回转换后的 NumPy 数组

# 定义 num_classes
num_classes = len(motion_name)
# 计算运动名称列表的长度，即分类的数量

model = load_model(DEF_MODEL_NAME)
# 加载预训练的 Keras 模型

def predict_motion(inputs_array):
    # 转换为张量并增加批次维度
    inputs_tensor = tf.convert_to_tensor(inputs_array, dtype=tf.float32)
    # 将输入数组转换为 TensorFlow 张量
    inputs_tensor = tf.expand_dims(inputs_array, axis=0)  # 现在形状为 (1, channels, time_steps)
    # 在第 0 维增加一个维度，用于表示批次

    # 现在可以安全地访问 inputs
    outputs = model(inputs_tensor)
    # 使用加载的模型对输入张量进行预测，得到输出结果
    print(outputs)
    # 打印模型的输出结果
    index = 0
    # 初始化索引变量，用于记录最大输出值的索引
    temp = 0
    # 初始化临时变量，用于存储最大输出值
    for i in range(0, 5, 1):
        # 遍历输出结果的前 5 个元素
        if outputs[0][i] > temp:
            # 如果当前元素的值大于临时变量的值
            temp = outputs[0][i]
            # 更新临时变量的值为当前元素的值
            index = i
            # 更新索引变量为当前元素的索引

    print(temp)
    # 打印最大输出值
    if temp >= 0.4:
        # 如果最大输出值大于等于 0.90
        return motion_name[index]
        # 返回对应的运动名称
    else:
        return "Unrecognized"
        # 否则返回 "Unrecognized" 表示未识别

# 主函数
def main():
    serial_using = Serial_init()
    # 调用 Serial_init 函数，初始化所选串口并返回串口对象
    user_input = 'y'
    # 初始化用户输入变量为 'y'
    while user_input == 'y':
        # 当用户输入为 'y' 时，进入循环
        test_count = int(input("How many tests:"))
        # 提示用户输入测试次数，并将其转换为整数
        while test_count >= 0:
            # 当测试次数大于等于 0 时，进入循环
            received = serial_using.readall().decode("ASCII")
            # 从串口读取所有数据，并将其解码为 ASCII 字符串
            if len(received) != 0 and Check_Title(received):
                # 如果接收到的数据长度不为 0 且标题匹配
                test_string = IMU_String(received)
                # 调用 IMU_String 函数，从接收到的数据中截取标题之后的部分
                inputs_array = Str2Array(test_string)
                # 调用 Str2Array 函数，将截取的数据转换为 NumPy 数组
                inputs_array = inputs_array.T
                # 对数组进行转置操作
                print(predict_motion(inputs_array))
                # 调用 predict_motion 函数对输入数组进行预测，并打印预测结果
                test_count -= 1
                # 测试次数减 1
        user_input = input("Again? (y/n)")
        # 提示用户是否再次进行测试，并获取用户输入
    print("Bye!")
    # 打印告别信息

main()
# 调用主函数，启动程序