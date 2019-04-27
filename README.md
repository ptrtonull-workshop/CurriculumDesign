# CurriculumDesign

大二下课程设计：无线传输层

### 模块情况

### 概况

| 模块                     | 数量 | 备注     |
| ------------------------ | ---- | -------- |
| 51单片机                 | 2    | 老师提供 |
| 人体红外感应模块HC-SR501 | 1    | 老师提供 |
| Risym火焰传感器          | 1    | 老师提供 |
| 天燃气传感器MQ-4         | 1    | 老师提供 |
| 无线模块esp8266          | 2    | 已购买   |
| 短信GPRS模块SIM900A      | 1    | 老师提供 |
| SIM卡                    | 1    | 待准备   |

### 模块引脚

####  ESP8266

| 引脚  | 描述 |
| ----- | ---- |
| GND   | GND  |
| GPIO2 |1.开机上电时必须为高电平，禁止硬件下拉 |
|		|2.内部默认已拉高|
|GPIO 0|1.默认WiFi Status：WiFi工作状态指示灯控制信号|
|       	  |2.工作模式选择：|
|		|悬空：Flash Boot，工作模式；|
|		|下拉：UART Download，下载模式；|
| URXD  |1.UART_RXD，接收；|
|		|2.General Purpose Input/Output：GPIO3；|
|UTXD	   |1.UART_TXD，发送；|
|          |2.General Purpose Input/Output：GPIO1；|
|			|3.开机时禁止下拉；|
| CH_PD 	|1.高电平工作；|
|			|2.低电平模块供电关掉；|
|RESET（GPIO 16）|外部Reset信号，低电平复位，高电平工作（默认高）；|
|	VCC		|	3.3V，模块供电；|

#### MQ-4

| 引脚 | 描述               |
| ---- | ------------------ |
| +5V  | 连接5v电压进行供电 |
| DOUT | TTL高低电平输出端  |
| AOUT | 模拟电压输出端     |
| GND  | 接地端             |

#### 火焰传感器

| 引脚 | 描述             |
| ---- | ---------------- |
| VCC  | 接电源正极3.3-5V |
| GND  | 接地端           |
| D0   | TTL开关信号输出  |

### SIM900A

| 引脚     | 描述 |
| -------- | ---- |
| 3.3vRXD  |      |
| 3.3v TXD |      |
| 5v RXD   |      |
| 5v TXD   |      |
| GND      |      |
| VCC_mcu  |      |


### 项目分工

#### 第一阶段 

- [x] **郭亚辰**：完成两个51单片机的焊接

- [x] **王听正**：完成SIM芯片的测试，能够在单片机里发送一条短信  

#### 第二阶段

- [x] **郭亚辰**：任意挑选两个传感器进行测试，要达到报警时，51单片机上的灯会亮

- [x] **王听正**：挑选1个传感器，同上

#### 第三阶段

- [x] **郭亚辰**：挑选一个ESP8266进行配置客户端/用户端

- [x] **王听正**：挑选一个ESP8266进行配置客户端/用户端

#### 第四阶段

- [x] 组合起来，测试

### 模块使用

- [SIM900A](https://github.com/ptrtonull-workshop/CurriculumDesign/blob/master/测试资料/sim900a.md)

- [火焰模块](https://github.com/ptrtonull-workshop/CurriculumDesign/blob/master/测试资料/火焰传感器.md)
- MQ-4
- HC-SR501

