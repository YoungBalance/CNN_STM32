import os
# 导入os模块，用于与操作系统进行交互，例如文件和目录操作。
import numpy as np # type: ignore
# 导入numpy库，用于处理数值计算和数组操作，# type: ignore用于忽略类型检查警告。
import tensorflow as tf # type: ignore
# 导入tensorflow库，一个强大的深度学习框架，同样忽略类型检查警告。
from tensorflow.keras.models import load_model, save_model # type: ignore
# 从tensorflow.keras.models模块中导入load_model和save_model函数，分别用于加载和保存模型。
from tensorflow.keras.preprocessing.sequence import pad_sequences # type: ignore
# 从tensorflow.keras.preprocessing.sequence模块中导入pad_sequences函数，用于对序列进行填充以达到统一长度。
from tensorflow.keras import * # type: ignore
# 导入tensorflow.keras的所有内容，方便后续使用keras的各种功能。
from tensorflow.keras.layers import * # type: ignore
# 导入tensorflow.keras.layers的所有内容，用于构建神经网络的各种层。
from nnom import * # type: ignore
# 导入nnom模块的所有内容，推测nnom模块用于模型的生成等操作。
import re
# 导入re模块，用于正则表达式操作，方便对文件名进行匹配和解析。

# 动作分类名
motion_names = ['0','1','2','3','4','5','6','7','8','9','a','b','c']
# 定义一个列表，包含所有可能的动作分类名称。

# 定义目录路径
DEF_SAVE_TO_PATH = './TraningData_3_11/'
# 定义训练数据所在的目录路径。
DEF_MODEL_NAME = 'model.h5'
# 定义保存模型的文件名，使用.h5格式，这是Keras模型常用的保存格式。
DEF_MODEL_H_NAME = 'weights.h'
# 定义保存模型权重的头文件名称。
DEF_FILE_MAX = 100
# 定义文件名中数字的最大范围，用于筛选符合要求的文件。
#DEF_N_ROWS = 60
DEF_N_ROWS = 150
# 定义读取文件时的最大行数。

# 文件格式
DEF_FILE_FORMAT = '.txt'
# 定义训练数据文件的格式为.txt。
# 文件名分隔符
DEF_FILE_NAME_SEPERATOR = '_'
# 定义文件名中用于分隔不同部分的分隔符。
DEF_BATCH_SIZE = 10
# 定义训练模型时的批次大小。
DEF_NUM_EPOCH = 300
# 定义训练模型的迭代次数。

# 动作名称到标签的映射
motion_to_label = {name: idx for idx, name in enumerate(motion_names)}
# 使用字典推导式创建一个字典，将动作名称映射到对应的整数标签。

def train(x_train, y_train, x_test, y_test, input_shape=(DEF_N_ROWS, 3), num_classes=len(motion_names), batch_size=DEF_BATCH_SIZE, epochs=DEF_NUM_EPOCH):
    # 定义一个名为train的函数，用于训练模型，接收训练数据、测试数据、输入形状、类别数量、批次大小和迭代次数作为参数。
    inputs = layers.Input(shape=input_shape) # type: ignore
    # 定义模型的输入层，指定输入形状。
    # 卷积层
    x = layers.Conv1D(30, kernel_size=3, strides=3)(inputs) # type: ignore
    # 添加一个一维卷积层，包含30个滤波器，卷积核大小为3，步长为3。
    x = layers.ReLU()(x) # type: ignore
    # 添加ReLU激活函数层，对卷积层的输出进行非线性变换。
    x = layers.Conv1D(30, kernel_size=3, strides=3)(x) # type: ignore
    # 再添加一个一维卷积层，包含15个滤波器，卷积核大小为3，步长为3。
    x = layers.ReLU()(x)# type: ignore
    # 再次添加ReLU激活函数层。

   # x = layers.MaxPooling1D(pool_size=2, strides=1)(x)# type: ignore
    # 添加一个一维最大池化层，池化窗口大小为3，步长为3。
    # 展平层
    x = layers.Flatten()(x)# type: ignore
    # 添加一个展平层，将多维的输入数据展平为一维向量。
   # x = layers.Dropout(0.5)(x)# type: ignore
    # 注释掉的代码，原本用于添加Dropout层，防止过拟合。
    # 全连接层1
    x = layers.Dense(num_classes)(x)# type: ignore
    # 添加一个全连接层，神经元数量等于类别数量。
    x = layers.Dropout(0.5)(x)# type: ignore
    # 添加Dropout层，以0.5的概率随机丢弃神经元，防止过拟合。
    outputs = layers.Softmax()(x)# type: ignore
    # 添加Softmax激活函数层，将输出转换为概率分布。
    
    model = models.Model(inputs=inputs, outputs=outputs)# type: ignore
    # 使用Model类构建模型，指定输入和输出层。
    
    # 编译模型
    model.compile(optimizer=optimizers.Adam(), # type: ignore
                  loss=losses.CategoricalCrossentropy(), # type: ignore
                  metrics=['accuracy'])# type: ignore
    # 编译模型，指定优化器为Adam，损失函数为分类交叉熵，评估指标为准确率。
    
    model.summary()
    # 打印模型的结构信息。
    
    # Callbacks
    early_stopping = callbacks.EarlyStopping(monitor='val_loss', patience=10)# type: ignore
    # 定义一个早停回调函数，当验证集损失在10个epoch内没有改善时停止训练。
    checkpoint = callbacks.ModelCheckpoint(DEF_MODEL_NAME, monitor='val_accuracy', save_best_only=True, mode='max')# type: ignore
    # 定义一个模型检查点回调函数，根据验证集准确率保存最佳模型。
    
    # 训练模型
    history = model.fit(
        x_train,
        y_train,
        batch_size=batch_size,
        epochs=epochs,
        verbose=2,
        validation_data=(x_test, y_test),
        shuffle=True,
        callbacks=[early_stopping, checkpoint]
    )
    # 使用fit方法训练模型，指定训练数据、批次大小、迭代次数、验证数据等参数，并使用回调函数。
    
    # 清除会话
    del model
    # 删除模型对象，释放内存。
    tf.keras.backend.clear_session()
    # 清除TensorFlow的会话，释放资源。
    
    return history
    # 返回训练历史记录。

