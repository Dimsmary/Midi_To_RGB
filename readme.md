# 基本介绍

这是一个Arduino工程，开发基于Leonardo

该工程通过Leonardo的USB外设与PC进行串口通讯，PC运行[*loopMIDI*](https://www.tobias-erichsen.de/software/loopmidi.html) （创建虚拟MIDI端口，与Ableton连接）和*[hairless-midiserial](https://github.com/projectgus/hairless-midiserial)*（串口转MIDI端口与loopMIDI连接）后，Leonardo将可以直接与Ableton进行MIDI通讯。

Leonardo在接收到来自Ableton的MIDI消息后，将按预设值点亮WS2812灯珠。

本开源工程包括了：

1）Arduino源代码

2）灯板PCB工程文件（立创EDA）

3）PCB生产文件



# 代码适配部分

你可以通过修改下述代码适配不同的arduino或是你自己的相关工程。

### #define DATA_PIN

通过修改这个宏可以改变Arduino用于控制WS2812的引脚



### #define XXXX_NOTE

```C++
#define KICK_NOTE 36
#define HIHAT_NOTE 37
#define SNARE_NOTE 38
```

通过修改这些宏定义可以改变Arduino响应的音符。



### CRGB

```
CRGB KICK = CRGB(55,122,55);
CRGB SNARE = CRGB(0,55,122);
CRGB HIHAT = CRGB(122,22,55);
```

通过修改这些变量可以改变不同音符的响应颜色。

# Arduino与Ableton连接过程

![eg1](/readme_picture/eg1.png)

首先使用LoopMIDI创建一个端口，不要关闭此软件。

![eg2](/readme_picture/eg2.png)



启动Hairless MIDI，Serial port选择你的Arduino COM口，MIDI In 选择你刚刚创建的端口。



![eg3](/readme_picture/eg3.png)

此时在你的Abeleton设置中，可以看到刚刚创建的端口，将所有OFF设置为ON。

![eg4](/readme_picture/eg4.png)

选择一个MIDI轨道，输出选择为你创建的MIDI端口。此时，你的Ableton与Arduino已经建立了连接。