# 加载数据集
def load_dataset(root_dir, max_rows=None):
    # 定义一个名为load_dataset的函数，用于加载数据集，接收根目录和最大行数作为参数。
    file_list = []
    # 初始化一个空列表，用于存储加载的数据。
    labels = []
    # 初始化一个空列表，用于存储对应的标签。
    for filename in os.listdir(root_dir):
        # 遍历根目录下的所有文件。
        if filename.endswith(DEF_FILE_FORMAT):
            # 检查文件是否以指定的文件格式结尾。
            match = re.match(rf'^([\w]+)_([\d]+){DEF_FILE_FORMAT}$', filename)
            # 使用正则表达式匹配文件名，提取动作名称和数字。
            if match:
                # 如果匹配成功。
                motion_name = match.group(1)
                # 获取动作名称。
                number_str = match.group(2)
                # 获取文件名中的数字字符串。
                number = int(number_str)
                # 将数字字符串转换为整数。
                if 0 <= number <= DEF_FILE_MAX:
                    # 检查数字是否在指定范围内。
                    if motion_name in motion_to_label:
                        # 检查动作名称是否在映射字典中。
                        file_path = os.path.join(root_dir, filename)
                        # 构建文件的完整路径。
                        # 使用max_rows参数限制读取的行数
                        data = np.loadtxt(file_path, delimiter=' ', usecols=(0, 1, 2), max_rows=max_rows)
                        # 使用numpy的loadtxt函数加载文件数据，指定分隔符、使用的列和最大行数。
                        file_list.append(data)
                        # 将加载的数据添加到文件列表中。
                        labels.append(motion_to_label[motion_name])
                        # 将对应的标签添加到标签列表中。
                    else:
                        print(f"Motion name not recognized: {filename}")
                        # 如果动作名称未被识别，打印警告信息。
                else:
                    print(f"Number out of range: {filename}")
                    # 如果数字超出范围，打印警告信息。
            else:
                print(f"Invalid file name format: {filename}")
                # 如果文件名格式无效，打印警告信息。
    return file_list, labels
    # 返回加载的数据列表和标签列表。

file_list, labels = load_dataset(DEF_SAVE_TO_PATH, max_rows=DEF_N_ROWS)
# 调用load_dataset函数加载数据集，指定根目录和最大行数。

# 数据预处理，例如填充序列以达到统一长度
max_len = max([len(x) for x in file_list])  # 找到最长序列的长度
# 计算文件列表中所有序列的最大长度。
print(f"Max length of sequences: {max_len}")  # 打印max_len的值
# 打印最大序列长度。
file_list_padded = pad_sequences(file_list, maxlen=max_len, dtype='float32', padding='post', value=0)
# 使用pad_sequences函数对序列进行填充，使其长度达到最大长度。
    
# 转换标签为one-hot编码
labels_one_hot = utils.to_categorical(labels, num_classes=len(motion_names)) # type: ignore
# 使用to_categorical函数将标签转换为one-hot编码。

# 计算分割点前，先确保数据集被完全构建
num_elements = len(file_list_padded)
# 计算填充后数据的元素数量。

train_size = int(num_elements * 0.8)
# 计算训练集的大小，占总数据的80%。

# 先shuffle再分割
indices = np.arange(num_elements)
# 生成一个从0到num_elements-1的整数数组。
np.random.shuffle(indices)
# 随机打乱数组的顺序。

# 分割数据集
train_indices = indices[:train_size]
# 提取前train_size个索引作为训练集的索引。
test_indices = indices[train_size:]
# 提取剩余的索引作为测试集的索引。

# 获取训练和测试数据
x_train = file_list_padded[train_indices]
# 根据训练集的索引获取训练数据。
y_train = labels_one_hot[train_indices]
# 根据训练集的索引获取训练标签。
x_test = file_list_padded[test_indices]
# 根据测试集的索引获取测试数据。
y_test = labels_one_hot[test_indices]
# 根据测试集的索引获取测试标签。

# 训练模型
history = train(x_train, y_train, x_test, y_test, batch_size=DEF_BATCH_SIZE, epochs=DEF_NUM_EPOCH)
# 调用train函数训练模型，指定训练数据、测试数据、批次大小和迭代次数。

# 加载模型
model = load_model(DEF_MODEL_NAME)
# 使用load_model函数加载之前保存的最佳模型。

model.compile(optimizer=optimizers.Adam(),              # type: ignore
              loss=losses.CategoricalCrossentropy(), # type: ignore
              metrics=['accuracy'])                 # type: ignore
# 重新编译加载的模型，指定优化器、损失函数和评估指标。

model.summary()
# 打印加载模型的结构信息。

# 从训练数据集中获取一个批次作为校准数据集
# 这里直接使用x_test
x_test_sample = x_test[:100]  # 使用前100个样本作为校准数据集
# 从测试数据中选取前100个样本作为校准数据集。

# 假设generate_model函数已经定义在nnom模块中
generate_model(model, x_test_sample, format='hwc', name=DEF_MODEL_H_NAME)
# 调用nnom模块中的generate_model函数，根据模型和校准数据集生成头文件。